/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
	Michael "Chishm" Chisholm
	Dave "WinterMute" Murphy
	Claudio "sverx"

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

------------------------------------------------------------------*/
#include <nds.h>
#include <fat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

#include <string.h>
#include <unistd.h>
#include <maxmod9.h>
#include "gl2d.h"

#include "graphics/graphics.h"

#include "graphics/fontHandler.h"

#include "level.h"
#include "timesettings.h"

#include "soundbank.h"
#include "soundbank_bin.h"

bool fadeType = true;				// false = out, true = in

mm_sound_effect snd_jump;

void InitSound() {
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	mmLoadEffect( SFX_JUMP );

	snd_jump = {
		{ SFX_JUMP } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		128,	// panning
	};
}

//---------------------------------------------------------------------------------
void stop (void) {
//---------------------------------------------------------------------------------
	while (1) {
		swiWaitForVBlank();
	}
}

//---------------------------------------------------------------------------------
void doPause(int x, int y) {
//---------------------------------------------------------------------------------
	// iprintf("Press start...\n");
	printSmall(false, x, y, "Press start...");
	while(1) {
		scanKeys();
		if(keysDown() & KEY_START)
			break;
	}
	scanKeys();
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	defaultExceptionHandler();

	//fatInitDefault();

	InitSound();	
	graphicsInit();
	fontInit();

	while (1) {
		clearText();
		levelMode();
		timeSettingsMode();
		swiWaitForVBlank();
	}

	return 0;
}
