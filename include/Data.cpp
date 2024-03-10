#include "Data.hpp"

namespace AMPT {
    namespace Statistics {

        void Data_ampt::SetupCustomHistograms(){

            centrality_edges_custom["1:PbPb"] = (std::vector<double>){0.00, 3.49, 4.93, 6.98, 8.55, 9.87, 11.00, 12.10,  13.10, 14.00, 14.90, 20.00};

            rapidity_edges_custom["1:p_pbar"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["1:p_pbar"]  = (std::vector<double>){0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 , 0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 , 1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 , 2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 , 5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20. };
            rapidity_edges_custom["1:K+_K-"]   = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["1:K+_K-"]   = (std::vector<double>){0.2 ,  0.25,  0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 , 0.65,  0.7 ,  0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 , 1.2 ,  1.3 ,  1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  , 2.2 ,  2.4 ,  2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 , 4.  ,  4.5 ,  5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };
            rapidity_edges_custom["1:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["1:pi+_pi-"] = (std::vector<double>){0.1 ,  0.12,  0.14,  0.16,  0.18,  0.2 ,  0.25,  0.3 ,  0.35, 0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 ,  0.75,  0.8 , 0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 ,  1.4 ,  1.5 , 1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 ,  2.6 ,  2.8 , 3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 ,  5.  ,  5.5 , 6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };
            rapidity_edges_custom["1:charged"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["1:charged"] = (std::vector<double>){0.1 ,  0.12,  0.14,  0.16,  0.18,  0.2 ,  0.25,  0.3 ,  0.35, 0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 ,  0.75,  0.8 , 0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 ,  1.4 ,  1.5 , 1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 ,  2.6 ,  2.8 , 3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 ,  5.  ,  5.5 , 6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };

            rapidity_edges_custom["2:p_pbar"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["2:p_pbar"]  = (std::vector<double>){0.5, 1. , 1.5, 2. , 2.5, 3. , 4. , 6. };
            rapidity_edges_custom["2:K+_K-"]   = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["2:K+_K-"]   = (std::vector<double>){0.3, 0.6, 1. , 1.5, 2. , 2.5, 3. , 4. , 6.  };
            rapidity_edges_custom["2:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["2:pi+_pi-"] = (std::vector<double>){0.2 ,  0.3 ,  0.4 ,  0.5 ,  0.6 ,  0.7 ,  0.8 ,  0.9 ,  1.  ,1.25,  1.5 ,  1.75,  2.  ,  2.25,  2.5 ,  3.  ,  3.5 ,  4.  ,5.  ,  6.  ,  8.  , 10.   };
            rapidity_edges_custom["2:charged"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["2:charged"] = (std::vector<double>){0.2 ,  0.3 ,  0.4 ,  0.5 ,  0.6 ,  0.7 ,  0.8 ,  0.9 ,  1.  , 1.25,  1.5 ,  1.75,  2.  ,  2.25,  2.5 ,  3.  ,  3.5 ,  4.  , 5.  ,  6.  ,  8.  , 10.   };


            rapidity_edges_custom["3:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["3:pi+_pi-"]  = (std::vector<double>){0.2 ,  0.25,  0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 , 0.65,  0.7 ,  0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 , 1.2 ,  1.3 ,  1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  , 2.2 ,  2.4 ,  2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 , 4.  ,  4.5 ,  5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };
            rapidity_edges_custom["4:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["4:pi+_pi-"]  = (std::vector<double>){0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 , 0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 , 1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 , 2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 , 5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20. };
            
            

            histograms_custom["1:p_pbar"]  = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["1:p_pbar"], rapidity_edges_custom["1:p_pbar"]);
            histograms_custom["1:K+_K-"]   = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["1:K+_K-"], rapidity_edges_custom["1:K+_K-"]);
            histograms_custom["1:pi+_pi-"] = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["1:pi+_pi-"], rapidity_edges_custom["1:pi+_pi-"]);
            histograms_custom["1:charged"] = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["1:charged"], rapidity_edges_custom["1:charged"]);

            histograms_custom["2:p_pbar"]  = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["2:p_pbar"], rapidity_edges_custom["2:p_pbar"]);
            histograms_custom["2:K+_K-"]   = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["2:K+_K-"], rapidity_edges_custom["2:K+_K-"]);
            histograms_custom["2:pi+_pi-"] = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["2:pi+_pi-"], rapidity_edges_custom["2:pi+_pi-"]);
            histograms_custom["2:charged"] = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["2:charged"], rapidity_edges_custom["2:charged"]);

            histograms_custom["3:pi+_pi-"]  = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["3:pi+_pi-"], rapidity_edges_custom["3:pi+_pi-"]);
            histograms_custom["4:pi+_pi-"]  = std::make_unique<Histogram3D>(centrality_edges_custom["1:PbPb"], momentum_edges_custom["4:pi+_pi-"], rapidity_edges_custom["4:pi+_pi-"]);

            centrality_custom["1:PbPb"] = std::make_unique<Histogram1D>(centrality_edges_custom["1:PbPb"]);


            filenames_custom["1:p_pbar"]  = "yield_2212_-2212";
            filenames_custom["1:K+_K-"]   = "yield_321_-321";
            filenames_custom["1:pi+_pi-"] = "yield_211_-211";
            filenames_custom["1:charged"] = "yield_charged";


            filenames_custom["2:p_pbar"]  = "v2_2212_-2212";
            filenames_custom["2:K+_K-"]   = "v2_321_-321";
            filenames_custom["2:pi+_pi-"] = "v2_211_-211";
            filenames_custom["2:charged"] = "v2_charged";

            filenames_custom["3:pi+_pi-"]  = "yield_321_211_-211";
            filenames_custom["4:pi+_pi-"]  = "yield_2212_211_-211";

            filenames_custom["1:PbPb"] = "centrality";

           
        }





        Data_ampt::Data_ampt(std::string SettingsDirectory){
            // ReadBinEdges(SettingsDirectory);
            InitializeHistograms();
        }
        Data_ampt::Data_ampt(int nharmonic_min_, int nharmonic_max_) : nharmonic_min(nharmonic_min_), nharmonic_max(nharmonic_max_){
            InitializeHistograms();
        }
        Data_ampt::Data_ampt(){
            InitializeHistograms();
        }
        void Data_ampt::ReserveEventBlocks(int reservesize){
            EventBlocks.reserve(reservesize);
        }

        void Data_ampt::ShrinkEventBlocks(){
            EventBlocks.shrink_to_fit();
            NumberOfBlocks = EventBlocks.size();
        }

        void Data_ampt::InitializeHistograms(){
            for(int iv = nharmonic_min; iv <= nharmonic_max; ++iv){
                AnisotropicFlow[iv] = HistogramMap3D(centrality_edges, momentum_edges_flow, rapidity_edges_flow);
            }
            Yield = HistogramMap3D(centrality_edges, momentum_edges, rapidity_edges);
            TransverseMomentum = HistogramMap3D(centrality_edges, momentum_edges, rapidity_edges);
            // Rapidity = HistogramMap3D(centrality_edges, momentum_edges, rapidity_edges);
            // PseudoRapidity = HistogramMap3D(centrality_edges, momentum_edges, rapidity_edges);
            Centrality = Histogram1D(centrality_edges);
            SetupCustomHistograms();
        }

        // void AddEvent()

         void Data_ampt::AddParticle(double & b, Line_ampt & line){
            for(int iv = nharmonic_min; iv <= nharmonic_max; ++iv){
                if(line.AnisotropicFlow[iv]==line.AnisotropicFlow[iv]){
                    AnisotropicFlow[iv].Add(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID, line.AnisotropicFlow[iv]);
                }
            }
            Yield.AddCurrent(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID,1);
            TransverseMomentum.Add(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID, line.TransverseMomentum);
            AddParticleCustom(b, line);
        }

        void Data_ampt::AddEvent(Block_ampt & block){
            EventBlocks.emplace_back(block);
            Centrality.Add(block.ImpactParameter,1);
            Yield.AddEvent();
            AddEventCustom(block);
        }

        void Data_ampt::AddParticleCustom(double & b, Line_ampt & line){
            // if(line.Rapidity > -0.5 && line.Rapidity < 0.5){
                if(line.ParticlePythiaID == 211 | line.ParticlePythiaID == -211){
                    histograms_custom["1:pi+_pi-"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["2:pi+_pi-"]->Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["3:pi+_pi-"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["4:pi+_pi-"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                }
                else if(line.ParticlePythiaID == 321 | line.ParticlePythiaID == -321){
                    histograms_custom["1:K+_K-"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["2:K+_K-"]->Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                }
                else if(line.ParticlePythiaID == 2212 | line.ParticlePythiaID == -2212){
                    histograms_custom["1:p_pbar"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["2:p_pbar"]->Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                }
                if(ChargeMap[line.ParticlePythiaID] != 0){
                    histograms_custom["1:charged"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["2:charged"]->Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                }
            // }
            
        }

        void Data_ampt::AddEventCustom(Block_ampt & block){

            centrality_custom["1:PbPb"]->Add(block.ImpactParameter, 1);
            histograms_custom["1:pi+_pi-"]->AddEvent();
            histograms_custom["1:K+_K-"]  ->AddEvent();
            histograms_custom["1:p_pbar"] ->AddEvent();
            histograms_custom["1:charged"]->AddEvent();
            histograms_custom["3:pi+_pi-"]->AddEvent();
            histograms_custom["4:pi+_pi-"]->AddEvent();
        }

        void Data_ampt::AddCustom( Data_ampt const & obj){
            for (const auto& entry : histograms_custom) {
                if (histograms_custom.find(entry.first) != histograms_custom.end() && 
                    obj.histograms_custom.find(entry.first) != obj.histograms_custom.end()) {
                    // Check if both histograms exist before attempting to add them
                    *histograms_custom.at(entry.first) += *obj.histograms_custom.at(entry.first);
                } else {
                    // Handle missing histogram case if necessary
                }
            }
            for (const auto& entry : centrality_custom) {
                if (centrality_custom.find(entry.first) != centrality_custom.end() &&
                    obj.centrality_custom.find(entry.first) != obj.centrality_custom.end()) {
                    // Check if both histograms exist before attempting to add them
                    *centrality_custom.at(entry.first) += *obj.centrality_custom.at(entry.first);
                } else {
                    // Handle missing histogram case if necessary
                }
            }
        }

        void Data_ampt::operator+=(Data_ampt const & obj){
            for(int iv = nharmonic_min; iv <= nharmonic_max; ++iv){
                AnisotropicFlow[iv] += obj.AnisotropicFlow[iv];
            }
            Yield += obj.Yield;
            TransverseMomentum += obj.TransverseMomentum;
            Centrality += obj.Centrality;
            // std::cout << EventBlocks.size() << std::endl;
            // std::cout << "here" << std::endl;
            AMPT::Functions::Concatenate(EventBlocks, obj.EventBlocks);
            // std::cout << "here" << std::endl;
            NumberOfBlocks += obj.NumberOfBlocks;
            int StartIndex = NumberOfBlocks - obj.NumberOfBlocks;
            // std::cout << EventBlocks.size() << std::endl;
            // std::cout << StartIndex << std::endl;
            for(int i = StartIndex; i < NumberOfBlocks; ++i){
                EventBlocks[i].EventID += StartIndex;
            }
            // std::cout << "here" << std::endl;
            AddCustom(obj);
            
        }

        void Data_ampt::WriteDataCustom(std::string directory){
            std::stringstream filename;
            std::ofstream file;
            double filesize;

            for(const auto& entry : histograms_custom){
                filename << directory << "/" << filenames_custom[entry.first] << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintCount(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintTotal(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintTotalSQR(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintEdges(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();
            }

            filename << directory << "/" << filenames_custom["1:PbPb"] << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            centrality_custom["1:PbPb"] -> PrintCount(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();
            
            
        }


        void Data_ampt::WriteData(std::string directory){
            std::stringstream filename;
            std::ofstream file;
            double filesize;
            
   
            // Yield
            Yield.Convert();
            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintCount(file);
          
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

           

            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintTotal(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintTotalSQR(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            // TransverseMomentum
            TransverseMomentum.Convert();
            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintCount(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintTotal(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintTotalSQR(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            // AnisotropicFlow
            
            for(int iv = nharmonic_min; iv <= nharmonic_max; ++iv){
                AnisotropicFlow[iv].Convert();
                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintCount(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintTotal(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintTotalSQR(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();
            }

            filename << directory << "/" << DEFAULT_NAME_CENTRALITYINFO << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Centrality.PrintCount(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            WriteDataCustom(directory);

        }

        void Data_ampt::WriteEventData(std::string directory){
            std::stringstream filename; 
            std::ofstream file;
            double filesize;
            filename << directory << "/" << DEFAULT_NAME_EVENTINFO << "." << DEFAULT_EXTENSION_LIST;
            file.open(filename.str(), std::ios::out);
            
            for(int i = 0; i < NumberOfBlocks; ++i){
                file << EventBlocks[i] << "\n";
            }
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            file.close();
            filename.str("");
            filename.clear();
        }

        void Data_ampt::WriteSettings(std::string directory){

            std::stringstream filename;
            std::ofstream file;
            double filesize;
           
            filename << directory << "/" << DEFAULT_NAME_SETTINGS << "." << DEFAULT_EXTENSION_SETTINGS;
            file.open(filename.str(), std::ios::out);
            
            file << "Centrality edges" << "\n";
            file << "n = " << centrality_edges.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < centrality_edges.size(); ++ix){
                file << centrality_edges[ix] << " ";
            }
            file << "\n";
            file << "Participation edges" << "\n";
            file << "n = " << participation_edges.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < participation_edges.size(); ++ix){
                file << participation_edges[ix] << " ";
            }
            file << "\n";
            file << "Momentum edges" << "\n";
            file << "n = " << momentum_edges.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < momentum_edges.size(); ++ix){
                file << momentum_edges[ix] << " ";
            }
            file << "\n";
            file << "Rapidity edges" << "\n";
            file << "n = " << rapidity_edges.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < rapidity_edges.size(); ++ix){
                file << rapidity_edges[ix] << " ";
            }
            file << "\n";
            file << "Pseudorapidity edges" << "\n";
            file << "n = " << pseudorapidity_edges.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < pseudorapidity_edges.size(); ++ix){
                file << pseudorapidity_edges[ix] << " ";
            }
            file << "\n";
            file << "Momentum edges (flow)" << "\n";
            file << "n = " << momentum_edges_flow.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < momentum_edges_flow.size(); ++ix){
                file << momentum_edges_flow[ix] << " ";
            }
            file << "\n";
            file << "Rapidity edges (flow)" << "\n";
            file << "n = " << rapidity_edges_flow.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < rapidity_edges_flow.size(); ++ix){
                file << rapidity_edges_flow[ix] << " ";
            }
            file << "\n";
            file << "Pseudorapidity edges (flow)" << "\n";
            file << "n = " << pseudorapidity_edges_flow.size() - 1 << "\n";
            file << "x = ";
            for(int ix = 0; ix < pseudorapidity_edges_flow.size(); ++ix){
                file << pseudorapidity_edges_flow[ix] << " ";
            }
            file << "\n";
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%s[%07.3fMB]%s ", PP::highlight, filesize, PP::end);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();
        }
    }

    
}