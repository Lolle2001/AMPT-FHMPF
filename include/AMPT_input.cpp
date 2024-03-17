#include "AMPT_input.hpp"

namespace AMPT {


    void File_input::ReadFile(){
        std::ifstream file;
        file.open(InputDirectory.c_str(), std::ios::in);
        if (file.is_open()){
            std::string sa;
            while (getline(file, sa)){
                ExtractedString         = AMPT::Functions::Extract(sa);
                // SizeOfExtractedString   = ExtractedString.size();
                
                if(LineNumber == EmbedLine_1){
                    ExtractedParameters.push_back(ExtractedString[0]);
                    ExtractedParameters.push_back(ExtractedString[1]);
                    // std::cout << linenumber << "\t" << extracted[0] << "\t" << extracted[1] << std::endl;
                }
                else if(LineNumber == EmbedLine_2){
                    ExtractedParameters.push_back(ExtractedString[0]);
                    ExtractedParameters.push_back(ExtractedString[1]);
                    // std::cout << linenumber << "\t" << extracted[0] << "\t" << extracted[1] << std::endl;
                }
                else if(LineNumber == EmbedLine_3){
                    ExtractedParameters.push_back(ExtractedString[0]);
                    ExtractedParameters.push_back(ExtractedString[1]);
                    ExtractedParameters.push_back(ExtractedString[2]);
                    // std::cout << linenumber << "\t" << extracted[0] << "\t" << extracted[1] << "\t" << extracted[2] << std::endl;
                }
                else{
                    ExtractedParameters.push_back(ExtractedString[0]);
                    // std::cout << linenumber << "\t" << extracted[0] << std::endl;
                }

                LineNumber += 1;
                if(LineNumber == EndLine){
                    break;
                }
            }
        }
        else{
            std::cout << "Could not open file" << std::endl;
        }
        file.close();
        FormatParameters();
    };

   
 

   

    double File_input::fdtod(std::string &s){
        std::replace(s.begin(), s.end(), 'd', 'E');
        return std::stod(s);
    }

    double File_input::csdtod(std::string &s){
        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        return std::stod(s);
    }
    double File_input::csitoi(std::string &s){
        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        return std::stoi(s);
    }
    
    void File_input::FormatParameters(){
        EFRM        = std::stod(ExtractedParameters[0]);
        FRAME       = ExtractedParameters[1];
        PROJ        = ExtractedParameters[2];
        TARG        = ExtractedParameters[3];
        IAP         = std::stoi(ExtractedParameters[4]);
        IZP         = std::stoi(ExtractedParameters[5]);
        IAT         = std::stoi(ExtractedParameters[6]);
        IZT         = std::stoi(ExtractedParameters[7]);
        NEVENT      = std::stoi(ExtractedParameters[8]);
        BMIN        = std::stod(ExtractedParameters[9]);
        BMAX        = std::stod(ExtractedParameters[10]);
        ISOFT       = std::stoi(ExtractedParameters[11]);
        NTMAX       = std::stoi(ExtractedParameters[12]);
        DT          = std::stod(ExtractedParameters[13]);
        PARJ_41     = std::stod(ExtractedParameters[14]);
        PARJ_42     = std::stod(ExtractedParameters[15]);
        IPOP        = std::stoi(ExtractedParameters[16]);
        PARJ_5      = std::stod(ExtractedParameters[17]);
        IHPR2_6     = std::stoi(ExtractedParameters[18]);
        IHPR2_4     = std::stoi(ExtractedParameters[19]);
        HIPR1_14    = std::stod(ExtractedParameters[20]);
        HIPR1_8     = std::stod(ExtractedParameters[21]);
        XMU         =     fdtod(ExtractedParameters[22]);
        IZPC        = std::stod(ExtractedParameters[23]);
        ALPHA       =     fdtod(ExtractedParameters[24]);
        DPCOAL      =     fdtod(ExtractedParameters[25]);
        DRCOAL      =     fdtod(ExtractedParameters[26]);
        IHJSED      = std::stoi(ExtractedParameters[27]);
        NSEED       = std::stoi(ExtractedParameters[28]);
        ISEEDP      = std::stoi(ExtractedParameters[29]);
        IKSDCY      = std::stoi(ExtractedParameters[30]);
        IPHIDCY     = std::stoi(ExtractedParameters[31]);
        IPI0DCY     = std::stoi(ExtractedParameters[32]);
        IOSCAR      = std::stoi(ExtractedParameters[33]);
        IDPERT      = std::stoi(ExtractedParameters[34]);
        NPERTD      = std::stoi(ExtractedParameters[35]);
        IDXSEC      = std::stoi(ExtractedParameters[36]);
        PTTRIG      = std::stod(ExtractedParameters[37]);
        MAXMISS     = std::stoi(ExtractedParameters[38]);
        IHPR2_2     = std::stoi(ExtractedParameters[39]);
        IHPR2_5     = std::stoi(ExtractedParameters[40]);
        IEMBED      = std::stoi(ExtractedParameters[41]);
        PXQEMBD     =    csdtod(ExtractedParameters[42]);
        PYQEMBD     = std::stod(ExtractedParameters[43]);
        XEMBD       =    csdtod(ExtractedParameters[44]);
        YEMBD       = std::stod(ExtractedParameters[45]);
        NSEMBD      =    csitoi(ExtractedParameters[46]);
        PSEMBD      =    csdtod(ExtractedParameters[47]);
        TMAXEMBD    = std::stod(ExtractedParameters[48]);
        ISHADOW     = std::stoi(ExtractedParameters[49]);
        DSHADOW     =     fdtod(ExtractedParameters[50]);
        IPHIRP      = std::stoi(ExtractedParameters[51]);

        
    };


    std::string File_input::GetAtomName(const std::string &Type, const int &AtomicWeight, const int &AtomicNumber, bool fullname)
    {
        std::string name;

        std::map<int, std::string> atom_names = {
            {1, "H"},
            {2, "He"},
            {3, "Li"},
            {4, "Be"},
            {5, "B"},
            {6, "C"},
            {7, "N"},
            {8, "O"},
            {9, "F"},
            {10, "Ne"},
            {11, "Na"},
            {12, "Mg"},
            {13, "Al"},
            {14, "Si"},
            {15, "P"},
            {16, "S"},
            {17, "Cl"},
            {18, "Ar"},
            {19, "K"},
            {20, "Ca"},
            {21, "Sc"},
            {22, "Ti"},
            {23, "V"},
            {24, "Cr"},
            {25, "Mn"},
            {26, "Fe"},
            {27, "Co"},
            {28, "Ni"},
            {29, "Cu"},
            {30, "Zn"},
            {31, "Ga"},
            {32, "Ge"},
            {33, "As"},
            {34, "Se"},
            {35, "Br"},
            {36, "Kr"},
            {37, "Rb"},
            {38, "Sr"},
            {39, "Y"},
            {40, "Zr"},
            {41, "Nb"},
            {42, "Mo"},
            {43, "Tc"},
            {44, "Ru"},
            {45, "Rh"},
            {46, "Pd"},
            {47, "Ag"},
            {48, "Cd"},
            {49, "In"},
            {50, "Sn"},
            {51, "Sb"},
            {52, "Te"},
            {53, "I"},
            {54, "Xe"},
            {55, "Cs"},
            {56, "Ba"},
            {57, "La"},
            {58, "Ce"},
            {59, "Pr"},
            {60, "Nd"},
            {61, "Pm"},
            {62, "Sm"},
            {63, "Eu"},
            {64, "Gd"},
            {65, "Tb"},
            {66, "Dy"},
            {67, "Ho"},
            {68, "Er"},
            {69, "Tm"},
            {70, "Yb"},
            {71, "Lu"},
            {72, "Hf"},
            {73, "Ta"},
            {74, "W"},
            {75, "Re"},
            {76, "Os"},
            {77, "Ir"},
            {78, "Pt"},
            {79, "Au"},
            {80, "Hg"},
            {81, "Tl"},
            {82, "Pb"},
            {83, "Bi"},
            {84, "Po"},
            {85, "At"},
            {86, "Rn"},
            {87, "Fr"},
            {88, "Ra"},
            {89, "Ac"},
            {90, "Th"},
            {91, "Pa"},
            {92, "U"},
            {93, "Np"},
            {94, "Pu"},
            {95, "Am"},
            {96, "Cm"},
            {97, "Bk"},
            {98, "Cf"},
            {99, "Es"},
            {100, "Fm"},
            {101, "Md"},
            {102, "No"},
            {103, "Lr"},
            {104, "Rf"},
            {105, "Db"},
            {106, "Sg"},
            {107, "Bh"},
            {108, "Hs"},
            {109, "Mt"},
            {110, "Ds"},
            {111, "Rg"},
            {112, "Cn"},
            {113, "Nh"},
            {114, "Fl"},
            {115, "Mc"},
            {116, "Lv"},
            {117, "Ts"},
            {118, "Og"}};

        name = atom_names[AtomicNumber];

        if (fullname)
        {
            name += "-" + std::to_string(AtomicWeight);
        }

        return name;
    }

    std::string File_input::GetProjectileName(bool include_ia){
        return GetAtomName(PROJ, IAP, IZP, include_ia);
    };
    std::string File_input::GetTargetName(bool include_ia){
        return GetAtomName(TARG, IAT, IZT, include_ia);
    }
    
    void File_input::Print(){
       
        for(int i = 0 ; i < ParameterKeys.size() ; ++i){
            std::cout << std::setw(8) << std::right << ParameterKeys[i] << " = ";
            std::cout << std::setw(9) << std::left << ExtractedParameters[i] << std::endl;
        }
    }

    void File_input::FormatParametersSummary(){
        EFRM        = std::stod(ExtractedParameters[0]);
        FRAME       = ExtractedParameters[1];
        PROJ        = ExtractedParameters[2];
        TARG        = ExtractedParameters[3];
        IAP         = std::stoi(ExtractedParameters[4]);
        IZP         = std::stoi(ExtractedParameters[5]);
        IAT         = std::stoi(ExtractedParameters[6]);
        IZT         = std::stoi(ExtractedParameters[7]);
        NEVENT      = std::stoi(ExtractedParameters[8]);
        BMIN        = std::stod(ExtractedParameters[9]);
        BMAX        = std::stod(ExtractedParameters[10]);
        ISOFT       = std::stoi(ExtractedParameters[11]);
        NTMAX       = std::stoi(ExtractedParameters[12]);
        DT          = std::stod(ExtractedParameters[13]);
        PARJ_41     = std::stod(ExtractedParameters[14]);
        PARJ_42     = std::stod(ExtractedParameters[15]);
        IPOP        = std::stoi(ExtractedParameters[16]);
        PARJ_5      = std::stod(ExtractedParameters[17]);
        IHPR2_6     = std::stoi(ExtractedParameters[18]);
        IHPR2_4     = std::stoi(ExtractedParameters[19]);
        HIPR1_14    = std::stod(ExtractedParameters[20]);
        HIPR1_8     = std::stod(ExtractedParameters[21]);
        XMU         = std::stod(ExtractedParameters[22]);
        IZPC        = std::stod(ExtractedParameters[23]);
        ALPHA       = std::stod(ExtractedParameters[24]);
        DPCOAL      = std::stod(ExtractedParameters[25]);
        DRCOAL      = std::stod(ExtractedParameters[26]);
        IHJSED      = std::stoi(ExtractedParameters[27]);
        NSEED       = std::stoi(ExtractedParameters[28]);
        ISEEDP      = std::stoi(ExtractedParameters[29]);
        IKSDCY      = std::stoi(ExtractedParameters[30]);
        IPHIDCY     = std::stoi(ExtractedParameters[31]);
        IPI0DCY     = std::stoi(ExtractedParameters[32]);
        IOSCAR      = std::stoi(ExtractedParameters[33]);
        IDPERT      = std::stoi(ExtractedParameters[34]);
        NPERTD      = std::stoi(ExtractedParameters[35]);
        IDXSEC      = std::stoi(ExtractedParameters[36]);
        PTTRIG      = std::stod(ExtractedParameters[37]);
        MAXMISS     = std::stoi(ExtractedParameters[38]);
        IHPR2_2     = std::stoi(ExtractedParameters[39]);
        IHPR2_5     = std::stoi(ExtractedParameters[40]);
        IEMBED      = std::stoi(ExtractedParameters[41]);
        PXQEMBD     = std::stod(ExtractedParameters[42]);
        PYQEMBD     = std::stod(ExtractedParameters[43]);
        XEMBD       = std::stod(ExtractedParameters[44]);
        YEMBD       = std::stod(ExtractedParameters[45]);
        NSEMBD      = std::stoi(ExtractedParameters[46]);
        PSEMBD      = std::stod(ExtractedParameters[47]);
        TMAXEMBD    = std::stod(ExtractedParameters[48]);
        ISHADOW     = std::stoi(ExtractedParameters[49]);
        DSHADOW     = std::stod(ExtractedParameters[50]);
        IPHIRP      = std::stoi(ExtractedParameters[51]);

        
    };

    void File_input::WriteSummary(std::string Filename){
        std::ofstream File;
        File.open(Filename.c_str(), std::ios::out);
        if(File.is_open()){
            for(int i = 0; i < ParameterKeys.size();++i){
                File << std::setw(30) << std::left << ExtractedParameters[i] ;
                File << "! " << ParameterKeys[i] << std::endl;
            }
            std::cout << PP::FINISHED << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Written input to: " << Filename << std::endl;
        }
        else{
            std::cout << PP::WARNING << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Cannot open file: " << Filename << std::endl;
        }
        File.close();

    }

    void File_input::WriteTabSeperated(std::string Filename){
        std::ofstream File;
        File.open(Filename.c_str(), std::ios::out);
        if(File.is_open()){
            for(int i = 0; i < ParameterKeys.size();++i){
                File << ExtractedParameters[i] << "\t";
            }
            File.flush();
            std::cout << PP::FINISHED << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Written input to: " << Filename << std::endl;
        }
        else{
            std::cout << PP::WARNING << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Cannot open file: " << Filename << std::endl;
        }
        File.close();

    }

    void File_input::ReadSummary(std::string Filename){
        std::ifstream File;
        File.open(Filename.c_str(), std::ios::in);
        if(File.is_open()){
            ExtractedParameters.resize(ParameterKeys.size());
            std::string delimiter;
            std::string key;
            for(int i = 0; i < ParameterKeys.size(); ++i){
                File >> ExtractedParameters[i] >> delimiter >> key;
            }
            FormatParametersSummary();
            // FormatParameters();
            std::cout << PP::FINISHED << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Read input from: " << Filename << std::endl;
        }
        else{
            std::cout << PP::WARNING << "[AMPT::File_input]" << PP::RESET << " ";
            std::cout << "Cannot open file: " << Filename << std::endl;
        }
        File.close();
    }

    void File_input::PrintTabSeperated(){
        
        
       
        for(int i = 0; i < ParameterKeys.size();++i){
            std::cout << ExtractedParameters[i] << "\t";
        }
        std::cout << std::endl;
        

    }

    

    
    
    




File_input * Combine_file_input(int NRun, int NBatchMin, int NBatchMax, std::string Directory){
    File_input * cinput = new File_input();
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        File_input * input = new File_input(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");
        input -> ReadFile();
        // input -> Print();
        *cinput += *input;
        delete input;
    }
    cinput -> NRun = NRun;
    // cinput -> Update(Directory,NRun);
    system(("mkdir -p \"" + Directory + std::to_string(NRun) + "/processed\"").c_str());
    cinput -> WriteSummary(Directory + std::to_string(NRun) + "/processed/inputsummary.ampt");
    cinput -> WriteTabSeperated(Directory + std::to_string(NRun) + "/processed/inputsheet.ampt");
    
    return cinput;
}

File_input * Read_file_input(int NRun, std::string Directory){
    
    std::cout << PP::STARTED << "[AMPT::File_input]" << PP::RESET << " ";
    std::cout << "Reading input data from run: " << NRun << std::endl; 
    File_input * cinput = new File_input();
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    cinput -> ReadSummary(Directory  + std::to_string(NRun) + "/processed/inputsummary.ampt");
    cinput -> NRun = NRun;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::FINISHED << "[AMPT::File_input]" << PP::RESET << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::HIGHLIGHT << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::RESET << std::endl;
    return cinput;
}

}