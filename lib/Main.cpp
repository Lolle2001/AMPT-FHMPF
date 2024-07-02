// Copyright (C) 2024 Lieuwe Huisman

#include <fmt/chrono.h>
#include "Manager.hpp"
#include <iostream>
#include "Progressbar.hpp"
#include "Messenger.hpp"
#include "Timer.hpp"
#include <argparse/argparse.hpp>
#define NAME "ampt-mp"
#define AUTHOR "Liewe Huisman"
#define PROGRAM_VERSION "1.0.0"
#define COMPILER_VERSION "1.0.0"
#define DEBUG 0
using PP = Utilities::PretyPrint;

int main(int argc, char **argv)
{

    argparse::ArgumentParser program(NAME, PROGRAM_VERSION);
    program.add_description("This program is an interface to run multiple AMPT executables simultaneously such that all CPU cores can be used. Disclaimer: the method used has no proper synchronization.");

    program.add_argument("-i", "--input")
        .default_value(std::string{"ampt@default.par"})
        .help("the filename of the input.");
    program.add_argument("-id", "--input-directory")
        .default_value(std::string{"./input"})
        .help("the directory where the input file is located.");
    program.add_argument("-o", "--output")
        .default_value(std::string{"1"})
        .help("the name of the output.");
    program.add_argument("-od", "--output-directory")
        .default_value(std::string{"./data"})
        .help("the directory where the output is stored (i.e. the folders ana and ana1 and logs).");
    program.add_argument("-bd", "--bin-directory")
        .default_value(std::string{"./bin"})
        .help("the directory where the instance directories must be located.");
    program.add_argument("-b", "--binrange")
        .default_value(std::vector<int>{1, 1})
        .nargs(2)
        .scan<'i', int>()
        .help("the number range of the instance directories.");
    program.add_argument("-in", "--instance-name")
        .default_value(std::string{"ampt"})
        .help("the prefix of the instance directories.");

    /* TO BE IMPLEMENTED
        program.add_argument("-if", "--input-format")
        .default_value(std::string{"ampt"})
        .choices("ampt", "json");

    program.add_argument("-rgm", "--random-generator-mode")
        .default_value("both")
        .choices("hijing", "zpc", "both");

    argparse::ArgumentParser subparser_add("add");
    
    subparser_add.add_description("add multiple different folders and combine them in one new, if two seperate runs have been done with the same input file.");
    ampt.log -> renamed into ampt-1-10.log , ampt-11-20.log etc. 
    subparser_add.add_argument("-f", "--file");
    subparser_add.add_argument("-fd", "--file-directory");
    // subparser_add.add_argument("-fid", "--file-is-directory").flag();
    -> add warning message and check if directories/files would be overwritten unintionally.


    */
    
    argparse::ArgumentParser compiler("compiler", COMPILER_VERSION);
    compiler.add_description("the compiler is a subprogram that makes and compiles the instance directories in the bin directory.");
    compiler.add_argument("-s", "--source")
        .default_value(std::string{"original"})
        .help("the name of the source (i.e. the directory where the fortran files and Makefile are located).");
    compiler.add_argument("-sd", "--source-directory")
        .default_value(std::string{"./src"})
        .help("the directory where the source is located.");
    compiler.add_argument("-bd", "--bin-directory")
        .default_value(std::string{"./bin"})
        .help("the directory where the instance directories must be located.");
    compiler.add_argument("-b", "--binrange")
        .default_value(std::vector<int>{1, 1})
        .nargs(2)
        .scan<'i', int>()
        .help("the number range of the instance directories.");
    compiler.add_argument("-in", "--instance-name")
        .default_value(std::string{"ampt"})
        .help("the prefix of the instance directories.");

    program.add_subparser(compiler);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    if (!program.is_subcommand_used(compiler))
    {
        /*
        MAINPROGRAM
        */
        std::string output_directory = program.get<std::string>("-od");

        std::string output_name = program.get<std::string>("-o");
        std::string input_directory = program.get<std::string>("-id");
        std::string input_name = program.get<std::string>("-i");
        std::string instance_name = program.get<std::string>("-in");
        std::vector<int> b_range = program.get<std::vector<int>>("-b");

        std::stringstream s1;
        s1 << output_directory << "/" << output_name;
        std::filesystem::path path_output = s1.str();
        std::stringstream s2;
        s2 << input_directory << "/" << input_name;
        std::filesystem::path path_input = s2.str();

        // std::cout << path_input << std::endl;
        // std::cout << path_output << std::endl;

        unsigned int b_min = b_range[0];
        unsigned int b_max = b_range[1];

        unsigned int b_num = b_max - b_min + 1;

        TimePoint time_start = Clock::now();

        std::string date_start = Utilities::return_current_time_and_date();

        std::ifstream file(path_input);
        std::string line;
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::getline(file, line);
        std::stringstream ss(line);
        size_t NEVENT;
        ss >> NEVENT;
        file.close();

        std::string screen_output;

        AMPT::Manager manager(path_input, path_output, output_name, "bin", b_min, b_max, instance_name);
        manager.NEVENT_SINGLE = NEVENT;
        manager.Initialize();
        manager.Run();
        manager.Finalize();

        screen_output += manager.PrintInitInfo();
        screen_output += manager.screenstring;
        screen_output += manager.PrintFinalInfo();

        std::ofstream outfile(path_output / "run.log");
        outfile << screen_output;
        outfile.close();
    }
    else if (program.is_subcommand_used(compiler))
    {
        /*
        SUBPROGRAM
        */
        std::string source_name = compiler.get<std::string>("-s");
        ;
        std::filesystem::path source_directory = compiler.get<std::string>("-sd");
        ;
        std::filesystem::path bin_directory = compiler.get<std::string>("-bd");
        ;
        std::string instance_name = compiler.get<std::string>("-in");

        std::vector<int> b_range = compiler.get<std::vector<int>>("-b");
        unsigned int b_min = b_range[0];
        unsigned int b_max = b_range[1];

        AMPT::Manager manager(bin_directory,
                              source_directory / source_name, b_min, b_max, instance_name);
        manager.Compile();
    }

    return 0;
}