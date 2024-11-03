module;

#include <format>
#include <iostream>
#include <string>

export module utils;

// declarations
namespace assert {
	void print_file_data(int line = 0, const std::string& function = "", const std::string& file = "");

	export template <typename T>
	void equal(T wanted, T got, int line = 0, const std::string& function = "", const std::string& file = "");

	export template <typename T>
	void not_equal(T wanted, T got, int line = 0, const std::string& function = "", const std::string& file = "");
	export void condition(bool cond, const std::string& msg, int line = 0, const std::string& function = "",
	                      const std::string& file = "");
}

// implementation of template functions
namespace assert {
	template <typename T>
	void equal(T wanted, T got, int line, const std::string& function, const std::string& file) {
		if (wanted != got) {
			std::cout << "assertion failed: " << "expected: " << wanted << " got: " << got << std::endl;
			print_file_data(line, function, file);
			std::exit(1);
		}
	}

	template <typename T>
	void not_equal(T wanted, T got, int line, const std::string& function, const std::string& file) {
		if (wanted == got) {
			std::cout << "assertion failed: " << "expected: " << wanted << " got: " << got << std::endl;
			print_file_data(line, function, file);
			std::exit(1);
		}
	}
}
