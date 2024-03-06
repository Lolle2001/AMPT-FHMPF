#ifndef AMPT_AMPT_HPP
#define AMPT_AMPT_HPP

// User header files
#include "AMPT_statistics.hpp"
#include "AMPT_particleproperties.hpp"
#include "AMPT_data.hpp"
#include "AMPT_fourierflow.hpp"
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

// Default naming
#define DEFAULT_SPECIFIER_CENTRALITY "centrality"
#define DEFAULT_SPECIFIER_PARTICIPATION "participation"
#define DEFAULT_DIRECTORY "processed"

#define DEFAULT_EXTENSION_SETTINGS "dat"
#define DEFAULT_EXTENSION_HISTOGRAM "hist"
#define DEFAULT_EXTENSION_LIST "dat"

#define DEFAULT_NAME_ANISOTROPICFLOW "anisotropicflow"
#define DEFAULT_NAME_TRANSVERSEMOMENTUM "transversemomentum"
#define DEFAULT_NAME_YIELD "yield"
#define DEFAULT_NAME_SETTINGS "settings"
#define DEFAULT_NAME_EVENTINFO "eventinfo"

using PP = AMPT::Functions::PretyPrint;

// u is an abbreviation that the type is a user alias.
using Clock_u     = std::chrono::high_resolution_clock;
using TimePoint_u = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace AMPT {

class File_ampt {
        private:
        
        public:
        std::string FileDirectory;
        std::vector<Block_ampt> EventBlocks;

        // std::vector<double> momentum_edges         = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0};
       
        // Subevent Statistics -> Statistics::EllipticFlow
        std::vector<double> centrality_edges       = {0, 1.57, 2.22, 2.71, 3.13, 3.5, 4.94, 6.05, 6.98, 7.81, 8.55, 9.23, 9.88, 10.47, 11.04, 11.58, 12.09, 12.58, 13.05, 13.52, 13.97, 14.43, 14.96, 15.67, 20};
        // Event Statistics -> Statistics
        std::vector<double> centrality_percentages = {0, 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
        // Event Statistics -> Statistics
        std::vector<double> participation_edges    = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420};
        // Event Statistics -> Statistics
        std::vector<int> centrality_event_counter;

        // int momentum_nbins      = 0;
        int centrality_nbins    = 0;
        int participation_nbins = 0;
        // int participation_nbins = 0;

        // double pseudorapidity_max = 1.0;
        // double pseudorapidity_min = -1.0;


        // std::vector<std::map<int, StatisticsContainer>>              EllipticFlow_event;
        // std::vector<std::map<int, std::vector<StatisticsContainer>>> EllipticFlow_event_momentum_map_vector;
        // std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_event_momentum_vector_map;
        // std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_event_pseudorapidity;
        
        // std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_centrality_momentum;
        // std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_centrality_pseudorapidity;
        
        Statistics::Statistics Statistics;
        // Statistics::Statistics 
        int NumberOfEvents         = 0;
        int ExpectedNumberOfEvents = 0;

        

        File_ampt(std::string FileDirectory_) : FileDirectory(FileDirectory_) {
            InitializeBins();
        };
        File_ampt(std::string FileDirectory_, unsigned int ExpectedNumberOfEvents_) : FileDirectory(FileDirectory_), ExpectedNumberOfEvents(ExpectedNumberOfEvents_){
            EventBlocks.reserve(ExpectedNumberOfEvents_);
            InitializeBins();
        };
       
        File_ampt(){
            InitializeBins();
        };

        void InitializeBins();

      

        void Parse2();


        void Convert();

        void WriteEventInfo(std::string Filename);

         void WriteEllipticFlow(std::string Filename);

        void WriteFourierFlow(std::string Filename, int n);

        void WriteYield(std::string Filename);

        void WriteTransverseMomentum(std::string Filename);

        void WriteSettings(std::string Filename);

        void ReadSettings(std::string Filename);

        void ReadFourierFlow(std::string Directory, int n);

        void ReadEllipticFlow(std::string Directory);

        void ReadTransverseMomentum(std::string Directory);

        void ReadYield(std::string Directory);

        void ReadEventInfo(std::string Directory);

        void PrintEventInfo();

        void operator+=(File_ampt const & obj);

        

};

File_ampt * Combine_ampt_multi_queued(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads);
File_ampt * Combine_ampt_multi_queued_omp(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads);

AMPT::File_ampt * ReadAMPT(int NRun, std::string Directory);


}


#endif