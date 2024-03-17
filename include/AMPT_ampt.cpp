#include "AMPT_ampt.hpp"

namespace AMPT {

    
    void File_ampt::InitializeBins(){
        Data = Statistics::Data_ampt(1, 5);
        Data.InitializeHistograms();
    
    }

    
    void File_ampt::Parse(){
        #pragma omp critical
        {
        printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
        printf("%-17s : %s\n", "Parsing data from", FileDirectory.c_str());
        fflush(stdout);
        }
      
        std::ifstream File;
        File.open(FileDirectory.c_str(), std::ios::in);
        if(File.is_open()){
            Block_ampt TempBlock;
            Line_ampt TempLine;
            while(File >> TempBlock){
                for(int i = 0; i < TempBlock.NumberOfParticles; ++i){
                    File >> TempLine;
                    TempLine.CalculateProperties(1, 5);
                    Data.AddParticle(TempBlock.ImpactParameter, TempLine);
                }
                Data.AddEvent(TempBlock);
            }
            Data.ShrinkEventBlocks();
            
            
            #pragma omp critical
            {
            
            printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
            printf("%-17s : %s\n", "Parsed data from", FileDirectory.c_str());
            fflush(stdout);
            }
        
        }
        else{
            #pragma omp critical 
            {
            printf("%s%s%s ", PP::WARNING, "[WARNING]", PP::RESET);
            printf("%-17s : %s\n", "Cannot open file", FileDirectory.c_str());
            fflush(stdout);
            }
            
        }
        File.close();
    }


       

       

         void File_ampt::operator+=(File_ampt const & obj){
           
      
            Data += obj.Data;
           
           
        }

        
// [U] Add function that automatically determines NBatch.


File_ampt * CombineAMPT(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads, int collisiontype){
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %d(%d)\n", "Reading data from run (size)", NRun, NBatchMax - NBatchMin + 1);
    fflush(stdout);
   
    
    File_ampt * campt = new File_ampt(collisiontype);


    File_ampt * data[50];
   
    File_input * input;
    

    double FileSize = 0;
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        FileSize += AMPT::Functions::GetFileSize(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", 3);
    }
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %s%.3f GB%s\n", "Total datasize to read", PP::HIGHLIGHT, FileSize, PP::RESET);
    fflush(stdout);
   
    int TotalNevent = 0;

    int nevent[50];
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        input = new File_input(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");  
        input -> ReadFile();
        TotalNevent += input -> NEVENT;
        nevent[i] = input -> NEVENT;
        
    }
    printf("%s%s%s ", PP::STARTED, "[INFO]", PP::RESET);
    printf("%s : %s%d%s\n", "Total datasize to read", PP::HIGHLIGHT, TotalNevent, PP::RESET);
    fflush(stdout);

    // std::cout << input -> IAT << " " << input -> IZT << std::endl;
  
    for(int i = NBatchMin; i <= NBatchMax; ++i){    
        data[i] = new File_ampt(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", nevent[i], input, collisiontype);
        // data[i] -> Data.SetParameters(input);
        // data[i] -> Data.InitializeHistograms();
    }

    TimePoint_u start = Clock_u::now();
    #pragma omp parallel 
    {
        #pragma omp for
        for(int i = NBatchMin; i <= NBatchMax; ++i){    
            data[i] -> Parse();
        }
    }
    TimePoint_u stop = Clock_u::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02lld.%03lld%s\n", "Reading time", PP::HIGHLIGHT, duration.cminutes, duration.cseconds, duration.cmilliseconds, PP::RESET);
    fflush(stdout);
  
    for(int i = NBatchMin; i <= NBatchMax; ++i){      
        *campt += *data[i];   
        delete data[i];
    }
    TimePoint_u start2 = Clock_u::now();
  
    std::stringstream datadirectory;
    datadirectory << Directory << NRun << "/" << "processed";
    system(("mkdir -p \"" + datadirectory.str() + "\"").c_str());
    campt -> Data.WriteData(datadirectory.str());
    campt -> Data.WriteSettings(datadirectory.str());
    campt -> Data.WriteEventData(datadirectory.str());


    TimePoint_u stop2 = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration2(start2, stop2, 'M');
    long double totalsize = 0;
    std::filesystem::recursive_directory_iterator datadirectory_iter(datadirectory.str());
     for(const auto & entry : datadirectory_iter){
        totalsize += Functions::GetFileSize(entry.path(), 2);
        // std::cout <<  << std::endl;
    }
    
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%03ld:%02lld.%03lld%s\n", "Writing time", PP::HIGHLIGHT, duration2.cminutes, duration2.cseconds, duration2.cmilliseconds, PP::RESET);
    fflush(stdout);
    printf("%s%s%s ", PP::FINISHED, "[INFO]", PP::RESET);
    printf("%s : %s%.3Lf MB%s\n", "Total datasize written", PP::HIGHLIGHT, totalsize, PP::RESET);
    fflush(stdout);

  
    return campt;

}

AMPT::File_ampt * ReadAMPT(int NRun, std::string Directory){
    
    std::cout << PP::STARTED << "[AMPT::File_ampt]" << PP::RESET << " ";
    std::cout << "Reading processed data from run: " << NRun << std::endl; 
    
    AMPT::File_ampt * ampt = new AMPT::File_ampt(0);
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    // ampt -> ReadSettings(Directory + std::to_string(NRun) + "/processed/ampt_settings.dat");
    // ampt -> InitializeBins();
    // for(int i = 0; i < 6; ++i){
    //     ampt -> ReadFourierFlow(Directory  + std::to_string(NRun) + "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    // }
    // ampt -> ReadEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    // ampt -> ReadTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    
    // ampt -> ReadYield(Directory + std::to_string(NRun) + "/processed/ampt_particleyield_centrality.dat");
    // ampt -> ReadEventInfo(Directory  + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::FINISHED << "[AMPT::File_ampt]" << PP::RESET << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::HIGHLIGHT << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::RESET << std::endl;
    return ampt;
}


}

