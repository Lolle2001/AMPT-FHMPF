#include "../include/AMPT_ampt.hpp"
#include "../include/AMPT_input.hpp"
#include <fstream>
#include <iostream>

using PP = AMPT::Functions::PretyPrint;

int main(int argc, char *argv[]){
    int NRun = std::stoi(argv[1]);
    int NBatch = std::stoi(argv[2]);
    
    std::string Directory = argv[3];

    std::cout << PP::highlight << "╭─" <<            "────────────────────────────────────────────────────────────────────"                  << "─╮" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "AMPT data processer for large data                                  " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "v23.02.2024                                                         " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "│ " << PP::end << "Made by Lieuwe Huisman                                              " << PP::highlight << " │" << '\n';
    std::cout << PP::highlight << "╰─"               "────────────────────────────────────────────────────────────────────"                  << "─╯" << '\n';
    // std::cout << std::endl;
    AMPT::File_ampt  * ampt  = AMPT::Combine_ampt_multi_queued_omp(NRun, 1, NBatch, Directory + "/", 20);
    AMPT::File_input * input = AMPT::Combine_file_input       (NRun, 1, NBatch, Directory + "/");


    return 0;
}