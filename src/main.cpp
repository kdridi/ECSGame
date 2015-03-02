#include <iostream>

#include "arkanoid.h"
#include "tilemap.h"

int main()
{
    std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
    std::cout << "DATA_PATH [" << DATA_PATH << "]" << std::endl;
    
    return tilemap_main();
}
