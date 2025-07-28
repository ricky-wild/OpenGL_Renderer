
#include "Common.h"
#include <iostream>

int main()
{

    MyApp app;
    std::cerr << "\nwildlogicgames opengl app intializing..." << std::endl;
    try 
    {
        app.Run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "\nError: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
