#ifndef AMPT_DATA_HPP
#define AMPT_DATA_HPP

// #include "AMPT_statistics.hpp"
// #include "AMPT_ampt.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <iomanip>

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

    double Phi;
    double v[6];

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

    void GetPhi(){
        Phi = std::acos(MomX / TransverseMomentum);
    }
    void GetFourierFlow(){
        v[0] = std::cos(   Phi);
        v[1] = std::cos(2.*Phi);
        v[2] = std::cos(3.*Phi);
        v[3] = std::cos(4.*Phi);
        v[4] = std::cos(5.*Phi);
        v[5] = std::cos(6.*Phi);
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
        GetPhi();
        GetFourierFlow();
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
    int    NumberOfParticipantNucleons_TARG;
    int    NumberOfParticipantNucleonsElastic_PROJ;
    int    NumberOfParticipantNucleonsInelastic_PROJ;
    int    NumberOfParticipantNucleonsElastic_TARG;
    int    NumberOfParticipantNucleonsInelastic_TARG;
    double PhiRP; // Written to file 16: ampt.dat


        




    Block_ampt( int    EventID_, int    EventIterationFlag_, int    NumberOfParticles_, double ImpactParameter_, 
            int    NumberOfParticipantNucleons_PROJ_, int    NumberOfParticipantNucleons_TARG_, 
            int    NumberOfParticipantNucleonsElastic_PROJ_, int    NumberOfParticipantNucleonsInelastic_PROJ_, 
            int    NumberOfParticipantNucleonsElastic_TARG_, int    NumberOfParticipantNucleonsInelastic_TARG_, double PhiRP_
            ) : 
            EventID(EventID_), EventIterationFlag(EventIterationFlag_), NumberOfParticles(NumberOfParticles_), ImpactParameter(ImpactParameter_), 
            NumberOfParticipantNucleons_PROJ(NumberOfParticipantNucleons_PROJ_), NumberOfParticipantNucleons_TARG(NumberOfParticipantNucleons_TARG_), 
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
            >> obj.NumberOfParticipantNucleons_TARG
            >> obj.NumberOfParticipantNucleonsElastic_PROJ
            >> obj.NumberOfParticipantNucleonsInelastic_PROJ
            >> obj.NumberOfParticipantNucleonsElastic_TARG
            >> obj.NumberOfParticipantNucleonsInelastic_TARG
            >> obj.PhiRP; 
            return input;
        }

        // friend std::ifstream& operator>>(std::ifstream& input, Block_ampt& obj){
        //     input 
        //     >> obj.EventID 
        //     >> obj.EventIterationFlag  
        //     >> obj.NumberOfParticles
        //     >> obj.ImpactParameter
        //     >> obj.NumberOfParticipantNucleons_PROJ
        //     >> obj.NumberOfParticipantNulceons_TARG
        //     >> obj.NumberOfParticipantNucleonsElastic_PROJ
        //     >> obj.NumberOfParticipantNucleonsInelastic_PROJ
        //     >> obj.NumberOfParticipantNucleonsElastic_TARG
        //     >> obj.NumberOfParticipantNucleonsInelastic_TARG
        //     >> obj.PhiRP; 
        //     return input;
        // }

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
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleons_TARG<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_PROJ<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_PROJ<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_TARG<< " ";
            output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_TARG<< " ";
            output << std::scientific << std::setw(13)  << std::left << obj.PhiRP << " ";
            return output;
        }
};



    // struct Line {

    // };

    // struct Block {

    // };

    // class Data {

    // };

    

    // class File_zpc : Data {

    // };

    // etc...
}

#endif