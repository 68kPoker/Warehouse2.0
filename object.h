
#include <exec/types.h>
#include "objectTypes.h"

#define DIST  16
#define SPEED 2

#define WIDE  20
#define TALL  16

#define AMMO_PACK 8

struct objectInfo {
	enum objectTypes type;
	UWORD frame;
};

struct gfxInfo {
	enum dirTypes dir;
	UWORD dist;
	UWORD gfxFrame;
};

struct fullInfo {
	struct objectInfo object;
	struct gfxInfo gfx, prevGfx[2];
	BOOL updateGfx;
	BOOL drawn;
	BOOL scanned;
};

struct boardInfo {
	struct fullInfo info[WIDE][TALL];
	UWORD frame;
	BOOL moveHero;
	UWORD collected, total, keys, ammo;
	struct RastPort *rp;
};

void scanBoard(struct boardInfo *bi);
BOOL animateObjectMove(struct fullInfo *info);
void setObject(struct fullInfo *info, enum objectTypes type);

extern struct objectTypeInfo typeInfo[TYPES];
extern WORD offsets[];
