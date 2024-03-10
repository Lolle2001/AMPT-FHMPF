#include "../include/AMPT_ampt.hpp"
#include "../include/AMPT_input.hpp"
#include <fstream>
#include <iostream>

using PP = AMPT::Functions::PretyPrint;

int GetNBatch(std::string FileDirectory){
    std::filesystem::path path(FileDirectory);

    std::string directoryname = path.filename();
    std::string datafolder = path.parent_path();

    std::string subfoldernames[50];

    int nbatch = 0;
    for (const auto & entry : std::filesystem::directory_iterator(FileDirectory)){
        std::string filename = entry.path().filename();
        if(filename.substr(0, filename.find("_")) == directoryname){
            // std::cout << filename << std::endl;
            
            nbatch++;
        }
    }
    return nbatch;
}




int main(int argc, char *argv[]){
    int NRun;
    int NBatch;
    std::string Directory;
   

    std::cout << PP::highlight << "╭─" <<            "────────────────────────────────────────────────────────────────────"                  << "─╮" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "AMPT data processer for large data                                  " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "v23.02.2024                                                         " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "Made by Lieuwe Huisman                                              " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "╰─"               "────────────────────────────────────────────────────────────────────"                  << "─╯" << '\n';
    // std::cout << std::endl;
    if(argc == 4){
        NRun = std::stoi(argv[1]);
        NBatch = std::stoi(argv[2]);
        
        Directory = argv[3];
    }
    else if(argc == 3){
        NRun = std::stoi(argv[1]);
        Directory = argv[2];
        NBatch = GetNBatch(Directory + "/" + std::to_string(NRun));
    }

    AMPT::File_ampt  * ampt  = AMPT::CombineAMPT(NRun, 1, NBatch, Directory + "/", 20);
    AMPT::File_input * input = AMPT::Combine_file_input       (NRun, 1, NBatch, Directory + "/");

    return 0;
}