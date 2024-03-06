#include "AMPT_data.hpp"

namespace AMPT {

    std::istream & operator>>(std::istream & input, Line_ampt & obj){
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

    void Line_ampt::CalculateMomentum(){
        // Needs transverse momentum
        MomentumSQR = TransverseMomentumSQR + MomZ * MomZ;
        Momentum = std::sqrt(MomentumSQR);
    }

    void Line_ampt::CalculateEnergy(){
        // Needs momentum
        Energy = std::sqrt(Mass * Mass + MomentumSQR);
    }

    void Line_ampt::CalculatePhi(){
        Phi = std::atan2(MomY,MomX);
    }

    void Line_ampt::CalculateTransverseMomentum(){
        TransverseMomentumSQR = MomX*MomX + MomY*MomY;
        TransverseMomentum = std::sqrt(TransverseMomentumSQR);
    }

    void Line_ampt::CalculateAnisotropicFlow(int nharmonic){
        // Needs phi
        AnisotropicFlow[nharmonic] = std::cos(nharmonic*Phi);
    }

    void Line_ampt::CalculateTransverseMass(){
        // Needs transverse momentum
        TransverseMass = std::sqrt(Mass * Mass + TransverseMomentumSQR);
    }

    void Line_ampt::CalculatePseudoRapidity(){
        // Needs momentum
        PseudoRapidity = std::atanh(MomZ/Momentum);
    }

    void Line_ampt::CalculateRapidity(){
        // Needs momentum and energy
        Energy = std::sqrt(Mass * Mass + MomentumSQR);
        Rapidity = 0.5 * std::log((Energy + MomZ)/(Energy - MomZ));
    }

    void Line_ampt::CalculateProperties(int nharmonic_min, int nharmonic_max){
        CalculateTransverseMomentum();
        CalculateMomentum();
        CalculateEnergy();
        CalculatePhi();
        for(int i =  nharmonic_min; i <= nharmonic_max; ++i){
            CalculateAnisotropicFlow(i);
        }
        CalculatePseudoRapidity();
        CalculateRapidity(); 
    }

    std::istream& operator>>(std::istream& input, Block_ampt& obj){
        input 
        >> obj.EventID 
        >> obj.EventIterationFlag  
        >> obj.NumberOfParticles
        >> obj.ImpactParameter
        >> obj.NumberOfParticipantNucleons_PROJ
        >> obj.NumberOfParticipantNulceons_TARG
        >> obj.NumberOfParticipantNucleonsElastic_PROJ
        >> obj.NumberOfParticipantNucleonsInelastic_PROJ
        >> obj.NumberOfParticipantNucleonsElastic_TARG
        >> obj.NumberOfParticipantNucleonsInelastic_TARG
        >> obj.PhiRP; 
        return input;
    }

    std::ostream& operator<<(std::ostream& output, Block_ampt& obj){
        output <<  std::setw(6)  << std::left << obj.EventID << " ";
        output <<  std::setw(3) << std::left << obj.EventIterationFlag  << " ";
        output <<  std::setw(9) << std::left << obj.NumberOfParticles<< " ";
        output << std::scientific << std::setw(13) << std::left << obj.ImpactParameter<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleons_PROJ<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNulceons_TARG<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_PROJ<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_PROJ<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsElastic_TARG<< " ";
        output <<  std::setw(3) << std::left << obj.NumberOfParticipantNucleonsInelastic_TARG<< " ";
        output << std::scientific << std::setw(13)  << std::left << obj.PhiRP << " ";
        return output;
    }
        
}