#ifndef AMPT_INPUT_HPP
#define AMPT_INPUT_HPP

#include <vector>
#include <iostream>
#include "AMPT_functions.hpp"
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>



namespace AMPT {

using PP = AMPT::Functions::PretyPrint;

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
    
    // Parameter<double>       EFRM;
    // Parameter<std::string>  FRAME;
    double      EFRM; // Center of Mass Energy
    std::string FRAME; // Collision Frame
    std::string PROJ; // Projectile Type
    std::string TARG; // Projectile Type
    int         IAP; // Atomic number
    int         IZP; // Proton number
    int         IAT; // Atomic number
    int         IZT; // Proton number
    int         NEVENT = 0; // Amount of events
    double      BMIN; // Lowest impact parameter
    double      BMAX; // Highest impact parameter
    int         ISOFT; // Default AMPT or String Melting
    int         NTMAX; //
    double      DT;
    double      PARJ_41;
    double      PARJ_42;
    int         IPOP;
    double      PARJ_5;
    int         IHPR2_6; // Shadowing flag
    int         IHPR2_4; // Quenching flag
    double      HIPR1_14; // Quenching rate
    double      HIPR1_8; // Maximum pT of hard or semihard scatterings in HIJING
    double      XMU; // the d stands for double precision, the integer after that is probably the exponent
    int         IZPC;
    double      ALPHA;
    double      DPCOAL;
    double      DRCOAL;
    int         IHJSED;
    int         NSEED; // Default -> find a way to get it from the other files.
    int         ISEEDP;
    int         IKSDCY;
    int         IPHIDCY;
    int         IPI0DCY;
    int         IOSCAR;
    int         IDPERT;
    int         NPERTD;
    int         IDXSEC;
    double      PTTRIG;
    int         MAXMISS;
    int         IHPR2_2;
    int         IHPR2_5;
    int         IEMBED;
    
    int         EmbedLine_1 = 43 - 1;
    int         EmbedLine_2 = 44 - 1;
    int         EmbedLine_3 = 45 - 1;

    double      PXQEMBD; //43
    double      PYQEMBD; //43
    double      XEMBD; //44
    double      YEMBD; //44
    int         NSEMBD; //45
    double      PSEMBD; //45
    double      TMAXEMBD; //45
    int         ISHADOW;
    double      DSHADOW;
    int         IPHIRP;


    int EndLine = 49 - 1;  


    int NRun = 0;

    File_input(std::string InputDirectory_) : InputDirectory(InputDirectory_){};
    File_input(std::string InputDirectory_, int NRun_) : InputDirectory(InputDirectory_), NRun(NRun_){};
    File_input(){}

    void ReadFile();

   
 

   

    double fdtod(std::string &s);
    double csdtod(std::string &s);
    double csitoi(std::string &s);
    
    void FormatParameters();


    std::string GetAtomName(const std::string &Type, const int &AtomicWeight, const int &AtomicNumber, bool fullname = false);
   

    std::string GetProjectileName(bool include_ia = false);
    std::string GetTargetName(bool include_ia = false);
    
    void Print();
    

    void FormatParametersSummary();

    void WriteSummary(std::string Filename);

    void WriteTabSeperated(std::string Filename);

    void ReadSummary(std::string Filename);

    void PrintTabSeperated();

    
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


};

File_input * Combine_file_input(int NRun, int NBatchMin, int NBatchMax, std::string Directory);

File_input * Read_file_input(int NRun, std::string Directory);
}

#endif