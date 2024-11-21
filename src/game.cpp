module;

#include <csignal>
#include <iostream>
#include <termios.h>

module game;

import renderer;
import renderer_utils;
import engine;
import buffer;
import utils;
import random;
import block;
import game_utils;
import input;

void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nCaught Ctrl+C! Exiting..." << std::endl;
        input::stop = 1; // Set the stop flag
    }
}

namespace game {
    void run() {
        std::signal(SIGINT, handleSignal);
        input::input::instance();
    }
}
