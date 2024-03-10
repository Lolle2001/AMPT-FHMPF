#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
#include "ParticleProperties.hpp"
#include "HistogramMap.hpp"
#include "Histogram1D.hpp"
#include "Histogram3D.hpp"
#include "AMPT_data.hpp"
#include <string>

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
#define DEFAULT_NAME_CENTRALITYINFO "centralityinfo"

namespace AMPT {
    namespace Statistics {

        // Optimization: instead of outputting multiple count files or storing multiple counts,
        // it might be better to just store the total and totalsqr of every observable and then store
        // one time the count. But be careful as sometimes v[i] is undefined and this could cause 
        // a difference between file format.
        class Data_ampt {
            private:

            // std::vector<Block_ampt> EventBlocks;
            // std::vector<

            HistogramMap3D AnisotropicFlow[6];
            HistogramMap3D Yield;
            HistogramMap3D TransverseMomentum;

            Histogram1D Centrality;


            std::vector<Block_ampt> EventBlocks;
            int NumberOfBlocks = 0;
            // HistogramMap3D Rapidity;
            // HistogramMap3D PseudoRapidity;
            
            
            std::vector<double> centrality_edges       = {0, 1.57, 2.22, 2.71, 3.13, 3.5, 4.94, 6.05, 6.98, 7.81, 8.55, 9.23, 9.88, 10.47, 11.04, 11.58, 12.09, 12.58, 13.05, 13.52, 13.97, 14.43, 14.96, 15.67, 20};
            std::vector<double> participation_edges    = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420};

            std::vector<double> momentum_edges         = {0, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20};
            std::vector<double> rapidity_edges         = { -10, -2.5, -1.0, -0.8, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.8, 1.0, 2.5, 10};
            std::vector<double> pseudorapidity_edges   = { -10, -2.5, -1.0, -0.8, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.8, 1.0, 2.5, 10};
            
            std::vector<double> momentum_edges_flow         = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.25, 1.5, 1.75, 2.0, 2.25, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 8.0, 10.0};
            std::vector<double> rapidity_edges_flow         = { -10, -2.5, -1.0, -0.8, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.8, 1.0, 2.5, 10};
            std::vector<double> pseudorapidity_edges_flow   = { -10, -2.5, -1.0, -0.8, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.8, 1.0, 2.5, 10};



            std::map<std::string, std::unique_ptr<Histogram1D>> centrality_custom;
            std::map<std::string, std::vector<double>> centrality_edges_custom;
            std::map<std::string, std::vector<double>> rapidity_edges_custom;
            std::map<std::string, std::vector<double>> momentum_edges_custom;


            std::map<std::string, std::unique_ptr<Histogram3D>> histograms_custom;

            std::map<std::string, std::string> filenames_custom;



            
            int nharmonic_min = 1;
            int nharmonic_max = 5;

            

            public:

            Data_ampt(std::string SettingsDirectory);

            Data_ampt(int nharmonic_min_, int nharmonic_max_);

            Data_ampt();

            // void ReadBinEdges(std::string SettingsDirectory);

            void InitializeHistograms();

            void SetupCustomHistograms();

            // void AddEvent(Block_ampt & block);

            void AddParticle(double & b, Line_ampt & line);

            void AddParticleCustom(double & b, Line_ampt & line);

            void AddEvent(Block_ampt & block);

            void AddEventCustom(Block_ampt & block);

            void WriteData(std::string directory);

            void WriteSettings(std::string directory);

            void WriteEventData(std::string directory);

            void WriteDataCustom(std::string directory);


            void ReserveEventBlocks(int reservesize);
            void ShrinkEventBlocks();

            void AddCustom(Data_ampt  const & obj);

            void operator+=(Data_ampt const & obj);
            
         
            
        };


    }
}

#endif