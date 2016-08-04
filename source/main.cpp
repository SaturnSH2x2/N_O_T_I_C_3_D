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

#include <iostream>
#include <string>

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

#include "app.h"

int main(int argc, char **argv)
{
	//Initialize gfx (note: not needed if you're using SF2Dlib)
	gfxInitDefault();

        app::run();	

	gfxExit();
	return 0;
}
