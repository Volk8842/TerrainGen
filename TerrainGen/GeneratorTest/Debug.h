#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define DEBUG

#ifdef DEBUG

#define LOG() std::cout << __FUNCTION__ << "() in line " << __LINE__ << "\n"
#define LOG_MSG(str) std::cout << __FUNCTION__ << "() in line " << __LINE__ << ": " << str << "\n"

#else
#define LOG()
#define LOG_MSG(str)

#endif // DEBUG
#endif // DEBUG_H