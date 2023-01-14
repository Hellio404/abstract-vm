#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "VirtualMachine.hpp"
#include "Exception.hpp"

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " [file]" << std::endl;
        return 1;
    }

    std::string str;
    if (argc < 2)
    {
        // read from stdin until a line found that contains only ";;"
        std::string line;
        while (!std::cin.bad() && std::getline(std::cin, line))
        {
            if (line == ";;")
                break;
            str += line + "\n";
        }
        if (line != ";;")
        {
            std::cerr << "Error: no end of input found" << std::endl;
            return 1;
        }
    }
    else if (argc == 2)
    {

        std::ifstream t(argv[1]);
        if (!t.is_open())
        {
            std::cerr << "Cannot open file " << argv[1] << std::endl;
            return 1;
        }
        str = std::string((std::istreambuf_iterator<char>(t)),
                          std::istreambuf_iterator<char>());
        t.close();
    }
    VirtualMachine vm(str.c_str());
    vm.run();

}