#ifndef HISTOGRAM3D_HPP
#define HISTOGRAM3D_HPP

#include "StatisticsContainer.hpp"
#include "AMPT_functions.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <cmath>
#include <chrono>
#include <sstream>

using PP = AMPT::Functions::PretyPrint;

// namespace AMPT {
    namespace Statistics {
        using Vector3DMap = std::vector<std::vector<std::vector<std::map<int, StatisticsContainer>>>>;
        using Vector2DMap = std::vector<std::vector<std::map<int, StatisticsContainer>>>;
        using Vector1DMap = std::vector<std::map<int, StatisticsContainer>>;
        using Vector0DMap = std::map<int, StatisticsContainer>;
        
        
        
        using Vector1DMapVector1D = std::vector<std::map<int, std::vector<StatisticsContainer>>>;
        using Vector1DMapVector2D = std::vector<std::map<int, std::vector<std::vector<StatisticsContainer>>>>;
        using MapVector1D = std::map<int, std::vector<StatisticsContainer>>;

        using Vector3D = std::vector<std::vector<std::vector<StatisticsContainer>>>;
        using Vector2D = std::vector<std::vector<StatisticsContainer>>;
        using Vector1D = std::vector<StatisticsContainer>;
        

        class Histogram3D {
            private:
            Vector3D Contents;
            

            int nx, ny, nz;

            std::map < int, int > IndexMapX;
            std::map < int, int > IndexMapY;
            std::map < int, int > IndexMapZ;
            double x_max;
            double x_min;
            double x_width;
            double y_max;
            double y_min;
            double y_width;
            double z_max;
            double z_min;
            double z_width;

            std::vector<double> EdgesX;
            std::vector<double> EdgesY;
            std::vector<double> EdgesZ;

            public:
            Histogram3D(){};
            Histogram3D(int & nx_, int & ny_, int & nz_);
            Histogram3D(std::vector<double> EdgesX_, std::vector<double> EdgesY_, std::vector<double> EdgesZ_);

            void Resize(int & nx_, int & ny_, int & nz_);

            void InitializeIndexMap();

            void AddEvent();
            void Add(double & valx, double & valy, double & valz, double  valcontent);
            void AddCurrent(double & valx, double & valy, double & valz, double  valcontent);

            // void Convert();
            void PrintEdges(std::ostream & output);
            void PrintTotalSQR(std::ostream & output);
            void PrintTotal(std::ostream & output);
            void PrintCount(std::ostream & output);

            void ReadEdges(std::string filename);
            void ReadTotalSQR(std::string filename);
            void ReadTotal(std::string filename);
            void ReadCount(std::string filename);
            
            
            StatisticsContainer & operator()(int & ix, int & iy, int & iz);
            Vector1D & operator()(int & ix, int & iy);
            Vector2D & operator()(int & ix);

            
            StatisticsContainer & operator()(double & valx, double & valy, double & valz);
            Vector1D & operator()(double & valx, double & valy);
            Vector2D & operator()(double & valx);

            void operator+=(Histogram3D const & obj);



        };



    }
// }



#endif