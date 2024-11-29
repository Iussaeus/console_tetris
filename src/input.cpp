module;

#include <chrono>
#include <map>
#include <csignal>
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>

module input;

import utils;

namespace engine {
    volatile sig_atomic_t stop = 0;

    input::input(): buffer_size_(64) {
        start_capture_();

        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
    }

    input::~input() {
        stop_capture_();
    }

    const std::map<std::string, std::string>& input::action_pairs() {
        return action_pairs_;
    }

    void input::capture_one_input() {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        if (select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout) > 0) {
            char buffer[8];
            ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                buffer_.emplace_back(buffer);
            }
        }
        else buffer_.emplace_back("empty");

        clear_buffer_();
    }

    void input::start_capture_() {
        tcgetattr(STDIN_FILENO, &oldt_);
        newt_ = oldt_;

        newt_.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt_);
    }

    void input::stop_capture_() const {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt_);
    }

    void input::print_buffer_() const {
        for (const auto& elem : buffer_) {
            std::cout << "Final input: ";
            std::cout << elem;
        }
        std::cout << "\n";
    }

    void input::clear_buffer_() {
        if (buffer_size_ == buffer_.size()) {
            buffer_.clear();
        }
    }

    void input::add_action_pair(const std::string& a, const std::string& b) {
        if (!action_pairs_.contains(a)) {
            action_pairs_[a] = b;
        }
    }

    bool input::is_button_just_pressed(const std::string& b) const {
        if (buffer_.empty()) return false;

        const auto button = *buffer_.rbegin();

        return button == b;
    }

    bool input::is_action_just_pressed(const std::string& a) const {
        if (action_pairs_.empty()) return false;

        const auto& last_input = *buffer_.rbegin();
        const auto& desired_input = action_pairs_.find(a);

        if (desired_input->second == last_input) return is_button_just_pressed(desired_input->second);

        return false;
    }
};
