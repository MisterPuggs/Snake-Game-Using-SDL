#include "Core.h"

// Define Renderer and Surface objects only once
SDL_Renderer* renderer;
SDL_Surface* surface;

Window::Window(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow(title, // creates a window
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           width, height, 0);

    renderer = SDL_CreateRenderer(win, -1, render_flags);
    winwidth = width;
    winheight = height;
}

void Window::CheckerDisplay(int borderx, int bordery, int rows, int columns)
{
    bool altbg = false;
    int sqwidth = (winwidth-borderx)/rows;
    int sqheight = (winwidth-bordery)/columns;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            SDL_Rect bgsquare {c*sqwidth + borderx/2, r*sqheight+bordery/2, sqwidth, sqheight};
            if (!altbg)
            {
                SDL_SetRenderDrawColor(renderer, lightBg.r, lightBg.g, lightBg.b, lightBg.a);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, darkBg.r, darkBg.g, darkBg.b, darkBg.a);
            }
            altbg = !altbg;
            SDL_RenderDrawRect(renderer, &bgsquare);
            SDL_RenderFillRect(renderer, &bgsquare);
        }
        altbg = !altbg;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
