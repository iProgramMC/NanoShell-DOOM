//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//

//#include "config.h"

#include <nanoshell.h>

//#include "doomtype.h"
//#include "i_system.h"
#include "m_argv.h"

//
// D_DoomMain()
// Not a globally visible function, just included for source reference,
// calls all startup code, parses command line options.
//

void D_DoomMain (void);

void M_FindResponseFile(void);

bool dg_Create();

char doom_nse_arg[] = { 'd','o','o','m','.','n','s','e','\0' };//TODO

char* arguments_v[] = {
	doom_nse_arg,
	NULL
};

int main()
{
    // save arguments

    myargc = 1;
    myargv = arguments_v;

    //M_FindResponseFile();

    // start doom
    LogMsg("Starting D_DoomMain\r\n");
    
	if (dg_Create())
		D_DoomMain ();

    return 0;
}

