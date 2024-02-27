#ifndef AMPT_INPUT2_HPP
#define AMPT_INPUT2_HPP

#include <vector>
#include <iostream>
#include "AMPT_functions.hpp"
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>



namespace AMPT {

using PP = AMPT::Functions::PretyPrint;

// using Parameter = AMPT::Functions::AMPTParameter<T>;
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

/*
ana/input.ampt
*/
class File_input {
    private:
    

    int LineNumber = 0;

    std::vector<std::string> ExtractedString;
    std::string InputDirectory;
    public:
    std::vector<std::string> ExtractedParameters;

   


    std::vector<std::string> ParameterKeys = 
       {"EFRM",
        "FRAME",
        "PROJ",
        "TARG",
        "IAP",
        "IZP",
        "IAT",
        "IZT",
        "NEVENT",
        "BMIN",
        "BMAX",
        "ISOFT",
        "NTMAX",
        "DT",
        "PARJ_41",
        "PARJ_42",
        "IPOP",
        "PARJ_5",
        "IHPR2_6",
        "IHPR2_4",
        "HIPR1_14",
        "HIPR1_8",
        "XMU",
        "IZPC",
        "ALPHA",
        "DPCOAL",
        "DRCOAL",
        "IHJSED",
        "NSEED",
        "ISEEDP",
        "IKSDCY",
        "IPHIDCY",
        "IPI0DCY",
        "IOSCAR",
        "IDPERT",
        "NPERTD",
        "IDXSEC",
        "PTTRIG",
        "MAXMISS",
        "IHPR2_2",
        "IHPR2_5",
        "IEMBED",
        "PXQEMBD",
        "PYQEMBD",
        "XEMBD",
        "YEMBD",
        "NSEMBD",
        "PSEMBD",
        "TMAXEMBD",
        "ISHADOW",
        "DSHADOW",
        "IPHIRP"};
    
    std::vector<std::string> ParameterUnits = 
       {"[GeV]",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "[fm]",
        "[fm]",
        "",
        "",
        "[fm/c]",
        "[?]",
        "[?]",
        "",
        "",
        "",
        "",
        "[GeV/fm]",
        "[GeV]",
        "[1/fm]",
        "",
        "",
        "[GeV]",
        "[fm]",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "[?]",
        "[GeV]",
        "",
        "",
        "",
        "",
        "[GeV]",
        "[GeV]",
        "[fm]",
        "[fm]",
        "",
        "[GeV]",
        "[rad]",
        "",
        "",
        ""};
    
    Parameter<double>       EFRM;//("EFRM", "[GeV]");
    Parameter<std::string>  FRAME;//("FRAME", "");

    // double      EFRM; // Center of Mass Energy
    // std::string FRAME; // Collision Frame
    Parameter<std::string > PROJ; // Projectile Type
    Parameter<std::string > TARG; // Projectile Type
    Parameter<int         > IAP; // Atomic number
    Parameter<int         > IZP; // Proton number
    Parameter<int         > IAT; // Atomic number
    Parameter<int         > IZT; // Proton number
    Parameter<int         > NEVENT; // Amount of events
    Parameter<double      > BMIN; // Lowest impact parameter
    Parameter<double      > BMAX; // Highest impact parameter
    Parameter<int         > ISOFT; // Default AMPT or String Melting
    Parameter<int         > NTMAX; //
    Parameter<double      > DT;
    Parameter<double      > PARJ_41;
    Parameter<double      > PARJ_42;
    Parameter<int         > IPOP;
    Parameter<double      > PARJ_5;
    Parameter<int         > IHPR2_6; // Shadowing flag
    Parameter<int         > IHPR2_4; // Quenching flag
    Parameter<double      > HIPR1_14; // Quenching rate
    Parameter<double      > HIPR1_8; // Maximum pT of hard or semihard scatterings in HIJING
    Parameter<double      > XMU; // the d stands for double precision, the integer after that is probably the exponent
    Parameter<int         > IZPC;
    Parameter<double      > ALPHA;
    Parameter<double      > DPCOAL;
    Parameter<double      > DRCOAL;
    Parameter<int         > IHJSED;
    Parameter<int         > NSEED; // Default -> find a way to get it from the other files.
    Parameter<int         > ISEEDP;
    Parameter<int         > IKSDCY;
    Parameter<int         > IPHIDCY;
    Parameter<int         > IPI0DCY;
    Parameter<int         > IOSCAR;
    Parameter<int         > IDPERT;
    Parameter<int         > NPERTD;
    Parameter<int         > IDXSEC;
    Parameter<double      > PTTRIG;
    Parameter<int         > MAXMISS;
    Parameter<int         > IHPR2_2;
    Parameter<int         > IHPR2_5;
    Parameter<int         > IEMBED;
    
    int         EmbedLine_1 = 43 - 1;
    int         EmbedLine_2 = 44 - 1;
    int         EmbedLine_3 = 45 - 1;

    Parameter<double      > PXQEMBD; //43
    Parameter<double      > PYQEMBD; //43
    Parameter<double      > XEMBD; //44
    Parameter<double      > YEMBD; //44
    Parameter<int         > NSEMBD; //45
    Parameter<double      > PSEMBD; //45
    Parameter<double      > TMAXEMBD; //45
    Parameter<int         > ISHADOW;
    Parameter<double      > DSHADOW;
    Parameter<int         > IPHIRP;


    int EndLine = 49 - 1;  


    int NRun = 0;

    File_input(std::string InputDirectory_) : InputDirectory(InputDirectory_){};
    File_input(std::string InputDirectory_, int NRun_) : InputDirectory(InputDirectory_), NRun(NRun_){};
    File_input(){}

    

    void ReadFile(){
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

   
 

   

    double fdtod(std::string &s){
        std::replace(s.begin(), s.end(), 'd', 'E');
        return std::stod(s);
    }

    double csdtod(std::string &s){
        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        return std::stod(s);
    }
    double csitoi(std::string &s){
        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        return std::stoi(s);
    }
    
    void FormatParameters(){
        EFRM = Parameter<double>(std::stod(ExtractedParameters[0]), "EFRM", "GeV");
        FRAME = Parameter<std::string>(ExtractedParameters[1], "FRAME", "");
        PROJ = Parameter<std::string>(ExtractedParameters[2], "PROJ", "");
        TARG = Parameter<std::string>(ExtractedParameters[3], "TARG", "");
        IAP = Parameter<int>(std::stoi(ExtractedParameters[4]), "IAP", "");
        IZP = Parameter<int>(std::stoi(ExtractedParameters[5]), "IZP", "");
        IAT = Parameter<int>(std::stoi(ExtractedParameters[6]), "IAT", "");
        IZT = Parameter<int>(std::stoi(ExtractedParameters[7]), "IZT", "");
        NEVENT = Parameter<int>(std::stoi(ExtractedParameters[8]), "NEVENT", "");
        BMIN = Parameter<double>(std::stod(ExtractedParameters[9]), "BMIN", "fm");
        BMAX = Parameter<double>(std::stod(ExtractedParameters[10]), "BMAX", "fm");
        ISOFT = Parameter<int>(std::stoi(ExtractedParameters[11]), "ISOFT", "");
        NTMAX = Parameter<int>(std::stoi(ExtractedParameters[12]), "NTMAX", "");
        DT = Parameter<double>(std::stod(ExtractedParameters[13]), "DT", "fm/c");
        PARJ_41 = Parameter<double>(std::stod(ExtractedParameters[14]), "PARJ(41)", "");
        PARJ_42 = Parameter<double>(std::stod(ExtractedParameters[15]), "PARJ(42)", "");
        IPOP = Parameter<int>(std::stoi(ExtractedParameters[16]), "IPOP", "");
        PARJ_5 = Parameter<double>(std::stod(ExtractedParameters[17]), "PARJ(5)", "");
        IHPR2_6 = Parameter<int>(std::stoi(ExtractedParameters[18]), "IHPR2(6)", "");
        IHPR2_4 = Parameter<int>(std::stoi(ExtractedParameters[19]), "IHPR2(4)", "");
        HIPR1_14 = Parameter<double>(std::stod(ExtractedParameters[20]), "HIPR1(14)", "");
        HIPR1_8 = Parameter<double>(std::stod(ExtractedParameters[21]), "HIPR1(8)", "");
        XMU = Parameter<double>(fdtod(ExtractedParameters[22]), "XMU", "");
        IZPC = Parameter<double>(std::stod(ExtractedParameters[23]), "IZPC", "");
        ALPHA = Parameter<double>(fdtod(ExtractedParameters[24]), "ALPHA", "");
        DPCOAL = Parameter<double>(fdtod(ExtractedParameters[25]), "DPCOAL", "fm");
        DRCOAL = Parameter<double>(fdtod(ExtractedParameters[26]), "DRCOAL", "fm");
        IHJSED = Parameter<int>(std::stoi(ExtractedParameters[27]), "IHJSED", "");
        NSEED = Parameter<int>(std::stoi(ExtractedParameters[28]), "NSEED", "");
        ISEEDP = Parameter<int>(std::stoi(ExtractedParameters[29]), "ISEEDP", "");
        IKSDCY = Parameter<int>(std::stoi(ExtractedParameters[30]), "IKSDCY", "");
        IPHIDCY = Parameter<int>(std::stoi(ExtractedParameters[31]), "IPHIDCY", "");
        IPI0DCY = Parameter<int>(std::stoi(ExtractedParameters[32]), "IPI0DCY", "");
        IOSCAR = Parameter<int>(std::stoi(ExtractedParameters[33]), "IOSCAR", "");
        IDPERT = Parameter<int>(std::stoi(ExtractedParameters[34]), "IDPERT", "");
        NPERTD = Parameter<int>(std::stoi(ExtractedParameters[35]), "NPERTD", "");
        IDXSEC = Parameter<int>(std::stoi(ExtractedParameters[36]), "IDXSEC", "");
        PTTRIG = Parameter<double>(std::stod(ExtractedParameters[37]), "PTTRIG", "GeV/c");
        MAXMISS = Parameter<int>(std::stoi(ExtractedParameters[38]), "MAXMISS", "");
        IHPR2_2 = Parameter<int>(std::stoi(ExtractedParameters[39]), "IHPR2_2", "");
        IHPR2_5 = Parameter<int>(std::stoi(ExtractedParameters[40]), "IHPR2_5", "");
        IEMBED = Parameter<int>(std::stoi(ExtractedParameters[41]), "IEMBED", "");
        PXQEMBD = Parameter<double>(csdtod(ExtractedParameters[42]), "PXQEMBD", "GeV/c");
        PYQEMBD = Parameter<double>(std::stod(ExtractedParameters[43]), "PYQEMBD", "GeV/c");
        XEMBD = Parameter<double>(csdtod(ExtractedParameters[44]), "XEMBD", "fm");
        YEMBD = Parameter<double>(std::stod(ExtractedParameters[45]), "YEMBD", "fm");
        NSEMBD = Parameter<int>(csitoi(ExtractedParameters[46]), "NSEMBD", "");
        PSEMBD = Parameter<double>(csdtod(ExtractedParameters[47]), "PSEMBD", "GeV/c");
        TMAXEMBD = Parameter<double>(std::stod(ExtractedParameters[48]), "TMAXEMBD", "GeV");
        ISHADOW = Parameter<int>(std::stoi(ExtractedParameters[49]), "ISHADOW", "");
        DSHADOW = Parameter<double>(fdtod(ExtractedParameters[50]), "DSHADOW", "fm");
        IPHIRP = Parameter<int>(std::stoi(ExtractedParameters[51]), "IPHIRP", "");


        
    };


    std::string GetAtomName(const std::string &Type, const int &AtomicWeight, const int &AtomicNumber, bool fullname = false)
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

    std::string GetProjectileName(bool include_ia = false){
        return GetAtomName(PROJ, IAP, IZP, include_ia);
    };
    std::string GetTargetName(bool include_ia = false){
        return GetAtomName(TARG, IAT, IZT, include_ia);
    }
    
    void Print(){
       
        for(int i = 0 ; i < ParameterKeys.size() ; ++i){
            std::cout << std::setw(8) << std::right << ParameterKeys[i] << " = ";
            std::cout << std::setw(9) << std::left << ExtractedParameters[i] << std::endl;
        }
    }

    void FormatParametersSummary(){
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

    void WriteSummary(std::string Filename){
        std::ofstream File;
        File.open(Filename.c_str(), std::ios::out);
        if(File.is_open()){
            for(int i = 0; i < ParameterKeys.size();++i){
                File << std::setw(30) << std::left << ExtractedParameters[i] ;
                File << "! " << ParameterKeys[i] << std::endl;
            }
            std::cout << PP::finished << "[AMPT::File_input]" << PP::end << " ";
            std::cout << "Written input to: " << Filename << std::endl;
        }
        else{
            std::cout << PP::warning << "[AMPT::File_input]" << PP::end << " ";
            std::cout << "Cannot open file: " << Filename << std::endl;
        }
        File.close();

    }

    void ReadSummary(std::string Filename){
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
            std::cout << PP::finished << "[AMPT::File_input]" << PP::end << " ";
            std::cout << "Read input from: " << Filename << std::endl;
        }
        else{
            std::cout << PP::warning << "[AMPT::File_input]" << PP::end << " ";
            std::cout << "Cannot open file: " << Filename << std::endl;
        }
        File.close();
    }

    
    
    void operator+=(File_input const& obj){
        
        EFRM      = obj.EFRM      ;
        FRAME     = obj.FRAME     ;
        PROJ      = obj.PROJ      ;
        TARG      = obj.TARG      ;
        IAP       = obj.IAP       ;
        IZP       = obj.IZP       ;
        IAT       = obj.IAT       ;
        IZT       = obj.IZT       ;
        NEVENT   += obj.NEVENT    ;
        BMIN      = obj.BMIN      ;
        BMAX      = obj.BMAX      ;
        ISOFT     = obj.ISOFT     ;
        NTMAX     = obj.NTMAX     ;
        DT        = obj.DT        ;
        PARJ_41   = obj.PARJ_41   ;
        PARJ_42   = obj.PARJ_42   ;
        IPOP      = obj.IPOP      ;
        PARJ_5    = obj.PARJ_5    ;
        IHPR2_6   = obj.IHPR2_6   ;
        IHPR2_4   = obj.IHPR2_4   ;
        HIPR1_14  = obj.HIPR1_14  ;
        HIPR1_8   = obj.HIPR1_8   ;
        XMU       = obj.XMU       ;
        IZPC      = obj.IZPC      ;
        ALPHA     = obj.ALPHA     ;
        DPCOAL    = obj.DPCOAL    ;
        DRCOAL    = obj.DRCOAL    ;
        IHJSED    = obj.IHJSED    ;
        NSEED     = obj.NSEED     ;
        ISEEDP    = obj.ISEEDP    ;
        IKSDCY    = obj.IKSDCY    ;
        IPHIDCY   = obj.IPHIDCY   ;
        IPI0DCY   = obj.IPI0DCY   ;
        IOSCAR    = obj.IOSCAR    ;
        IDPERT    = obj.IDPERT    ;
        NPERTD    = obj.NPERTD    ;
        IDXSEC    = obj.IDXSEC    ;
        PTTRIG    = obj.PTTRIG    ;
        MAXMISS   = obj.MAXMISS   ;
        IHPR2_2   = obj.IHPR2_2   ;
        IHPR2_5   = obj.IHPR2_5   ;
        IEMBED    = obj.IEMBED    ;
        PXQEMBD   = obj.PXQEMBD   ;
        PYQEMBD   = obj.PYQEMBD   ;
        XEMBD     = obj.XEMBD     ;
        YEMBD     = obj.YEMBD     ;
        NSEMBD    = obj.NSEMBD    ;
        PSEMBD    = obj.PSEMBD    ;
        TMAXEMBD  = obj.TMAXEMBD  ;
        ISHADOW   = obj.ISHADOW   ;
        DSHADOW   = obj.DSHADOW   ;
        IPHIRP    = obj.IPHIRP    ;
        ExtractedParameters = obj.ExtractedParameters;
        ExtractedParameters[8] = std::to_string(NEVENT);
    };

    // static File_input * Combine_file_input(int NRun, int NBatchMin, int NBatchMax, std::string Directory){
    //     File_input * cinput = new File_input();
    //     for(int i = NBatchMin; i <= NBatchMax; ++i){
    //         File_input * input = new File_input(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");
    //         input -> ReadFile();
    //         // input -> Print();
    //         *cinput += *input;
    //         delete input;
    //     }
    //     cinput -> NRun = NRun;
    //     // cinput -> Update(Directory,NRun);
    //     system(("mkdir -p \"" + Directory + std::to_string(NRun) + "/processed\"").c_str());
    //     cinput -> WriteSummary(Directory + std::to_string(NRun) + "/processed/inputsummary.ampt");

        
    //     return cinput;
    // }


};

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

    
    return cinput;
}

File_input * Read_file_input(int NRun, std::string Directory){
    
    std::cout << PP::started << "[AMPT::File_input]" << PP::end << " ";
    std::cout << "Reading input data from run: " << NRun << std::endl; 
    File_input * cinput = new File_input();
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    cinput -> ReadSummary(Directory  + std::to_string(NRun) + "/processed/inputsummary.ampt");
    cinput -> NRun = NRun;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::finished << "[AMPT::File_input]" << PP::end << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    return cinput;
}
}

#endif