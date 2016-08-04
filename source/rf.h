/*
 * Licensed under the WTFPL
 * 
DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE F*** YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE F*** YOU WANT TO.

*/

#ifndef RF_H
#define RF_H

#include <iostream>
#include <string>
#include <fstream>

#include <stdlib.h>

using namespace std;

namespace rf {
    int number_of_lines(std::string filename);
    
    std::string *read_from_file(std::string filename) {
        std::string *contents;
        int i;
        
        // get number of lines in file, then allocate enough space to hold
        // the file's contents
        int lines = number_of_lines(filename);
        contents = new std::string[lines];
        
        ifstream file(filename.c_str());
        
        if (file.is_open()) {
            for (i = 0; i < lines; i++) {
                std::getline(file, contents[i]);
            }
        } else {
            std::cout << "Error reading file!";
            return NULL;
        }
        
        return contents;
    }
    
    int number_of_lines(std::string filename) {
        int number_of_lines = 0;
        std::string dummy;
        
        ifstream f (filename.c_str());
        
        if (f.is_open()) {
            while (std::getline(f, dummy)) {
                number_of_lines += 1;
            }
        } else {
            std::cout << "Error reading file!\n";
        }
        
        return number_of_lines;
    }
}


#endif /* RF_H */

