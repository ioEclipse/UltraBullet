#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include <stdlib.h>

//SDL and Events
void init(const char* title, int xpos, int ypos, int width, int height);
void handleEvents();
void clean();
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;

//Textures
SDL_Texture* startCircle;

//Ultrabullet functions
void drawCurve(SDL_FRect Line);
void randomizePoints();
void drawOutsideBorder();
void drawInnerBorder();
void circleMouse(SDL_Point mousePos);
SDL_Point newControlPoint(rand);
SDL_FPoint BezierPoint(double PointT, SDL_Point Point0, SDL_Point Point1, SDL_Point Point2, SDL_Point Point3);
SDL_FRect BezierLine(SDL_FPoint BezierPoint1, SDL_FPoint BezierPoint2);
float calcDistance(float x1, float y1, float x2, float y2);
void startFollowingMouse();
void checkLineContact();

void nextCurve();
//bool isOnLine(SDL_Point mousePos, );

//struct
struct FRect {
	SDL_FRect Line;
	float distance;
	bool onPoint;
	bool scanned;
};
struct FRect BezierPoints[100];

//Variables

bool isRunning; //Game loop
SDL_Point P0;  //Anchor
SDL_Point P1; //Control
SDL_Point P2; //Control
SDL_Point P3;; //Anchor

SDL_FPoint B1;
SDL_FPoint B2;
SDL_FRect L;
//Mouse position
SDL_Point mouse_position;
SDL_Rect mouseCircle;

int r;
int g;
int b;
int failedPoints;
int pointCount;
int completedCurves;
int increment;

double incT;
double t; //Bezier func variable

bool isTouching;
bool followMouse;
bool newCurve;
bool onLine;

#endif /* Game_h */