module;

#include <format>
#include <iostream>
#include <string>

export module utils;

export namespace assert {
    void print_file_data(int line = 0, const std::string& function = "", const std::string& file = "");
    void condition(bool cond, const std::string& msg, int line = 0, const std::string& function = "",
                   const std::string& file = "");
}