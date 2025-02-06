module;
#include <array>
#include <string>
export module renderer_utils;

export namespace renderer {
    /// alias for the wstring that is used to represent the ansi color code the unicode symbol
    using color = std::wstring;
}

export namespace symbols {
    constexpr wchar_t left_upper_corner = L'\u2554';
    constexpr wchar_t left_lower_corner = L'\u255A';
    constexpr wchar_t horizontal_line = L'\u2550';
    constexpr wchar_t vertical_line = L'\u2551';
    constexpr wchar_t right_upper_corner = L'\u2557';
    constexpr wchar_t right_lower_corner = L'\u255D';
}

export namespace colors {
    const renderer::color black = L"\033[30m";
    const renderer::color red = L"\033[31m";
    const renderer::color green = L"\033[32m";
    const renderer::color yellow = L"\033[33m";
    const renderer::color blue = L"\033[34m";
    const renderer::color magenta = L"\033[35m";
    const renderer::color cyan = L"\033[36m";
    const renderer::color white = L"\033[37m";

    const renderer::color black_background = L"\033[40m";
    const renderer::color red_background = L"\033[41m";
    const renderer::color green_background = L"\033[42m";
    const renderer::color yellow_background = L"\033[43m";
    const renderer::color blue_background = L"\033[44m";
    const renderer::color magenta_background = L"\033[45m";
    const renderer::color cyan_background = L"\033[46m";
    const renderer::color white_background = L"\033[47m";

    const renderer::color reset = L"\033[0m";

    std::array array = {black, red, green, yellow, blue, magenta, cyan, white};
}
