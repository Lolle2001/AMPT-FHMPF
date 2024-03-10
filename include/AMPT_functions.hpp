#ifndef AMPT_FUCNTIONS_HPP
#define AMPT_FUCNTIONS_HPP

#include <vector>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <map>

#include <cmath>

#include <sstream>

namespace AMPT {
    namespace Functions {
       

        double igcd(double a, double b, double base);


        template<typename T>
        void Concatenate(std::vector<T> &v1, const std::vector<T> &v2){
            v1.insert(std::end(v1), std::begin(v2), std::end(v2));
        };

        std::vector<std::string> Extract(const std::string& Text);

        long double GetFileSize(std::filesystem::path filepath, const int option = 0);

        std::vector<double> InitializeBins( int nbins, double min, double max);
        
        void PrintTiming(
            std::chrono::time_point<std::chrono::high_resolution_clock>  & start, 
            std::chrono::time_point<std::chrono::high_resolution_clock> & stop, 
            std::string & Filename
            );

        struct Duration {
            std::chrono::duration<int64_t, std::nano> duration;
            std::chrono::time_point<std::chrono::high_resolution_clock>  start;
            std::chrono::time_point<std::chrono::high_resolution_clock>  stop;

            int64_t cnanoseconds;
            int64_t cmicroseconds;
            int64_t cmilliseconds;
            int64_t cseconds;
            int64_t cminutes;
            int64_t chours;

            std::chrono::nanoseconds nanoseconds;;
            std::chrono::microseconds microseconds;;
            std::chrono::milliseconds milliseconds;;
            std::chrono::seconds seconds;;
            std::chrono::minutes minutes;;
            std::chrono::hours hours;;
            

            Duration(std::chrono::duration<int64_t, std::nano> & duration_) : duration(duration_){};
            Duration( 
                std::chrono::time_point<std::chrono::high_resolution_clock>  & start_, 
                std::chrono::time_point<std::chrono::high_resolution_clock> & stop_) : start(start_), stop(stop_){
                    GetDuration();
                };
            Duration( 
                std::chrono::time_point<std::chrono::high_resolution_clock>  & start_, 
                std::chrono::time_point<std::chrono::high_resolution_clock> & stop_, char option) : start(start_), stop(stop_){
                    GetDuration();
                    GetCounts(option);
                };
            
            void GetCounts(char option){
                if(option == 'H'){
                    hours = std::chrono::duration_cast<std::chrono::hours>(duration);
                    duration -= hours;
                    minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
                    duration -= minutes;
                    seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                    duration -= seconds;
                    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
                    chours = hours.count();
                    cminutes = minutes.count();
                    cseconds = seconds.count();
                    cmilliseconds = milliseconds.count();
                    
                }
                else if(option == 'M'){
                    minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
                    duration -= minutes;
                    seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                    duration -= seconds;
                    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
                   
                    cminutes = minutes.count();
                    cseconds = seconds.count();
                    cmilliseconds = milliseconds.count();
                }
                else if(option == 'S'){
                    seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                    duration -= seconds;
                    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
                    
                    cseconds = seconds.count();
                    cmilliseconds = milliseconds.count();
                }
                
            }
           
            private:
            void GetDuration(){
                duration = stop - start; 
            }
            
        };

        void PrintTiming(
            std::chrono::time_point<std::chrono::high_resolution_clock>  & start, 
            std::chrono::time_point<std::chrono::high_resolution_clock> & stop
            
            );

        struct PrettyPrint {
            std::string warning   = "\033[1;38;2;255;0;0m";
            std::string end       = "\033[0m";
            std::string started   = "\033[1;38;2;255;199;6m";
            std::string finished  = "\033[1;38;2;57;181;74m";
            std::string highlight = "\033[1;38;2;255;255;255m";

        };

        

        struct PretyPrint {
            inline static const char * BOLD   = "\033[1m";
            inline static const char * RED    = "\033[38;2;255;0;0m";
            inline static const char * YELLOW = "\033[38;2;255;199;6m";
            inline static const char * GREEN  = "\033[38;2;57;181;74m";
            inline static const char * WHITE  = "\033[38;2;255;255;255m";
            inline static const char * RESET  = "\033[0m";



            inline static const char * warning   = "\033[1;38;2;255;0;0m";
            inline static const char * end       = "\033[0m";
            inline static const char * started   = "\033[1;38;2;255;199;6m";
            inline static const char * finished  = "\033[1;38;2;57;181;74m";
            inline static const char * highlight = "\033[1;38;2;255;255;255m";

            
           
            
        };

    }
}

#endif