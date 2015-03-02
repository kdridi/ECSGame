#include <iostream>

#include "arkanoid.h"

int main()
{
    std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
    std::cout << "DATA_PATH [" << DATA_PATH << "]" << std::endl;
    
    return arkanoid_main();
}
