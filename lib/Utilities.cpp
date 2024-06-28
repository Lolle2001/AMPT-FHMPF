#include "Utilities.hpp"
namespace Utilities
{
    void remove_files_by_extension(const std::filesystem::path &directory, const std::string &extension)
    {
        try
        {
            // Iterate through the directory
            for (const auto &entry : std::filesystem::directory_iterator(directory))
            {
                // Check if the file has a .log extension
                if (entry.is_regular_file() && entry.path().extension() == extension)
                {
                    // Remove the file
                    std::filesystem::remove(entry.path());
                    // std::cout << "Removed: " << entry.path() << std::endl;
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
            // Iterate through the directory
            for (const auto &entry : std::filesystem::directory_iterator(directory_src))
            {
                // Check if the file has a .log extension
                if (entry.is_regular_file() && entry.path().extension() == extension)
                {
                    // Remove the file
                    std::filesystem::copy(entry.path(), directory_out, option);
                    // std::cout << "Copied: " << entry.path() << std::endl;
                }
            }
        }
        catch (std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}