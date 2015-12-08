#include "stdafx.h"
#include "usermsg.h"

struct mymsg
{
	unsigned int msg;
	WPARAM wp;
	LPARAM lp;
};

BOOL CALLBACK send_usermsg(HWND hwnd, LPARAM lParam)
{
	PostMessage(hwnd, ((mymsg *)lParam)->msg, ((mymsg *)lParam)->wp, ((mymsg *)lParam)->lp);
	return 1;
}

void update_name()
{
	mymsg m;
	m.msg = UPDATE_NAME;
	m.wp = 0;
	m.lp = 0;
	EnumThreadWindows(GetCurrentThreadId(), send_usermsg, (LPARAM)&m);
}
void update_reihe(int zeile, int name, int farbe)
{
	mymsg m;
	m.msg = UPDATE_REIHE;
	m.wp = zeile;
	m.lp = 0;
	if (name)
		m.lp |= FLAG_NAME;
	if (farbe)
		m.lp |= FLAG_FARBE;
	EnumThreadWindows(GetCurrentThreadId(), send_usermsg, (LPARAM)&m);
}
void update_wert(int zeile, int spalte)
{
	mymsg m;
	m.msg = UPDATE_WERT;
	m.wp = zeile;
	m.lp = spalte;
	EnumThreadWindows(GetCurrentThreadId(), send_usermsg, (LPARAM)&m);
}
void update_all(int name, int farbe, int wert)
{
	mymsg m;
	m.msg = UPDATE_ALL;
	m.wp = 0;
	m.lp = 0;
	if (name)
		m.lp |= FLAG_NAME;
	if (farbe)
		m.lp |= FLAG_FARBE;
	if (wert)
		m.lp |= FLAG_WERT;
	EnumThreadWindows(GetCurrentThreadId(), send_usermsg, (LPARAM)&m);
}

void close_all()
{
	mymsg m;
	m.msg = CLOSE_ALL;
	m.wp = 0;
	m.lp = 0;
	EnumThreadWindows(GetCurrentThreadId(), send_usermsg, (LPARAM)&m);
}