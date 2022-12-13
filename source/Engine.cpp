#include "Engine.h"

Engine::Engine() : window()
{
    std::string path = std::getenv("PATH");
    
    
    int start=0; 
    for(int end=0; end<path.size(); end++)
    {
      if(path[end] == ':')
      {
        std::string t = path.substr(start,end-start);
        pathList.push_back(t);
        start = end+1;
      }
      else if(end == path.size() -1)
      {
          std::string t = path.substr(start,end-start+1);
          pathList.push_back(t);
      }
    }

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
    hexagons.insert(0,0, 0,0.83f,0.79f, 0.35f);
    hexagons.insert(-0.55f,0.35f, 0.39f,0.33f,0.21f, 0.35f); // 1
    hexagons.insert(0,0.7f, 0.39f,0.33f,0.21f, 0.35f); // 2
    hexagons.insert(0.55f,0.35f, 0.39f,0.33f,0.21f, 0.35f); // 3
    hexagons.insert(-0.55f,-0.35f, 0.39f,0.33f,0.21f, 0.35f); // 4
    hexagons.insert(0,-0.7f, 0.39f,0.33f,0.21f, 0.35f); // 5
    hexagons.insert(0.55f,-0.35f, 0.39f,0.33f,0.21f, 0.35f); // 6
    // 1 2 3
    // 4 5 6
    fontAtlas.setAtlas("hexFontAtlas");
}

void Engine::input()
{

    if(mode == INSERT)
    {
        insertModeInput();
    }
    else if(mode == VISUAL)
    {
        visualModeInput();
    }
    window.pollEvents();
}

void Engine::insertModeInput()
{
    if(window.keyPressed(GLFW_KEY_ESCAPE) && !escapePressed)
    {
        escapePressed = true;
        mode = VISUAL;
        modeChange = true;
    }
    if(window.keyReleased(GLFW_KEY_ESCAPE) && escapePressed)
        escapePressed = false;
    
    if(window.keyPressed(GLFW_KEY_BACKSPACE) && !backspacePressed) 
    {
        backspacePressed = true;
        if(typedString.length() > 0)
            typedString = typedString.substr(0,typedString.length()-1);
        hexagons.str[0] = typedString;
        searchStringChanged = true;
    }
    if(window.keyReleased(GLFW_KEY_BACKSPACE) && backspacePressed)
        backspacePressed = false;

    
    if(Win::charInputEvent)
    {
        Win::charInputEvent = false;
        typedString += Win::currentChar;
        hexagons.str[0] = typedString;
        searchStringChanged = true;
    }

}

void Engine::visualModeInput()
{
    if(window.keyPressed(GLFW_KEY_Q) && !keyActive)
    {
        keyActive = true;
        window.close();
    }
    if(window.keyPressed(GLFW_KEY_I) && !keyActive)
    {
        keyActive = true;
        mode = INSERT;
        modeChange = true;
    }
    if(window.keyReleased(GLFW_KEY_I) && keyActive)
        keyActive = false;

    if(window.keyPressed(GLFW_KEY_H) && !hPressed)
    {
        hPressed = true;
        if(side == 0 && selectedHexagon > 1)
            selectedHexagon--;
        if(side == 1 && selectedHexagon > 4)
            selectedHexagon--;
    }
    if(window.keyReleased(GLFW_KEY_H) && hPressed)
        hPressed = false;

    if(window.keyPressed(GLFW_KEY_L) && !lPressed)
    {
        lPressed = true;
        if(side == 0 && selectedHexagon < 3)
            selectedHexagon++;
        if(side == 1 && selectedHexagon < 6)
            selectedHexagon++;
    }
    if(window.keyReleased(GLFW_KEY_L) && lPressed)
        lPressed = false;

    if(window.keyPressed(GLFW_KEY_J) && !jPressed)
    {
        jPressed = true;
        side = (side + 1)%2;
        int idx = selectedHexagon - 1;
        idx = (idx + 3)%6;
        selectedHexagon = idx+1;
    }
    if(window.keyReleased(GLFW_KEY_J) && jPressed)
        jPressed = false;

    if(window.keyPressed(GLFW_KEY_K) && !kPressed)
    {
        kPressed = true;
        side = (side + 1)%2;
        int idx = selectedHexagon - 1;
        idx = (idx + 3)%6;
        selectedHexagon = idx+1;
    }
    if(window.keyReleased(GLFW_KEY_K) && kPressed)
        kPressed = false;

    if(window.keyPressed(GLFW_KEY_ENTER) && !enterPressed)
    {
        enterPressed = true;
        std::string command = std::string(hexagons.str[selectedHexagon] + " &");
        system(command.c_str());
        window.close();
    }
}

void Engine::update()
{
   if(modeChange)
   {
       modeChange = false;
       if(mode == INSERT)
       {
           hexagons.r[0] = 0.06f;
           hexagons.g[0] = 0.83f;
           hexagons.b[0] = 0.79f;
           for(int i=1; i<7; i++)
           {
                hexagons.r[i] = 0.39f;
                hexagons.g[i] = 0.33f;
                hexagons.b[i] = 0.21f;
           }
       }
       else if(mode == VISUAL)
       {
           hexagons.r[0] = 0.0f;
           hexagons.g[0] = 0.3f;
           hexagons.b[0] = 0.25f;
           for(int i=1; i<7; i++)
           {
               hexagons.r[i] = 0.89f;
               hexagons.g[i] = 0.61f;
               hexagons.b[i] = 0.04f;
           }
       }

       if(searchStringChanged)
       {
           searchStringChanged = false;

       }
   }

   if(searchStringChanged)
   {
        searchStringChanged = false;
        // update strings of other hexagons;
        if(typedString.size() > 0)
            updateHexagonStrings();
   }
}

void Engine::render(double dt)
{
    glClear(GL_COLOR_BUFFER_BIT);
    int renderBgIndex = (mode == VISUAL) ? selectedHexagon : 10;
    hexagonRenderer.renderBg(hexagons,renderBgIndex);
    hexagonRenderer.render(hexagons);
    fontRenderer.render(fontAtlas, hexagons, 0.0f, 0.5f, 0.8f);
    window.swapBuffers();
}

void Engine::clean()
{
    
}

void Engine::updateHexagonStrings()
{
    FILE *fp;
    int status;

    std::string searchString=typedString; 
    std::vector<std::string> progName;
    for(unsigned int i=0; i<pathList.size(); i++)
    {
        std::string command("find " + pathList[i] + " -name *" + searchString + "*");  
        fp = popen(command.c_str(), "r");
        const int bufferLen = 256;
        char res[bufferLen];
        
        while(fgets(res, bufferLen, fp) != NULL)
        {
            std::string pName = "";

            int stringIndex = 0;
            int startIndex = 0;
            char ch;
            while((ch = res[stringIndex]) != '\0') 
            {
               if(stringIndex-1 >= 0 && res[stringIndex-1] == '/') 
                   startIndex = stringIndex;
                stringIndex++;
            }
            for(int j=startIndex; j<stringIndex; j++)
                pName += res[j];
            progName.push_back(pName);
 
        }

        status = pclose(fp);
    }
    
    int next[6] = {2,3,6,5,4,1}; 
    // hexagons are arranged that way,
    // changing it will change hjkl motion, so dont change
    for(unsigned int i=0; i<6; i++)
    {
        if(i < progName.size())
            hexagons.str[next[i]] = progName[i];
        else
            hexagons.str[next[i]] = "";
    }

}
