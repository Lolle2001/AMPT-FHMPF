#ifndef AMPT_STATISTICS_HPP
#define AMPT_STATISTICS_HPP

// #include "AMPT_ampt.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

namespace AMPT {
    /*
    Object that temporarly stores data from a read line. Putting it in to an 
    object allows cleaner code and easier generalisation of functions.
    */


    
    struct StatisticsContainer  {
        long double Total             = 0;
        long double TotalSQR          = 0;
        long int    EntryCount        = 0;
        long double Average           = 0;
        long double AverageSQR        = 0;
        long double Variance          = 0;
        long double StandardDeviation = 0;
        long double StandardError     = 0;
        long int    SampleCount       = 0;
        
        // StatisticsContainer();
       

        void Add(long double value){
            Total      += value;
            TotalSQR   += value*value;
            EntryCount += 1;
        }

        void RedefineTotalSQR(){
            TotalSQR = Total * Total;
        }
        void SetVariance(long double Variance_){
            Variance = Variance_;
        }
        void SetStandardError(long double StandardError_){
            StandardError = StandardError_;
        }

        void CalculatePoissonError(){
            StandardDeviation = std::sqrt(Average);
        }
       

        void CalculateAverage(){
            Average = Total/(long double)EntryCount;
        }

        void CalculateAverageSQR(){     
            AverageSQR = TotalSQR/(long double)EntryCount;
        }

        void CalculateVariance(){
            Variance = AverageSQR - Average*Average;
        }

        void CalculateStandardDeviation(){
            StandardDeviation = std::sqrt(Variance);
        }

        void CalculateStandardError(){
            // if(SampleCount > 0){
            StandardError = StandardDeviation/std::sqrt(EntryCount);
            // }
            // else{
                // std::cout << "SampleCount is zero, cannot calculate standard error." << std::endl;
            // }
        }

        void CalculateStatistics(){
            CalculateAverage();
            CalculateAverageSQR();
            CalculateVariance();
            CalculateStandardDeviation();
            CalculateStandardError();
        }

        long double GetAverage(){
            return Average;
        }

        long double GetAverageSQR(){
            return AverageSQR;
        }

        long double GetVariance(){
            return Variance;
        }

        long double GetStandardDeviation(){
            return StandardDeviation;
        }

        long double GetStandardError(){
            return StandardError;
        }

        long int GetSampleCount(){
            return SampleCount;
        }

        long int GetEntryCount(){
            return EntryCount;
        }

        void operator+=(StatisticsContainer const& rhs){
            Total             += rhs.Total;
            TotalSQR          += rhs.TotalSQR;
            EntryCount        += rhs.EntryCount;
            SampleCount       += rhs.SampleCount;
        }

        StatisticsContainer operator+(StatisticsContainer const& rhs){
            Total             += rhs.Total;
            TotalSQR          += rhs.TotalSQR;
            EntryCount        += rhs.EntryCount;
            SampleCount       += rhs.SampleCount;
            return * this;
        }

        void operator-=(StatisticsContainer const& rhs){    
            Total             -= rhs.Total;
            TotalSQR          -= rhs.TotalSQR;
            EntryCount        -= rhs.EntryCount;
            SampleCount       -= rhs.SampleCount;
        }

        StatisticsContainer operator-(StatisticsContainer const& rhs){  
            Total             -= rhs.Total;
            TotalSQR          -= rhs.TotalSQR;
            EntryCount        -= rhs.EntryCount;
            SampleCount       -= rhs.SampleCount;
            return * this;
        }

        friend std::ostream& operator<<(std::ostream& output, StatisticsContainer& obj){
            output << std::setw(13) << std::scientific << std::right << obj.Total            << " ";
            output << std::setw(13) << std::scientific << std::right << obj.TotalSQR         << " ";
            output << std::setw(13) << std::scientific << std::right << (long double)obj.EntryCount       << " ";
            output << std::setw(13) << std::scientific << std::right << obj.Average          << " ";
            output << std::setw(13) << std::scientific << std::right << obj.AverageSQR       << " ";
            output << std::setw(13) << std::scientific << std::right << obj.Variance         << " ";
            output << std::setw(13) << std::scientific << std::right << obj.StandardDeviation<< " ";
            output << std::setw(13) << std::scientific << std::right << obj.StandardError    << " ";
            output << std::setw(13) << std::scientific << std::right << (long double)obj.SampleCount      ;
            return output;
        }
    };
    
}

#endif