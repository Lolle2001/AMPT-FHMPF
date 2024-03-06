// #include "../include/AMPT_ampt.hpp"
#include "../include/AMPT_input.hpp"
// #include <fstream>
// #include <iostream>

// #include <TGraphErrors.h>
// #include <TAxis.h>
// #include <TPaveText.h>
// #include <TCanvas.h>
// #include <TLegend.h>
// #include <TF1.h>
// #include <map>
#include "../include/AMPT_functions.hpp"
// #include <string>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <type_traits>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>
struct PretyPrint {


    
    inline static const char * warning   = "\033[1;38;2;255;0;0m";
    inline static const char * end       = "\033[0m";
    inline static const char * started   = "\033[1;38;2;255;199;6m";
    inline static const char * finished  = "\033[1;38;2;57;181;74m";
    inline static const char * highlight = "\033[1;38;2;255;255;255m";
};



template<typename type>
struct Parameter {
    std::string name;
    type value;
    std::string stringvalue;
    std::string unit;
    Parameter(type value_, std::string name_, std::string unit_) : value(value_), name(name_), unit(unit_){};
    Parameter(std::string name_, std::string unit_) : name(name_), unit(unit_){};
    Parameter(){};
    
    
    
    friend std::ostream& operator<<(std::ostream &os, Parameter &p) {
        os << p.name << " = " << p.value;
        return os;
    }
    std::string GetName(){
        return name;
    }
    type GetValue(){
        return value;
    }
    std::string GetStringValue(){
        return stringvalue;
    }
    void SetName(std::string name_){
        name = name_;
    }
    void SetValue(type value_){
        value = value_;
    }
    void SetStringValue(){
        stringvalue = std::to_string(value);
    }
    void SetStringUnit(std::string unit_){
        unit = unit_;
    }
};


void test(){

    // std::cout << PretyPrint::highlight << "╭─" <<                    "──────────────────────────────────"                          << "─╮" << std::endl;
    // std::cout << PretyPrint::highlight << "│ " << PretyPrint::end << "AMPT data processer for large data" << PretyPrint::highlight << " │" << std::endl;
    // std::cout << PretyPrint::highlight << "│ " << PretyPrint::end << "v23.02.2024                       " << PretyPrint::highlight << " │" << std::endl;
    // std::cout << PretyPrint::highlight << "│ " << PretyPrint::end << "Made by Lieuwe Huisman            " << PretyPrint::highlight << " │" << std::endl;
    // std::cout << PretyPrint::highlight << "╰─"                       "──────────────────────────────────"                          << "─╯" << PretyPrint::end<< std::endl;

    // // AMPT::File_input * input = AMPT::Read_file_input(109, "data/");

    // Parameter<double>       EFRM("EFRM", "[GeV]");
    // Parameter<std::string>  FRAME("FRAME", "");

    // EFRM.SetValue(2);
    // FRAME.SetValue("CMS");



    // std::cout << EFRM << std::endl;
    // std::cout << FRAME << std::endl;

    std::vector<int> runs = {201, 202, 203, 205, 206, 207, 301, 302, 303, 304, 305, 401, 601, 1000, 1001, 1002, 1003, 1004, 1310};
    AMPT::File_input * inputs[20];
    int i = 0;
    for(auto entry: runs){
        inputs[i] = AMPT::Read_file_input(entry, "data/");
        i++;
        
        
    }
    std::ofstream File;
    File.open("test.ampt", std::ios::out);
    for(int j = 0; j < runs.size(); ++j){
        // inputs[i] -> PrintTabSeperated();
        
        if(inputs[j] -> NEVENT > 0){
            File << runs[j] << "\t";
            for(int i = 0; i < inputs[j] -> ParameterKeys.size();++i){
                File << inputs[j] -> ExtractedParameters[i] << "\t";
            }
            File << std::endl;
        }
        else{
            std::cout << runs[j] << std::endl;
        }
        
    }
    File.close();
    
    
    // std::string name = input -> GetAtomName("A", 12, 79);

    // std::cout << name << std::endl;


}
