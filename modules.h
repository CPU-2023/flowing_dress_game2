#define _CRT_SECURE_NO_WARN
#pragma once
#include<stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <string.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")



#ifndef __COLOR_LIST_
#define __COLOR_LIST_

enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

#endif

void gotoxy(int x, int y);
void gotoxy_2x(int x, int y);
void CursorView();
void setBackColor(int forground, int background);
void setColor(int color);
int keyControl(int, int, int);