module;

#include <format>
#include <iostream>

module utils;

namespace assert {
	void print_file_data(const int line, const std::string& function, const std::string& file) {
		if (line) std::cout << "at line: " << line << std::endl;
		if (function != "") std::cout << "from function: " << function << std::endl;
		if (file != "") std::cout << "in file: " << file << std::endl;
	}

	void condition(const bool cond, const std::string& msg, const int line, const std::string& function,
	               const std::string& file) {
		if (!cond) {
			std::cout << "assertion failed: " << msg << std::endl;
			print_file_data(line, function, file);
			std::exit(1);
		}
	}
}
