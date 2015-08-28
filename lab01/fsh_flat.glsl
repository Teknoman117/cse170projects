# version 330 core
#define M_PI 3.1415926535897932384626433832795
#define M_1_R2 0.70710678118

uniform float vTime;

in vec4 Color;
out vec4 fColor;

void main() 
{ 
    float r = atan(Color.y * M_1_R2, Color.x * M_1_R2) + M_PI + (2 * length(Color.xy));
    float p = 12*r + vTime;

    fColor = vec4((vec3(sin(p), sin(p + 2), sin(p + 4)) / 2) + 0.5, 1.0);
} 
