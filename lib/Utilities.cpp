// Copyright (C) 2024 Lieuwe Huisman
#include "Utilities.hpp"
namespace Utilities
{
    void remove_files_by_extension(const std::filesystem::path &directory, const std::string &extension)
    {
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator(directory))
            {

                if (entry.is_regular_file() && entry.path().extension() == extension)
                {
                    std::filesystem::remove(entry.path());
                }
            }
        }
        catch (std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void copy_files_by_extension(const std::filesystem::path &directory_src, const std::filesystem::path &directory_out, const std::string &extension, const std::filesystem::copy_options &option)
    {
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator(directory_src))
            {
                if (entry.is_regular_file() && entry.path().extension() == extension)
                {
                    std::filesystem::copy(entry.path(), directory_out, option);
                }
            }
        }
        catch (std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}