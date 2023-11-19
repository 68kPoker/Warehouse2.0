
#include <stdio.h>
#include "debug.h"

#include "object.h"
#include "objectTypes.h"
#include "dirTypes.h"

void heroHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info);
void bulletHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info);
void fireHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info);
void skullHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info);

struct objectTypeInfo typeInfo[TYPES] = {
	{ NULL },
	{ NULL },
	{ heroHandler, SPEED },
	{ NULL },
	{ NULL },
	{ NULL },
	{ NULL },
	{ NULL },
	{ NULL },
	{ bulletHandler, SPEED * 2 },
	{ fireHandler },
	{ skullHandler, SPEED },
	{ NULL }
};

WORD offsets[] = {
	-TALL, TALL, -1, 1
};

void scanBoard(struct boardInfo *bi)
{
	UWORD i, j;
	struct fullInfo *info = &bi->info[0][0];

	for (j = 0; j < WIDE; j++) {
		for (i = 0; i < TALL; i++) {				
			if (!info->scanned) {
				struct objectTypeInfo *oti = typeInfo + info->object.type;				

				if (oti->handler) {					
					oti->handler(bi, j, i, info);
				}				
			}
			info->scanned = FALSE;
			info++;
		}
	}
}

void beginObjectMove(struct fullInfo *info, enum dirTypes dir)
{
	D(bug("Begin movement.\n"));
	WORD offset = offsets[info->gfx.dir];
	struct fullInfo *sibInfo = info + offset;
	struct gfxInfo *sibGfx = &sibInfo->gfx;
	struct objectTypeInfo *oti = typeInfo + info->object.type;

	sibInfo->object = info->object;
	info->object.type = FLOOR;
	info->updateGfx = TRUE;
	info->gfx.dist = 0;
	info->gfx.gfxFrame = FLOOR;

	sibGfx->dir = dir;
	sibGfx->dist = DIST - oti->speed;

	sibGfx->gfxFrame = sibInfo->object.type;

	sibInfo->updateGfx = TRUE;
	
	if (offset > 0) {
		sibInfo->scanned = TRUE;
	}
}

void setObject(struct fullInfo *info, enum objectTypes type)
{
	info->object.type = type;
	info->object.frame = 0;

	info->gfx.gfxFrame = info->object.type;
	info->gfx.dist = 0;

	info->updateGfx = TRUE;
}

void setSibObject(struct fullInfo *info, enum dirTypes dir, enum objectTypes type)
{
	WORD offset = offsets[dir];
	struct fullInfo *sibInfo = info + offset;

	sibInfo->object.type = type;
	sibInfo->object.frame = 0;

	sibInfo->gfx.gfxFrame = sibInfo->object.type;
	sibInfo->gfx.dist = 0;

	sibInfo->updateGfx = TRUE;

	if (offset > 0) {
		sibInfo->scanned = TRUE;
	}
}

/* Move object smoothly. Return TRUE if it is ready for next movement */
BOOL animateObjectMove(struct fullInfo *info)
{
	struct gfxInfo *gi = &info->gfx;
	struct objectTypeInfo *oti = typeInfo + info->object.type;

	if (gi->dist > 0) {
		gi->dist -= oti->speed;
		info->updateGfx = TRUE;
		return(FALSE);
	}
	return(TRUE);
}

void heroHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
	if (animateObjectMove(info)) {
		if (bi->moveHero) {
			enum dirTypes dir = info->gfx.dir;
			WORD offset = offsets[dir];
			struct fullInfo *sibInfo = info + offset;

			switch (sibInfo->object.type) {
			case FLOOR:
				beginObjectMove(info, dir);
				break;
			case CHERRY:
				bi->collected++;
				beginObjectMove(info, dir);
				break;
			case AMMO:
				bi->ammo += AMMO_PACK;
				beginObjectMove(info, dir);
			case KEY:
				bi->keys++;
				beginObjectMove(info, dir);
				break;
			case DOOR:
				if (bi->keys > 0)
				{
					bi->keys--;
					setSibObject(info, dir, FLOOR);
					break;
				}
				break;			
			case SKULL:
				setSibObject(info, dir, FIRE);
				setObject(info, FLOOR);
				break;
			default:
				break;
			}
		}
	}
}

void bulletHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
	D(bug("Bullet (%d)\n", info->gfx.dist));
	if (animateObjectMove(info)) {
		enum dirTypes dir = info->gfx.dir;
		WORD offset = offsets[dir];
		struct fullInfo *sibInfo = info + offset;

		switch (sibInfo->object.type) {
		case FLOOR:
			beginObjectMove(info, dir);
			break;
		case HERO:
		case DEBRIS:
		case SKULL:
			setSibObject(info, dir, FIRE);
			setObject(info, FLOOR);
			break;
		default:
			setObject(info, FIRE);
			break;
		}		
	}
}

void fireHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{
	const UWORD frames = 8;

	info->updateGfx = TRUE; /* Note: Update only if gfxFrame changed. */

	if (++info->object.frame == frames) {
		setObject(info, FLOOR);
	}
}

void skullHandler(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info)
{	
	D(bug("Skull (%d)\n", info->gfx.dist));
	if (animateObjectMove(info)) {
		enum dirTypes dir = info->gfx.dir;
		WORD offset = offsets[dir];
		struct fullInfo *sibInfo = info + offset;

		switch (sibInfo->object.type) {
		case FLOOR:
			beginObjectMove(info, dir);
			break;
		case HERO:		
			setSibObject(info, dir, FIRE);
			setObject(info, FLOOR);
			break;
		default:
			info->gfx.dir = oppositeDir(dir);
			break;
		}
	}
}
