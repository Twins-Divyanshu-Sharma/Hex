#ifndef ENGINE_H
#define ENGINE_H

#include <unistd.h>
#include "Win.h"
#include <time.h>
#include "HexagonRenderer.h"
#include "Hexagons.h"
#include "FontRenderer.h"
#include "FontAtlas.h"
#include <cstdlib>
#include <algorithm>

#define INSERT 0
#define VISUAL 1

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
        FontAtlas fontAtlas;
        FontRenderer fontRenderer;
        
        int mode = INSERT;

        void insertModeInput();
        void visualModeInput();

        bool keyActive = false;
        int selectedHexagonIndex = 1;
        bool modeChange = false;

        int selectedHexagon = 2;
        int side = 0; // 0 top, 1 bot
                      //

        bool hPressed=false,jPressed=false,kPressed=false,lPressed=false;
        bool enterPressed=false;

        std::string typedString;
        bool escapePressed=false, backspacePressed=false;
        bool searchStringChanged=false;
        std::vector<std::string> pathList;

        void updateHexagonStrings();
};

#endif
