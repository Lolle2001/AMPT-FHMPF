#ifndef INSTANCEMANAGER_HPP
#define INSTANCEMANAGER_HPP

#include <string>
#include <filesystem>
#include "Timer.hpp"
#include <fstream>

namespace time_c = std::chrono;
using clock_c = std::chrono::high_resolution_clock;

namespace AMPT
{

    class InstanceManager
    {
    private:
        std::filesystem::path path;
        size_t ID;
        size_t HIJING_seed;
        size_t ZPC_seed;
        size_t NEVENT;
        int execution_state;
        time_c::time_point<clock_c> starttime;
        time_c::time_point<clock_c> endtime;

        time_c::nanoseconds duration;
        time_c::nanoseconds duration_per_event;

    public:
        InstanceManager(size_t ID_, std::filesystem::path path_) : path(path_), ID(ID_)
        {
            path = std::filesystem::absolute(path);
        };

        // void SetPath(std::filesystem::path path);
        // void SetID(size_t ID);
        void SetSeeds(size_t HIJING_seed, size_t ZPC_seed)
        {
            std::filesystem::path out(path);
            out.append("hijing_seed.dat");

            std::ofstream file(out, std::ios::out);
            file << HIJING_seed;
            file.close();
        };
        void Initialize(std::filesystem::path input_path)
        {
            input_path = std::filesystem::absolute(input_path);
            std::filesystem::path out1(path);
            std::filesystem::path out2(path);
            std::filesystem::path out3(path);
            out1.append("input.ampt");
            out2.append("ana/");
            std::filesystem::create_directories(out2);
            out3.append("ana1/");
            std::filesystem::create_directories(out3);
            out2.append("input.ampt");
            std::filesystem::copy_file(input_path, out1);
            std::filesystem::copy_file(input_path, out2);
        };

        void MoveResults(std::filesystem::path output_path)
        {

            output_path = std::filesystem::absolute(output_path);

            std::filesystem::copy(path / "ana", output_path);
            std::filesystem::copy(path / "ana1", output_path);
            std::filesystem::copy(path / "ampt.log", output_path);
            std::filesystem::copy(path / "ampt.err", output_path);
        }
        void RunInstance()
        {

            starttime = clock_c::now();
            std::stringstream command;
            command << "cd " << path << " && " << "./ampt < nseed 1> " << "ampt.log 2> " << "ampt.err";
            execution_state = std::system(command.str().c_str());
            endtime = clock_c::now();
            duration = endtime - starttime;
            duration_per_event = duration / NEVENT;
        };
    };

}

#endif