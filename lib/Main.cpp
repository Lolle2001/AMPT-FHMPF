#include <fmt/chrono.h>
#include "Manager.hpp"
#include <iostream>
#include "Progressbar.hpp"
#include "Messenger.hpp"
#include "Timer.hpp"
using PP = Utilities::PretyPrint;
void PrintInfo(AMPT::Manager &manager, std::ostream &output)
{
    std::string c_00;
    std::string c_01;
    std::string c_10;
    std::string c_11;
    std::string w_00;
    std::string b_00;
    std::string b_01;
    if (&output == &std::cout)
    {
        c_00 = fmt::format("{}{}╭{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        c_01 = fmt::format("{}{}╮{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        c_10 = fmt::format("{}{}╰{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        c_11 = fmt::format("{}{}╯{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        w_00 = fmt::format("{}{}│{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        b_00 = fmt::format("{}{}├{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
        b_01 = fmt::format("{}{}┤{}", PP::HIGHLIGHT, PP::WHITE, PP::RESET);
    }
    else
    {
        c_00 = "╭";
        c_01 = "╮";
        c_10 = "╰";
        c_11 = "╯";
        w_00 = "│";
        b_00 = "├";
        b_01 = "┤";
    }

    std::string s;
    size_t b_min = 1;
    size_t b_max = 10;
    size_t b_num = b_max - b_min + 1;
    std::string path_input = "data";
    std::string path_output = "bin";
    size_t NEVENT = 10;
    std::string date_start = Utilities::return_current_time_and_date();
    s += fmt::format("{}{:<67}{}\n", c_00, Utilities::repeat(67, "─"), c_01);
    s += fmt::format("{} {:<65} {}\n", w_00, "AMPT Multiprocessing Interface", w_00);
    s += fmt::format("{} {:<65} {}\n", w_00, "Version 1.0.0", w_00);
    s += fmt::format("{} {:<65} {}\n", w_00, "Made by Lieuwe Huisman", w_00);
    s += fmt::format("{} {:<65} {}\n", w_00, "Made for AMPT version: v23.02.2024", w_00);
    s += fmt::format("{}{:<67}{}\n", b_00, Utilities::repeat(67, "─"), b_01);
    s += fmt::format("{} {:<16} : {:03} to {:03} {:<35} {}\n", w_00, "Bin range", b_min, b_max, "", w_00);
    s += fmt::format("{} {:<16} : {:<3} {:<42} {}\n", w_00, "Number of events", b_num * NEVENT, "", w_00);
    s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Input file", path_input.c_str(), w_00);
    s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Output directory", path_output.c_str(), w_00);
    s += fmt::format("{} {:<16} : {:<46} {}\n", w_00, "Starting time", date_start.c_str(), w_00);
    s += fmt::format("{}{:<67}{}\n", b_00, Utilities::repeat(67, "─"), b_01);
    output << s << std::endl;
}

int main(int argc, char **argv)
{
    AMPT::Manager manager;
    PrintInfo(manager, std::cout);
    std::ofstream file("test.txt");
    PrintInfo(manager, file);
    file.close();
    return 0;
}