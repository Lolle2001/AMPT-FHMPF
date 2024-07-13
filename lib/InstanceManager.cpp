// Copyright (C) 2024 Lieuwe Huisman
#include "InstanceManager.hpp"

namespace AMPT
{

    InstanceManager::InstanceManager(size_t ID_, std::filesystem::path path_) : path(path_), ID(ID_)
    {
        path = std::filesystem::absolute(path);
    };

    // void SetPath(std::filesystem::path path);
    // void SetID(size_t ID);
    void InstanceManager::SetSeeds(size_t HIJING_seed)
    {

        std::ofstream file(path / "hijing_seed.dat", std::ios::out);
        file << HIJING_seed;
        file.close();
    };

    void InstanceManager::Clearbin()
    {
        Utilities::remove_files_by_extension(path, ".log");
        Utilities::remove_files_by_extension(path, ".ampt");
        Utilities::remove_files_by_extension(path, ".dat");
        Utilities::remove_files_by_extension(path, ".dat");
    }
    void InstanceManager::Initialize(std::filesystem::path input_path)
    {
        manager_name = fmt::format("Manager {:02}", ID);
        Clearbin();
        input_path = std::filesystem::absolute(input_path);

        std::filesystem::path out1(path);
        std::filesystem::path out2(path);
        std::filesystem::path out3(path);
        out1.append("input.ampt");
        out2.append("ana/");
        if (std::filesystem::exists(out2))
        {
            std::filesystem::remove_all(out2);
        }
        std::filesystem::create_directories(out2);

        out3.append("ana1/");
        if (std::filesystem::exists(out3))
        {
            std::filesystem::remove_all(out3);
        }
        std::filesystem::create_directories(out3);

        out2.append("input.ampt");
        std::filesystem::copy_file(input_path, out1, std::filesystem::copy_options::overwrite_existing);

        std::filesystem::copy_file(input_path, out2, std::filesystem::copy_options::overwrite_existing);
    };

    void InstanceManager::MoveResults(std::filesystem::path output_path)
    {

        output_path = std::filesystem::absolute(output_path);
        std::filesystem::create_directories(output_path);

        std::filesystem::remove_all(output_path / "ana");
        std::filesystem::remove_all(output_path / "ana1");
        // std::filesystem::create_directories(output_path / "ana");
        // std::filesystem::create_directories(output_path / "ana1");
        std::filesystem::rename(path / "ana", output_path / "ana");

        std::filesystem::rename(path / "ana1", output_path / "ana1");

        std::filesystem::rename(path / "ampt.log", output_path / "ampt.log");

        std::filesystem::rename(path / "ampt.err", output_path / "ampt.err");
        std::filesystem::rename(path / "hijing_seed.dat", output_path / "hijing_seed.dat");

        std::filesystem::remove(path / "input.ampt");
    }
    void InstanceManager::RunInstance()
    {

        starttime = clock_c::now();
        std::stringstream command;
        command << "cd " << path << " && " << "./ampt < hijing_seed.dat 1> " << "ampt.log 2> " << "ampt.err";
        execution_state = std::system(command.str().c_str());
        endtime = clock_c::now();
        duration = endtime - starttime;

        // duration_per_event = duration / NEVENT;
    };

    void InstanceManager::CompileFromSource(std::filesystem::path source_path)
    {
        std::filesystem::path sp = std::filesystem::absolute(source_path);
        std::filesystem::create_directories(path / "src");
        Utilities::copy_files_by_extension(sp, path / "src", ".f", std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy(sp / "Makefile", path / "src", std::filesystem::copy_options::overwrite_existing);
        std::stringstream command;
        command << "cd " << path / "src" << " && " << "make -j " << omp_get_max_threads() << " 1> make.log 2> " << "make.err";
        std::system(command.str().c_str());
        std::filesystem::rename(path / "src/ampt", path / "ampt");
    }
};
