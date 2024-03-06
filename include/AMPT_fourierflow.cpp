#include "AMPT_fourierflow.hpp"

namespace AMPT {
    namespace Statistics {

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
        
    }
}
