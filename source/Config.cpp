#include "Config.h"

Config::Config()
{

   std::string configFilePath = "";
   if(HEX_DEBUG == 0)
   {
        configFilePath = std::string(std::getenv("HOME")) + "/.config/Hex/config";
   }
   else
   {
        configFilePath = "res/config";
   }

   configFile.open(configFilePath);
   
   if(! configFile.good() )
   {
        std::cerr << "the path : "<< configFilePath << " does not exists " << std::endl;
        pathExists = false;       
   }
   else
   {
        pathExists = true;
        attainValues();
   }
}

Config::~Config()
{
    configFile.close();
}

void Config::attainValues()
{
    std::string line;
    std::string name;
    char equal;
    int r, g, b;
    while(std::getline(configFile, line))
    {
        std::istringstream iss(line);
        iss >> name >> equal >> r >> g >> b;
        Color& color = colorMap[name];
        color.r = (double)r/255.0;
        color.g = (double)g/255.0;
        color.b = (double)b/255.0;
    }

    configFile.close();

    hdr(colorMap["insertColor"]);
    hdr(colorMap["visualColor"]);
    //hdr(colorMap["disabledColor"]);
    //hdr(colorMap["textColor"]);
    //hdr(colorMap["selectedTextColor"]);
}

void Config::hdr(Color& color)
{ 
    color.r = pow(2.0, 7.5*color.r - 5);
    color.g = pow(2.0, 7.5*color.g - 5);
    color.b = pow(2.0, 7.5*color.b - 5);
}

bool Config::failedLoading()
{
    return !pathExists;
}

std::map<std::string,Color>& Config::getValues()
{
    return colorMap;
}