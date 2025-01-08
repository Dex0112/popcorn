#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>

#include <deck.h>
#include <stdio.h>

#include "SDL3/SDL_video.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer("Popcorn", 700, 950, SDL_WINDOW_OPENGL, &window,
                                &renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Deck deck;

    create_deck(&deck);
    populate_deck(&deck);

    printf("\n\n\n");
    print_deck(&deck);
    shuffle_deck(&deck);
    printf("\n\n\n");
    print_deck(&deck);
    printf("\n\n\n");

    free_deck(&deck);

    SDL_Quit();

    return 0;
}
