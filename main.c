#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#define width 640
#define height 480
#define MAX 300


typedef struct particle{
	int x;
	int y;
	char d; // Directions;
	struct particle* next;
} particle;

void main_func();
particle* build_list();
void coalision(particle* current, particle* temp);




void main_func(){

	particle* head = build_list();
	particle* temp;


	if (SDL_Init(SDL_INIT_VIDEO) != 0) { fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError()); exit(-1); }
	SDL_Window* window = SDL_CreateWindow("Particle Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) { fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError()); SDL_Quit(); exit(-1); }
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) { fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError()); SDL_DestroyWindow(window); SDL_Quit(); exit(-1); }


	while(true){

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);        //
		SDL_RenderClear(renderer);                             // clear the screen with black
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white

		temp = head;
		while(temp!=NULL){

			SDL_Event event;                                                           //
			while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) { exit(-1); }} // for exiting


			switch (temp->d){
				case 'l': temp->x--; break;
				case 'u': temp->x--; temp->y--; break;
				case 't': temp->y--; break;
				case 'x': temp->x++; temp->y--; break;
				case 'r': temp->x++; break;
				case 'y': temp->x++; temp->y++; break;
				case 'b': temp->y++; break;
				case 'z': temp->x--; temp->y++; break;

			}
			if (temp->x == -1){
				switch (temp->d){
					case 'l': temp->d='r'; break;
					case 'u': temp->d='x'; temp->y--; break;
					case 'z': temp->d='y'; temp->y++; break;
				}
				temp->x = 1;
			}
			else if (temp->x == width){
				switch (temp->d){
					case 'r': temp->d='l'; break;
					case 'x': temp->d='u'; temp->y--; break;
					case 'y': temp->d='z'; temp->y++; break;
				}
				temp->x = width-1;
			}

			if (temp->y == -1){
				switch (temp->d){
					case 't': temp->d='b'; break;
					case 'u': temp->d='z'; temp->x--; break;
					case 'x': temp->d='y'; temp->x++; break;
				}
				temp->y = 1;
			}
			else if (temp->y == height){
				switch (temp->d){
					case 'b': temp->d='t'; break;
					case 'z': temp->d='u'; temp->x--; break;
					case 'y': temp->d='x'; temp->x++; break;
				}
				temp->y = height-1;
			}





			coalision(temp, head);


			SDL_RenderDrawPoint(renderer, temp->x, temp->y);
			temp = temp->next;
		}



		SDL_RenderPresent(renderer);
		usleep(10000);

	}






	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


}



void coalision(particle* current, particle* temp){

	while(temp != current){

		if(temp->x==current->x){
			if(temp->y==current->y){

				switch(current->d){
					case 'b': switch(temp->d){

						case 'z': current->d='z'; temp->d='b'; break;
						case 'l': current->d='l'; temp->d='b'; break;
						case 'u': current->d='l'; temp->d='z'; break;
						case 't': current->d='t'; temp->d='b'; break;
						case 'x': current->d='r'; temp->d='y'; break;
						case 'r': current->d='r'; temp->d='b'; break;
						case 'y': current->d='y'; temp->d='b'; break;
					} break;
					case 'z': switch(temp->d){

						case 'b': current->d='b'; temp->d='z'; break;
						case 'l': current->d='l'; temp->d='z'; break;
						case 'u': current->d='u'; temp->d='z'; break;
						case 't': current->d='u'; temp->d='l'; break;
						case 'x': current->d='x'; temp->d='z'; break;
						case 'r': current->d='y'; temp->d='b'; break;
						case 'y': current->d='y'; temp->d='z'; break;
					} break;
					case 'l': switch(temp->d){

						case 'z': current->d='z'; temp->d='l'; break;
						case 'b': current->d='b'; temp->d='l'; break;
						case 'u': current->d='u'; temp->d='l'; break;
						case 't': current->d='t'; temp->d='l'; break;
						case 'x': current->d='t'; temp->d='u'; break;
						case 'r': current->d='r'; temp->d='l'; break;
						case 'y': current->d='b'; temp->d='z'; break;
					} break;
					case 'u': switch(temp->d){

						case 'z': current->d='z'; temp->d='u'; break;
						case 'l': current->d='l'; temp->d='u'; break;
						case 'b': current->d='z'; temp->d='l'; break;
						case 't': current->d='t'; temp->d='u'; break;
						case 'x': current->d='x'; temp->d='u'; break;
						case 'r': current->d='x'; temp->d='t'; break;
						case 'y': current->d='y'; temp->d='u'; break;
					} break;
					case 't': switch(temp->d){

						case 'z': current->d='l'; temp->d='u'; break;
						case 'l': current->d='l'; temp->d='t'; break;
						case 'u': current->d='u'; temp->d='t'; break;
						case 'b': current->d='b'; temp->d='t'; break;
						case 'x': current->d='x'; temp->d='t'; break;
						case 'r': current->d='r'; temp->d='t'; break;
						case 'y': current->d='r'; temp->d='x'; break;
					} break;
					case 'x': switch(temp->d){

						case 'z': current->d='z'; temp->d='x'; break;
						case 'l': current->d='u'; temp->d='t'; break;
						case 'u': current->d='u'; temp->d='x'; break;
						case 't': current->d='t'; temp->d='x'; break;
						case 'b': current->d='y'; temp->d='r'; break;
						case 'r': current->d='r'; temp->d='x'; break;
						case 'y': current->d='y'; temp->d='x'; break;
					} break;
					case 'r': switch(temp->d){

						case 'z': current->d='b'; temp->d='y'; break;
						case 'l': current->d='l'; temp->d='r'; break;
						case 'u': current->d='t'; temp->d='x'; break;
						case 't': current->d='t'; temp->d='r'; break;
						case 'x': current->d='x'; temp->d='r'; break;
						case 'b': current->d='b'; temp->d='r'; break;
						case 'y': current->d='y'; temp->d='r'; break;
					} break;
					case 'y': switch(temp->d){

						case 'z': current->d='z'; temp->d='y'; break;
						case 'l': current->d='z'; temp->d='b'; break;
						case 'u': current->d='u'; temp->d='y'; break;
						case 't': current->d='x'; temp->d='r'; break;
						case 'x': current->d='x'; temp->d='y'; break;
						case 'r': current->d='r'; temp->d='y'; break;
						case 'b': current->d='b'; temp->d='y'; break;
					} break;
				}
			}
		}
		temp = temp->next;
	}
}










particle* build_list(){
	int i;
	char directions[8] = {'l', 'u', 't', 'x', 'r', 'y', 'b', 'z'};
	particle* head = NULL;
	particle* temp;

	for(i=0;i<MAX;i++){
		temp = (particle*)malloc(sizeof(particle));
		temp->x = rand()%width;
		temp->y = rand()%height;
		temp->d = directions[rand()%8];
		temp->next = head;
		head = temp;
	}
	return head;
}





int main(int argc, char* argv[]){

	main_func();
	return 0;
}
