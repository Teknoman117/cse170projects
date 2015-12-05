#include <chrono>

#include <project2/common.hpp>
#include <project2/application.hpp>

int main(int argc, char *argv[])
{
    // Setup clock to track shit
    std::chrono::high_resolution_clock             applicationClock;
    std::chrono::high_resolution_clock::time_point applicationStart = applicationClock.now();
    
    // Setup SDL
    SDL_Window *mainwindow;
    SDL_GLContext maincontext;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "[FATAL] SDL: Unable to initialize" << std::endl;
        return 1;
    }
    
    // Setup OpenGL context settings
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // Setup window manager frame buffer settings
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    //we use deferred rendering, no depth test in final buffer
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    
    // Setup OpenGL Accelerated Window
    mainwindow = SDL_CreateWindow("ENGR 180 Final Project - Terrain Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!mainwindow)
    {
        std::cerr << "[FATAL] SDL: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    maincontext = SDL_GL_CreateContext(mainwindow);
    
    // Setup GLEW
    glewExperimental = GL_TRUE;
    GLenum rev = glewInit();
    if (GLEW_OK != rev)
    {
        std::cerr << "[FATAL] " << glewGetErrorString(rev) << std::endl;
        return 1;
    }
    
    // Enable vsync
    SDL_GL_SetSwapInterval(1);
    
    Application *app = new Application(mainwindow, maincontext);
    
    // Record simulation starting times, report start time
    std::chrono::high_resolution_clock::time_point simulationStart = applicationClock.now();
    std::chrono::high_resolution_clock::time_point simulationPrevious = applicationStart;
    bool                                           running = true;
    
    std::chrono::duration<float> duration = simulationStart - applicationStart;
    std::cout << "[INFO] Application up:  " << duration.count() << "s" << std::endl;
    
    // Simulatio
    while(running)
    {
        // Compute frame times
        std::chrono::high_resolution_clock::time_point simulationCurrent = applicationClock.now();
        std::chrono::duration<float>                   simulationTime    = simulationCurrent - simulationStart;
        std::chrono::duration<float>                   simulationDelta   = simulationCurrent - simulationPrevious;
        
        // Process queued events
        SDL_Event event;
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                running = false;
            }
            
            else if(event.type == SDL_WINDOWEVENT)
            {
                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    int w,h;
                    SDL_GetWindowSize(mainwindow,&w,&h);
                    app->OnResize(w, h);
                }
            }
            
            else
            {
                app->OnEvent(event);
            }
        }
        
        // Render the simulation
        app->OnDisplay(simulationTime.count(), simulationDelta.count());
        simulationPrevious = simulationCurrent;
        SDL_GL_SwapWindow(mainwindow);
    }
    
    
    // Delete our opengl context, destroy our window, and shutdown SDL
    std::cout << "[INFO] Application terminating" << std::endl;
    
    delete app;
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    
    return 0;
}