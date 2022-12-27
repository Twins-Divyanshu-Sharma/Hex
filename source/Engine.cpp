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
        //newInput();
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
    float right=10, left=-10, top=10, bottom=-10, far=10, near = -10;
    
    ortho[0] = 2/(right-left);
    ortho[3] = -(right+left)/(right-left);
    ortho[5] = 2/(top-bottom);
    ortho[7] = -(top+bottom)/(top-bottom);
    ortho[10] = -2/(far-near);
    ortho[11] = -(far+near)/(far-near);
    ortho[15] = 1;

    float r=disabledColor.r, g=disabledColor.g, b=disabledColor.b, size=3.0f;
    float radius = 6;
    double root3 = sqrt(3);
    float root3by2 = (float)(root3/2.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0,0,0);
    hexagons.insert(0,0, insertColor.r, insertColor.g, insertColor.b, size);
    hexagons.insert(-root3by2*radius, 0.5*radius, r, g, b, size); // 1
    hexagons.insert(0.0,    radius,   r, g, b, size); // 2
    hexagons.insert(root3by2*radius, 0.5*radius,  r, g, b, size); // 3
    hexagons.insert(-root3by2*radius,-0.5*radius, r, g, b, size); // 4
    hexagons.insert(0.0, -radius, r, g, b, size); // 5
    hexagons.insert(root3by2*radius,-0.5*radius, r, g, b, size); // 6
    // 1 2 3
    // 4 5 6

    //fontAtlas.setAtlas("hexFontAtlas");
    fontAtlas.setAtlas("defaultFontAtlas");

    screenQuad.createScreenQuadMesh();
    worldFBO.attachTexture(window.getWidth(), window.getHeight());
    worldFBO.attachTexture(window.getWidth(), window.getHeight());
    worldFBO.lockAttachments();


    ping.attachTexture(window.getWidth(), window.getHeight());
    ping.lockAttachments();

    pong.attachTexture(window.getWidth(), window.getHeight());
    pong.lockAttachments();
    
}

void Engine::input()
{
    if(window.keyPressed(GLFW_KEY_ESCAPE) && !escapePressed)
    {
        escapePressed = true;
        window.close();
    }

    if(window.keyPressed(GLFW_KEY_TAB) && !tabPressed)
    {
        tabPressed = true;
        mode = (mode+1)%2;
        modeChange = true;
        ignore = true;
    }
    else if(window.keyReleased(GLFW_KEY_TAB) && tabPressed)
        tabPressed = false;



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

void Engine::insertModeInput() {
   
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

    
    if(Win::charInputEvent && !ignore)
    {
        Win::charInputEvent = false;
        typedString += Win::currentChar;
        hexagons.str[0] = typedString;
        searchStringChanged = true;
    }

    if(ignore)
        Win::charInputEvent = ignore = false;

}

void Engine::visualModeInput()
{

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
        std::cout << "=============== command ===============" << std::endl;
        std::cout << command.c_str() << std::endl;
        std::cout << "======================================" << std::endl;
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
           hexagons.r[0] = insertColor.r;
           hexagons.g[0] = insertColor.g;
           hexagons.b[0] = insertColor.b;
           for(int i=1; i<7; i++)
           {
                hexagons.r[i] = disabledColor.r;
                hexagons.g[i] = disabledColor.g;
                hexagons.b[i] = disabledColor.b;
           }
       }
       else if(mode == VISUAL)
       {
           hexagons.r[0] = disabledColor.r;
           hexagons.g[0] = disabledColor.g;
           hexagons.b[0] = disabledColor.b;
           for(int i=1; i<7; i++)
           {
               hexagons.r[i] = visualColor.r;
               hexagons.g[i] = visualColor.g;
               hexagons.b[i] = visualColor.b;
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
    worldFBO.bind();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int renderBgIndex = (mode == VISUAL) ? selectedHexagon : 10;
    hexagonRenderer.renderBg(hexagons,renderBgIndex, ortho,visualColor);
    hexagonRenderer.render(hexagons, ortho);
   worldFBO.unbind();

    bloomRenderer.render(screenQuad, worldFBO, ping, pong);  
    
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    screenQuadRenderer.render(screenQuad, worldFBO, pong);
    fontRenderer.render(fontAtlas, hexagons, ortho, textColor, selectedTextColor, renderBgIndex);
  

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
            ch = res[stringIndex];
            while(ch != '\0' && ch != '\n') 
            {
               if(stringIndex-1 >= 0 && res[stringIndex-1] == '/') 
                   startIndex = stringIndex;
                stringIndex++;
                ch = res[stringIndex];
            }
            for(int j=startIndex; j<stringIndex; j++)
                pName += res[j];
            progName.push_back(pName);
 
        }

        status = pclose(fp);
    }

    std::sort(progName.begin(),progName.end());
    std::vector<std::string> sortedProgName;
    for(unsigned int i=0; i<progName.size(); i++)
    {
        if(searchString.compare(progName[i]) == 0)
            sortedProgName.push_back(progName[i]);
    }

    for(unsigned int i=0; i<progName.size(); i++)
    {
        if(searchString.compare(progName[i]) != 0)
            sortedProgName.push_back(progName[i]);
    }   
    int next[6] = {2,3,6,5,4,1}; 
    // hexagons are arranged that way,
    // changing it will change hjkl motion, so dont change
    for(unsigned int i=0; i<6; i++)
    {
        if(i < sortedProgName.size())
            hexagons.str[next[i]] = sortedProgName[i];
        else
            hexagons.str[next[i]] = "";
    }

}
