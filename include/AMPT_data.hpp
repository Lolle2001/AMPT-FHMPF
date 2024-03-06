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

            double TransverseMomentum   ;
            double TransverseMomentumSQR;
            double Momentum;
            double MomentumSQR;
            double Energy;
            double TransverseMass;
            double AnisotropicFlow[6];
            double Phi;
            double PseudoRapidity;
            double Rapidity;

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
            
            
            void CalculateTransverseMomentum();
            void CalculateMomentum();
            void CalculateEnergy();
            void CalculatePhi();
            void CalculateAnisotropicFlow(int nharmonic);
            void CalculateTransverseMass();
            void CalculatePseudoRapidity();
            void CalculateRapidity();

            void CalculateProperties(int nharmonic_min, int nharmonic_max);
            
            int    GetParticlePythiaID() const {return ParticlePythiaID;}
            double GetMass() const {return Mass;}
            double GetFreezeOutTime() const {return FreezeOutTime;}
            double GetPosX() const {return PosX;}
            double GetPosY() const {return PosY;}
            double GetPosZ() const {return PosZ;}
            double GetMomX() const {return MomX;}
            double GetMomY() const {return MomY;}
            double GetMomZ() const {return MomZ;}

            double GetEnergy() const {return Energy;}
            double GetTransverseMomentum() const {return TransverseMomentum;}
            double GetTransverseMass() const {return TransverseMass;}
            double GetPseudoRapidity() const {return PseudoRapidity;}
            double GetRapidity() const {return Rapidity;}
            double GetMomentum() const {return Momentum;}
            double GetPhi() const {return Phi;}
            double GetAnisotropicFlow(int nharmonic) const {return AnisotropicFlow[nharmonic];}

            

        };

    std::istream & operator>>(std::istream & input, Line_ampt & obj);

    struct Block_ampt {
            int    EventID;
            int    EventIterationFlag;
            int    NumberOfParticles; // Hadrons and Deuterons
            double ImpactParameter;
            int    NumberOfParticipantNucleons_PROJ;
            int    NumberOfParticipantNulceons_TARG;
            int    NumberOfParticipantNucleonsElastic_PROJ;
            int    NumberOfParticipantNucleonsInelastic_PROJ;
            int    NumberOfParticipantNucleonsElastic_TARG;
            int    NumberOfParticipantNucleonsInelastic_TARG;
            double PhiRP; // Written to file 16: ampt.dat

            Block_ampt( int    EventID_, int    EventIterationFlag_, int    NumberOfParticles_, double ImpactParameter_, 
                int    NumberOfParticipantNucleons_PROJ_, int    NumberOfParticipantNulceons_TARG_, 
                int    NumberOfParticipantNucleonsElastic_PROJ_, int    NumberOfParticipantNucleonsInelastic_PROJ_, 
                int    NumberOfParticipantNucleonsElastic_TARG_, int    NumberOfParticipantNucleonsInelastic_TARG_, double PhiRP_
                ) : 
                EventID(EventID_), EventIterationFlag(EventIterationFlag_), NumberOfParticles(NumberOfParticles_), ImpactParameter(ImpactParameter_), 
                NumberOfParticipantNucleons_PROJ(NumberOfParticipantNucleons_PROJ_), NumberOfParticipantNulceons_TARG(NumberOfParticipantNulceons_TARG_), 
                NumberOfParticipantNucleonsElastic_PROJ(NumberOfParticipantNucleonsElastic_PROJ_), 
                NumberOfParticipantNucleonsInelastic_PROJ(NumberOfParticipantNucleonsInelastic_PROJ_), 
                NumberOfParticipantNucleonsElastic_TARG(NumberOfParticipantNucleonsElastic_TARG_), 
                NumberOfParticipantNucleonsInelastic_TARG(NumberOfParticipantNucleonsInelastic_TARG_), 
                PhiRP(PhiRP_){};

            Block_ampt(){};

            // std::istream& operator>>(std::istream& input){
            //     input 
            //     >> EventID 
            //     >> EventIterationFlag  
            //     >> NumberOfParticles
            //     >> ImpactParameter
            //     >> NumberOfParticipantNucleons_PROJ
            //     >> NumberOfParticipantNulceons_TARG
            //     >> NumberOfParticipantNucleonsElastic_PROJ
            //     >> NumberOfParticipantNucleonsInelastic_PROJ
            //     >> NumberOfParticipantNucleonsElastic_TARG
            //     >> NumberOfParticipantNucleonsInelastic_TARG
            //     >> PhiRP; 
            //     return input;
            // }

            
        };

    std::istream& operator>>(std::istream& input, Block_ampt& obj);

    std::ostream& operator<<(std::ostream& output, Block_ampt& obj);

}

#endif