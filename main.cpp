//Program entry point, main.cpp
#include "Common.h"
#include <iostream>

int main()
{

    App app;
    try 
    {
        app.Run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
