module;

#include <iostream>

module game;

import renderer;
import engine;
import buffer;
import utils;

namespace game {
	void run() {
		std::cout << engine::random(0, 100) << "\n";
	}
}
