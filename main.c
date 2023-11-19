
#include "object.h"
#include "draw.h"
#include "dirTypes.h"

#include <stdio.h>
#include "debug.h"

#include <intuition/intuition.h>
#include <clib/intuition_protos.h>

int main(void)
{
	static struct boardInfo bi;
	WORD i;
	struct Screen *s;
	struct Window *w;

	setObject(&bi.info[2][2], WALL);
	setObject(&bi.info[12][2], WALL);

	setObject(&bi.info[3][2], BULLET);
	bi.info[3][2].gfx.dir = RIGHT;

	setObject(&bi.info[5][2], BULLET);
	bi.info[5][2].gfx.dir = RIGHT;


	setObject(&bi.info[11][2], SKULL);
	bi.info[11][2].gfx.dir = RIGHT;

	setObject(&bi.info[9][2], DEBRIS);

	if (s = OpenScreenTags(NULL,
	    SA_LikeWorkbench, TRUE,
	    SA_Depth, 5,
	    SA_DisplayID, LORES_KEY,
	    SA_Title, "Warehouse 2.0",
	    SA_Interleaved, TRUE,
	    TAG_DONE))
	{
	    if (w = OpenWindowTags(NULL,
	        WA_CustomScreen, s,
	        WA_Left, 0,
	        WA_Top, 0,
	        WA_Width, s->Width,
	        WA_Height, s->Height,
	        WA_Backdrop, TRUE,
	        WA_Borderless, TRUE,
	        WA_Activate, TRUE,
	        TAG_DONE))
	    {
	        bi.rp = w->RPort;

        	updateBoardGfx(&bi);

        	for (i = 0; i < 200; i++) {
		        D(bug("Phase %d\n", i));

		        WaitTOF();
        		scanBoard(&bi);
		        updateBoardGfx(&bi);
        	}
        	CloseWindow(w);
        }
        CloseScreen(s);
    }
	return(0);
}
