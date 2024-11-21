module;

#include <chrono>
#include <csignal>
#include <map>
#include <string>

export module input;

export namespace engine {
    class input {
    private:
        std::vector<char> buffer_;
        uint8_t buffer_size_;

        std::map<std::string, char> action_pairs_;

    private:
        void capture_input();
        void clear_buffer();
        [[nodiscard]] bool is_button_pressed_(char b) const;

    public:
        explicit input();

        // no copying
        input(const input& other) = delete;
        input& operator=(const input& other) = delete;

        void add_action_pair(const std::string& a, char b);

        [[nodiscard]] bool is_action_just_pressed(const std::string& a) const;
        [[nodiscard]] bool is_button_just_pressed(char b) const;

        /// get the instance
        static input& instance();
    };
};
