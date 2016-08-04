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

#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>

#include <stdlib.h>
#include <3ds.h>

#include "rf.h"

using namespace std;
//using namespace string;

namespace app {
    PrintConsole top, bottom;
    
    bool is_first_run = true;
    bool is_program_running = true;
    
    void display_text_file(u32 kHeld);
    void display_instructions();
    void clear_screens();
    
    void run() {
        // initialize console to print on the top screen
        consoleInit(GFX_TOP, &top);
        consoleInit(GFX_BOTTOM, &bottom);
        
        consoleSelect(&top);
        
        printf("Variables and console initialized successfully.\n");
        
        while (aptMainLoop()) {
            //clear_screens();
        
            display_instructions();
            //printf("Displaying instructions.\n");
            
            //Scan all the inputs. This should be done once for each frame
            hidScanInput();

            //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
            //hidKeysHeld returns information about which buttons are currently pressed (regardless if they were pressed or not pressed in the previous frame)
            //hidKeysUp returns information about which buttons are not pressed but were pressed in the previous frame
            u32 kDown = hidKeysDown();
            display_text_file(kDown);
            
            if (is_program_running == false) break; // break in order to return to hbmenu

            // Flush and swap framebuffers, this is needed for rendering these will not be needed when using SF2D lib
            gfxFlushBuffers();
            gfxSwapBuffers();

            //Wait for VBlank, this is needed for rendering these will not be needed when using SF2D lib
            gspWaitForVBlank();
        }
    }
    
    void display_text_file(u32 kDown) {
        consoleSelect(&top);
        
        // name of text file to be loaded.  included as variable for syntactic sugar
        static string filename = "/data/N_O_T_I_C_3_D/notice.txt";
        
        // contents of text file
        static string *txt_contents = rf::read_from_file(filename);
        
        // number of lines of aforementioned text file
        static int num_of_lines = rf::number_of_lines(filename);

        // index at which to start printing content from text file
        static int str_index = 0;
        
        // gets previous value of str_index
        int prev_index = str_index;
        
        // counts how many lines are written to the screen
        int lines_written = 0;
        
        int i;  // iterator
        
        // read input, make changes to variables accordingly
        if (kDown & KEY_UP   ) str_index -= 1;
        if (kDown & KEY_DOWN ) str_index += 1;
        if (kDown & KEY_START) is_program_running = false;
        
        // make sure str_index value is valid
        if (str_index < 0)                str_index = 0;
        if (str_index > num_of_lines - 1) str_index = num_of_lines - 1;
                
        if (prev_index != str_index || is_first_run == true) {
            clear_screens();
            display_instructions();
            
            printf("\x1b[0;0H");
        
            for (i = str_index; i < num_of_lines; i++) {
                printf(txt_contents[i].c_str());
                printf("\n");
                lines_written += 1;
                
                if (lines_written > 25) break;
            }
            
            is_first_run = false;
        }
        
        //consoleClear();
    }
    
    // displays instructions on the lower screen
    void display_instructions() {
        consoleSelect(&bottom);
        
        // extremely disorganized print statements incoming
        printf("\x1b[0;0H +-------------------------------------+");
                
        printf("\x1b[1;1H|Controls:                            |"
                " |UP    - scroll up                    |"
                " |DOWN  - scroll down                  |"
                " |START - return to Homebrew Launcher/ |"
                " |        3DS Home Menu                |"
                " +-------------------------------------+");

        printf("\x1b[15;0H +-------------------------------------+"
                          " |                                     |"
                          " |   N_O_T_I_C_3_D                     |"
                          " |             app by B_E_P_I_S_M_A_N  |"
                          " |                                     |"
                          " +-------------------------------------+");
        
        consoleSelect(&top);
    }
    
    // clears both the top and bottom screens
    void clear_screens() {
        consoleSelect(&top);
        consoleClear();
        
        //consoleInit(GFX_TOP, &top);
        
        consoleSelect(&bottom);
        consoleClear();
        
        //consoleInit(GFX_BOTTOM, &bottom);
        
        consoleSelect(&top);
    }
    
    
}


#endif /* APP_H */

 