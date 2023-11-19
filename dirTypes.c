
#include "dirTypes.h"

enum dirTypes oppositeDir(enum dirTypes dir)
{
	return(dir ^ 1);
}

enum dirTypes clockWise(enum dirTypes dir)
{
	static enum dirTypes clockWise[] = {
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	return(clockWise[dir]);
}
