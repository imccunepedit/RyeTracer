#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace Rye::Utils {

    static void log(std::string info)
    {
        std::cout << info << std::endl;
    }
}
#endif /* LOG_H */
