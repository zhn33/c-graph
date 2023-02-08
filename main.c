#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
int y[SCREEN_WIDTH];
static unsigned int INCR = 2;
void DrawFunction(SDL_Renderer* renderer,SDL_Window* window, int INCR, char* FUNCTION);
void DrawLines(SDL_Renderer* renderer, SDL_Window* window);
void Input(SDL_Renderer* renderer,SDL_Window* window, char* FUNCTION);
void Quit(SDL_Renderer* renderer,SDL_Window* window);

int main( int argc, char* args[] ){
  SDL_Window* window;
  SDL_Renderer* renderer;
  int i;
  double x,d;
	char FUNCTION[10] = "(10*d)+100";
  const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL) ;
  y[0] = 0;
  i = 1;
  SDL_Init( SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	DrawLines(renderer,window);
	DrawFunction(renderer,window, INCR,FUNCTION);
	SDL_UpdateWindowSurface( window );
	while(true){
		Input(renderer,window, FUNCTION);
	}
  return 0;
}

void Input(SDL_Renderer* renderer,SDL_Window* window, char* FUNCTION){
SDL_Event event;
int mouseX,mouseY;
while( SDL_PollEvent( &event ) ){
	switch( event.type ){
		case SDL_MOUSEMOTION:{
			SDL_GetMouseState( &mouseX, &mouseY);
			printf("%d\n", y[SCREEN_WIDTH-(mouseX/INCR)]);
			printf("%d\n", mouseX);
			break;
		}
		case SDL_KEYDOWN:
			switch( event.key.keysym.sym ){
				case SDLK_LEFT:
				case SDLK_RIGHT:
				case SDL_QUIT:
					Quit(renderer,window);
					break;
				case SDLK_UP:
					INCR += 1;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderClear(renderer);
					DrawLines(renderer,window);
					DrawFunction(renderer,window, INCR,FUNCTION);
					SDL_UpdateWindowSurface( window );
					break;
				case SDLK_DOWN:
					if(INCR > 1){
						INCR -= 1;
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
						SDL_RenderClear(renderer);
						DrawLines(renderer,window);
						DrawFunction(renderer,window, INCR,FUNCTION);
						SDL_UpdateWindowSurface( window );
					}
					break;
				default:
					break;
			}
		}
	}
}

void DrawFunction(SDL_Renderer* renderer,SDL_Window* window, int INCR, char* FUNCTION){
  int i,x;
  double d;
  y[0] = 0;
  i = (SCREEN_WIDTH/2);
	SDL_SetRenderDrawColor(renderer, 255,20,20,255);
	for(x = (SCREEN_WIDTH/2)-INCR, d = 0;x<=SCREEN_WIDTH;x += INCR, i++,d++){
		if(x == (SCREEN_WIDTH/2)-INCR){
			d -= 1;
			y[i-1]=100*tan(d/10);//eval(FUNCTION);
			d += 1;
		}
		y[i]=100*tan(d/10);//(10*d)+100;
		if(y[i]<(SCREEN_HEIGHT+200)){
			SDL_RenderDrawLine(renderer, x, (SCREEN_HEIGHT/2)-(y[i-1]), x+INCR,
			(SCREEN_HEIGHT/2)-(y[i]));
		}
	}
		printf("%d\n",y[320]);
	  i = (SCREEN_WIDTH/2);
	for(x = (SCREEN_WIDTH/2)+INCR, d = 0;x>=0;x -= INCR, i--,d--){
		if(x == (SCREEN_WIDTH/2)+INCR){
			d += 1;
			y[i+1]=100*tan(d/10);//(10*d)+100;
			d -= 1;
		}
		y[i]=100*tan(d/10);
		if(y[i]<(SCREEN_HEIGHT+200)){
			SDL_RenderDrawLine(renderer, x, (SCREEN_HEIGHT/2)-(y[i+1]), x-INCR,
			(SCREEN_HEIGHT/2)-(y[i]));
		}
	}
		printf("%d\n",y[320]);
	SDL_RenderPresent( renderer);
    SDL_UpdateWindowSurface( window );
}

void DrawLines(SDL_Renderer* renderer, SDL_Window* window){
	SDL_SetRenderDrawColor(renderer, 255,0,0,255);
	SDL_RenderDrawLine(renderer, 0,(SCREEN_HEIGHT/2),(SCREEN_WIDTH),(SCREEN_HEIGHT/2));
	SDL_RenderDrawLine(renderer, (SCREEN_WIDTH/2),0,(SCREEN_WIDTH/2),(SCREEN_HEIGHT));
	SDL_RenderPresent( renderer);
    SDL_UpdateWindowSurface( window );
}

void Quit(SDL_Renderer* renderer,SDL_Window* window){
  SDL_DestroyRenderer( renderer);
  SDL_DestroyWindow( window );
  SDL_Quit();
  exit(0);
}
