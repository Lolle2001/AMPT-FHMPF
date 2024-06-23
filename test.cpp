#include <filesystem>
#include <iostream>

void test()
{

    std::filesystem::path p = "test";
    std::filesystem::copy_file("input/default.par", p.append("ana/input.ampt"));
    std::cout << p << std::endl;
}