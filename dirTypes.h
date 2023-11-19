
#include <exec/types.h>

enum dirTypes {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum dirTypes oppositeDir(enum dirTypes dir);
enum dirTypes clockWise(enum dirTypes dir);
