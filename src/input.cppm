module;

#include <chrono>
#include <map>
#include <string>
#include <termios.h>

export module input;

export namespace engine {
    class input {
    private:
        std::vector<std::string> buffer_;
        uint8_t buffer_size_;

        termios oldt_{}, newt_{};
        fd_set readfds{};
        timeval timeout;

        std::map<std::string, std::string> action_pairs_;

    private:
        void start_capture_();
        void stop_capture_() const;

        void clear_buffer_();

    public:
        input();
        ~input();

        input(const input& other) = delete;
        input& operator=(const input& other) = delete;

        const std::map<std::string, std::string>& action_pairs();

        void capture_one_input();
        void print_buffer_() const;

        void add_action_pair(const std::string& a, const std::string& b);

        [[nodiscard]] bool is_action_just_pressed(const std::string& a) const;
        [[nodiscard]] bool is_button_just_pressed(const std::string& b) const;
    };
};
