#include <iostream>
#include <fstream>
#include <string>

#include "libahcc.h"

void help(char * av[]) {
    // Help menu (no arguments given or "--help" argument used)
    std::cout << " == Another Hand-Crafted Compressor (Pre-Pre-Alpha) == " << std::endl << std::endl;
    std::cout << "Usage: " << av[0] << " [options] <input file name> <output file name>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "    --help  Show help menu" << std::endl;
    std::cout << "    -c      Compress file (default: -x)" << std::endl;
    std::cout << "    -x      Extract file (default: -x)" << std::endl;
    std::cout << "            -c and -x are exclusive, the last one given in the parameters will be used" << std::endl;
}

int main(int ac, char * av[])
{
    if (ac == 1) {
        help(av);
        return 1;
    } else {
        // Arguments parsing
        int compressing = 0;
        int files_given = 0;
        
        std::ifstream input_file;
        std::ofstream output_file;
        
        for (int i = 1; i < ac; i++) {
            std::string argument = av[i];
            if ((! argument.compare("--help")) || (! argument.compare("--help"))) {
                help(av);
                return 1;
            } else if (! argument.compare("-c")) {
                // Enable compressing
                compressing = 1;
            } else if (! argument.compare("-x")) {
                // Enable decompressing
                compressing = 0;
            } else {
                // Manage input / output files
                if (files_given == 0) {
                    // Opens input file
                    input_file.open(argument.c_str(), std::ifstream::in);
                    
                    if (! input_file) {
                        std::cerr << "Error: Couldn't open input file" << std::endl;
                        return 2; 
                    }
                } else if (files_given == 1) {
                    // Opens output file
                    output_file.open(argument.c_str(), std::ofstream::out);
                    
                    if (! output_file) {
                        std::cerr << "Error: Couldn't open output file" << std::endl;
                    }
                } else {
                    std::cerr << "Error: Too much files were given" << std::endl;
                    return 1;
                }
                
                files_given += 1;
            }
        }
        
        if (compressing == 1) {
            compress(input_file, output_file);
        } else {
            uncompress(input_file, output_file);
        }
    }

    return 0;
}
