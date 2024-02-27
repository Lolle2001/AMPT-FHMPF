#ifndef AMPT_AMPT_OLD_HPP
#define AMPT_AMPT_OLD_HPP


// #include "AMPT_data.hpp"
#include "AMPT_statistics.hpp"
#include "AMPT_particleproperties.hpp"
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


struct Line_ampt {
    int    ParticlePythiaID;
    double MomX            ;
    double MomY            ;
    double MomZ            ;
    double Mass            ;
    double PosX            ;
    double PosY            ;
    double PosZ            ;
    double FreezeOutTime   ;

    double TransverseMomentum;
    double TransverseMomentumSQR;
    double Momentum;
    double MomentumSQR;
    double Energy;
    double TransverseMass;
    double EllipticFlow;
    double PseudoRapidity;
    double Rapidity;

    Line_ampt(){};
    Line_ampt(
        int   ParticlePythiaID_,
        double MomX_,            
        double MomY_,            
        double MomZ_,            
        double Mass_,            
        double PosX_,            
        double PosY_,            
        double PosZ_,            
        double FreezeOutTime_
        ) : ParticlePythiaID(ParticlePythiaID_),
            MomX(MomX_),
            MomY(MomY_),
            MomZ(MomZ_),
            Mass(Mass_),
            PosX(PosX_),
            PosY(PosY_),
            PosZ(PosZ_),
            FreezeOutTime(FreezeOutTime_){};
    
    friend std::istream& operator>>(std::istream& input, Line_ampt& obj){
        input 
        >> obj.ParticlePythiaID
        >> obj.MomX
        >> obj.MomY
        >> obj.MomZ
        >> obj.Mass
        >> obj.PosX
        >> obj.PosY
        >> obj.PosZ
        >> obj.FreezeOutTime;
        
        return input;
    }
    void GetTransverseMomentum(){
        TransverseMomentumSQR = MomX*MomX + MomY*MomY;
        TransverseMomentum = std::sqrt(TransverseMomentumSQR);
    }
    void GetEllipticFlow(){
        EllipticFlow = (MomX*MomX - MomY*MomY)/TransverseMomentumSQR;
    }
    void GetTransverseMass(){
        TransverseMass = std::sqrt(Mass * Mass + TransverseMomentumSQR);
    }

    void GetPseudoRapidity(){
        MomentumSQR = TransverseMomentumSQR + MomZ * MomZ;
        Momentum = std::sqrt(MomentumSQR);
        PseudoRapidity = std::atanh(MomZ/Momentum);
    }

    void GetRapidity(){
        Energy = std::sqrt(Mass * Mass + MomentumSQR);
        Rapidity = 0.5 * std::log((Energy + MomZ)/(Energy - MomZ));
    }

    void CalculateProperties(){
        GetTransverseMomentum();
        GetEllipticFlow();
        GetTransverseMass();
        GetPseudoRapidity();
        GetRapidity();
    }
};

double GetEllipticFlow(Line_ampt & line){
    return (line.MomX*line.MomX - line.MomY*line.MomY)/(line.MomX * line.MomX + line.MomY * line.MomY);
}

struct Block_ampt  {   
    int    EventID;
    int    EventIterationFlag;
    int    NumberOfParticles; // Hadrons and Deuterons
    double ImpactParameter;
    int    NumberOfParticipantNucleons_PROJ;
    int    NumberOfParticipantNulceons_TARG;
    int    NumberOfParticipantNucleonsElastic_PROJ;
    int    NumberOfParticipantNucleonsInelastic_PROJ;
    int    NumberOfParticipantNucleonsElastic_TARG;
    int    NumberOfParticipantNucleonsInelastic_TARG;
    double PhiRP; // Written to file 16: ampt.dat


        




    Block_ampt( int    EventID_, int    EventIterationFlag_, int    NumberOfParticles_, double ImpactParameter_, 
            int    NumberOfParticipantNucleons_PROJ_, int    NumberOfParticipantNulceons_TARG_, 
            int    NumberOfParticipantNucleonsElastic_PROJ_, int    NumberOfParticipantNucleonsInelastic_PROJ_, 
            int    NumberOfParticipantNucleonsElastic_TARG_, int    NumberOfParticipantNucleonsInelastic_TARG_, double PhiRP_
            ) : 
            EventID(EventID_), EventIterationFlag(EventIterationFlag_), NumberOfParticles(NumberOfParticles_), ImpactParameter(ImpactParameter_), 
            NumberOfParticipantNucleons_PROJ(NumberOfParticipantNucleons_PROJ_), NumberOfParticipantNulceons_TARG(NumberOfParticipantNulceons_TARG_), 
            NumberOfParticipantNucleonsElastic_PROJ(NumberOfParticipantNucleonsElastic_PROJ_), 
            NumberOfParticipantNucleonsInelastic_PROJ(NumberOfParticipantNucleonsInelastic_PROJ_), 
            NumberOfParticipantNucleonsElastic_TARG(NumberOfParticipantNucleonsElastic_TARG_), 
            NumberOfParticipantNucleonsInelastic_TARG(NumberOfParticipantNucleonsInelastic_TARG_), 
            PhiRP(PhiRP_){};

        Block_ampt(){};

        friend std::istream& operator>>(std::istream& input, Block_ampt& obj){
            input 
            >> obj.EventID 
            >> obj.EventIterationFlag  
            >> obj.NumberOfParticles
            >> obj.ImpactParameter
            >> obj.NumberOfParticipantNucleons_PROJ
            >> obj.NumberOfParticipantNulceons_TARG
            >> obj.NumberOfParticipantNucleonsElastic_PROJ
            >> obj.NumberOfParticipantNucleonsInelastic_PROJ
            >> obj.NumberOfParticipantNucleonsElastic_TARG
            >> obj.NumberOfParticipantNucleonsInelastic_TARG
            >> obj.PhiRP; 
            return input;
        }

        void PrintHeader(std::ostream & output){
            output << "\033[1;97;48m" << std::setw(9) << std::left << "Event ID"            << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(16) << std::left << "Event Iteration"     << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(20) << std::left << "Number of Particles" << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(17) << std::left << "Impact Parameter"    << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(10) << std::left << "NOPN_PROJ"           << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(10) << std::left << "NOPN_TARG"           << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(13) << std::left << "NOPN_EL_PROJ"        << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(13) << std::left << "NOPN_IN_PROJ"        << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(13) << std::left << "NOPN_EL_TARG"        << " | " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(13) << std::left << "NOPN_IN_TARG"        << " |  " << "\033[0m";
            output << "\033[1;97;48m" << std::setw(6)  << std::left << "PhiRP"                << " | " << "\033[0m";
            output << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& output, Block_ampt& obj){
            output <<  std::setw(6)  << std::left << obj.EventID << " ";
            output <<  std::setw(3) << std::left << obj.EventIterationFlag  << " ";
            output <<  std::setw(9) << std::left << obj.NumberOfParticles<< " ";
            output << std::scientific << std::setw(13) << std::left << obj.ImpactParameter<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleons_PROJ<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNulceons_TARG<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_PROJ<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_PROJ<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_TARG<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_TARG<< " ";
            output << std::scientific << std::setw(13)  << std::left << obj.PhiRP << " ";
            return output;
        }
};




class File_ampt {
        public:
        std::string FileDirectory;
        std::vector<Block_ampt> EventBlocks;

        // std::vector<double> momentum_edges         = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0};
        std::vector<double> momentum_edges = {0., 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0};
        // Subevent Statistics -> Statistics::EllipticFlow
        std::vector<double> centrality_edges       = {0, 1.57, 2.22, 2.71, 3.13, 3.5, 4.94, 6.05, 6.98, 7.81, 8.55, 9.23, 9.88, 10.47, 11.04, 11.58, 12.09, 12.58, 13.05, 13.52, 13.97, 14.43, 14.96, 15.67, 20};
        // Event Statistics -> Statistics
        std::vector<double> centrality_percentages = {0, 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
        // Event Statistics -> Statistics
        std::vector<double> participation_edges    = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420};
        // Event Statistics -> Statistics

        int momentum_nbins      = 0;
        int centrality_nbins    = 0;
        int participation_nbins = 0;

        double pseudorapidity_max = 1.0;
        double pseudorapidity_min = -1.0;


        std::vector<std::map<int, StatisticsContainer>>              EllipticFlow_event;
        std::vector<std::map<int, std::vector<StatisticsContainer>>> EllipticFlow_event_momentum_map_vector;
        std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_event_momentum_vector_map;
        std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_event_pseudorapidity;
        
        std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_centrality_momentum;
        std::vector<std::vector<std::map<int, StatisticsContainer>>> EllipticFlow_centrality_pseudorapidity;
        
        
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
            momentum_nbins      = momentum_edges     .size() - 1;
            centrality_nbins    = centrality_edges   .size() - 1;
            participation_nbins = participation_edges.size() - 1;
        }

        void Parse(){//std::map<std::string, Statistics *> & statistics){
            std::ifstream File;
            File.open(FileDirectory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
                Line_ampt TempLine;
                // TempBlock.PrintHeader(std::cout);
                int BlockCounter = TempBlock.EventID - 1;
                while(File >> TempBlock){
                    EventBlocks.emplace_back(TempBlock);
                    std::map<int, StatisticsContainer> TempEllipticFlow_event;
                    std::vector<std::map< int, StatisticsContainer>> TempEllipticFlow_event_momentum(momentum_nbins);
                    for(int i = 0; i < TempBlock.NumberOfParticles; ++i){
                        File >> TempLine;
                        TempLine.CalculateProperties();
                        
                        if(TempLine.EllipticFlow==TempLine.EllipticFlow){ // No diverging elliptic flow included
                        // std::cout << momentum_nbins << std::endl;
                            for(int j = 0; j < momentum_nbins; ++j){
                                if(TempLine.TransverseMomentum >= momentum_edges[j] && TempLine.TransverseMomentum < momentum_edges[j + 1] && TempLine.PseudoRapidity > pseudorapidity_min && TempLine.PseudoRapidity < pseudorapidity_max){
                                    TempEllipticFlow_event_momentum[j][TempLine.ParticlePythiaID].Add(TempLine.EllipticFlow);
                                    // std::cout << "check" << std::endl;
                                }
                            }
                        }
                    }
                    EllipticFlow_event_momentum_vector_map.emplace_back(TempEllipticFlow_event_momentum);
                    TempEllipticFlow_event_momentum.clear();
                    // std::cout << TempBlock << std::endl;;
                }
               
                EventBlocks.shrink_to_fit();
                NumberOfEvents = EventBlocks.size();
            }
            else{
                std::cout << "Error: Could not open file " << FileDirectory << std::endl;
            }
            File.close();
        }

        // void SaveStatistics(){
            // std::unique_ptr<TFile
        // }
        void Write(std::string Directory){
            std::ofstream File;
            // std::cout << NumberOfEvents << std::endl;
            File.open(Directory.c_str(), std::ios::out);
            // std::ofstream File = std::cout;
            File << NumberOfEvents << std::endl;
            for(int i = 0; i < NumberOfEvents; ++i){
                File << EventBlocks[i] << std::endl;
                File << EllipticFlow_event_momentum_map_vector[i].size() << std::endl;
                for(auto Entry: EllipticFlow_event_momentum_map_vector[i]){
                    File << std::right << std::setw(6) << Entry.first << " ";
                    for(int j = 0; j < momentum_nbins; ++j){
                        Entry.second[j].CalculateStatistics();
                        File << std::scientific << std::right << std::setw(13) << Entry.second[j].Total << " ";
                        File << std::scientific << std::right << std::setw(13) << Entry.second[j].TotalSQR << " ";
                        File << std::scientific << std::right << std::setw(9) << Entry.second[j].EntryCount << " ";
                    }
                    File << std::endl;
                }
               
            }
            File.close();
        }

        void Read(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
                std::vector<StatisticsContainer> TempVector(momentum_nbins);
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                File >> NumberOfEvents;
                EventBlocks.resize(NumberOfEvents);
                EllipticFlow_event_momentum_map_vector.resize(NumberOfEvents);
                for(int i = 0; i < NumberOfEvents; ++i){
                    File >> TempBlock;
                    File >> TempMapSize;
                    // std::cout << TempBlock << std::endl;
                    // std::cout << TempMapSize << std::endl;
                    for(int j = 0; j < TempMapSize; ++j){
                        getline(File >> std::ws, line); // remove leading whitesapce? 
                        // std::cout << line << std::endl;
                        std::istringstream iss(line);
                        // while(iss >> value){
                        //     std::cout << value << std::endl;
                        // }
                        iss >> TempID;

                        TempVector.resize(momentum_nbins);
                        for(int k = 0; k < momentum_nbins; ++k){
                            iss >> TempVector[k].Total;
                            iss >> TempVector[k].TotalSQR;
                            iss >> TempVector[k].EntryCount;
                        }
                      
                        EllipticFlow_event_momentum_map_vector[i][TempID] = TempVector;
                        // TempVector.clear();
                    }
                    EventBlocks[i] = TempBlock;
                }
                // std::cout << "here" << std::endl;

            }
            File.close();
        }
    

        void Convert(){
            EllipticFlow_event_momentum_map_vector.resize(NumberOfEvents);
            for(int i = 0; i < NumberOfEvents; ++i){
                for(int j = 0; j < momentum_nbins; ++j){
                    for(auto Entry: EllipticFlow_event_momentum_vector_map[i][j]){
                        if(EllipticFlow_event_momentum_map_vector[i].count(Entry.first) == 0){
                            EllipticFlow_event_momentum_map_vector[i][Entry.first].resize(momentum_nbins);
                            EllipticFlow_event_momentum_map_vector[i][Entry.first][j] = Entry.second;
                        }
                        else{
                            
                            EllipticFlow_event_momentum_map_vector[i][Entry.first][j] += Entry.second;
                        }
                        // std::cout << Entry.second << std::endl;
                        
                    }
                }
            }
        }

        std::vector<std::vector<StatisticsContainer>> Combine(){
            std::vector<std::vector<StatisticsContainer>> FlowMap(centrality_nbins);
            for(int k = 0; k < centrality_nbins; ++k){
                FlowMap[k].resize(momentum_nbins);
            }
            
            for(int i = 0; i < NumberOfEvents; ++i){
                
                for(int k = 0; k < centrality_nbins; ++k){
                    
                    if(EventBlocks[i].ImpactParameter >= centrality_edges[k] && EventBlocks[i].ImpactParameter < centrality_edges[k+1]){
                        for(auto Entry: EllipticFlow_event_momentum_map_vector[i]){
                            for(int j = 0; j < momentum_nbins; ++j){
                            
                                if(ChargeMap[Entry.first]!=0){
                                    FlowMap[k][j] += Entry.second[j];
                                }
                            }
                            
                        }
                    }
                }
                
                
            }
            return FlowMap;

        }

      
        std::vector<StatisticsContainer> Combine2(){
            std::vector<StatisticsContainer> FlowMap(centrality_nbins);
         
            for(int i = 0; i < NumberOfEvents; ++i){
                
                for(int k = 0; k < centrality_nbins; ++k){
                    
                    if(EventBlocks[i].ImpactParameter >= centrality_edges[k] && EventBlocks[i].ImpactParameter < centrality_edges[k+1]){
                        for(auto Entry: EllipticFlow_event_momentum_map_vector[i]){
                            for(int j = 0; j < momentum_nbins; ++j){
                            
                                if(ChargeMap[Entry.first]!=0){
                                    FlowMap[k] += Entry.second[j];
                                }
                            }
                            
                        }
                    }
                }
                
                
            }
            return FlowMap;

        }

        std::vector<StatisticsContainer> Combine2(std::vector<std::vector<int>> & CentralityRange){
            std::vector<StatisticsContainer> FlowMap(CentralityRange.size());
            
            
            for(int i = 0; i < NumberOfEvents; ++i){
                
                for(int k = 0; k < CentralityRange.size(); ++k){
                    
                    if(EventBlocks[i].ImpactParameter >= centrality_edges[CentralityRange[0][0]] && EventBlocks[i].ImpactParameter < centrality_edges[CentralityRange[0][1]]){
                        for(auto Entry: EllipticFlow_event_momentum_map_vector[i]){
                            for(int j = 0; j < momentum_nbins; ++j){
                            
                                if(ChargeMap[Entry.first]!=0){
                                    FlowMap[k] += Entry.second[j];
                                }
                            }
                            
                        }
                    }
                }
                
                
            }
            return FlowMap;

        }

        std::vector<std::vector<StatisticsContainer>> Combine4(std::vector<std::vector<int>> & CentralityRange){
            std::vector<std::vector<StatisticsContainer>> FlowMap(CentralityRange.size());
            for(int k = 0; k < CentralityRange.size(); ++k){
                FlowMap[k].resize(momentum_nbins);
            }
            
            for(int i = 0; i < NumberOfEvents; ++i){
                
                for(int k = 0; k < CentralityRange.size(); ++k){
                    
                    if(EventBlocks[i].ImpactParameter >= centrality_edges[CentralityRange[k][0]] && EventBlocks[i].ImpactParameter < centrality_edges[CentralityRange[k][1]]){
                        for(auto Entry: EllipticFlow_event_momentum_map_vector[i]){
                            for(int j = 0; j < momentum_nbins; ++j){
                            
                                if(ChargeMap[Entry.first]!=0){
                                    FlowMap[k][j] += Entry.second[j];
                                }
                            }
                            
                        }
                    }
                }
                
                
            }
            return FlowMap;

        }


        

       
        void operator+=(File_ampt const & obj){
            AMPT::Functions::Concatenate(EventBlocks, obj.EventBlocks);
            AMPT::Functions::Concatenate(EllipticFlow_event_momentum_map_vector, obj.EllipticFlow_event_momentum_map_vector);
            AMPT::Functions::Concatenate(EllipticFlow_event_momentum_vector_map, obj.EllipticFlow_event_momentum_vector_map);
            NumberOfEvents += obj.NumberOfEvents;
            int StartIndex = NumberOfEvents - obj.NumberOfEvents;
            for(int i = StartIndex; i < NumberOfEvents; ++i){
                EventBlocks[i].EventID += StartIndex;
            }

        }

        

};

File_ampt * Combine_ampt_multi_queued(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads){
    File_ampt * campt = new File_ampt();


    File_ampt * data[50];
    std::thread threads[50];
    

    double FileSize = 0;
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        FileSize += AMPT::Functions::GetFileSize(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", 3);
    }

    std::cout << "Total datasize to read: \033[1:97m" << std::setprecision(3) << FileSize << " GB\033[0m" << std::endl;

    
    for(int i = NBatchMin; i <= NBatchMax; ++i){    
        
        File_input * input = new File_input(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");  
        data[i] = new File_ampt(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", input -> NEVENT);
        threads[i] = std::thread(&File_ampt::Parse, data[i]);
        delete input;
    }

    int ThreadCounter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        ThreadCounter++;
        if(ThreadCounter == NumberOfThreads){
            for(int j = i - NumberOfThreads + 1; j <=i; j++){
                threads[j].join();
            }
            for(int j = i - NumberOfThreads + 1; j <= i; j++){
                // threads[j].join();
            
                std::cout << "Loaded data: \033[1:97m";
                std::cout << std::to_string(NRun) + "_" + std::to_string(j);
                std::cout << "\033[0m\t";
                std::cout << "Amount of events: \033[1:97m";
                std::cout << std::to_string(data[j] -> NumberOfEvents);
                std::cout << "\033[0m" << std::endl;
            }
            ThreadCounter = 0;
        }
    }
    for(int i = NBatchMax - ThreadCounter + 1; i <= NBatchMax; ++i){
        threads[i].join();
    }
    for(int i = NBatchMax - ThreadCounter + 1; i <= NBatchMax; ++i){
        std::cout << "Loaded data: \033[1:97m";
        std::cout << std::to_string(NRun) + "_" + std::to_string(i);
        std::cout << "\033[0m\t";
        std::cout << "Amount of events: \033[1:97m";
        std::cout << std::to_string(data[i] -> NumberOfEvents);
        std::cout << "\033[0m" << std::endl;
    
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto difference = stop - start;
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(difference);
    difference -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(difference);
    difference -= seconds;
    auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(difference);
    std::cout << "Reading Time [min:sec:milisec]: \033[1:97m" << minutes.count() << ":" << seconds.count() << ":" << miliseconds.count() << "\033[0m"<< std::endl;
    for(int i = NBatchMin; i <= NBatchMax; ++i){      
        *campt += *data[i];   
        delete data[i];
    }
    return campt;

}


}


#endif