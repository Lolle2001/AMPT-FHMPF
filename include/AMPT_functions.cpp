#include "AMPT_functions.hpp"

namespace AMPT {
    namespace Functions {
       
        // template<typename T>
        // void Concatenate(std::vector<T> &v1, const std::vector<T> &v2){
        //     v1.insert(std::end(v1), std::begin(v2), std::end(v2));
        // };
        double igcd(double a, double b, double base){
            if (a < b){
                return igcd(b, a, base);
            }
            if (std::fabs(b) < base){
                return a;
            }
            else {
                return (igcd(b, a - std::floor(a / b) * b, base));
            }
        }

        std::vector<std::string> Extract(const std::string& Text) {
            std::vector<std::string> Words;
            std::stringstream ss(Text);
            std::string Buf;

            while (ss >> Buf){
                // Words.push_back(std::move(Buf));
                Words.push_back(Buf);
            }

            return Words;
        }

        long double GetFileSize(std::filesystem::path filepath, const int option){
            long double GB = 1000000000.; // 3
            long double MB = 1000000.; // 2
            long double KB = 1000; // 1
            try {
                
                
                std::uintmax_t size = std::filesystem::file_size(filepath);
                long double filesize = static_cast<long double>(size);
                switch(option){
                    case 3:
                        return filesize/GB;
                    case 2:
                        return filesize/MB;
                    case 1:
                        return filesize/KB;
                    default:
                        return filesize;
                }
            }
            catch (const std::filesystem::filesystem_error&e){
                std::cerr << "Error accessing the file: " << e.what() << std::endl;
                return 0.;
            }
        }

        std::vector<double> InitializeBins( int nbins, double min, double max){
            std::vector<double> binedges(nbins+1);
            double binwidth = (max - min)/nbins;
            for(int i = 0; i < nbins + 1;++i){
                binedges[i] = min + binwidth * i;
            }
            return binedges;
        }
        
        void PrintTiming(
            std::chrono::time_point<std::chrono::high_resolution_clock>  & start, 
            std::chrono::time_point<std::chrono::high_resolution_clock> & stop, 
            std::string & Filename
            ){
            double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
           
            std::chrono::duration<int64_t, std::nano> difference = stop - start;
            std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(difference);
            difference -= minutes;
            std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(difference);
            difference -= seconds;
            std::chrono::milliseconds miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(difference);
            std::cout << "--------------------------------------------------------------------" << std::endl;
            std::cout << "Created file          : " << Filename << std::endl;
            std::cout << "Total datasize written: \033[1:97m" << std::setprecision(3) << Filesize << " MB\033[0m" << std::endl;
            std::cout << "Writing Time [m:s:ms] : \033[1:97m" << minutes.count() << ":" << std::setw(2) << std::setfill('0') << seconds.count() << ":" << std::setw(3) << std::setfill('0') << miliseconds.count() << "\033[0m"<< std::endl;
            std::cout << "--------------------------------------------------------------------" << std::endl;

        }

       

        void PrintTiming(
            std::chrono::time_point<std::chrono::high_resolution_clock>  & start, 
            std::chrono::time_point<std::chrono::high_resolution_clock> & stop
            
            ){
            
           
            std::chrono::duration<int64_t, std::nano> difference = stop - start;
            std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(difference);
            difference -= minutes;
            std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(difference);
            difference -= seconds;
            std::chrono::milliseconds miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(difference);
            
            
            
            std::cout << "Reading Time [m:s:ms] : \033[1:97m" << minutes.count() << ":" << std::setw(2) << std::setfill('0') << seconds.count() << ":" << std::setw(3) << std::setfill('0') << miliseconds.count() << "\033[0m"<< std::endl;
            

        }

        


         

    }
}

