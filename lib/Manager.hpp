#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "InstanceManager.hpp"
#include <vector>
namespace AMPT
{

    class Manager
    {
    private:
        // input path
        // output path
        // bin path
        // bin_ids
        // starttime
        // endttime
        // nevent
        std::string instancedirectory_name;
        std::vector<size_t> bin_ids;

        std::filesystem::path input_path;
        std::filesystem::path output_path;
        std::filesystem::path bin_path;

        time_c::time_point<clock_c> starttime;
        time_c::time_point<clock_c> endtime;

        time_c::nanoseconds duration;
        time_c::nanoseconds duration_per_event;

        size_t NEVENT;
        size_t NEVENT_SINGLE;
        std::vector<InstanceManager> instance_managers;

    public:
        Manager() = default;
        Manager(std::filesystem::path input_path_,
                std::filesystem::path output_path_,
                std::filesystem::path bin_path_)
            : input_path(input_path_),
              output_path(output_path_),
              bin_path(bin_path_){};

        void Initialize()
        {
            for (size_t i = 0; i < bin_ids.size(); i++)
            {
                std::stringstream instance_name;
                instance_name << instancedirectory_name << "_" << bin_ids[i];
                instance_managers.push_back(InstanceManager(bin_ids[i], bin_path / instance_name.str()));
            }
        };

        void Run()
        {
            for (size_t i = 0; i < bin_ids.size(); i++)
            {
                starttime = clock_c::now();
                instance_managers[i].RunInstance();
                endtime = clock_c::now();
                duration = endtime - starttime;
                duration_per_event = duration / NEVENT;
            }
        }
    };
}

#endif