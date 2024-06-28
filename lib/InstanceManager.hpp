#ifndef INSTANCEMANAGER_HPP
#define INSTANCEMANAGER_HPP

#include <string>
#include <filesystem>
#include "Timer.hpp"
#include <omp.h>
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include "Utilities.hpp"
#include <mutex>
namespace time_c = std::chrono;
using clock_c = std::chrono::high_resolution_clock;

namespace AMPT
{

    class InstanceManager
    {
    public:
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

        std::string manager_name;
        InstanceManager() = default;
        InstanceManager(size_t ID_, std::filesystem::path path_);

        // void SetPath(std::filesystem::path path);
        // void SetID(size_t ID);
        void SetSeeds(size_t HIJING_seed);

        void Clearbin();
        void Initialize(std::filesystem::path input_path);

        void MoveResults(std::filesystem::path output_path);
        void RunInstance();

        void CompileFromSource(std::filesystem::path source_path);
    };

}

#endif