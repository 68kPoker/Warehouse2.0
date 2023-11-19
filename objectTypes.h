
#ifndef OBJECT_TYPES_H
#define OBJECT_TYPES_H

#include <exec/types.h>

enum backGroundTypes {
	BACKGROUND
};

enum objectTypes {
	FLOOR,
	WALL,
	HERO,
	BOX,
	CHERRY,
	KEY,
	DOOR,
	AMMO,
	DEBRIS,
	BULLET,
	FIRE,
	SKULL,
	EXIT,
	TYPES
};

struct objectTypeInfo {
	void (*handler)(struct boardInfo *bi, UWORD j, UWORD i, struct fullInfo *info);
	UWORD speed;
};

#endif 
