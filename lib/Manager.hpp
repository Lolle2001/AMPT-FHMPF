#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "InstanceManager.hpp"
#include <vector>
#include <fmt/chrono.h>
#include "Progressbar.hpp"
#include <omp.h>
#include "Timer.hpp"
#include <random>
#include <unistd.h>
#include <iostream>
namespace AMPT
{

    class Manager
    {
    public:
         std::string c_00 = "╭";
        std::string c_01 = "╮";
        std::string c_10 = "╰";
        std::string c_11 = "╯";
        std::string w_00 = "│";
        std::string b_00 = "├";
        std::string b_01 = "┤";
        std::string instancedirectory_name;
        size_t bin_id_min;
        size_t bin_id_max;
        size_t bin_id_num;
        std::vector<size_t> bin_ids;

        std::filesystem::path input_path;
        std::filesystem::path output_path;
        std::filesystem::path bin_path;
        std::string output_name;

        time_c::time_point<clock_c> starttime;
        time_c::time_point<clock_c> endtime;
        std::string startdate;
        std::string enddate;
        std::string screenstring;
        std::filesystem::path source_path;

        time_c::nanoseconds duration;
        time_c::nanoseconds duration_per_event;

        size_t NEVENT;
        size_t NEVENT_SINGLE;
        std::vector<InstanceManager> instance_managers;

        Manager() = default;
        Manager(std::filesystem::path input_path_,
                std::filesystem::path output_path_,
                std::string output_name_,
                std::filesystem::path bin_path_,
                size_t b_min_, size_t b_max_,
                std::string instancedirectory_name_);
        Manager(std::filesystem::path bin_path_,
                std::filesystem::path source_path_,
                size_t b_min_, size_t b_max_, std::string instancedirectory_name_);

        void SetNevents(size_t events);

        void Initialize();

        void Compile();

        void Finalize();

        void Run();
        std::string PrintFinalInfo();
        std::string PrintInitInfo();
    };
}

#endif