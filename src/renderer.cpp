module;

#include <iostream>

module renderer;
import buffer;

namespace renderer {
	screen::screen(): width_(16), height_(48) {
		buffer_ = buffer::buffer_2d<wchar_t>(width_, height_);
	}

	screen::screen(int x, int y): width_(x), height_(y) {
		buffer_ = buffer::buffer_2d<wchar_t>(width_, height_);
	}

	screen::~screen() {
	}

	void screen::init() {
		std::locale::global(std::locale(""));
		for (int i = 0; i < buffer_.get_height(); i++) {
			for (int j = 0; j < buffer_.get_width(); j++) {
				buffer_[i][j] = L'*';
			}
		}
	}

	void screen::draw() {
		for (int i = 0; i < buffer_.get_height(); i++) {
			for (int j = 0; j < buffer_.get_width(); j++) {
				std::wcout << buffer_[i][j];
			}
			std::wcout << std::endl;
		}
	}

	void screen::clear() {
		std::wcout << L"\033[2J\033[1;1H";
	}
}
