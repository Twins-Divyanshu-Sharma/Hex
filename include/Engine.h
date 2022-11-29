#ifndef ENGINE_H
#define ENGINE_H

#include "Win.h"
#include <time.h>
#include "HexagonRenderer.h"
#include "Hexagons.h"

class Engine
{
    public:
        Engine();
        ~Engine(); 
    private:
        Win window;
        double fps = 120.0f;
        double millisecPerUpdate = 1000.0f/fps;
        
        void init();
        void clean();
        void update();
        void input();
        void render(double);
        void loop();

        HexagonRenderer hexagonRenderer;
        Hexagons hexagons;
        
};

#endif
