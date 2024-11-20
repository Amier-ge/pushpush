#ifndef _HEADER_H
#define _HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>

#define TRUE			1
#define FALSE			0

#define PUSH_SIZE		20

#define KEY_UP			72
#define KEY_DOWN		80
#define KEY_RIGHT		77
#define KEY_LEFT		75

#define ICON_WALL		0
#define ICON_EMPTY		1
#define ICON_USER		2
#define ICON_BLOCK		3
#define ICON_TARGET		4
		
int getKey();
void init();
void display();
int checkMove(int );
int moveUser(int , int );
int checkFinish();
void gotoxy(int , int );

#endif