#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DRAW_INTERVAL 16

static Uint32 onTimer(Uint32 interval, void *param) {
    (void) interval;
    int * drawEvent = (param);
    SDL_Event event;
    event.type = *drawEvent;
    SDL_PushEvent(&event);

    return DRAW_INTERVAL;
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "error: failed to init sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window * window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (NULL == window) {
        fprintf(stderr, "error: could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    Uint32 drawEvent = SDL_RegisterEvents(1);
    if (drawEvent == ((Uint32) -1)) {
        fprintf(stderr, "error: failed to register user event");
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_TimerID timerId = SDL_AddTimer(DRAW_INTERVAL, onTimer, &drawEvent);
    if (timerId == 0) {
        fprintf(stderr, "error: failed to add timer");
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bool done = false;
    while (!done) {
        SDL_Event event;
        int const rc = SDL_WaitEvent(&event);
        if (rc == 1) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_MOUSEMOTION:
                    printf("mouse moved: %d : %d\n", event.motion.x, event.motion.y);
                    break;
                default:
                    if (event.type == drawEvent) {
                        SDL_Surface * surface = SDL_GetWindowSurface(window);
                        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
                        SDL_UpdateWindowSurface(window);
                    }
                    break;
            }
        }

    }

    SDL_RemoveTimer(timerId);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}