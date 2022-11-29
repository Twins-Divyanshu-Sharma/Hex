#include "Engine.h"

Engine::Engine() : window()
{
    loop();
}

Engine::~Engine()
{

}

void Engine::loop()
{
    clock_t prev = clock();
    double elapsed =0, lag=0;
    clock_t curr = clock();
    init();


    while(!window.isClosed())
    {
        elapsed = ((double)curr - (double)prev) * 1000 / CLOCKS_PER_SEC;
        lag += elapsed;
        prev = clock();

        input();
        while(lag >= millisecPerUpdate)
        {
            update();
            lag -= millisecPerUpdate;
        }
        render(lag/millisecPerUpdate);
        curr = clock();
    }
    clean();
    std::cout << "Exited" << std::endl;
}

void Engine::init()
{
    glClearColor(0,0,0,0);
    hexagons.insert(0,0, 0,0,1.0f, 0.5f);
}

void Engine::input()
{
    window.pollEvents();
}

void Engine::update()
{

}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT);
    hexagonRenderer.render(hexagons);
    window.swapBuffers();
}

void Engine::clean()
{
    
}
