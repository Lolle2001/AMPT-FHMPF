#include "Manager.hpp"

namespace AMPT
{

    Manager::Manager(std::filesystem::path input_path_,
                     std::filesystem::path output_path_,
                     std::string output_name_,
                     std::filesystem::path bin_path_,
                     size_t b_min_, size_t b_max_,
                     std::string instancedirectory_name_)
        : input_path(input_path_),
          output_path(output_path_),
          bin_path(bin_path_), bin_id_min(b_min_), bin_id_max(b_max_), output_name(output_name_), instancedirectory_name(instancedirectory_name_){};

    Manager::Manager(std::filesystem::path bin_path_,
                     std::filesystem::path source_path_,
                     size_t b_min_, size_t b_max_, std::string instancedirectory_name_)
        : bin_path(bin_path_), source_path(source_path_), bin_id_min(b_min_), bin_id_max(b_max_), instancedirectory_name(instancedirectory_name_)
    {
    }

    void Manager::SetNevents(size_t events)
    {
        NEVENT_SINGLE = events;
    }

    void Manager::Initialize()
    {
        bin_id_num = bin_id_max - bin_id_min + 1;
        NEVENT = bin_id_num * NEVENT_SINGLE;
        bin_ids.resize(bin_id_num);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99999999); // distribution in range [1, 6]

        for (size_t i = 0; i < bin_ids.size(); i++)
        {

            bin_ids[i] = bin_id_min + i;
            std::stringstream instance_name;
            instance_name << instancedirectory_name << "-" << bin_ids[i];
            instance_managers.push_back(InstanceManager(bin_ids[i], bin_path / instance_name.str()));
            instance_managers[i].Initialize(input_path);
            instance_managers[i].SetSeeds(dist(rng));
        }
        startdate = Utilities::return_current_time_and_date();
    };

    void Manager::Compile()
    {
        bin_id_num = bin_id_max - bin_id_min + 1;
        bin_ids.resize(bin_id_num);
        for (size_t i = 0; i < bin_ids.size(); i++)
        {
            bin_ids[i] = bin_id_min + i;
            std::stringstream instance_name;
            instance_name << instancedirectory_name << "-" << bin_ids[i];
            instance_managers.push_back(InstanceManager(bin_ids[i], bin_path / instance_name.str()));
            instance_managers[i].CompileFromSource(source_path);
            std::string tempstring = fmt::format("Compiled instance: {}\n",instance_name.str());
            std::cout << tempstring;
        }
    }

    void Manager::Finalize()
    {
        for (size_t i = 0; i < bin_ids.size(); ++i)
        {
            std::stringstream suboutputname;
            suboutputname << output_path.string() << "/" << output_name << "-" << i + 1;
            instance_managers[i].MoveResults(std::filesystem::path(suboutputname.str()));
        }
    }

    void Manager::Run()
    {
        // std::cout << bin_id_num << std::endl;
        starttime = clock_c::now();
        std::cout << PrintInitInfo();

#pragma omp parallel for schedule(dynamic) ordered
        for (size_t i = 0; i < bin_ids.size(); i++)
        {

#pragma omp critical
            {
                std::string tempstring = fmt::format("{} Job {:02} started at  : {:<44} {}\n", w_00, bin_ids[i], Utilities::return_current_time_and_date().c_str(), w_00);
                std::cout << tempstring;
                screenstring += tempstring;
            }

            instance_managers[i].RunInstance();
            Utilities::Duration subduration('H', instance_managers[i].duration);

#pragma omp critical
            {

                std::string tempstring = fmt::format("{} Job {:02} finished at : {:<44} {}\n", w_00, bin_ids[i], Utilities::return_current_time_and_date().c_str(), w_00);
                std::cout << tempstring;
                screenstring += tempstring;
                tempstring = fmt::format("{} Job {:02} finished in : {:04d}:{:02d}:{:02d}.{:03d} {:<29} {}\n",
                                         w_00, bin_ids[i],
                                         (int)subduration.chours,
                                         (int)subduration.cminutes,
                                         (int)subduration.cseconds,
                                         (int)subduration.cmilliseconds, " ", w_00);
                std::cout << tempstring;
                screenstring += tempstring;
            }
        }

        endtime = clock_c::now();

        enddate = Utilities::return_current_time_and_date();

        duration = endtime - starttime;

        duration_per_event = duration / NEVENT;

        std::cout << PrintFinalInfo();
    }
    std::string Manager::PrintFinalInfo()
    {
        std::string s;
        std::chrono::nanoseconds min_time(instance_managers.front().duration);
        std::chrono::nanoseconds max_time(instance_managers.back().duration);
        std::chrono::nanoseconds total_subduration(0);
        for (size_t i = 0; i < instance_managers.size(); i++)
        {
            total_subduration += instance_managers[i].duration;
            if (instance_managers[i].duration < min_time)
            {
                min_time = instance_managers[i].duration;
            }
            if (instance_managers[i].duration > max_time)
            {
                max_time = instance_managers[i].duration;
            }
        }

        // std::cout << min_time.count() << " " << max_time.count() << " " << total_subduration.count() << " " << duration.count() << " " << duration_per_event.count();

        Utilities::Duration duration_total('H', duration);
        Utilities::Duration duration_spread('H', max_time - min_time);
        Utilities::Duration duration_pe('H', duration_per_event);
        double efficiency = -1;

        if (duration.count() > 0)
        {
            efficiency = (double)total_subduration.count() / (double)duration.count();
        }
        s += fmt::format("{}{:<67}{}\n", b_00, Utilities::repeat(67, "─"), b_01);
        s += fmt::format("{} Ending Time       : {:<45} {}\n", w_00, enddate.c_str(), w_00);
        s += fmt::format("{} Elapsed Time      : {:04}:{:02}:{:02}.{:03} {:<30} {}\n",
                         w_00,
                         (size_t)duration_total.chours,
                         (size_t)duration_total.cminutes,
                         (size_t)duration_total.cseconds,
                         (size_t)duration_total.cmilliseconds, " ", w_00);
        s += fmt::format("{} Time spread       : {:04}:{:02}:{:02}.{:03} {:<30} {}\n",
                         w_00, (size_t)duration_spread.chours,
                         (size_t)duration_spread.cminutes,
                         (size_t)duration_spread.cseconds,
                         (size_t)duration_spread.cmilliseconds, " ", w_00);
        s += fmt::format("{} Time per event    : {:04}:{:02}:{:02}.{:03} {:<30} {}\n",
                         w_00, (size_t)duration_pe.chours,
                         (size_t)duration_pe.cminutes,
                         (size_t)duration_pe.cseconds,
                         (size_t)duration_pe.cmilliseconds, " ", w_00);
        s += fmt::format("{} Effeciency factor : {:6.3} {:<38} {}\n", w_00, efficiency, " ", w_00);
        s += fmt::format("{}{:<67}{}\n", c_10, Utilities::repeat(67, "─"), c_11);
        return s;
    }
    std::string Manager::PrintInitInfo()
    {

        std::string s;

        s += fmt::format("{}{:<67}{}\n", c_00, Utilities::repeat(67, "─"), c_01);
        s += fmt::format("{} {:<65} {}\n", w_00, "AMPT Multiprocessing Interface", w_00);
        s += fmt::format("{} {:<65} {}\n", w_00, "Version 1.0.0", w_00);
        s += fmt::format("{} {:<65} {}\n", w_00, "Made by Lieuwe Huisman", w_00);
        s += fmt::format("{} {:<65} {}\n", w_00, "Made for AMPT version: v23.02.2024", w_00);
        s += fmt::format("{}{:<67}{}\n", b_00, Utilities::repeat(67, "─"), b_01);
        s += fmt::format("{} {:<16} : {:03} to {:03} {:<35} {}\n", w_00, "Bin range", bin_id_min, bin_id_max, "", w_00);
        s += fmt::format("{} {:<16} : {:<10} {:<35} {}\n", w_00, "Number of events", NEVENT, "", w_00);
        s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Input file", input_path.c_str(), w_00);
        s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Output directory", output_path.c_str(), w_00);
        s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Bin directory", bin_path.c_str(), w_00);
        s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Starting time", startdate.c_str(), w_00);
        s += fmt::format("{}{:<67}{}\n", b_00, Utilities::repeat(67, "─"), b_01);

        return s;
    }

}