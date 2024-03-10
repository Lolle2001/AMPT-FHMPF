#ifndef AMPT_AMPT_HPP
#define AMPT_AMPT_HPP

// User header files
#include "Data.hpp"
// #include "AMPT_particleproperties.hpp"
#include "AMPT_data.hpp"
// #include "AMPT_fourierflow.hpp"
#include "AMPT_functions.hpp"
#include "AMPT_input.hpp"

// Standard header files
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <cmath>
#include <omp.h>
#include <chrono>
#include <sstream>



using PP = AMPT::Functions::PretyPrint;

// u is an abbreviation that the type is a user alias.
using Clock_u = std::chrono::high_resolution_clock;
using TimePoint_u = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace AMPT
{

    class File_ampt
    {
    private:
    public:
        std::string FileDirectory;
        Statistics::Data_ampt Data;

        int ExpectedNumberOfEvents = 0;

        File_ampt(std::string FileDirectory_) : FileDirectory(FileDirectory_)
        {
            InitializeBins();
        };
        File_ampt(std::string FileDirectory_, unsigned int ExpectedNumberOfEvents_) : FileDirectory(FileDirectory_)
        {
            Data.ReserveEventBlocks(ExpectedNumberOfEvents_);
            InitializeBins();
        };

        File_ampt()
        {
            InitializeBins();
        };

        void InitializeBins();

        void Parse();

        // void Convert();

        // void WriteEventInfo(std::string Filename);

        // void WriteEllipticFlow(std::string Filename);

        // void WriteFourierFlow(std::string Filename, int n);

        // void WriteYield(std::string Filename);

        // void WriteTransverseMomentum(std::string Filename);

        // void WriteSettings(std::string Filename);

        // void ReadSettings(std::string Filename);

        // void ReadFourierFlow(std::string Directory, int n);

        // void ReadEllipticFlow(std::string Directory);

        // void ReadTransverseMomentum(std::string Directory);

        // void ReadYield(std::string Directory);

        // void ReadEventInfo(std::string Directory);

    

        void operator+=(File_ampt const &obj);
    };

    
    File_ampt *CombineAMPT(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads);

    AMPT::File_ampt *ReadAMPT(int NRun, std::string Directory);

}

#endif