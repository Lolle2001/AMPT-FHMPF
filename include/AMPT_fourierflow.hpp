#ifndef AMPT_FOURIERFLOW_HPP
#define AMPT_FOURIERFLOW_HPP

#include "AMPT_statistics.hpp"
#include "AMPT_data.hpp"
#include "AMPT_functions.hpp"

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
    namespace Statistics {

        // class Statistics {
        //     public: 
        //     std::vector<std::vector<std::map<int, StatisticsContainer>>> event_momentum_pseudorapidity_vector_map;
        // };
        using Vector3DMap = std::vector<std::vector<std::vector<std::map<int, StatisticsContainer>>>>;
        using Vector2DMap = std::vector<std::vector<std::map<int, StatisticsContainer>>>;
        using Vector1DMap = std::vector<std::map<int, StatisticsContainer>>;
        using Vector1DMapVector1D = std::vector<std::map<int, std::vector<StatisticsContainer>>>;
        using Vector1DMapVector2D = std::vector<std::map<int, std::vector<std::vector<StatisticsContainer>>>>;
        using MapVector1D = std::map<int, std::vector<StatisticsContainer>>;

        struct StatisticsArray1D {
            Vector1DMapVector1D CMap;
            Vector2DMap DMap;

            int idim;
            int jdim;

            StatisticsArray1D(){};
            void resize(int & idim_, int & jdim_){
                idim = idim_;
                jdim = jdim_;
            
                DMap.resize(idim);

                for(int i = 0; i < idim; ++i){
                    DMap[i].resize(jdim);
                }
            }

            void convert(){
                CMap.resize(idim);
                for(int i = 0; i < idim; ++i){
                    for(int j = 0; j < jdim; ++j){
                        for(auto Entry: DMap[i][j]){
                            if(CMap[i].count(Entry.first) == 0){
                                CMap[i][Entry.first].resize(jdim);
                                CMap[i][Entry.first][j] = Entry.second;
                            }
                            else{
                                CMap[i][Entry.first][j] += Entry.second;
                            }
                        }
                    }
                }
            }

            void Write(std::ofstream & File, int & ievent){
                for(auto Entry : CMap[ievent]){
                    File << std::right << std::setw(6) << Entry.first << " ";
                    for(int j = 0; j < jdim; ++j){
                      
                        File << std::scientific << std::right << std::setw(13) << Entry.second[j].Total << " ";
                        File << std::scientific << std::right << std::setw(13) << Entry.second[j].TotalSQR << " ";
                        File << std::scientific << std::right << std::setw(9) << Entry.second[j].EntryCount << " ";
                        
                    }
                    File << std::endl;
                }
            }

            void Read(std::ifstream & File, int & ievent, int & mapsize){
                std::string line;
                int TempID;
                for(int m = 0; m < mapsize; ++m){
                    getline(File >> std::ws, line);
                    std::istringstream iss(line);
                    iss >> TempID;
                    for(int j = 0; j < jdim; ++j){
                        
                        iss >> DMap[ievent][j][TempID].Total;
                        iss >> DMap[ievent][j][TempID].TotalSQR;
                        iss >> DMap[ievent][j][TempID].EntryCount;
                        
                    }

                }
            }

            std::map<int, StatisticsContainer> operator()(int & i, int & j){
                return DMap[i][j];
            }

            std::vector<std::map<int, StatisticsContainer>> operator()(int &i){
                return DMap[i];
            }

            void operator+=(StatisticsArray1D const & obj){
                for(int i = 0; i < idim; ++i){
                    for(int j = 0; j < jdim; ++j){
                        for(auto Entry: obj.DMap[i][j]){
                            DMap[i][j][Entry.first] += Entry.second;
                        }
                    }
                }
            }
        };


        struct StatisticsArray {
            Vector3DMap VectorMap_3D;
            Vector1DMapVector2D VectorMap_1D2D;
            Vector1DMapVector1D cen_map_mom;
            Vector1DMapVector1D cen_map_psr;
            Vector2DMap cen_mom_map;
            Vector2DMap cen_psr_map;
            int idim ;
            int jdim ;
            int kdim ;

            StatisticsArray(){};

            

            void resize(int & idim_, int & jdim_, int & kdim_){
                idim = idim_;
                jdim = jdim_;
                kdim = kdim_;
                VectorMap_3D.resize(idim);
                // cen_mom_map.resize(idim);
                // cen_psr_map.resize(idim);
                for(int i = 0; i < idim; ++i){
                    VectorMap_3D[i].resize(jdim);

                    for(int j = 0; j < jdim; ++j){
                        VectorMap_3D[i][j].resize(kdim);
                    }
                }
            }

            void convert(){
             
                VectorMap_1D2D.resize(idim);
                for(int i = 0; i < idim; ++i){
                    for(int j = 0; j < jdim; ++j){
                        for(int k = 0; k < kdim; ++k){
                            for(auto Entry: VectorMap_3D[i][j][k]){
                                if(VectorMap_1D2D[i].count(Entry.first) == 0){
                                    VectorMap_1D2D[i][Entry.first].resize(jdim);
                                    for(int ej = 0; ej < jdim; ++ej){
                                        VectorMap_1D2D[i][Entry.first][ej].resize(kdim);
                                    }
                                    VectorMap_1D2D[i][Entry.first][j][k] = Entry.second;
                                }
                                else{
                                    VectorMap_1D2D[i][Entry.first][j][k] += Entry.second;
                                }
                            }
                        }
                    }
                }
            }

            
            Vector1DMapVector2D contract(std::vector<std::vector<int>> cen_range, std::vector<std::vector<int>> mom_range, std::vector<std::vector<int>> psr_range){
                int nidim = cen_range.size();
                int njdim = mom_range.size();
                int nkdim = psr_range.size();

                if(njdim == 0){
                    njdim =jdim;

                    mom_range.resize(njdim);
                    for(int nj = 0; nj < njdim; ++nj){
                        mom_range[nj].resize(2);
                        mom_range[nj][0] = nj;
                        mom_range[nj][1] = nj;
                    }
                }
                for(auto entry : mom_range){
                    std::cout << entry[0] << " " << entry[1] << std::endl;
                }
                if(nkdim == 0){
                    nkdim = kdim;

                    psr_range.resize(nkdim);
                    for(int nk = 0; nk < nkdim; ++nk){
                        psr_range[nk].resize(2);
                        psr_range[nk][0] = nk;
                        psr_range[nk][1] = nk;
                    }
                }


                Vector1DMapVector2D Map;

                Map.resize(nidim);
                for(int ni = 0; ni < nidim;++ni){
                    for(int i = cen_range[ni][0]; i <= cen_range[ni][1]; ++i){
                        for(auto Entry: VectorMap_1D2D[i]){
                            if(Map[ni][Entry.first].size() == 0){
                                Map[ni][Entry.first].resize(njdim);
                            }
                            for(int nj = 0; nj < njdim; ++nj){
                                for(int j = mom_range[nj][0]; j <= mom_range[nj][1]; ++j){
                                    if(Map[ni][Entry.first][nj].size() == 0){
                                        Map[ni][Entry.first][nj].resize(nkdim);
                                    }
                                    for(int nk = 0; nk < nkdim; ++nk){
                                        for(int k = psr_range[nk][0]; k <= psr_range[nk][1]; ++k){
                                            Map[ni][Entry.first][nj][nk] += Entry.second[j][k];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                return Map;
            }

            void Write(std::ofstream & File, int & ievent){
                File << VectorMap_1D2D[ievent].size() << std::endl;
                for(auto Entry : VectorMap_1D2D[ievent]){
                    File << std::right << std::setw(6) << Entry.first << " ";
                    for(int j = 0; j < jdim; ++j){
                        for(int k = 0; k < kdim; ++k){
                            File << std::scientific << std::right << std::setw(13) << Entry.second[j][k].Total << " ";
                            File << std::scientific << std::right << std::setw(13) << Entry.second[j][k].TotalSQR << " ";
                            File << std::scientific << std::right << std::setw(9) << Entry.second[j][k].EntryCount << " ";
                        }
                    }
                    File << std::endl;
                }
            }

            void Read(std::ifstream & File, int & ievent, int & mapsize){
                std::string line;
                int TempID;
                for(int m = 0; m < mapsize; ++m){
                    getline(File >> std::ws, line);
                    std::istringstream iss(line);
                    iss >> TempID;
                    for(int j = 0; j < jdim; ++j){
                        for(int k = 0; k < kdim; ++k){
                            iss >> VectorMap_3D[ievent][j][k][TempID].Total;
                            iss >> VectorMap_3D[ievent][j][k][TempID].TotalSQR;
                            iss >> VectorMap_3D[ievent][j][k][TempID].EntryCount;
                        }
                    }

                }
            }

            std::map<int, StatisticsContainer> operator()(int & i, int & j, int & k){
                return VectorMap_3D[i][j][k];
            }
            std::vector<std::map<int, StatisticsContainer>> operator()(int &i, int &j){
                return VectorMap_3D[i][j];
            }
            std::vector<std::vector<std::map<int, StatisticsContainer>>> operator()(int &i){
                return VectorMap_3D[i];
            }

            void operator+=(StatisticsArray const & obj){
                // std::cout << idim << obj.idim << std::endl;
                // std::cout << jdim << obj.jdim << std::endl;
                // std::cout << kdim << obj.kdim << std::endl;

                for(int i = 0; i < idim; ++i){
                    for(int j = 0; j < jdim; ++j){
                        for(int k = 0; k < kdim; ++k){
                           
                            for(auto Entry: obj.VectorMap_3D[i][j][k]){
                                VectorMap_3D[i][j][k][Entry.first] += Entry.second;
                            }
                            // std::cout << i << " "<< j << " "<< k << " " << obj.VectorMap_3D[i][j][k].size() << std::endl;
                        }
                    }
                }
                // AMPT::Functions::Concatenate(VectorMap_3D, obj.VectorMap_3D);
            }
        };

        struct Statistics {
            
            Vector1DMap event_map;   
            StatisticsArray EllipticFlow;
            StatisticsArray v[6];
        
        
        
        
            StatisticsArray ParticleYield;
            StatisticsArray1D TransverseMomentum;

            // One file with vectors for binning;
            // One file with information about events;
            // One file with maps to 2d arrays printed for every event, header -> index, mapsize
            // 2d array is morphed into 1d array with pseudorapidity binning for every momentum bin.



            // Vector3DMap ellipticflow_event_momentum_pseudorapidity_vector_map;
            // Vector3DMap particleyield_event_momentum_pseudorapidity_vector_map;
            // // event_momentum_pseudorapidity_vector_map;

            // Vector1DMapVector event_momentum_map_vector;
            // Vector1DMapVector event_pseudorapidity_map_vector;
            // Vector1DMapVector centrality_momentum_map_vector;
            // Vector2DMap       centrality_momentum_map;
            // Vector2DMap       centrality_pseudorapidity_map;
            // Vector1DMap       centrality_map;

            std::vector<double> momentum_edges         = {0, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 11, 12, 13, 14, 15, 16, 18, 19, 20};
            // std::vector<double> momentum_edges         = {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0};
            // std::vector<double> pseudorapidity_edges   = {-10, -1.0, -0.5, 0., 0.5, 1.0, 10};
            std::vector<double> pseudorapidity_edges   = { -10, -1.0, -0.5, -0.4, -0.3, -0.2, -0.1, 0., 0.1, 0.2, 0.3, 0.4, 0.5, 1.0, 10};
            // For flexible data comparison, a binwidth of 0.01 is recommended for transverse momentum.
            // to a range of 20. One may also apply a custom binrange.

            int momentum_nbins;
            int pseudorapidity_nbins;
            Statistics(){
               
                
            };

            void InitializeTransverseMomentumBins(int nbins, double min, double max){
                momentum_edges = AMPT::Functions::InitializeBins(nbins, min, max);
                momentum_nbins = nbins;
            }
            void InitializePseudoRapidityBins(int nbins, double min, double max){
                pseudorapidity_edges = AMPT::Functions::InitializeBins(nbins, min, max);
                pseudorapidity_nbins = nbins;
            }

            void SetTransverseMomentumBins(std::vector<double> & binedges){
                momentum_edges = binedges;
                momentum_nbins = binedges.size() - 1;
            }

            void SetPseudoRapidityBins(std::vector<double> & binedges){
                pseudorapidity_edges = binedges;
                pseudorapidity_nbins = binedges.size() - 1;
            }
            
            
            void Initialize(int & ExpectedSize){
                momentum_nbins = momentum_edges.size() - 1;
                pseudorapidity_nbins = pseudorapidity_edges.size() - 1;
                for(int i = 0; i < 6;++i){
                    v[i].resize(ExpectedSize, momentum_nbins, pseudorapidity_nbins);
                }
                TransverseMomentum.resize(ExpectedSize, pseudorapidity_nbins);
                ParticleYield.resize(ExpectedSize, momentum_nbins, pseudorapidity_nbins);
                EllipticFlow.resize(ExpectedSize, momentum_nbins, pseudorapidity_nbins);
            }

            void Convert(){
                for(int i = 0; i < 6;++i){
                    v[i].convert();
                }
                TransverseMomentum.convert();
                ParticleYield.convert();
                EllipticFlow.convert();
            }

            // Vector1DMapVector2D Combine(std::vector<std::vector<int>> cen_range, std::vector<std::vector<int>> mom_range, std::vector<std::vector<int>> psr_range){
            //     return EllipticFlow.contract(cen_range, mom_range, psr_range);
            // }

           

            void Add(int & ievent, AMPT::Line_ampt & line){//, Vector2DMap & map){
                
                for(int k = 0; k < pseudorapidity_nbins; ++k){
                    for(int j = 0; j < momentum_nbins; ++j){
                        if(
                            line.TransverseMomentum >= momentum_edges[j] && 
                            line.TransverseMomentum < momentum_edges[j+1] && 
                            line.PseudoRapidity >= pseudorapidity_edges[k] && 
                            line.PseudoRapidity < pseudorapidity_edges[k+1]
                            ){
                                for(int i = 0; i < 6; ++i){
                                    if(line.v[i]==line.v[i]){
                                        v[i].VectorMap_3D[ievent][j][k][line.ParticlePythiaID].Add(line.v[i]);
                                    }
                                }
                                if(line.EllipticFlow==line.EllipticFlow){
                                    EllipticFlow.VectorMap_3D[ievent][j][k][line.ParticlePythiaID].Add(line.EllipticFlow);
                                }
                                
                                ParticleYield.VectorMap_3D[ievent][j][k][line.ParticlePythiaID].Total += 1;
                                
                        }
                    }
                    if(line.PseudoRapidity >= pseudorapidity_edges[k] && 
                        line.PseudoRapidity < pseudorapidity_edges[k+1]   ){
                            TransverseMomentum.DMap[ievent][k][line.ParticlePythiaID].Add(line.TransverseMomentum);
                    }
                }
            }
            
            

            void operator+=(Statistics const & obj){
                for(int i = 0; i < 6; ++i){
                    v[i] += obj.v[i];
                }
                EllipticFlow += obj.EllipticFlow;
                ParticleYield += obj.ParticleYield;
                TransverseMomentum += obj.TransverseMomentum;
            }
        };

    }


}
#endif