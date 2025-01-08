#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <assert.h>
#include <deck.h>
#include <stdbool.h>

#include "SDL3/SDL_video.h"

void get_srect(Card card, SDL_FRect *s_rect);

int main() {
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *card_spritesheet;
    SDL_Texture *card_back_spritesheet;

    SDL_FRect card_back_srect;
    SDL_FRect card_srect;
    SDL_FRect deck_rect;
    SDL_FRect draw_pile_rect;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer("Popcorn", 1080, 1080, SDL_WINDOW_OPENGL,
                                &window, &renderer);

    card_spritesheet = IMG_LoadTexture(renderer, "./gfx/playingCards.png");
    card_back_spritesheet =
        IMG_LoadTexture(renderer, "./gfx/playingCardBacks.png");

    card_srect.w = 140;
    card_srect.h = 190;

    card_back_srect.x = 0;
    card_back_srect.y = 0;
    card_back_srect.w = 140;
    card_back_srect.h = 190;

    deck_rect.w = 140;
    deck_rect.h = 190;
    deck_rect.x = 1080 - 140;
    deck_rect.y = 0;

    draw_pile_rect.w = 140;
    draw_pile_rect.h = 190;
    draw_pile_rect.x = 0;
    draw_pile_rect.y = 0;

    Deck deck;

    create_deck(&deck, DECK_CAPACITY);
    populate_deck(&deck);
    shuffle_deck(&deck);


    bool running = true;

    get_srect(draw_from_deck(&deck), &card_srect);

    // Render the deck and start drawing
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                continue;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                // Draw card logic
                Card card = draw_from_deck(&deck);
                get_srect(card, &card_srect);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, card_spritesheet, &card_srect,
                          &draw_pile_rect);
        SDL_RenderTexture(renderer, card_back_spritesheet, &card_back_srect,
                          &deck_rect);
        SDL_RenderPresent(renderer);
    }

    free_deck(&deck);

    SDL_DestroyTexture(card_back_spritesheet);
    SDL_DestroyTexture(card_spritesheet);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

void get_srect(Card card, SDL_FRect *s_rect) {
    s_rect->x = (card.suit) * s_rect->w;
    s_rect->y = (card.value) * s_rect->h;
}
