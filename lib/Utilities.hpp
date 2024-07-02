// Copyright (C) 2024 Lieuwe Huisman
#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <filesystem>
#include <string>
#include <iostream>

namespace Utilities
{
    void remove_files_by_extension(const std::filesystem::path &directory, const std::string &extension);
    void copy_files_by_extension(const std::filesystem::path &directory_src, const std::filesystem::path &directory_out, const std::string &extension, const std::filesystem::copy_options &option = std::filesystem::copy_options::none);
}

#endif