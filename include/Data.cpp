#include "Data.hpp"

// namespace AMPT {
    namespace Statistics {


        // Add functionality based on input: correct selection of centrality bins
        // proton-proton, lead-lead, proton-lead, etc.

        void Data_ampt::SetupCustomHistograms(){
            // BINEDGES
            // std::string centrality_key = "1:PbPb";
           
            centrality_edges_custom["1:PbPb5020"] = (std::vector<double>){0.00, 3.49, 4.93, 6.98, 8.55, 9.87, 11.00, 12.10,  13.10, 14.00, 14.90, 20.00};
            // centrality_edges_custom["2:PbPb5020"] = (std::vector<double>){0.00,3.49,4.93,6.04,6.98,7.80,8.55,9.23,9.87,10.50,11.00,11.60,12.10,12.60,13.10,13.50,14.00,14.40,14.90,15.60,20.00};
            centrality_edges_custom["1:pPb5020"]  = (std::vector<double>){0.00, 1.82, 2.58, 3.65, 4.47, 5.16, 5.77,  6.32,  6.84,  7.36,  7.99,  14.70};
            centrality_edges_custom["1:pp5020"]   = (std::vector<double>){0.00, 20.00};
         
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


            rapidity_edges_custom["3:p_pbar"]  = (std::vector<double>){-10.0,-9.5,-9.0,-8.5,-8.0,-7.5,-7.0,-6.5,-6.0,-5.5,-5.0,-4.5,-4.0,-3.5,-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0};
            momentum_edges_custom["3:p_pbar"]  = (std::vector<double>){0.01, 20.};
            rapidity_edges_custom["3:K+_K-"]   = (std::vector<double>){-10.0,-9.5,-9.0,-8.5,-8.0,-7.5,-7.0,-6.5,-6.0,-5.5,-5.0,-4.5,-4.0,-3.5,-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0};
            momentum_edges_custom["3:K+_K-"]   = (std::vector<double>){0.01, 20.};
            rapidity_edges_custom["3:pi+_pi-"] = (std::vector<double>){-10.0,-9.5,-9.0,-8.5,-8.0,-7.5,-7.0,-6.5,-6.0,-5.5,-5.0,-4.5,-4.0,-3.5,-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0};
            momentum_edges_custom["3:pi+_pi-"] = (std::vector<double>){0.01, 20.};
            rapidity_edges_custom["3:charged"] = (std::vector<double>){-10.0,-9.5,-9.0,-8.5,-8.0,-7.5,-7.0,-6.5,-6.0,-5.5,-5.0,-4.5,-4.0,-3.5,-3.0,-2.5,-2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0,7.5,8.0,8.5,9.0,9.5,10.0};
            momentum_edges_custom["3:charged"] = (std::vector<double>){0.01, 20.};

            rapidity_edges_custom["4:p_pbar"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["4:p_pbar"]  = (std::vector<double>){0.2, 5.};
            rapidity_edges_custom["4:K+_K-"]   = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["4:K+_K-"]   = (std::vector<double>){0.2, 5.};
            rapidity_edges_custom["4:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["4:pi+_pi-"] = (std::vector<double>){0.2, 5.};
            rapidity_edges_custom["4:charged"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["4:charged"] = (std::vector<double>){0.2, 5.};

            rapidity_edges_custom["5:p_pbar"]  = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["5:p_pbar"]  = (std::vector<double>){0.2, 2.};
            rapidity_edges_custom["5:K+_K-"]   = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["5:K+_K-"]   = (std::vector<double>){0.2, 2.};
            rapidity_edges_custom["5:pi+_pi-"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["5:pi+_pi-"] = (std::vector<double>){0.2, 2.};
            rapidity_edges_custom["5:charged"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["5:charged"] = (std::vector<double>){0.2, 2.};

            rapidity_edges_custom["1:meanpt"] = (std::vector<double>){-0.5, 0.5};
            momentum_edges_custom["1:meanpt"] = (std::vector<double>){0., 3.};

            // rapidity_edges_custom["3:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
            // momentum_edges_custom["3:pi+_pi-"]  = (std::vector<double>){0.2 ,  0.25,  0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 , 0.65,  0.7 ,  0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 , 1.2 ,  1.3 ,  1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  , 2.2 ,  2.4 ,  2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 , 4.  ,  4.5 ,  5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20.  };
            // rapidity_edges_custom["4:pi+_pi-"]  = (std::vector<double>){-0.5, 0.5};
            // momentum_edges_custom["4:pi+_pi-"]  = (std::vector<double>){0.3 ,  0.35,  0.4 ,  0.45,  0.5 ,  0.55,  0.6 ,  0.65,  0.7 , 0.75,  0.8 ,  0.85,  0.9 ,  0.95,  1.  ,  1.1 ,  1.2 ,  1.3 , 1.4 ,  1.5 ,  1.6 ,  1.7 ,  1.8 ,  1.9 ,  2.  ,  2.2 ,  2.4 , 2.6 ,  2.8 ,  3.  ,  3.2 ,  3.4 ,  3.6 ,  3.8 ,  4.  ,  4.5 , 5.  ,  5.5 ,  6.  ,  6.5 ,  7.  ,  8.  ,  9.  , 10.  , 11.  , 12.  , 13.  , 14.  , 15.  , 16.  , 18.  , 20. };
            
            
            // HISTOGRAMS
            histograms_custom["meanpt_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["meanpt_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["meanpt_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["meanpt_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["yield_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["yield_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["yield_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);
            histograms_custom["yield_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:meanpt"], rapidity_edges_custom["1:meanpt"]);

            histograms_custom["pt_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:p_pbar"],  rapidity_edges_custom["1:p_pbar"]);
            histograms_custom["pt_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:K+_K-"],   rapidity_edges_custom["1:K+_K-"]);
            histograms_custom["pt_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:pi+_pi-"], rapidity_edges_custom["1:pi+_pi-"]);
            histograms_custom["pt_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:charged"], rapidity_edges_custom["1:charged"]);
            histograms_custom["v2_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:p_pbar"],  rapidity_edges_custom["2:p_pbar"]);
            histograms_custom["v2_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:K+_K-"],   rapidity_edges_custom["2:K+_K-"]);
            histograms_custom["v2_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:pi+_pi-"], rapidity_edges_custom["2:pi+_pi-"]);
            histograms_custom["v2_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:charged"], rapidity_edges_custom["2:charged"]);
            histograms_custom["v3_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:p_pbar"],  rapidity_edges_custom["2:p_pbar"]);
            histograms_custom["v3_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:K+_K-"],   rapidity_edges_custom["2:K+_K-"]);
            histograms_custom["v3_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:pi+_pi-"], rapidity_edges_custom["2:pi+_pi-"]);
            histograms_custom["v3_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:charged"], rapidity_edges_custom["2:charged"]);
            histograms_custom["v4_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:p_pbar"],  rapidity_edges_custom["2:p_pbar"]);
            histograms_custom["v4_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:K+_K-"],   rapidity_edges_custom["2:K+_K-"]);
            histograms_custom["v4_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:pi+_pi-"], rapidity_edges_custom["2:pi+_pi-"]);
            histograms_custom["v4_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:charged"], rapidity_edges_custom["2:charged"]);
            histograms_custom["v5_chprotons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:p_pbar"],  rapidity_edges_custom["2:p_pbar"]);
            histograms_custom["v5_chkaons"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:K+_K-"],   rapidity_edges_custom["2:K+_K-"]);
            histograms_custom["v5_chpions"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:pi+_pi-"], rapidity_edges_custom["2:pi+_pi-"]);
            histograms_custom["v5_charged"]                      = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["2:charged"], rapidity_edges_custom["2:charged"]);
            histograms_custom["pt_ratio_chpions_to_chkaons"]     = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:K+_K-"],   rapidity_edges_custom["1:K+_K-"]);
            histograms_custom["pt_ratio_chpions_to_chprotons"]   = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["1:p_pbar"],  rapidity_edges_custom["1:p_pbar"]);
            histograms_custom["rap_chprotons"]                   = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:p_pbar"],  rapidity_edges_custom["3:p_pbar"]);
            histograms_custom["rap_chkaons"]                     = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:K+_K-"],   rapidity_edges_custom["3:K+_K-"]);
            histograms_custom["rap_chpions"]                     = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:pi+_pi-"], rapidity_edges_custom["3:pi+_pi-"]);
            histograms_custom["rap_charged"]                     = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:charged"], rapidity_edges_custom["3:charged"]);
            histograms_custom["psrap_chprotons"]                 = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:p_pbar"],  rapidity_edges_custom["3:p_pbar"]);
            histograms_custom["psrap_chkaons"]                   = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:K+_K-"],   rapidity_edges_custom["3:K+_K-"]);
            histograms_custom["psrap_chpions"]                   = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:pi+_pi-"], rapidity_edges_custom["3:pi+_pi-"]);
            histograms_custom["psrap_charged"]                   = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["3:charged"], rapidity_edges_custom["3:charged"]);

            histograms_custom["v2_2_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:p_pbar"],  rapidity_edges_custom["4:p_pbar"]);
            histograms_custom["v2_2_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:K+_K-"],   rapidity_edges_custom["4:K+_K-"]);
            histograms_custom["v2_2_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:pi+_pi-"], rapidity_edges_custom["4:pi+_pi-"]);
            histograms_custom["v2_2_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:charged"], rapidity_edges_custom["4:charged"]);
            histograms_custom["v3_2_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:p_pbar"],  rapidity_edges_custom["4:p_pbar"]);
            histograms_custom["v3_2_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:K+_K-"],   rapidity_edges_custom["4:K+_K-"]);
            histograms_custom["v3_2_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:pi+_pi-"], rapidity_edges_custom["4:pi+_pi-"]);
            histograms_custom["v3_2_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:charged"], rapidity_edges_custom["4:charged"]);
            histograms_custom["v4_2_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:p_pbar"],  rapidity_edges_custom["4:p_pbar"]);
            histograms_custom["v4_2_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:K+_K-"],   rapidity_edges_custom["4:K+_K-"]);
            histograms_custom["v4_2_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:pi+_pi-"], rapidity_edges_custom["4:pi+_pi-"]);
            histograms_custom["v4_2_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:charged"], rapidity_edges_custom["4:charged"]);
            histograms_custom["v5_2_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:p_pbar"],  rapidity_edges_custom["4:p_pbar"]);
            histograms_custom["v5_2_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:K+_K-"],   rapidity_edges_custom["4:K+_K-"]);
            histograms_custom["v5_2_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:pi+_pi-"], rapidity_edges_custom["4:pi+_pi-"]);
            histograms_custom["v5_2_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["4:charged"], rapidity_edges_custom["4:charged"]);
            histograms_custom["v2_3_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:p_pbar"],  rapidity_edges_custom["5:p_pbar"]);
            histograms_custom["v2_3_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:K+_K-"],   rapidity_edges_custom["5:K+_K-"]);
            histograms_custom["v2_3_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:pi+_pi-"], rapidity_edges_custom["5:pi+_pi-"]);
            histograms_custom["v2_3_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:charged"], rapidity_edges_custom["5:charged"]);
            histograms_custom["v3_3_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:p_pbar"],  rapidity_edges_custom["5:p_pbar"]);
            histograms_custom["v3_3_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:K+_K-"],   rapidity_edges_custom["5:K+_K-"]);
            histograms_custom["v3_3_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:pi+_pi-"], rapidity_edges_custom["5:pi+_pi-"]);
            histograms_custom["v3_3_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:charged"], rapidity_edges_custom["5:charged"]);
            histograms_custom["v4_3_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:p_pbar"],  rapidity_edges_custom["5:p_pbar"]);
            histograms_custom["v4_3_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:K+_K-"],   rapidity_edges_custom["5:K+_K-"]);
            histograms_custom["v4_3_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:pi+_pi-"], rapidity_edges_custom["5:pi+_pi-"]);
            histograms_custom["v4_3_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:charged"], rapidity_edges_custom["5:charged"]);
            histograms_custom["v5_3_chprotons"]                  = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:p_pbar"],  rapidity_edges_custom["5:p_pbar"]);
            histograms_custom["v5_3_chkaons"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:K+_K-"],   rapidity_edges_custom["5:K+_K-"]);
            histograms_custom["v5_3_chpions"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:pi+_pi-"], rapidity_edges_custom["5:pi+_pi-"]);
            histograms_custom["v5_3_charged"]                    = std::make_unique<Histogram3D>(centrality_edges_custom[centrality_key], momentum_edges_custom["5:charged"], rapidity_edges_custom["5:charged"]);




            centrality_custom["impactparameter"] = std::make_unique<Histogram1D>(centrality_edges_custom[centrality_key]);
            centrality_custom["participation"]   = std::make_unique<Histogram1D>(centrality_edges_custom[centrality_key]);
            // centrality_custom["participation_2"]   = std::make_unique<Histogram1D>(centrality_edges_custom["2:PbPb5020"]);


            filenames_custom["meanpt_chprotons"] = "meanpt_chprotons";
            filenames_custom["meanpt_chkaons"]   = "meanpt_chkaons";
            filenames_custom["meanpt_chpions"]   = "meanpt_chpions";
            filenames_custom["meanpt_charged"]   = "meanpt_charged";
            filenames_custom["yield_chprotons"]  = "yield_chprotons";
            filenames_custom["yield_chkaons"]    = "yield_chkaons";
            filenames_custom["yield_chpions"]    = "yield_chpions";
            filenames_custom["yield_charged"]    = "yield_charged";

            filenames_custom["pt_chprotons"]                  = "pt_chprotons";
            filenames_custom["pt_chkaons"]                    = "pt_chkaons";
            filenames_custom["pt_chpions"]                    = "pt_chpions";
            filenames_custom["pt_charged"]                    = "pt_charged";
            filenames_custom["v2_chprotons"]                  = "v2_chprotons";
            filenames_custom["v2_chkaons"]                    = "v2_chkaons";
            filenames_custom["v2_chpions"]                    = "v2_chpions";
            filenames_custom["v2_charged"]                    = "v2_charged";
            filenames_custom["v3_chprotons"]                  = "v3_chprotons";
            filenames_custom["v3_chkaons"]                    = "v3_chkaons";
            filenames_custom["v3_chpions"]                    = "v3_chpions";
            filenames_custom["v3_charged"]                    = "v3_charged";
            filenames_custom["v4_chprotons"]                  = "v4_chprotons";
            filenames_custom["v4_chkaons"]                    = "v4_chkaons";
            filenames_custom["v4_chpions"]                    = "v4_chpions";
            filenames_custom["v4_charged"]                    = "v4_charged";
            filenames_custom["v5_chprotons"]                  = "v5_chprotons";
            filenames_custom["v5_chkaons"]                    = "v5_chkaons";
            filenames_custom["v5_chpions"]                    = "v5_chpions";
            filenames_custom["v5_charged"]                    = "v5_charged";
            filenames_custom["pt_ratio_chpions_to_chkaons"]   = "pt_ratio_chpions_to_chkaons";
            filenames_custom["pt_ratio_chpions_to_chprotons"] = "pt_ratio_chpions_to_chprotons";


            filenames_custom["impactparameter"]  = "impactparameter";
            filenames_custom["participation"]    = "participation";
            // filenames_custom["participation_2"]    = "participation_2";

            filenames_custom["rap_chprotons"]   = "rap_chprotons";
            filenames_custom["rap_chkaons"]     = "rap_chkaons";
            filenames_custom["rap_chpions"]     = "rap_chpions";
            filenames_custom["rap_charged"]     = "rap_charged";
            filenames_custom["psrap_chprotons"] = "psrap_chprotons";
            filenames_custom["psrap_chkaons"]   = "psrap_chkaons";
            filenames_custom["psrap_chpions"]   = "psrap_chpions";
            filenames_custom["psrap_charged"]   = "psrap_charged";
            filenames_custom["v2_2_chprotons"]  = "v2_2_chprotons";
            filenames_custom["v2_2_chkaons"]    = "v2_2_chkaons";
            filenames_custom["v2_2_chpions"]    = "v2_2_chpions";
            filenames_custom["v2_2_charged"]    = "v2_2_charged";
            filenames_custom["v3_2_chprotons"]  = "v3_2_chprotons";
            filenames_custom["v3_2_chkaons"]    = "v3_2_chkaons";
            filenames_custom["v3_2_chpions"]    = "v3_2_chpions";
            filenames_custom["v3_2_charged"]    = "v3_2_charged";
            filenames_custom["v4_2_chprotons"]  = "v4_2_chprotons";
            filenames_custom["v4_2_chkaons"]    = "v4_2_chkaons";
            filenames_custom["v4_2_chpions"]    = "v4_2_chpions";
            filenames_custom["v4_2_charged"]    = "v4_2_charged";
            filenames_custom["v5_2_chprotons"]  = "v5_2_chprotons";
            filenames_custom["v5_2_chkaons"]    = "v5_2_chkaons";
            filenames_custom["v5_2_chpions"]    = "v5_2_chpions";
            filenames_custom["v5_2_charged"]    = "v5_2_charged";
            filenames_custom["v2_3_chprotons"]  = "v2_3_chprotons";
            filenames_custom["v2_3_chkaons"]    = "v2_3_chkaons";
            filenames_custom["v2_3_chpions"]    = "v2_3_chpions";
            filenames_custom["v2_3_charged"]    = "v2_3_charged";
            filenames_custom["v3_3_chprotons"]  = "v3_3_chprotons";
            filenames_custom["v3_3_chkaons"]    = "v3_3_chkaons";
            filenames_custom["v3_3_chpions"]    = "v3_3_chpions";
            filenames_custom["v3_3_charged"]    = "v3_3_charged";
            filenames_custom["v4_3_chprotons"]  = "v4_3_chprotons";
            filenames_custom["v4_3_chkaons"]    = "v4_3_chkaons";
            filenames_custom["v4_3_chpions"]    = "v4_3_chpions";
            filenames_custom["v4_3_charged"]    = "v4_3_charged";
            filenames_custom["v5_3_chprotons"]  = "v5_3_chprotons";
            filenames_custom["v5_3_chkaons"]    = "v5_3_chkaons";
            filenames_custom["v5_3_chpions"]    = "v5_3_chpions";
            filenames_custom["v5_3_charged"]    = "v5_3_charged";


           
        }



        // void Data_ampt::SetParameters(File_input * input){
        //     parameters = input;
        // }

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

         void Data_ampt::AddParticle(double & b, AMPT::Line_ampt & line){
            for(int iv = nharmonic_min; iv <= nharmonic_max; ++iv){
                if(line.AnisotropicFlow[iv]==line.AnisotropicFlow[iv]){
                    AnisotropicFlow[iv].Add(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID, line.AnisotropicFlow[iv]);
                }
            }
            Yield.AddCurrent(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID,1);
            TransverseMomentum.Add(b, line.TransverseMomentum, line.Rapidity, line.ParticlePythiaID, line.TransverseMomentum);
            AddParticleCustom(b, line);
        }

        void Data_ampt::AddEvent(AMPT::Block_ampt & block){
            EventBlocks.emplace_back(block);
            Centrality.Add(block.ImpactParameter,1);
            Yield.AddEvent();
            AddEventCustom(block);
        }

        void Data_ampt::AddParticleCustom(double & b, AMPT::Line_ampt & line){
            // if(line.Rapidity > -0.5 && line.Rapidity < 0.5){
                if(line.ParticlePythiaID == 211 | line.ParticlePythiaID == -211){
                 
                    histograms_custom["pt_chpions"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["yield_chpions"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["meanpt_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.TransverseMomentum);
                    histograms_custom["rap_chpions"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["psrap_chpions"]                   -> AddCurrent(b, line.TransverseMomentum, line.PseudoRapidity, 1.0);
                    histograms_custom["v2_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_2_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_2_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_2_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_2_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_3_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_3_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_3_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_3_chpions"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["pt_ratio_chpions_to_chkaons"]  -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["pt_ratio_chpions_to_chprotons"]-> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                }
                else if(line.ParticlePythiaID == 321 | line.ParticlePythiaID == -321){
                    histograms_custom["pt_chkaons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["yield_chkaons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["meanpt_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.TransverseMomentum);
                    histograms_custom["rap_chkaons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                    histograms_custom["psrap_chkaons"]                   -> AddCurrent(b, line.TransverseMomentum, line.PseudoRapidity, 1.0);
                    histograms_custom["v2_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_2_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_2_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_2_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_2_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_3_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_3_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_3_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_3_chkaons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                }
                else if(line.ParticlePythiaID == 2212 | line.ParticlePythiaID == -2212){
                     histograms_custom["pt_chprotons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                     histograms_custom["yield_chprotons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                      histograms_custom["meanpt_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.TransverseMomentum);
                     histograms_custom["rap_chprotons"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                     histograms_custom["psrap_chprotons"]                   -> AddCurrent(b, line.TransverseMomentum, line.PseudoRapidity, 1.0);
                    histograms_custom["v2_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_2_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_2_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_2_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_2_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_3_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_3_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_3_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_3_chprotons"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                }
                if(ChargeMap[line.ParticlePythiaID] != 0){
                     histograms_custom["pt_charged"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                     histograms_custom["yield_charged"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                     histograms_custom["meanpt_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.TransverseMomentum);
                     histograms_custom["rap_charged"]                   -> AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                     histograms_custom["psrap_charged"]                   -> AddCurrent(b, line.TransverseMomentum, line.PseudoRapidity, 1.0);
                    histograms_custom["v2_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_2_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_2_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_2_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_2_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    histograms_custom["v2_3_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[2]);
                    histograms_custom["v3_3_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[3]);
                    histograms_custom["v4_3_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[4]);
                    histograms_custom["v5_3_charged"]                   -> Add(b, line.TransverseMomentum, line.Rapidity, line.AnisotropicFlow[5]);
                    // histograms_custom["5:charged"]->AddCurrent(b, line.TransverseMomentum, line.Rapidity, 1.0);
                }
            // }
            
        }

        void Data_ampt::AddEventCustom(AMPT::Block_ampt & block){
            
            centrality_custom["impactparameter"]->Add(block.ImpactParameter, block.ImpactParameter);
            centrality_custom["participation"]->Add(block.ImpactParameter,  block.NumberOfParticipantNucleons_PROJ + block.NumberOfParticipantNulceons_TARG);
            // centrality_custom["participation_2"]->Add(block.ImpactParameter,  block.NumberOfParticipantNucleons_PROJ + block.NumberOfParticipantNulceons_TARG);
            // centrality_custom["5:pPb"]->Add(block.ImpactParameter, block.NumberOfParticipantNucleons_PROJ + block.NumberOfParticipantNulceons_TARG);
            histograms_custom["pt_chpions"]                   ->AddEvent();            
            histograms_custom["pt_ratio_chpions_to_chkaons"]  ->AddEvent();
            histograms_custom["pt_ratio_chpions_to_chprotons"]->AddEvent();
            histograms_custom["pt_chkaons"]                   ->AddEvent();
            histograms_custom["pt_chprotons"]                 ->AddEvent();
            histograms_custom["pt_charged"]                   ->AddEvent();
            histograms_custom["yield_chpions"]                   ->AddEvent();            
            histograms_custom["yield_chkaons"]                   ->AddEvent();
            histograms_custom["yield_chprotons"]                 ->AddEvent();
            histograms_custom["yield_charged"]                   ->AddEvent();
            histograms_custom["rap_chpions"]                   ->AddEvent();   
            histograms_custom["rap_chkaons"]                   ->AddEvent();
            histograms_custom["rap_chprotons"]                 ->AddEvent();
            histograms_custom["rap_charged"]                   ->AddEvent();
            histograms_custom["psrap_chpions"]                   ->AddEvent();   
            histograms_custom["psrap_chkaons"]                   ->AddEvent();
            histograms_custom["psrap_chprotons"]                 ->AddEvent();
            histograms_custom["psrap_charged"]                   ->AddEvent();
            // histograms_custom["5:charged"]->AddEvent();
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
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintTotal(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintTotalSQR(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                histograms_custom[entry.first] -> PrintEdges(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();
            }
            for(const auto& entry : centrality_custom){
                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                centrality_custom[entry.first] -> PrintTotal(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "COUNT" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                centrality_custom[entry.first] -> PrintCount(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                centrality_custom[entry.first] -> PrintTotalSQR(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << filenames_custom[entry.first] << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                centrality_custom[entry.first] -> PrintEdges(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();
            }
            
            
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
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

           

            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintTotal(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintTotalSQR(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_YIELD << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Yield.PrintEdges(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
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
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintTotal(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintTotalSQR(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_TRANSVERSEMOMENTUM << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            TransverseMomentum.PrintEdges(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
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
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintTotal(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintTotalSQR(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
                printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
                fflush(stdout);
                filename.str("");
                filename.clear();

                filename << directory << "/" << DEFAULT_NAME_ANISOTROPICFLOW << "_" << iv << "_" << DEFAULT_SPECIFIER_CENTRALITY << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
                file.open(filename.str(), std::ios::out);
                AnisotropicFlow[iv].PrintEdges(file);
                file.close();
                filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
                printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
                printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
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
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

            filename << directory << "/" << DEFAULT_NAME_CENTRALITYINFO << "_" << "TOTAL" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Centrality.PrintTotal(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

              filename << directory << "/" << DEFAULT_NAME_CENTRALITYINFO << "_" << "TOTALSQR" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Centrality.PrintTotalSQR(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();

              filename << directory << "/" << DEFAULT_NAME_CENTRALITYINFO << "_" << "SETTINGS" << "." << DEFAULT_EXTENSION_HISTOGRAM;
            file.open(filename.str(), std::ios::out);
            Centrality.PrintEdges(file);
            file.close();
            filesize = AMPT::Functions::GetFileSize(filename.str(), 2);
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
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
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
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
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%s[%07.3fMB]%s ", PP::HIGHLIGHT, filesize, PP::RESET);
            printf("%-14s : %s\n", "Writen data to", filename.str().c_str());
            fflush(stdout);
            filename.str("");
            filename.clear();
        }
    }

    
// }