#include <stdio.h>
#include <SDL2/SDL.h>

void handleInput(SDL_Event* event, int* game_active){
  while(SDL_PollEvent(event))
    switch(event->type){
      case SDL_QUIT:
      *game_active = 0; //Off
      break;
      case SDL_KEYDOWN:
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_SPACE:
        *game_active = 0;
          break;
        
        default:
          break;
        }
      break;
      //Handle the actual input here
    }
}
void handlePlayerMovement(){
  // Take movement input
  // Muliply by a few factors
  // Scale those factors to time (slow decay over time or custom timer)
}

int main(int argc, char* argv[])
{
  /* Initializes the timer, audio, video, joystick,
  haptic, gamecontroller and events subsystems */
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return -1;
  }
  

  SDL_Window* window = SDL_CreateWindow("The Gardener", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 420, 0);
  if (!window)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer){
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  int running = 1;
  SDL_Event event;

  while(running == 1){
    handleInput(&event, &running);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}