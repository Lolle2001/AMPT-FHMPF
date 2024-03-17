#include "../include/AMPT_ampt.hpp"
#include "../include/AMPT_input.hpp"
#include <fstream>
#include <iostream>
#include <string>


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

std::string repeat(int n, std::string c) {
    std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << c;
    return os.str();
}





int main(int argc, char *argv[]){
    int NRun;
    int NBatch;
    std::string Directory;
    int collisiontype;
    int LowerNBatch = 1;

    
    // std::cout << std::endl;

    bool flag_nr = false;
    bool flag_nb = false;
    bool flag_dir = false;
    bool flag_col = false;

    for(int i = 1; i < argc - 1; ++i){
        // std::cout << i << " " << argv[i] << std::endl;
        if(std::string(argv[i]).compare("-nr") == 0){
            NRun = std::stoi(argv[i+1]);
            flag_nr = true;
            i++;
        }
        if(std::string(argv[i]).compare("-nb") == 0){
            NBatch = std::stoi(argv[i+1]);
            flag_nb = true;
            i++;
        }
        if(std::string(argv[i]).compare("-dir") == 0){
            Directory = argv[i+1];
            flag_dir = true;
            i++;
        }
        if(std::string(argv[i]).compare("-col") == 0){
            collisiontype = std::stoi(argv[i+1]);
            flag_col = true;
            i++;
        }
        if(std::string(argv[i]).compare("-nbmin") == 0){
            LowerNBatch = std::stoi(argv[i+1]);
            // flag_col = true;
            i++;
        }
    }
    if(!flag_nr){
        NRun = std::stoi(argv[1]);
    }
    if(!flag_dir){
        Directory = "data";
    }
    if(!flag_nb){
        NBatch = GetNBatch(Directory + "/" + std::to_string(NRun));
    }
    if(!flag_col){
        collisiontype = 0;
    }
    std::string centralitybinningname;
    if(collisiontype == 0){
        centralitybinningname = "Pb-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if(collisiontype == 1){
        centralitybinningname = "p-Pb at 5.02 TeV (0-5-10-20-..90-100)";
    }
    if(collisiontype == 2){
        centralitybinningname = "p-p at 5.02 TeV (0-100)";
    }
    // std::cout << collisiontype << std::endl;
    
    
    
    // std::cout << "\033[1;48;2;0;111;184";
    
    printf("%s╭%-70s╮%s\n",PP::HIGHLIGHT, repeat(70, "─").c_str(), PP::RESET );
    printf("%s│%s %-68s %s│%s\n",PP::HIGHLIGHT, PP::RESET,"AMPT data processer for large data",PP::HIGHLIGHT, PP::RESET );
    printf("%s│%s %-68s %s│%s\n",PP::HIGHLIGHT, PP::RESET,"Version 3.1.0",PP::HIGHLIGHT, PP::RESET );
    printf("%s│%s %-68s %s│%s\n",PP::HIGHLIGHT, PP::RESET,"Made by Lieuwe Huisman",PP::HIGHLIGHT, PP::RESET );
    printf("%s│%s %-68s %s│%s\n",PP::HIGHLIGHT, PP::RESET,"Made using AMPT version: v23.02.2024",PP::HIGHLIGHT, PP::RESET );
    printf("%s├%-70s┤%s\n",PP::HIGHLIGHT, repeat(70, "─").c_str(), PP::RESET );
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT,PP::RESET, "Runnumber", std::to_string(NRun).c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT,PP::RESET, "Batchnumber", std::to_string(NBatch).c_str(), PP::HIGHLIGHT, PP::RESET);
    if(LowerNBatch > 1){
        printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT,PP::RESET, "Starting at bin", std::to_string(LowerNBatch).c_str(), PP::HIGHLIGHT, PP::RESET);
    }
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT,PP::RESET, "Data directory", Directory.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s│%s %-18s : %-47s %s│%s\n", PP::HIGHLIGHT,PP::RESET, "Centrality Binning", centralitybinningname.c_str(), PP::HIGHLIGHT, PP::RESET);
    printf("%s╰%-70s╯%s\n",PP::HIGHLIGHT, repeat(70, "─").c_str(), PP::RESET );

    AMPT::File_ampt  * ampt  = AMPT::CombineAMPT(NRun, LowerNBatch, NBatch, Directory + "/", 20, collisiontype);
    AMPT::File_input * input = AMPT::Combine_file_input       (NRun, LowerNBatch, NBatch, Directory + "/");

    return 0;
}