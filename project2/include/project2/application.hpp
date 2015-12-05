#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <map>

#include <project2/common.hpp>
#include <project2/program.hpp>

class Application
{
    SDL_Window     *window;
    SDL_GLContext&  context;
    
    GLint           width;
    GLint           height;
    float           aspect;
    
    std::map<std::string, std::shared_ptr<Program>> programs;
    
public:
    Application(SDL_Window *window, SDL_GLContext& context);
    ~Application();
    
    void OnDisplay(float frameTime, float frameDelta);
    void OnResize(GLint width, GLint height);
    void OnEvent(SDL_Event event);
};

#endif