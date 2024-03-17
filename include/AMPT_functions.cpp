#include "AMPT_functions.hpp"

namespace AMPT
{
    namespace Functions
    {

       
        double igcd(double a, double b, double base)
        {
            if (a < b)
            {
                return igcd(b, a, base);
            }
            if (std::fabs(b) < base)
            {
                return a;
            }
            else
            {
                return (igcd(b, a - std::floor(a / b) * b, base));
            }
        }

        std::vector<std::string> Extract(const std::string &Text)
        {
            std::vector<std::string> Words;
            std::stringstream ss(Text);
            std::string Buf;

            while (ss >> Buf)
            {
                // Words.push_back(std::move(Buf));
                Words.push_back(Buf);
            }

            return Words;
        }

        long double GetFileSize(std::filesystem::path filepath, const int option)
        {
            long double GB = 1000000000.; // 3
            long double MB = 1000000.;    // 2
            long double KB = 1000;        // 1
            try
            {

                std::uintmax_t size = std::filesystem::file_size(filepath);
                long double filesize = static_cast<long double>(size);
                switch (option)
                {
                case 3:
                    return filesize / GB;
                case 2:
                    return filesize / MB;
                case 1:
                    return filesize / KB;
                default:
                    return filesize;
                }
            }
            catch (const std::filesystem::filesystem_error &e)
            {
                std::cerr << "Error accessing the file: " << e.what() << std::endl;
                return 0.;
            }
        }

        std::vector<double> InitializeBins(int nbins, double min, double max)
        {
            std::vector<double> binedges(nbins + 1);
            double binwidth = (max - min) / nbins;
            for (int i = 0; i < nbins + 1; ++i)
            {
                binedges[i] = min + binwidth * i;
            }
            return binedges;
        }

        Duration::Duration(std::chrono::duration<int64_t, std::nano> &duration_) : duration(duration_){};
        Duration::Duration(
            std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
            std::chrono::time_point<std::chrono::high_resolution_clock> &stop_) : start(start_), stop(stop_)
        {
            GetDuration();
        };
        Duration::Duration(
            std::chrono::time_point<std::chrono::high_resolution_clock> &start_,
            std::chrono::time_point<std::chrono::high_resolution_clock> &stop_, char option) : start(start_), stop(stop_)
        {
            GetDuration();
            GetCounts(option);
        };

        void Duration::GetCounts(char option)
        {
            if (option == 'H')
            {
                hours = std::chrono::duration_cast<std::chrono::hours>(duration);
                duration -= hours;
                minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
                duration -= minutes;
                seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                duration -= seconds;
                milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
                chours = hours.count();
                cminutes = minutes.count();
                cseconds = seconds.count();
                cmilliseconds = milliseconds.count();
            }
            else if (option == 'M')
            {
                minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
                duration -= minutes;
                seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                duration -= seconds;
                milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

                cminutes = minutes.count();
                cseconds = seconds.count();
                cmilliseconds = milliseconds.count();
            }
            else if (option == 'S')
            {
                seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
                duration -= seconds;
                milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

                cseconds = seconds.count();
                cmilliseconds = milliseconds.count();
            }
        }

        void Duration::GetDuration()
        {
            duration = stop - start;
        }

        void PretyPrint::Warning(const std::string &text)
        {
            printf("%s%s%s\n", PretyPrint::WARNING, text.c_str(), PretyPrint::RESET);
        }
        void PretyPrint::Started(const std::string &text)
        {
            printf("%s%s%s\n", PretyPrint::STARTED, text.c_str(), PretyPrint::RESET);
        }
        void PretyPrint::Finished(const std::string &text)
        {
            printf("%s%s%s\n", PretyPrint::FINISHED, text.c_str(), PretyPrint::RESET);
        }
        void PretyPrint::Highlight(const std::string &text)
        {
            printf("%s%s%s\n", PretyPrint::HIGHLIGHT, text.c_str(), PretyPrint::RESET);
        }

    }
}
