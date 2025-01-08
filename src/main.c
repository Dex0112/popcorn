#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>

#include "SDL3/SDL_video.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *texture;
    SDL_FRect texture_rect;
    SDL_FRect texture_srect;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer("Popcorn", 700, 950, SDL_WINDOW_OPENGL, &window,
                                &renderer);

    texture = IMG_LoadTexture(renderer, "./gfx/playingCards.png");

    texture_rect.w = 140;
    texture_rect.h = 190;

    texture_srect.w = 140;
    texture_srect.h = 190;

    bool is_down = false;

    int idx = 0;

    while (1) {
        SDL_PollEvent(&event);

        if (event.type == SDL_EVENT_QUIT) break;

        float x, y;

        if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_LEFT) {
            texture_rect.x = x - texture_rect.w / 2;
            texture_rect.y = y - texture_rect.h / 2;

            if (is_down == false) {
                idx = (idx + 1) % 53;

                int idx_x = idx / 10;
                int idx_y = idx % 10;

                texture_srect.y = texture_srect.h * idx_y;
                texture_srect.x = texture_srect.w * idx_x;
                is_down = true;
            }
        } else {
            is_down = false;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, &texture_srect, &texture_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);

    SDL_Quit();

    return 0;
}
