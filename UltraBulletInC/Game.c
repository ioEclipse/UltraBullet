#include "Game.h"
#include <math.h>

//SDL Framework created by Carl Birch of Let's Make Games Youtube
//Modified by Steven Bojilov for HW B37VB assignment

//Define functions
//SDL
//Init
void init(const char* title, int xpos, int ypos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		surface = SDL_GetWindowSurface(window);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		isRunning = true;
	} else {
		isRunning = false;
	}

	//Textures
	SDL_Surface* tempSurface = IMG_Load("images/StartCircle.png");
	startCircle = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	//Randomize points (prevents anchor 0,0 default)
	randomizePoints();
}

//====================handleEvents=====================//
void handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_SPACE: //Create Curve
					newCurve = true;
					followMouse = false;
					break;
				default:
					break;
			}
		default:
			break;
	}		
}

//================UltraBullet Specific================//
//-------------------Bezier Curve---------------------//
SDL_FPoint BezierPoint(double PointT, SDL_Point Point0, SDL_Point Point1, SDL_Point Point2, SDL_Point Point3)
{
	double t = PointT;
	P0 = Point0; //Anchor
	P1 = Point1; //Control
	P2 = Point2; //Control
	P3 = Point3; //Anchor

	SDL_FPoint P;

	float Px = (pow((1 - t), 3) * P0.x + 3 * pow((1 - t), 2) * t * P1.x + 3 * (1 - t) * pow(t, 2) * P2.x + pow(t, 3) * P3.x); //Cubic Benzier Curve X
	float Py = (pow((1 - t), 3) * P0.y + 3 * pow((1 - t), 2) * t * P1.y + 3 * (1 - t) * pow(t, 2) * P2.y + pow(t, 3) * P3.y); //Cubic Benzier Curve Y

	P.x = Px;
	P.y = Py;

	return P;
}

SDL_FRect BezierLine(SDL_FPoint BezierPoint1, SDL_FPoint BezierPoint2)
{
	SDL_FRect rect = {BezierPoint1.x,BezierPoint1.y,BezierPoint2.x,BezierPoint2.y};

	return rect;
}

void drawCurve(SDL_FRect Line)
{
	SDL_FRect L = Line;
	//Render lines
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawLineF(renderer, L.x, L.y, L.w, L.h);
}

void randomizePoints()
{
	P0.x = P3.x;
	P0.y = P3.y;
	P1.x = 100 + rand() % 600;
	P1.y = 100 + rand() % 400;
	P2.x = 100 + rand() % 600;
	P2.y = 100 + rand() % 400;
	P3.x = 200 + rand() % 400;
	P3.y = 200 + rand() % 200;
}

void nextCurve()
{
	//randomize control points
	randomizePoints();
	//reset curve points for tracking
	pointCount = 0;
	failedPoints = 0;
	newCurve = false;
	//Bezier Curve
	t = 0;
	for (int i = 0; i < increment; i++) {
		//calc lines
		B1 = BezierPoint(t, P0, P1, P2, P3);
		B2 = BezierPoint(t + incT, P0, P1, P2, P3);
		L = BezierLine(B1, B2);
		BezierPoints[i].Line = L;
		BezierPoints[i].onPoint = false;
		BezierPoints[i].distance = 0;
		t += incT;
	}
}

//======================GameLogic====================//

void startFollowingMouse()
{
	if (mouse_position.x < P0.x + 5 && mouse_position.x > P0.x - 5 && mouse_position.y < P0.y + 5 && mouse_position.y > P0.y - 5) 
	{
		followMouse = true;
	}
}

void checkLineContact()
{
	for (int i = 0; i < increment; i++)
	{
		BezierPoints[i].distance = calcDistance(BezierPoints[i].Line.x, BezierPoints[i].Line.y, mouse_position.x, mouse_position.y);
		if (!BezierPoints[i].onPoint && BezierPoints[i].distance < 10) {
			BezierPoints[i].onPoint = true;
			BezierPoints[i].scanned = true;
			pointCount++;
			break;
			printf("%i\n", i);
		}
		else if (!BezierPoints[i].scanned  && BezierPoints[i].distance > 10) {
			failedPoints++;
			break;
		}
	}
	if (pointCount == 99) {
		newCurve = true;
		printf("Streak: %i\n", ++completedCurves);
	}
	if (failedPoints == 99) {
		SDL_Log("Fail");
		//SDL_Delay(750);
		newCurve = true;
		followMouse = false;
		completedCurves = 0;
	}
}

//========================Misc=======================//

void circleMouse(SDL_Point mousePos)
{
	SDL_Point mouse = mousePos;
	mouseCircle.x = mouse.x-10;
	mouseCircle.y = mouse.y-10;
	mouseCircle.w = 20;
	mouseCircle.h = 20;
}

float calcDistance(float x1, float y1, float x2, float y2)
{
	float x = x1;
	float y = y1;
	float w = x2;
	float h = y2;
	float distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); //in pixels
	return distance;
}

void drawOutsideBorder()
{
	SDL_RenderDrawLine(renderer, 100, 100, 100, 500);
	SDL_RenderDrawLine(renderer, 100, 100, 700, 100);
	SDL_RenderDrawLine(renderer, 700, 500, 100, 500);
	SDL_RenderDrawLine(renderer, 700, 500, 700, 100);
}

void drawInnerBorder()
{
	SDL_RenderDrawLine(renderer, 150, 150, 150, 450);
	SDL_RenderDrawLine(renderer, 150, 150, 650, 150);
	SDL_RenderDrawLine(renderer, 650, 450, 150, 450);
	SDL_RenderDrawLine(renderer, 650, 450, 650, 150);

	SDL_RenderDrawLine(renderer, 200, 200, 200, 400);
	SDL_RenderDrawLine(renderer, 200, 200, 600, 200);
	SDL_RenderDrawLine(renderer, 600, 400, 200, 400);
	SDL_RenderDrawLine(renderer, 600, 400, 600, 200);
}

//======================Clean========================//
void clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}