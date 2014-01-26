#ifndef TERMINAL_H
#define TERMINAL_H

#include "struct.h"
#include "chip.h"

// For terminal display, a color is simply an escape sequence
typedef char* color;

#define TermColor_Normal  	"\x1B[0m"
#define TermColor_Red  		"\x1B[31m"
#define TermColor_Green  	"\x1B[32m"
#define TermColor_Yellow 	"\x1B[33m"
#define TermColor_Blue  	"\x1B[34m"
#define TermColor_Magenta 	"\x1B[35m"
#define TermColor_Cyan 		"\x1B[36m"
#define TermColor_White 	"\x1B[37m"

#endif