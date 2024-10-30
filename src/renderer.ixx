module;

#include <string>
#include <vector>

export module renderer;

import buffer;

namespace renderer {
	struct block;

	export struct screen {
	private:
		int width_, height_;
		buffer::buffer_2d<wchar_t> buffer_;

	public:
		screen();
		screen(int x, int y);
		~screen();

		void init();
		void draw();
		static void clear();

	private:
		void update_buffer(const std::vector<block>& blocks);
		void draw_block(const block& b);
	};

	export namespace symbols {
		constexpr wchar_t left_upper_corner = L'\u2554';
		constexpr wchar_t left_lower_corner = L'\u255A';
		constexpr wchar_t horizontal_line = L'\u2550';
		constexpr wchar_t vertical_line = L'\u2551';
		constexpr wchar_t right_upper_corner = L'\u2557';
		constexpr wchar_t right_lower_corner = L'\u255D';
	}

	export namespace colors {
		/// alias for the wstring that is used to represent the ansi color code the unicode symbol
		using color = std::wstring;

		const color black = L"\033[30m";
		const color red = L"\033[31m";
		const color green = L"\033[32m";
		const color yellow = L"\033[33m";
		const color blue = L"\033[34m";
		const color magenta = L"\033[35m";
		const color cyan = L"\033[36m";
		const color white = L"\033[37m";

		const color black_background = L"\033[40m";
		const color red_background = L"\033[41m";
		const color green_background = L"\033[42m";
		const color yellow_background = L"\033[43m";
		const color blue_background = L"\033[44m";
		const color magenta_background = L"\033[45m";
		const color cyan_background = L"\033[46m";
		const color white_background = L"\033[47m";

		const color reset = L"\033[0m";
	}
}
