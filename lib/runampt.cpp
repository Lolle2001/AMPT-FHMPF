#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include "Messenger.hpp"
#include "Timer.hpp"
#include "Progressbar.hpp"
#include "argparse/argparse.hpp"
#include <random>
#include <fstream>
#include <thread>
#include <boost/filesystem.hpp>
#include <omp.h>

using PP = Utilities::PretyPrint;

void create_output_folders(const unsigned int b_num, const std::string output_directory, const std::string output_name)
{

    for (int ib = 1; ib <= b_num; ++ib)
    {
        std::stringstream foldername;
        foldername << output_directory << "/" << output_name << "/" << output_name << "_" << ib;
        boost::filesystem::create_directories(foldername.str());
    }
}

void clear_bin_folders(const unsigned int b_min, const unsigned int b_max, const std::string bindirectory)
{
    for (int ib = b_min; ib <= b_max; ++ib)
    {
        std::stringstream foldername;
        foldername << bindirectory << "/ampt_" << ib << "/ana";
        if (boost::filesystem::exists(foldername.str()))
        {
            boost::filesystem::remove_all(foldername.str());
        }
        boost::filesystem::create_directories(foldername.str());
        foldername << 1;
        if (boost::filesystem::exists(foldername.str()))
        {
            boost::filesystem::remove_all(foldername.str());
        }
        boost::filesystem::create_directories(foldername.str());
    }
}

void copy_input_to_bin(const unsigned int b_min, const unsigned int b_max, const std::string bindirectory, const std::string input_path)
{
    std::string input_name = "input.ampt";
    for (int ib = b_min; ib <= b_max; ++ib)
    {
        std::stringstream filename;
        std::stringstream filename2;
        filename << bindirectory << "/ampt_" << ib << "/" << input_name;
        filename2 << bindirectory << "/ampt_" << ib << "/ana/" << input_name;
        if (boost::filesystem::exists(input_path))
        {
            boost::filesystem::copy_file(input_path, filename.str(), boost::filesystem::copy_option::overwrite_if_exists);
            boost::filesystem::copy_file(input_path, filename2.str(), boost::filesystem::copy_option::overwrite_if_exists);
        }
        else
        {
            std::cout << "input file does not exist" << std::endl;
            return;
        }
    }
}

void run_job(unsigned int rannum, unsigned int ib, const std::string bindirectory, Utilities::Duration &duration)
{
    boost::filesystem::path bindir = boost::filesystem::absolute(bindirectory);
    std::string dir = bindir.string() + "/ampt_" + std::to_string(ib);
    std::ofstream seed(dir + "/nseed");
    seed << rannum;
    seed.close();

    // std::stringstream command;
    // command << "cd" << " " << dir << " && " << "echo " << rannum << " >  nseed";
    // std::system(command.str().c_str());
    // // std::cout << bindirectory << std::endl;
    // std::cout << dir << std::endl;
    // std::cout << "Running job in directory: " << dir << std::endl;
    try
    {
        // Change the working directory to the target directory

        // Build the command to run the executable

        std::stringstream command;
        command << "cd " << dir << " && " << "./ampt < nseed 1> " << "ampt.log 2> " << "ampt.err";
        // std::cout << command.str() << std::endl;
        // Run the command
        std::string date_start = Utilities::return_current_time_and_date();
#pragma omp critical
        {
            printf("│ Job %02d started at  : %-44s │\n", ib, date_start.c_str());
        }
        duration = Utilities::Duration('H');

        duration.Start();
#if DEBUG == 0
        int state = std::system(command.str().c_str());
#endif
        std::string date_end = Utilities::return_current_time_and_date();

        duration.Stop();
#pragma omp critical
        {
            printf("│ Job %02d finished at : %-44s │\n", ib, date_end.c_str());
            printf("│ Job %02d finished in : %04ld:%02ld:%02ld.%03ld %-29s │\n", ib, (size_t)duration.chours, (size_t)duration.cminutes, (size_t)duration.cseconds, (size_t)duration.cmilliseconds, " ");
        }
        // Restore the original working directory
    }
    catch (const boost::filesystem::filesystem_error &ex)
    {

        std::cerr << "Error: " << ex.what() << std::endl;
    }
};

void run_jobs(unsigned int b_min, unsigned int b_max, const std::string bindirectory, size_t NEVENT)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99999999); // distribution in range [1, 6]

    std::vector<std::thread> threads;
    std::vector<Utilities::Duration> durations(b_max - b_min + 1);
    Utilities::Duration current_duration('H');
    current_duration.Start();

    // for (int ib = b_min; ib <= b_max; ++ib)
    // {
    //     unsigned int rannum = dist(rng);
    //     // std::cout << rannum << std::endl;
    //     int i = ib - b_min;
    //     // Utilities::Duration &tdur = durations[i];
    //     threads.emplace_back(run_job, rannum, ib, bindirectory, std::ref(durations[i]));
    //     sleep(1);
    // }
    // for (auto &thread : threads)
    // {
    //     if (thread.joinable())
    //     {
    //         thread.join();
    //     }
    // }
    std::vector<unsigned int> rannums(b_max - b_min + 1);
    for (int ib = 0; ib < b_max - b_min + 1; ++ib)
    {
        rannums[ib] = dist(rng);
    }

    size_t num_procs = omp_get_max_threads();

#pragma omp parallel for schedule(dynamic)
    for (int ib = b_min; ib <= b_max; ++ib)
    {
        unsigned int rannum = rannums[ib - b_min];
        // std::cout << rannum << std::endl;
        int i = ib - b_min;
        // Utilities::Duration &tdur = durations[i];
        sleep(i % num_procs);
        run_job(rannum, ib, bindirectory, std::ref(durations[i]));
    }

    current_duration.Stop();

    Utilities::Duration total_duration('H');
    total_duration.duration = std::chrono::nanoseconds(0);

    Utilities::Duration diff_duration('H');

    std::vector<int64_t> durations_ns(b_max - b_min + 1);
    for (int ib = 0; ib < b_max - b_min + 1; ++ib)
    {
        durations_ns[ib] = durations[ib].duration.count();
    }

    int64_t time_low = *std::min_element(durations_ns.begin(), durations_ns.end());
    int64_t time_high = *std::max_element(durations_ns.begin(), durations_ns.end());
    diff_duration.duration = std::chrono::nanoseconds(time_high - time_low);
    for (auto &duration : durations)
    {
        // printf("Adding duration: %04ld:%02ld:%02ld.%03ld\n",
        //        (size_t)duration.chours,
        //        (size_t)duration.cminutes,
        //        (size_t)duration.cseconds,
        //        (size_t)duration.cmilliseconds);
        total_duration += duration;
    }
    diff_duration.GetCounts('H');
    total_duration.GetCounts('H');

    Utilities::Duration event_duration(total_duration);
    event_duration.duration /= (b_max - b_min + 1) * NEVENT;
    event_duration.GetCounts('H');

    printf("%s├%-67s┤%s\n", PP::HIGHLIGHT, Utilities::repeat(67, "─").c_str(), PP::RESET);
    printf("│ Ending Time       : %-45s │\n", Utilities::return_current_time_and_date().c_str());
    printf("│ Elapsed Time      : %04ld:%02ld:%02ld.%03ld %-30s │\n", (size_t)current_duration.chours,
           (size_t)current_duration.cminutes,
           (size_t)current_duration.cseconds,
           (size_t)current_duration.cmilliseconds, " ");
    printf("│ Time spread       : %04ld:%02ld:%02ld.%03ld %-30s │\n",
           (size_t)diff_duration.chours,
           (size_t)diff_duration.cminutes,
           (size_t)diff_duration.cseconds,
           (size_t)diff_duration.cmilliseconds, " ");
    printf("│ Time per event    : %04ld:%02ld:%02ld.%03ld %-30s │\n", (size_t)event_duration.chours,
           (size_t)event_duration.cminutes,
           (size_t)event_duration.cseconds,
           (size_t)event_duration.cmilliseconds, " ");

    printf("│ Effeciency factor : %6.3f %-38s │\n", (double)total_duration.duration.count() / (double)current_duration.duration.count(), " ");
    printf("%s╰%-67s╯%s\n", PP::HIGHLIGHT, Utilities::repeat(67, "─").c_str(), PP::RESET);
}

int not_main(int argc, char **argv)
{

    return 0;
}
