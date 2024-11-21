module;

#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>

module input;


namespace engine {
    using namespace std::chrono_literals;

    volatile sig_atomic_t stop = 0;

    input::input(): buffer_size_(15) {
        this->capture_input();
    }

    void input::capture_input() {
        auto next_timestamp = std::chrono::steady_clock::now().time_since_epoch() + refresh_rate_;
        termios oldt{}, newt{};

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;

        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::cout << "Type characters (press 'q' to quit):" << std::endl;

        while (!stop) {
            const char ch = getchar();
            const auto now = std::chrono::steady_clock::now().time_since_epoch();

            // Capture arrows
            auto c = (int)ch;

            if (c == 27) {
                // ESC
                getchar(); // Skip the '['
                c = getchar(); // Get the actual arrow key
                switch (c) {
                case 'A':
                    std::cout << "Up arrow pressed" << std::endl;
                    break;
                case 'B':
                    std::cout << "Down arrow pressed" << std::endl;
                    break;
                case 'C':
                    std::cout << "Right arrow pressed" << std::endl;
                    break;
                case 'D':
                    std::cout << "Left arrow pressed" << std::endl;
                    break;
                }
            }

            if (ch == 'q') {
                break;
            }
            if (now >= next_timestamp && buffer_.size() == buffer_size_) {
                buffer_.clear();
                std::cout << "Cleared" << "\n";
                next_timestamp = std::chrono::steady_clock::now().time_since_epoch() + refresh_rate_;
                continue;
            }
            buffer_.push_back(ch);
            std::this_thread::sleep_for(100ms);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings

        std::cout << "Final input: ";
        for (const auto& elem : buffer_) {
            std::cout << elem;
        }
        std::cout << "\n";
    }

    void input::clear_buffer() {
        if (buffer_size_ == buffer_.size()) {
            buffer_.clear();
        }
    }

    bool input::is_button_pressed_(char b) const {
        for (const auto& raw_char : buffer_) {
            if (raw_char == b) return true;
        }
        return false;
    }

    void input::add_action_pair(const std::string& a, char b) {}

    bool input::is_action_just_pressed(const std::string& a) const {
        for (const auto& [action, button] : action_pairs_) {
            if (action == a) return is_button_pressed_(button);
        }
        return false;
    }

    bool input::is_button_just_pressed(char button) const {
        for (const auto& raw_char : buffer_) {
            if (raw_char == button) return true;
        }
        return false;
    }

    input& input::instance() {
        static input input;
        return input;
    }
};
