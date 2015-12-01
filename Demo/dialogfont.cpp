#include "stdafx.h"
#include "dialogfont.h"


dialogfont::dialogfont()
{
	bold.CreateFont(-12, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0,
		0, "MS Sans Serif");
	normal.CreateFont(-8, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0,
		0, "MS Sans Serif");
}


dialogfont::~dialogfont()
{
	bold.CreateFont(-12, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0,
		0, "MS Sans Serif");
	normal.CreateFont(-8, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0,
		0, "MS Sans Serif");
}

