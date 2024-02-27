#ifndef AMPT_AMPT_HPP
#define AMPT_AMPT_HPP


// #include "AMPT_data.hpp"
#include "AMPT_statistics.hpp"
#include "AMPT_particleproperties.hpp"
#include "AMPT_data.hpp"
#include "AMPT_fourierflow.hpp"
#include "AMPT_functions.hpp"
#include "AMPT_input.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <cmath>
#include <chrono>
#include <sstream>

namespace AMPT {

using PP = AMPT::Functions::PretyPrint;

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

        void InitializeBins(){
          centrality_nbins = centrality_edges.size() - 1;
          centrality_event_counter.resize(centrality_nbins, 0);
          participation_nbins = participation_edges.size() - 1;
          Statistics.Initialize(centrality_nbins);
        }

        void Parse(){
            std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
            std::cout << "Parsing data from: " << FileDirectory << std::endl;
            // std::cout << "File size        : " << "\033[1:37m" << std::fixed << std::setprecision(3) << AMPT::Functions::GetFileSize(FileDirectory, 2) << " MB" << PP::end  << std::endl;;
            // std::cout << "Number of events : " << "\033[1:37m" << ExpectedNumberOfEvents <<  PP::end << std::endl;
            std::ifstream File;
            File.open(FileDirectory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
                Line_ampt TempLine;
                // std::vector<std::vector<std::map<int, StatisticsContainer>>> TempMap(Statistics.momentum_nbins);
                // for(auto entry : TempMap){
                //     entry.resize(Statistics.pseudorapidity_nbins);
                // }
                

                while(File >> TempBlock){
                    EventBlocks.emplace_back(TempBlock);
                    for(int b = 0; b < centrality_nbins; ++b){
                        if(TempBlock.ImpactParameter >= centrality_edges[b] && TempBlock.ImpactParameter < centrality_edges[b+1]){
                            centrality_event_counter[b] += 1;
                            // std::cout << b << " " << centrality_event_counter[b] << std::endl;
             
                            for(int i = 0; i < TempBlock.NumberOfParticles; ++i){
                                File >> TempLine;
                                TempLine.CalculateProperties();
                                Statistics.Add(b, TempLine);//, TempMap);
                                
                            }
                        }
                    }
                }
                EventBlocks.shrink_to_fit();
                NumberOfEvents = EventBlocks.size();
                std::cout << PP::finished << "[AMPT::File_ampt]" <<PP::end << " ";
                std::cout << "Parsed data from: " << FileDirectory << std::endl;
               
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << FileDirectory << std::endl;
            }
            File.close();
        }
        void Convert(){
            Statistics.Convert();
        }

        void WriteEventInfo(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            if(File.is_open()){
                File << NumberOfEvents << std::endl;
                
                for(int i = 0; i < NumberOfEvents; ++i){
                    File << EventBlocks[i] << std::endl;
                    // AMPT::Functions::printProgressBar(i, NumberOfEvents - 1);
                }
                // std::cout << std::endl;
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written event data to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "KB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

         void WriteEllipticFlow(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.EllipticFlow.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written flow data to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout  << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "MB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void WriteFourierFlow(std::string Filename, int n){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.v[n].Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written flow data to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout  << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "MB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void WriteYield(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.ParticleYield.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written yield data to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout  << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "MB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            // AMPT::Functions::PrintTiming(start, stop, Filename);
        }

        void WriteTransverseMomentum(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.TransverseMomentum.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written transverse momentum data to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout  << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "KB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void WriteSettings(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            if(File.is_open()){
                File << centrality_nbins << std::endl;
                for(int i = 0; i <= centrality_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << centrality_edges[i] << " ";
                }
                File << std::endl;
                File << participation_nbins << std::endl;
                for(int i = 0; i <= participation_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << participation_edges[i] << " ";
                }
                File << std::endl;
                File << Statistics.momentum_nbins << std::endl;
                for(int i = 0; i <=  Statistics.momentum_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << Statistics.momentum_edges[i] << " ";
                }
                File << std::endl;
                File << Statistics.pseudorapidity_nbins << std::endl;
                for(int i = 0; i <=  Statistics.pseudorapidity_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << Statistics.pseudorapidity_edges[i] << " ";
                }
                File << std::endl;
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Written settings to" << " " ;
                std::cout << PP::highlight << "[";
                std::cout  << std::fixed << std::setprecision(3) << std::right << Filesize; 
                std::cout << "KB]" << PP::end << ": " << Filename;
                std::cout << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
            
        }

        void ReadSettings(std::string Filename){
            std::ifstream File;
            File.open(Filename.c_str(), std::ios::in);

            if(File.is_open()){
                std::string line;
                std::stringstream ss;
                File >> centrality_nbins;
                centrality_edges.resize(centrality_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= centrality_nbins; i++){
                    ss >> centrality_edges[i];
                }
                File >> participation_nbins;
                participation_edges.resize(participation_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= participation_nbins; i++){
                    ss >> participation_edges[i];
                }
                File >> Statistics.momentum_nbins;
                Statistics.momentum_edges.resize(Statistics.momentum_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= Statistics.momentum_nbins; i++){
                    ss >> Statistics.momentum_edges[i];
                }
                File >> Statistics.pseudorapidity_nbins;
                Statistics.pseudorapidity_edges.resize(Statistics.pseudorapidity_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= Statistics.pseudorapidity_nbins; i++){
                    ss >> Statistics.pseudorapidity_edges[i];
                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read settings from: " << Filename << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Filename << std::endl;
            }
        }

        void ReadFourierFlow(std::string Directory, int n){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.v[n].Read(File, i, TempMapSize);
                    

                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read flow data from: " << Directory << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Directory << std::endl;
            }
            File.close();
        }

         void ReadEllipticFlow(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    // std::cout << centrality_event_counter[i] << std::endl;
                    File >> TempMapSize;

                    Statistics.EllipticFlow.Read(File, i, TempMapSize);
                    

                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read flow data from: " << Directory << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Directory << std::endl;
            }
            File.close();
        }

        void ReadTransverseMomentum(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.TransverseMomentum.Read(File, i, TempMapSize);
                    

                }
  
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read transverse momentum data from: " << Directory << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Directory << std::endl;
            }
            File.close();
        }

        void ReadYield(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.ParticleYield.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.ParticleYield.Read(File, i, TempMapSize);

                }
  

             std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read yield data from: " << Directory << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Directory << std::endl;
            }
            File.close();
        }

        void ReadEventInfo(std::string Directory){
            std::ifstream File;
            
            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                File >> NumberOfEvents;
                
                EventBlocks.resize(NumberOfEvents);
                for(int i = 0; i < NumberOfEvents; ++i){
                    // std::cout << i << std::endl;
                    File >> EventBlocks[i];
                    // std::cout << EventBlocks[i] << std::endl;
                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read event data from: " << Directory << std::endl;
            }
            else{
                std::cout <<  PP::warning << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Cannot open file: " << Directory << std::endl;
            }
            File.close();
        }


        void PrintEventInfo(){
            
            for(int i = 0; i < NumberOfEvents; ++i){
                std::cout << EventBlocks[i] << std::endl;
            }
        }

        

       
        void operator+=(File_ampt const & obj){
            AMPT::Functions::Concatenate(EventBlocks, obj.EventBlocks);
            // AMPT::Functions::Concatenate(EllipticFlow_event_momentum_map_vector, obj.EllipticFlow_event_momentum_map_vector);
            // AMPT::Functions::Concatenate(EllipticFlow_event_momentum_vector_map, obj.EllipticFlow_event_momentum_vector_map);
            Statistics += obj.Statistics;
            for(int b = 0 ; b < centrality_nbins; ++b){
                centrality_event_counter[b] += obj.centrality_event_counter[b];
            }
            NumberOfEvents += obj.NumberOfEvents;
            int StartIndex = NumberOfEvents - obj.NumberOfEvents;
            for(int i = StartIndex; i < NumberOfEvents; ++i){
                EventBlocks[i].EventID += StartIndex;
            }

        }

        

};

File_ampt * Combine_ampt_multi_queued(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads){
    
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading data from run (size): " << NRun << "(" << NBatchMax - NBatchMin + 1 << ")" << std::endl; 
    
    
    File_ampt * campt = new File_ampt();


    File_ampt * data[50];
    std::thread threads[50];
    

    double FileSize = 0;
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        FileSize += AMPT::Functions::GetFileSize(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", 3);
    }

    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Total datasize to read: ";
    std::cout << PP::highlight << std::fixed << std::setprecision(3) << FileSize << " GB" << PP::end << std::endl;
    int TotalNevent = 0;

    int nevent[50];
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        File_input * input = new File_input(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");  
        input -> ReadFile();
        TotalNevent += input -> NEVENT;
        nevent[i] = input -> NEVENT;
        delete input;
    }
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Total number of events to parse: " <<PP::highlight << TotalNevent << PP::end << std::endl;
    
    for(int i = NBatchMin; i <= NBatchMax; ++i){    
        
        
        // std::cout << input -> NEVENT << std::endl;
        data[i] = new File_ampt(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", nevent[i]);
        threads[i] = std::thread(&File_ampt::Parse, data[i]);
        
    }
    

    int ThreadCounter = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        ThreadCounter++;
        if(ThreadCounter == NumberOfThreads){
            for(int j = i - NumberOfThreads + 1; j <=i; j++){
                threads[j].join();
            }
           
            ThreadCounter = 0;
        }
    }
    for(int i = NBatchMax - ThreadCounter + 1; i <= NBatchMax; ++i){
        threads[i].join();
    }
   
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    for(int i = NBatchMin; i <= NBatchMax; ++i){      
        *campt += *data[i];   
        delete data[i];
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> start2 = std::chrono::high_resolution_clock::now();
    campt -> Convert();
    system(("mkdir -p \"" + Directory + std::to_string(NRun) + "/processed\"").c_str());
    campt -> WriteSettings(Directory + std::to_string(NRun)+ "/processed/ampt_settings.dat");
    for(int i = 0; i < 6; ++i){
         campt -> WriteFourierFlow(Directory + std::to_string(NRun)+ "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    }
    campt -> WriteEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    campt -> WriteTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    campt -> WriteYield(Directory + std::to_string(NRun)+ "/processed/ampt_particleyield_centrality.dat");
    campt -> WriteEventInfo(Directory + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    std::chrono::time_point<std::chrono::high_resolution_clock> stop2 = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration2(start2, stop2, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Writing time [m:s:ms]: " << PP::highlight << duration2.cminutes << ":" << std::setw(2) << std::setfill('0') << duration2.cseconds << ":" << std::setw(3) << std::setfill('0') << duration2.cmilliseconds << PP::end << std::endl;
    return campt;

}

AMPT::File_ampt * ReadAMPT(int NRun, std::string Directory){
    
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading processed data from run: " << NRun << std::endl; 
    
    AMPT::File_ampt * ampt = new AMPT::File_ampt();
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    ampt -> ReadSettings(Directory + std::to_string(NRun) + "/processed/ampt_settings.dat");
    ampt -> InitializeBins();
    for(int i = 0; i < 6; ++i){
        ampt -> ReadFourierFlow(Directory  + std::to_string(NRun) + "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    }
    ampt -> ReadEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    ampt -> ReadTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    
    ampt -> ReadYield(Directory + std::to_string(NRun) + "/processed/ampt_particleyield_centrality.dat");
    ampt -> ReadEventInfo(Directory  + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    return ampt;
}


}


#endif