
#include "object.h"
#include "draw.h"
#include "dirTypes.h"

#include <stdio.h>
#include "debug.h"

int main(void)
{
	static struct boardInfo bi;
	WORD i;

	setObject(&bi.info[1][1], WALL);
	setObject(&bi.info[4][1], WALL);
	setObject(&bi.info[4][0], WALL);
	setObject(&bi.info[4][2], WALL);

	setObject(&bi.info[2][1], BULLET);
	bi.info[2][1].gfx.dir = RIGHT;
	setObject(&bi.info[4][1], SKULL);
	bi.info[4][1].gfx.dir = LEFT;

	updateBoardGfx(&bi);

	for (i = 0; i < 16; i++) {
		D(bug("Phase %d\n", i));
		scanBoard(&bi);
		updateBoardGfx(&bi);		
	}

	return(0);
}