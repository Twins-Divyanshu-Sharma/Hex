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
#include "FBO.h"
#include "ScreenQuadRenderer.h"
#include "BloomRenderer.h"
#include "Color.h"
#include "Config.h"

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

        float ortho[16] = {0};
        
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
        bool iPressed=false;

        std::string typedString;
        bool escapePressed=false, backspacePressed=false;
        bool searchStringChanged=false;
        std::vector<std::string> pathList;

        void updateHexagonStrings();
    
        Mesh screenQuad;
        FBO worldFBO, ping, pong;
        ScreenQuadRenderer screenQuadRenderer;
        BloomRenderer bloomRenderer;
        
        Color insertColor = {0.06f, 0.03f, 0.01f};
        Color visualColor = {0.05f, 0.20f, 0.04f};
        Color disabledColor = {0.01f,0.01f,0.01f};
        
        Color textColor = {0.06f, 0.83f, 0.79f};
        Color selectedTextColor = {0,0,0};


        bool tabPressed = false;
        bool ignore = false;

        void goLeft();
        void goRight();
        void goUp();
        void goDown();

        void visualInputHJKL();
        void visualInputArrows();

        bool leftPressed=false,rightPressed=false,upPressed=false,downPressed=false;
        
};

#endif
