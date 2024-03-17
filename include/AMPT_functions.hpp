#ifndef AMPT_FUNCTIONS_HPP
#define AMPT_FUNCTIONS_HPP

#include <vector>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <map>

#include <cmath>

#include <sstream>

namespace AMPT
{
    namespace Functions
    {

        double igcd(double a, double b, double base);

        template <typename T>
        void Concatenate(std::vector<T> &v1, const std::vector<T> &v2)
        {
            v1.insert(std::end(v1), std::begin(v2), std::end(v2));
        };

        std::vector<std::string> Extract(const std::string &Text);

        long double GetFileSize(std::filesystem::path filepath, const int option = 0);

        std::vector<double> InitializeBins(int nbins, double min, double max);

        struct Duration
        {
            std::chrono::duration<int64_t, std::nano> duration;
            std::chrono::time_point<std::chrono::high_resolution_clock> start;
            std::chrono::time_point<std::chrono::high_resolution_clock> stop;

            int64_t cnanoseconds;
            int64_t cmicroseconds;
            int64_t cmilliseconds;
            int64_t cseconds;
            int64_t cminutes;
            int64_t chours;

            std::chrono::nanoseconds nanoseconds;
            ;
            std::chrono::microseconds microseconds;
            ;
            std::chrono::milliseconds milliseconds;
            ;
            std::chrono::seconds seconds;
            ;
            std::chrono::minutes minutes;
            ;
            std::chrono::hours hours;
            ;

            Duration(std::chrono::duration<int64_t, std::nano> &duration_);
            Duration(
                std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
                std::chrono::time_point<std::chrono::high_resolution_clock> &stop_);

            Duration(
                std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
                std::chrono::time_point<std::chrono::high_resolution_clock> &stop_, char option);

            void GetCounts(char option);

        private:
            void GetDuration();
        };

        struct PrettyPrint
        {
            std::string warning = "\033[1;38;2;255;0;0m";
            std::string end = "\033[0m";
            std::string started = "\033[1;38;2;255;199;6m";
            std::string finished = "\033[1;38;2;57;181;74m";
            std::string highlight = "\033[1;38;2;255;255;255m";
        };

        struct PretyPrint
        {
            inline static const char *BOLD = "\033[1m";
            inline static const char *RED = "\033[38;2;255;0;0m";
            inline static const char *YELLOW = "\033[38;2;255;199;6m";
            inline static const char *GREEN = "\033[38;2;57;181;74m";
            inline static const char *WHITE = "\033[38;2;255;255;255m";
            inline static const char *RESET = "\033[0m";

            inline static const char *WARNING = "\033[1;38;2;255;0;0m";
            inline static const char *STARTED = "\033[1;38;2;255;199;6m";
            inline static const char *FINISHED = "\033[1;38;2;57;181;74m";
            inline static const char *HIGHLIGHT = "\033[1;38;2;255;255;255m";

            void Warning(const std::string &text);
            void Started(const std::string &text);
            void Finished(const std::string &text);
            void Highlight(const std::string &text);
        };

    }
}

#endif