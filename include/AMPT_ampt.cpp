#include "AMPT_ampt.hpp"

namespace AMPT {

    
    void File_ampt::InitializeBins(){
        centrality_nbins = centrality_edges.size() - 1;
        centrality_event_counter.resize(centrality_nbins, 0);
        participation_nbins = participation_edges.size() - 1;
        Statistics.Initialize(centrality_nbins);
    }

    

    void File_ampt::Parse2(){
        #pragma omp critical
        {
        printf("%s%s%s ", PP::started, "[INFO]", PP::end);
        printf("%-17s : %s\n", "Parsing data from", FileDirectory.c_str());
        fflush(stdout);
        }
      
        std::ifstream File;
        File.open(FileDirectory.c_str(), std::ios::in);
        if(File.is_open()){
            Block_ampt TempBlock;
            Line_ampt TempLine;
          
            int ib;

            while(File >> TempBlock){
                EventBlocks.emplace_back(TempBlock);
                // for(int b = 0; b < centrality_nbins; ++b){
                    // if(TempBlock.ImpactParameter >= centrality_edges[b] && TempBlock.ImpactParameter < centrality_edges[b+1]){
                        
                        // std::cout << b << " " << centrality_event_counter[b] << std::endl;


                for(int i = 0; i < TempBlock.NumberOfParticles; ++i){
                    File >> TempLine;
                    TempLine.CalculateProperties(0, 3);
                    ib = Statistics.Add2(TempBlock.ImpactParameter, TempLine);//, TempMap);
                        
                        // }
                    // }
                }
                centrality_event_counter[ib] += 1;
            }
            EventBlocks.shrink_to_fit();
            NumberOfEvents = EventBlocks.size();
            
            #pragma omp critical
            {
            
            printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
            printf("%-17s : %s\n", "Parsed data from", FileDirectory.c_str());
            fflush(stdout);
            }
        
        }
        else{
            #pragma omp critical
            {
            printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
            printf("%-17s : %s\n", "Cannot open file", FileDirectory.c_str());
            fflush(stdout);
            }
            
        }
        File.close();
    }


        void File_ampt::Convert(){
            Statistics.Convert();
        }

        void File_ampt::WriteEventInfo(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            if(File.is_open()){
                File << NumberOfEvents << std::endl;
                
                for(int i = 0; i < NumberOfEvents; ++i){
                    File << EventBlocks[i] << std::endl;
                    // AMPT::Functions::printProgressBar(i, NumberOfEvents - 1);
                }
                // std::cout << std::endl;
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fKB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written event data to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

         void File_ampt::WriteEllipticFlow(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.EllipticFlow.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written flow data to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void File_ampt::WriteFourierFlow(std::string Filename, int n){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.v[n].Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written flow data to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void File_ampt::WriteYield(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.ParticleYield.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 2);
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fMB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written yield data to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            // AMPT::Functions::PrintTiming(start, stop, Filename);
        }

        void File_ampt::WriteTransverseMomentum(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();;
            if(File.is_open()){
                int TempMapSize;
                File << centrality_nbins << std::endl;
                for(int i = 0; i < centrality_nbins; ++i){
                    File << i << " " << centrality_event_counter[i] << " " << centrality_edges[i] << " " << centrality_edges[i+1] << std::endl;
                    Statistics.TransverseMomentum.Write(File, i);
                }
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fKB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written transverse momentum data to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            // std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();;
            
        }

        void File_ampt::WriteSettings(std::string Filename){
            std::ofstream File;
            File.open(Filename.c_str(), std::ios::out);
            if(File.is_open()){
                File << centrality_nbins << std::endl;
                for(int i = 0; i <= centrality_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << centrality_edges[i] << " ";
                }
                File << std::endl;
                File << participation_nbins << std::endl;
                for(int i = 0; i <= participation_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << participation_edges[i] << " ";
                }
                File << std::endl;
                File << Statistics.momentum_nbins << std::endl;
                for(int i = 0; i <=  Statistics.momentum_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << Statistics.momentum_edges[i] << " ";
                }
                File << std::endl;
                File << Statistics.pseudorapidity_nbins << std::endl;
                for(int i = 0; i <=  Statistics.pseudorapidity_nbins; i++){
                    File << std::scientific << std::right << std::setw(13) << Statistics.pseudorapidity_edges[i] << " ";
                }
                File << std::endl;
                File.close();
                double Filesize = AMPT::Functions::GetFileSize(Filename, 1);
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
                printf("%s[%07.3fKB]%s ", PP::highlight, Filesize, PP::end);
                printf("%-17s : %s\n", "Written settings to",  Filename.c_str());
                fflush(stdout);
                }
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
            
        }

        void File_ampt::ReadSettings(std::string Filename){
            std::ifstream File;
            File.open(Filename.c_str(), std::ios::in);

            if(File.is_open()){
                std::string line;
                std::stringstream ss;
                File >> centrality_nbins;
                centrality_edges.resize(centrality_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= centrality_nbins; i++){
                    ss >> centrality_edges[i];
                }
                File >> participation_nbins;
                participation_edges.resize(participation_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= participation_nbins; i++){
                    ss >> participation_edges[i];
                }
                File >> Statistics.momentum_nbins;
                Statistics.momentum_edges.resize(Statistics.momentum_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= Statistics.momentum_nbins; i++){
                    ss >> Statistics.momentum_edges[i];
                }
                File >> Statistics.pseudorapidity_nbins;
                Statistics.pseudorapidity_edges.resize(Statistics.pseudorapidity_nbins+1);
                getline(File >> std::ws, line);
                ss = std::stringstream(line);
                for(int i = 0; i <= Statistics.pseudorapidity_nbins; i++){
                    ss >> Statistics.pseudorapidity_edges[i];
                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read settings from: " << Filename << std::endl;
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Filename.c_str());
                fflush(stdout);
                }
            }
        }

        void File_ampt::ReadFourierFlow(std::string Directory, int n){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.v[n].Read(File, i, TempMapSize);
                    

                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read flow data from: " << Directory << std::endl;
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Directory.c_str());
                fflush(stdout);
                }
            }
            File.close();
        }

         void File_ampt::ReadEllipticFlow(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    // std::cout << centrality_event_counter[i] << std::endl;
                    File >> TempMapSize;

                    Statistics.EllipticFlow.Read(File, i, TempMapSize);
                    

                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read flow data from: " << Directory << std::endl;
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Directory.c_str());
                fflush(stdout);
                }
            }
            File.close();
        }

        void File_ampt::ReadTransverseMomentum(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.EllipticFlow.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.TransverseMomentum.Read(File, i, TempMapSize);
                    

                }
  
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read transverse momentum data from: " << Directory << std::endl;
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Directory.c_str());
                fflush(stdout);
                }
            }
            File.close();
        }

        void File_ampt::ReadYield(std::string Directory){
            std::ifstream File;

            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                Block_ampt TempBlock;
               
                std::string line;
                int TempMapSize;
                int TempID;
                std::string value;
                int TempCentralityBins;
                double Bmin;
                double Bmax;
                File >> TempCentralityBins;
           
                // std::cout << Statistics.ParticleYield.VectorMap_3D.size() << std::endl;
                for(int i = 0; i < TempCentralityBins; ++i){
                   
                    File >> TempID >> centrality_event_counter[i] >> Bmin >> Bmax;
                    File >> TempMapSize;

                    Statistics.ParticleYield.Read(File, i, TempMapSize);

                }
  

             std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read yield data from: " << Directory << std::endl;
            }
            else{
                #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Directory.c_str());
                fflush(stdout);
                }
            }
            File.close();
        }

        void File_ampt::ReadEventInfo(std::string Directory){
            std::ifstream File;
            
            File.open(Directory.c_str(), std::ios::in);
            if(File.is_open()){
                File >> NumberOfEvents;
                
                EventBlocks.resize(NumberOfEvents);
                for(int i = 0; i < NumberOfEvents; ++i){
                    // std::cout << i << std::endl;
                    File >> EventBlocks[i];
                    // std::cout << EventBlocks[i] << std::endl;
                }
                std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
                std::cout << "Read event data from: " << Directory << std::endl;
            }
            else{
                 #pragma omp critical
                {
                printf("%s%s%s ", PP::warning, "[WARNING]", PP::end);
                printf("%-17s : %s\n", "Cannot open file", Directory.c_str());
                fflush(stdout);
                }
            }
            File.close();
        }


        void File_ampt::PrintEventInfo(){
            
            for(int i = 0; i < NumberOfEvents; ++i){
                std::cout << EventBlocks[i] << std::endl;
            }
        }

         void File_ampt::operator+=(File_ampt const & obj){
            AMPT::Functions::Concatenate(EventBlocks, obj.EventBlocks);
            // AMPT::Functions::Concatenate(EllipticFlow_event_momentum_map_vector, obj.EllipticFlow_event_momentum_map_vector);
            // AMPT::Functions::Concatenate(EllipticFlow_event_momentum_vector_map, obj.EllipticFlow_event_momentum_vector_map);
            Statistics += obj.Statistics;
            for(int b = 0 ; b < centrality_nbins; ++b){
                centrality_event_counter[b] += obj.centrality_event_counter[b];
            }
            NumberOfEvents += obj.NumberOfEvents;
            int StartIndex = NumberOfEvents - obj.NumberOfEvents;
            for(int i = StartIndex; i < NumberOfEvents; ++i){
                EventBlocks[i].EventID += StartIndex;
            }

        }

        

       
        
        



File_ampt * Combine_ampt_multi_queued(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads){
    
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading data from run (size): " << NRun << "(" << NBatchMax - NBatchMin + 1 << ")" << std::endl; 
    
    
    File_ampt * campt = new File_ampt();


    File_ampt * data[50];
    std::thread threads[50];
    

    double FileSize = 0;
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        FileSize += AMPT::Functions::GetFileSize(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", 3);
    }

    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Total datasize to read: ";
    std::cout << PP::highlight << std::fixed << std::setprecision(3) << FileSize << " GB" << PP::end << std::endl;
    int TotalNevent = 0;

    int nevent[50];
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        File_input * input = new File_input(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");  
        input -> ReadFile();
        TotalNevent += input -> NEVENT;
        nevent[i] = input -> NEVENT;
        delete input;
    }
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Total number of events to parse: " <<PP::highlight << TotalNevent << PP::end << std::endl;
    
    for(int i = NBatchMin; i <= NBatchMax; ++i){    
        
        
        // std::cout << input -> NEVENT << std::endl;
        data[i] = new File_ampt(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", nevent[i]);
        threads[i] = std::thread(&File_ampt::Parse2, data[i]);
        
    }
    

    int ThreadCounter = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        ThreadCounter++;
        if(ThreadCounter == NumberOfThreads){
            for(int j = i - NumberOfThreads + 1; j <=i; j++){
                threads[j].join();
            }
           
            ThreadCounter = 0;
        }
    }
    for(int i = NBatchMax - ThreadCounter + 1; i <= NBatchMax; ++i){
        threads[i].join();
    }
   
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    for(int i = NBatchMin; i <= NBatchMax; ++i){      
        *campt += *data[i];   
        delete data[i];
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> start2 = std::chrono::high_resolution_clock::now();
    campt -> Convert();
    system(("mkdir -p \"" + Directory + std::to_string(NRun) + "/processed\"").c_str());
    campt -> WriteSettings(Directory + std::to_string(NRun)+ "/processed/ampt_settings.dat");
    for(int i = 0; i < 6; ++i){
         campt -> WriteFourierFlow(Directory + std::to_string(NRun)+ "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    }
    campt -> WriteEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    campt -> WriteTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    campt -> WriteYield(Directory + std::to_string(NRun)+ "/processed/ampt_particleyield_centrality.dat");
    campt -> WriteEventInfo(Directory + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    std::chrono::time_point<std::chrono::high_resolution_clock> stop2 = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration2(start2, stop2, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Writing time [m:s:ms]: " << PP::highlight << duration2.cminutes << ":" << std::setw(2) << std::setfill('0') << duration2.cseconds << ":" << std::setw(3) << std::setfill('0') << duration2.cmilliseconds << PP::end << std::endl;
    return campt;

}


File_ampt * Combine_ampt_multi_queued_omp(int NRun, int NBatchMin, int NBatchMax, std::string Directory, int NumberOfThreads){
    printf("%s%s%s ", PP::started, "[INFO]", PP::end);
    printf("%s : %d(%d)\n", "Reading data from run (size)", NRun, NBatchMax - NBatchMin + 1);
    fflush(stdout);
    // std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    // std::cout << "Reading data from run (size): " << NRun << "(" << NBatchMax - NBatchMin + 1 << ")" << std::endl; 
    
    
    File_ampt * campt = new File_ampt();


    File_ampt * data[50];
    // std::thread threads[50];
    

    double FileSize = 0;
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        FileSize += AMPT::Functions::GetFileSize(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", 3);
    }
    printf("%s%s%s ", PP::started, "[INFO]", PP::end);
    printf("%s : %s%.3f GB%s\n", "Total datasize to read", PP::highlight, FileSize, PP::end);
    fflush(stdout);
    // std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    // std::cout << "Total datasize to read: ";
    // std::cout << PP::highlight << std::fixed << std::setprecision(3) << FileSize << " GB" << PP::end << std::endl;
    int TotalNevent = 0;

    int nevent[50];
    for(int i = NBatchMin; i <= NBatchMax; ++i){
        File_input * input = new File_input(Directory + std::to_string(NRun)+ "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/input.ampt");  
        input -> ReadFile();
        TotalNevent += input -> NEVENT;
        nevent[i] = input -> NEVENT;
        delete input;
    }
    printf("%s%s%s ", PP::started, "[INFO]", PP::end);
    printf("%s : %s%d%s\n", "Total datasize to read", PP::highlight, TotalNevent, PP::end);
    fflush(stdout);
    // std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    // std::cout << "Total number of events to parse: " <<PP::highlight << TotalNevent << PP::end << std::endl;
    for(int i = NBatchMin; i <= NBatchMax; ++i){    
        data[i] = new File_ampt(Directory + std::to_string(NRun) + "/" + std::to_string(NRun) + "_" + std::to_string(i) + "/ana/ampt.dat", nevent[i]);
    }

    TimePoint_u start = Clock_u::now();
    #pragma omp parallel 
    {
        #pragma omp for
        for(int i = NBatchMin; i <= NBatchMax; ++i){    
            data[i] -> Parse2();
        }
    }
    TimePoint_u stop = Clock_u::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Reading time", PP::highlight, duration.cminutes, duration.cseconds, duration.cmilliseconds, PP::end);
    fflush(stdout);
    // std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    // std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    for(int i = NBatchMin; i <= NBatchMax; ++i){      
        *campt += *data[i];   
        delete data[i];
    }
    TimePoint_u start2 = Clock_u::now();
    campt -> Convert();
    system(("mkdir -p \"" + Directory + std::to_string(NRun) + "/processed\"").c_str());
    campt -> WriteSettings(Directory + std::to_string(NRun)+ "/processed/ampt_settings.dat");
    for(int i = 0; i < 6; ++i){
         campt -> WriteFourierFlow(Directory + std::to_string(NRun)+ "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    }
    campt -> WriteEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    campt -> WriteTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    campt -> WriteYield(Directory + std::to_string(NRun)+ "/processed/ampt_particleyield_centrality.dat");
    campt -> WriteEventInfo(Directory + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    TimePoint_u stop2 = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration2(start2, stop2, 'M');
    printf("%s%s%s ", PP::finished, "[INFO]", PP::end);
    printf("%s : %s%03ld:%02ld.%03ld%s\n", "Writing time", PP::highlight, duration2.cminutes, duration2.cseconds, duration2.cmilliseconds, PP::end);
    fflush(stdout);
    // std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    // std::cout << "Writing time [m:s:ms]: " << PP::highlight << duration2.cminutes << ":" << std::setw(2) << std::setfill('0') << duration2.cseconds << ":" << std::setw(3) << std::setfill('0') << duration2.cmilliseconds << PP::end << std::endl;
    return campt;

}

AMPT::File_ampt * ReadAMPT(int NRun, std::string Directory){
    
    std::cout << PP::started << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading processed data from run: " << NRun << std::endl; 
    
    AMPT::File_ampt * ampt = new AMPT::File_ampt();
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    ampt -> ReadSettings(Directory + std::to_string(NRun) + "/processed/ampt_settings.dat");
    ampt -> InitializeBins();
    for(int i = 0; i < 6; ++i){
        ampt -> ReadFourierFlow(Directory  + std::to_string(NRun) + "/processed/ampt_v" + std::to_string(i +1) + "_centrality.dat", i);
    }
    ampt -> ReadEllipticFlow(Directory + std::to_string(NRun)+ "/processed/ampt_ellipticflow_centrality.dat");
    ampt -> ReadTransverseMomentum(Directory + std::to_string(NRun) + "/processed/ampt_transversemomentum.dat");
    
    ampt -> ReadYield(Directory + std::to_string(NRun) + "/processed/ampt_particleyield_centrality.dat");
    ampt -> ReadEventInfo(Directory  + std::to_string(NRun) + "/processed/ampt_eventinfo.dat");
    std::chrono::time_point<std::chrono::high_resolution_clock> stop = std::chrono::high_resolution_clock::now();
    AMPT::Functions::Duration duration(start, stop, 'M');
    std::cout << PP::finished << "[AMPT::File_ampt]" << PP::end << " ";
    std::cout << "Reading time [m:s:ms]: " << PP::highlight << duration.cminutes << ":" << std::setw(2) << std::setfill('0') << duration.cseconds << ":" << std::setw(3) << std::setfill('0') << duration.cmilliseconds << PP::end << std::endl;
    return ampt;
}


}

