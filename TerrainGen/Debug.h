#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

namespace debug {
	inline void log(std::string message) {
		std::cout << message.c_str() << "\n"; 
	};
}
#endif // DEBUG_H