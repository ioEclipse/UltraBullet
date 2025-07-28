#include "Game.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	//Limit Frame rate, for now 60.
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	//Colors line colors #7044a0
	r = 112;
	g = 68;
	b = 160;
	//Curve points
	increment = 100;
	incT = 1.0 / increment;
	pointCount = 1;
	//Curve values
	newCurve = false;
	for (int i = 0; i < increment; i++) //fill structs with default data
	{
		BezierPoints[i].Line = L;
		BezierPoints[i].distance = 0;
		BezierPoints[i].onPoint = false;
		BezierPoints[i].scanned = false;

	}
	//Start Circle follow mouse
	followMouse = false;

	//====================Initilize game===================//
	init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
	while (isRunning)
	{

		frameStart = SDL_GetTicks(); //how many seconds it's been since SDL started

		//MOUSE
		SDL_GetMouseState(                    //    Sets mouse_position to...
			&mouse_position.x,                // ...mouse arrow coords on window
			&mouse_position.y
		);

		//EVENTS
		handleEvents();

		//=================Render==============//
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, r, g, b, 255); //current #7044a0
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //Doesn't do much for now

		//Draw outside border
		drawOutsideBorder();
		//drawInnerBorder(); debug border for testing curves

		//request next Curve
		if (newCurve) {
			nextCurve();
			//followMouse = false;
			pointCount = 0;
			failedPoints = 0;
			circleMouse(P0);
		}
		//draw lines
		for (int i = 0; i < increment; i++) {
			drawCurve(BezierPoints[i].Line);
			//BezierPoints[i].scanned = false;
		}

		startFollowingMouse();

		//Images
		if (followMouse)
		{
			circleMouse(mouse_position);
			checkLineContact();
		}
		SDL_RenderCopy(renderer, startCircle, NULL, &mouseCircle);

		//Present rendered things
		SDL_SetRenderDrawColor(renderer, 5, 34, 45, 255); //#05222d background 5, 34, 45, 255
		SDL_RenderPresent(renderer);
		//===============EndRender=============//

		frameTime = SDL_GetTicks() - frameStart; //how many ticks (miliseconds) the frame took

		if (frameDelay > frameTime) //check if we need to delay next frame
		{
			SDL_Delay(frameDelay - frameTime); //delay
		}

	}
	//===============Game has been exited==================//
	clean();
	printf("Game exited successfully");
	SDL_Delay(1000); // Delay for console

	return 0;
}