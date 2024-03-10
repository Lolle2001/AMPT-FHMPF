#include "Histogram1D.hpp"
namespace AMPT {
    namespace Statistics {


 Histogram1D::Histogram1D(int & nx_) : nx(nx_){
            Resize(nx);
        };

        Histogram1D::Histogram1D(
            std::vector<double> EdgesX_) : 
            EdgesX(EdgesX_)
 
         {
            nx = EdgesX.size() - 1;
   
            Resize(nx);
            InitializeIndexMap();
        }
         

        void Histogram1D::Resize(int & nx_){
            Contents.resize(nx_);
        }

        void Histogram1D::AddEvent(){
            for(int ix = 0; ix < nx; ++ix){
             
                Contents[ix].AddEvent();
                    
            }
        }

        void Histogram1D::Add(double & valx, double valcontent){
           if(valx >= x_min && valx < x_max){
                int ix = IndexMapX[(int)((valx - x_min)/(x_width))];
                Contents[ix].Add(valcontent);
            }
        }

         void Histogram1D::AddCurrent(double & valx, double valcontent){
           if(valx >= x_min && valx < x_max){
                int ix = IndexMapX[(int)((valx - x_min)/(x_width))];
                Contents[ix].AddCurrent(valcontent);
            }
        }



        void Histogram1D::InitializeIndexMap(){
            x_max = EdgesX.back() ;
            x_min = EdgesX.front();
     

            std::vector<double> xwidths(nx);

            for(int ix = 0; ix < nx; ++ix){
                xwidths[ix] = EdgesX[ix+1] - EdgesX[ix];
                // std::cout << xwidths[ix] << std::endl;
            }

            double x_smallest_width = xwidths[0];


            double x_temp_width;


            for(int ix = 0; ix < nx; ++ix){
                for(int jx = ix + 1; jx < nx; ++jx){
                    x_temp_width = AMPT::Functions::igcd(xwidths[ix], xwidths[jx], 0.001);
                    if(x_temp_width < x_smallest_width){
                        x_smallest_width = x_temp_width;
                    }
                }
            }
     

            x_width = x_smallest_width;
          
            int temp_nx = static_cast<int>((x_max - x_min)/x_width);
          
            double x;
          

            for(int ix = 0; ix < temp_nx; ++ix){
                x = (x_min + ix * x_width + x_width * 0.5);
                
                for(int jx = 0; jx < nx; ++jx){
                    if(x > EdgesX[jx] && x < EdgesX[jx+1]){
                        IndexMapX[ix] = jx;
                    }
                }
            }
      
            xwidths.clear();
      


        }

        StatisticsContainer & Histogram1D::operator()(int & ix){
            return Contents[ix];
        }   



        StatisticsContainer & Histogram1D::operator()(double & valx){
            
            int ix = IndexMapX[static_cast<int>((valx - x_min)/(x_width))];
        

            
            return Contents[ix];
        }   



        void Histogram1D::operator+=(Histogram1D const & obj){
            if(nx == obj.nx){
                for(int ix = 0; ix < nx; ++ix){
                    
                                Contents[ix] += obj.Contents[ix];
                        
                }
            }
            else{
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%s", "Cannot add two HistogramMaps of different sizes!");
            }
        }

        void Histogram1D::PrintCount(std::ostream & output){
            for(int ix = 0; ix < nx; ++ix){
                output << ix << " ";
                output << Contents[ix].EntryCount << "\n";
            }
        }

        void Histogram1D::PrintTotal(std::ostream & output){
            for(int ix = 0; ix < nx; ++ix){
                output << ix << " ";
                output << Contents[ix].Total << "\n";
            }
        }

        void Histogram1D::PrintTotalSQR(std::ostream & output){
            for(int ix = 0; ix < nx; ++ix){
                output << ix << " ";
                output << Contents[ix].TotalSQR << "\n";
            }
        }
    }
}