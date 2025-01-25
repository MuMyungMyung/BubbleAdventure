#include <SDL3/SDL.h>
#include <iostream>
#include "ecs/World.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

int main(void)
{
    SDL_Window *window = nullptr;
    SDL_Renderer *mainRenderer = nullptr;

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("BubbleAdventure", 800, 600, 0, &window, &mainRenderer);

    if (!window || !mainRenderer) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    World world;

    bool quit = false;
    auto previousTime = SDL_GetTicks();

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_DestroyWindow(window);
                quit = true;
            }
            world.handleEvents(event);
        }
        auto currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;
        world.updateSystems(deltaTime);
        SDL_RenderClear(mainRenderer);
        world.render(mainRenderer);
        SDL_RenderPresent(mainRenderer);
    }
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
