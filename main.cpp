#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <iostream>
#include "chip8.h"

constexpr int windowWidth = 64;
constexpr int windowHeight = 32;
constexpr int SCALE = 10;
const char* gameName = "draw_test.ch8";

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

chip8 c8;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata("Chip8 Example", "1.0", "com.example.chip8");

    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Example CHIP8 Window", 
                                    windowWidth*SCALE, windowHeight*SCALE, 
                                    SDL_WINDOW_RESIZABLE, &window, &renderer)){
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // For letterboxing to be used with resizing window
    SDL_SetRenderLogicalPresentation(renderer, windowWidth, windowHeight, 
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    c8.initialize();
    if(c8.loadGame(gameName)){
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_KEY_DOWN) {
        uint8_t c8key = c8.scancodeToChip8(event->key.scancode);
        if (c8key != 0xFF) c8.key[c8key] = 1;
    }
    else if (event->type == SDL_EVENT_KEY_UP) {
        uint8_t c8key = c8.scancodeToChip8(event->key.scancode);

        if (c8key != 0xFF) c8.key[c8key] = 0;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    c8.emulateCycle();

    //if(c8.drawFlag){
        //std::vector<SDL_FRect> rects;
        //rects.reserve(64*32);

        //update screen, draw black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // now draw white pixels (rects)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for(int i=0; i < 64*32; i++){
            if (c8.gfx[i]){
                SDL_FRect rect{
                    static_cast<float>(i % 64),
                    static_cast<float>(i / 64),
                    1.0f,
                    1.0f
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        //SDL_RenderFillRects(renderer, rects.data(), rects.size());
        SDL_RenderPresent(renderer);

        c8.drawFlag = false;
    //}

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    // SDL cleans it up for us.
}

