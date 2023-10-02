#ifndef H_C0NFI6_H
#define H_C0NFI6_H

#include <fstream>
#include <iostream>
#include <string>
#include "allgl.h"
#include "Color.h"
#include <sstream>
#include <map>
#include <math.h>

class Config
{
    private:
        std::ifstream configFile;
        bool pathExists = true;
        std::map<std::string,Color> colorMap;
        void hdr(Color&);
        void attainValues();
    public:
        Config();
        ~Config();
        std::map<std::string,Color>& getValues();
        bool failedLoading();
};

#endif