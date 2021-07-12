#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H


#include <inicpp/inicpp.h>
#include <vector>
#include <map>
#include <iostream>
#include <omp.h>
#include "PartArray.h"
#include "Vect.h"
#include "CommandLineParameters.h"
#include "CalculationParameter.h"
#include "CorrelationCore.h"
#include "CorrelationPointCore.h"
#include "MagnetisationCore.h"

static const std::map<std::string, unsigned> methods = 
    {{"xor",0},{"energy",1},{"scalar",2}};

class ConfigManager
{
public:
    bool check_config();
    static ConfigManager init(const CommandLineParameters & commandLineParameters, const inicpp::config & iniconfig);

    void printHeader();
    void getParameters(std::vector< std::unique_ptr< CalculationParameter > > &);

    const PartArray & getSystem(){return this->system;}

    std::vector<double> temperatures;

    int getSeed() const { return this->seed; }
    unsigned N() const { return this->system.size(); }
    unsigned getHeatup() { return this->heatup; }
    unsigned getCalculate() { return this->calculate; }

private:
    ConfigManager(){};

    std::string sysfile;
    unsigned heatup = 0;
    unsigned calculate = 0;
    double range = 0;
    int seed = 0;
    std::vector<std::unique_ptr< CalculationParameter > > parameters;
    PartArray system;

    static Vect strToVect(std::string val){
        Vect target;
        if (val=="x" || val=="X"){
            target = Vect(1,0,0);
        } else {
            if (val=="y" || val=="Y") 
                target = Vect(0,1,0); 
            else {
                auto pos = val.find('|');
                if (pos!=std::string::npos){
                    double x = stod(val.substr(0,pos));
                    double y = stod(val.substr(pos+1));
                    target = Vect(x,y,0);
                } else {
                    throw(std::invalid_argument("Vector format is x|y"));
                }
            }
        }
        return target;
    }
};

#endif //CONFIGMANAGER_H