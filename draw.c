
#include <stdio.h>

#include <clib/graphics_protos.h>

#include "object.h"
#include "objectTypes.h"
#include "draw.h"

#include "debug.h"

#define DRAW 1

#define MIN(a,b) ((a)<=(b)?(a):(b))
#define MAX(a,b) ((a)>=(b)?(a):(b))

char *dirNames[] = {
	"left",
	"right",
	"up",
	"down"
};

char *names[] = {
	"floor",
	"wall",
	"hero",
	"box",
	"cherry",
	"key",
	"door",
	"ammo",
	"debris",
	"bullet",
	"fire",
	"skull",
	"exit"
};

void addLeavingTile(struct boardInfo *bi, UWORD j, UWORD i, WORD offset, struct fullInfo *info, struct fullInfo *srcInfo)
{
	struct RastPort *rp = bi->rp;
	WORD dist = DIST - info->gfx.dist;
	WORD x0, y0, x1, y1, dx, dy;

	j -= dx = offset / TALL;
	i -= dy = offset % TALL;

	dx *= dist;
	dy *= dist;

	x0 = MAX(0, dx);
	x1 = MIN(DIST - 1, dx + DIST - 1);
	y0 = MAX(0, dy);
	y1 = MIN(DIST - 1, dy + DIST - 1);

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, info->gfx.gfxFrame));
#if DRAW
    	SetAPen(rp, info->gfx.gfxFrame);
        RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
    }
}

void drawLeavingTile(struct boardInfo *bi, UWORD j, UWORD i, WORD offset, struct fullInfo *info, struct fullInfo *srcInfo)
{
	struct RastPort *rp = bi->rp;
	WORD dist = DIST - info->gfx.dist;
	WORD x0, y0, x1, y1, dx, dy;

	j -= dx = offset / TALL;
	i -= dy = offset % TALL;

	dx *= dist;
	dy *= dist;

	x0 = MAX(0, dx);
	x1 = MIN(DIST - 1, dx + DIST - 1);
	y0 = MAX(0, dy);
	y1 = MIN(DIST - 1, dy + DIST - 1);

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, info->gfx.gfxFrame));
#if DRAW
    	SetAPen(rp, info->gfx.gfxFrame);
	    RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
	}

	if (dx) {
		if (x0 == 0) {
			x0 = x1 + 1;
			x1 = DIST - 1;
		}
		else {
			x1 = x0 - 1;
			x0 = 0;
		}
	}
	else {
		if (y0 == 0) {
			y0 = y1 + 1;
			y1 = DIST - 1;
		}
		else {
			y1 = y0 - 1;
			y0 = 0;
		}
	}

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, 0));
#if DRAW
    	SetAPen(rp, 0);
	    RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
    }
}

void addEnteringTile(struct boardInfo *bi, UWORD j, UWORD i, WORD offset, struct fullInfo *info)
{
	struct RastPort *rp = bi->rp;
	WORD dist = info->gfx.dist;
	WORD x0, y0, x1, y1, dx, dy;

	dx = (-offset) / TALL;
	dy = (-offset) % TALL;

	dx *= dist;
	dy *= dist;

	x0 = MAX(0, dx);
	x1 = MIN(DIST - 1, dx + DIST - 1);
	y0 = MAX(0, dy);
	y1 = MIN(DIST - 1, dy + DIST - 1);

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, info->gfx.gfxFrame));
#if DRAW
    	SetAPen(rp, info->gfx.gfxFrame);
	    RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
    }
}

void drawEnteringTile(struct boardInfo *bi, UWORD j, UWORD i, WORD offset, struct fullInfo *info)
{
	struct RastPort *rp = bi->rp;
	WORD dist = info->gfx.dist;
	WORD x0, y0, x1, y1, dx, dy;

	dx = (-offset) / TALL;
	dy = (-offset) % TALL;

	dx *= dist;
	dy *= dist;

	x0 = MAX(0, dx);
	x1 = MIN(DIST - 1, dx + DIST - 1);
	y0 = MAX(0, dy);
	y1 = MIN(DIST - 1, dy + DIST - 1);

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, info->gfx.gfxFrame));
#if DRAW
    	SetAPen(rp, info->gfx.gfxFrame);
	    RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
    }

	if (dx) {
		if (x0 == 0) {
			x0 = x1 + 1;
			x1 = DIST - 1;
		}
		else {
			x1 = x0 - 1;
			x0 = 0;
		}
	}
	else {
		if (y0 == 0) {
			y0 = y1 + 1;
			y1 = DIST - 1;
		}
		else {
			y1 = y0 - 1;
			y0 = 0;
		}
	}

	if (x0 <= x1 && y0 <= y1)
	{
		D(bug("[%d/%d]-[%d/%d] (%d)\n", x0, y0, x1, y1, 0));
#if DRAW
    	SetAPen(rp, 0);
	    RectFill(rp, (j << TILE) + x0, (i << TILE) + y0, (j << TILE) + x1, (i << TILE) + y1);
#endif
    }
}

void drawTile(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
    struct RastPort *rp = bi->rp;

#if DRAW
	SetAPen(rp, info->gfx.gfxFrame);
	RectFill(rp, (j << TILE), (i << TILE), (j << TILE) + 15, (i << TILE) + 15);
#endif
}

void updateAnimGfx(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
	struct gfxInfo *gfx = &info->gfx, *prevGfx = &info->prevGfx[bi->frame];
	enum dirTypes dir = gfx->dir, prevDir = prevGfx->dir;
	WORD offset = offsets[dir];
	struct fullInfo *srcInfo = info - offset;

	if (prevGfx->dist > 0) {
		if (gfx->dist == 0) {
			/* Erase object from previous cell */
			if (!srcInfo->drawn) {
				D(bug("Erasing object going %s to %d/%d\n", dirNames[prevDir], j, i));
				drawLeavingTile(bi, j, i, offset, info, srcInfo);
				srcInfo->drawn = TRUE;
			}
			else
				D(bug("Already erased going %s at %d/%d\n", dirNames[prevDir], j, i));
		}
	}

	if (gfx->dist > 0) {
		/* Draw object in previous cell */
		if (!srcInfo->drawn) {
			D(bug("Drawing object frame %s going %s to %d/%d (%d)\n", names[gfx->gfxFrame], dirNames[dir], j, i, gfx->dist));
			drawLeavingTile(bi, j, i, offset, info, srcInfo);
			srcInfo->drawn = TRUE;
		}
		else {
			D(bug("Adding object frame %s going %s to %d/%d (%d)\n", names[gfx->gfxFrame], dirNames[dir], j, i, gfx->dist));
			addLeavingTile(bi, j, i, offset, info, srcInfo);
		}
	}

	/* Draw object in cell */
	if (gfx->dist > 0) {

		if (!info->drawn) {
			D(bug("Drawing object frame %s heading %s to %d/%d (%d)\n", names[gfx->gfxFrame], dirNames[dir], j, i, gfx->dist));
			drawEnteringTile(bi, j, i, offset, info);
			info->drawn = TRUE;
		}
		else {
			D(bug("Adding object frame %s heading %s to %d/%d (%d)\n", names[gfx->gfxFrame], dirNames[dir], j, i, gfx->dist));
			addEnteringTile(bi, j, i, offset, info);
		}

		info->updateGfx = FALSE;
	}

	*prevGfx = *gfx;
}

void updateTileGfx(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
	struct gfxInfo *gfx = &info->gfx;

	if (!info->drawn) {
		D(bug("Drawing object frame %s at %d/%d\n", names[gfx->gfxFrame], j, i));
		drawTile(bi, j, i, info);
		info->drawn = TRUE;
	}
	else
		D(bug("Tile %d/%d already drawn.\n", j, i));
}

void updateBoardGfx(struct boardInfo *bi)
{
	UWORD i, j;
	struct fullInfo *info = &bi->info[0][0];

	for (j = 0; j < WIDE; j++) {
		for (i = 0; i < TALL; i++) {
			info->drawn = FALSE;
			info++;
		}
	}
	info = &bi->info[0][0];

	for (j = 0; j < WIDE; j++) {
		for (i = 0; i < TALL; i++) {
			if (info->updateGfx) {
				updateAnimGfx(bi, j, i, info);
			}
			info++;
		}
	}
	info = &bi->info[0][0];
	for (j = 0; j < WIDE; j++) {
		for (i = 0; i < TALL; i++) {
			if (info->updateGfx) {
				updateTileGfx(bi, j, i, info);
				info->updateGfx = FALSE;
			}
			info++;
		}
	}
}
