// Copyright (C) 2024 Lieuwe Huisman

#include "Timer.hpp"

namespace Utilities
{

    // Duration::Duration(std::chrono::duration<int64_t, std::nano> &duration_) : duration(duration_){};
    // Duration::Duration(
    //     std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
    //     std::chrono::time_point<std::chrono::high_resolution_clock> &stop_) : start(start_), stop(stop_)
    // {
    //     GetDuration();
    // };
    // Duration::Duration(
    //     std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
    //     std::chrono::time_point<std::chrono::high_resolution_clock> &stop_, char option) : start(start_), stop(stop_)
    // {
    //     GetDuration();
    //     GetCounts(option);
    // };

    std::string return_current_time_and_date()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        std::time_t in_time_t = std::chrono::high_resolution_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }
    Duration::Duration(char option_, std::chrono::nanoseconds duration_)
    {
        option = option_;
        duration = std::chrono::nanoseconds(duration_);

        GetCounts(option);
        // std::cout << duration_.count() << " " << duration.count() << std::endl;
    }
    Duration::Duration(char option_)
    {
        option = option_;
    }

    void Duration::Start()
    {
        start = Clock::now();
    }
    void Duration::Stop()
    {
        stop = Clock::now();
        GetDuration();
        GetCounts(option);
    }

    void Duration::GetCounts(char option)
    {
        std::chrono::nanoseconds tduration(duration);
        if (option == 'H')
        {
            hours = std::chrono::duration_cast<std::chrono::hours>(tduration);
            tduration -= hours;
            minutes = std::chrono::duration_cast<std::chrono::minutes>(tduration);
            tduration -= minutes;
            seconds = std::chrono::duration_cast<std::chrono::seconds>(tduration);
            tduration -= seconds;
            milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tduration);
            chours = (unsigned long int)hours.count();
            cminutes = (unsigned long int)minutes.count();
            cseconds = (unsigned long int)seconds.count();
            cmilliseconds = (unsigned long int)milliseconds.count();
        }
        else if (option == 'M')
        {
            minutes = std::chrono::duration_cast<std::chrono::minutes>(tduration);
            tduration -= minutes;
            seconds = std::chrono::duration_cast<std::chrono::seconds>(tduration);
            tduration -= seconds;
            milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tduration);

            cminutes = (unsigned long int)minutes.count();
            cseconds = (unsigned long int)seconds.count();
            cmilliseconds = (unsigned long int)milliseconds.count();
        }
        else if (option == 'S')
        {
            seconds = std::chrono::duration_cast<std::chrono::seconds>(tduration);
            tduration -= seconds;
            milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tduration);

            cseconds = (unsigned long int)seconds.count();
            cmilliseconds = (unsigned long int)milliseconds.count();
        }
    }

    void Duration::operator+=(const Duration &other)
    {
        this->duration += other.duration;
    }

    void Duration::GetDuration()
    {
        duration = stop - start;
    }
}; // namespace Utilities
