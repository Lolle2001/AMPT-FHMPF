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
    struct Line {

    };

    
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

    
    /*
    This class is a container for the statistics of the AMPT simulation. 
    It contains general functions for the child objects to access and 
    update the statistics.
    // */
    // class Statistics {
    //     public:
        
        
    //         // std::vector<std::vector<std::vector<std::map<int, StatisticsContainer * >>>> statistics;


    //         Statistics(){};


    //         // virtual void Add(Line & line){

    //         // }

    //         virtual void Calculate(){

    //         }

    //         void operator+=(const Statistics& other){

    //         };
    // };

    // class FourierFlow {
    //     public:
    //         std::vector<std::map<int, StatisticsContainer>> RadialFlow;
    //         std::vector<std::map<int, StatisticsContainer>> EllipticFlow;
    //         // std::vector<std::map<int, StatisticsContainer>> Flow3;
    //         // std::vector<std::map<int, StatisticsContainer>> Flow4;
    //         // std::vector<std::map<int, StatisticsContainer>> Flow5;
    //         // std::vector<std::map<int, StatisticsContainer>> Flow6;
    //         // std::vector<std::map<int, StatisticsContainer>> Flow7;

    //         FourierFlow(){};

    //         // void Add(Line_ampt & line , int & Event){
    //         //     if(line.EllipticFlow==line.EllipticFlow){
    //         //         if(line.TransverseMomentum > 0.1 && line.TransverseMomentum < 4. && line.PseudoRapidity > -0.5 && line.PseudoRapidity < 0.5 && ChargeMap[line.ParticlePythiaID] != 0){
    //         //                     EllipticFlow[Event][line.ParticlePythiaID].Add(line.EllipticFlow);
    //         //         }
    //         //     }
    //         // }

    //         // void Add(Line & line){

    //         // }

    //     // friend std::istream& operator>>(std::istream& input, Block_ampt& obj){
    //     //     input 
    //     //     >> obj.EventID 
    //     //     >> obj.EventIterationFlag  
    //     //     >> obj.NumberOfParticles
    //     //     >> obj.ImpactParameter
    //     //     >> obj.NumberOfParticipantNucleons_PROJ
    //     //     >> obj.NumberOfParticipantNulceons_TARG
    //     //     >> obj.NumberOfParticipantNucleonsElastic_PROJ
    //     //     >> obj.NumberOfParticipantNucleonsInelastic_PROJ
    //     //     >> obj.NumberOfParticipantNucleonsElastic_TARG
    //     //     >> obj.NumberOfParticipantNucleonsInelastic_TARG
    //     //     >> obj.PhiRP; 
    //     //     return input;
    //     // }


    // };
    // class TransverseMomentum : Statistics {

    // };
    // class TransverseMass : Statistics {

    // };
    // class ParticleYield : Statistics {

    // };




    
}

#endif