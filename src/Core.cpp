#include "Core.h"

// Extern Globals given definition
SDL_Renderer* renderer;
SDL_Surface* surface;
bool running;

Window::Window(const char* title, int width, int height, int sqwidth, int sqheight)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    running = true;
    SDL_Window* window = SDL_CreateWindow(title, // creates a window
                           SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height, 0);

    renderer = SDL_CreateRenderer(window, -1, render_flags);
    winwidth = width;
    winheight = height;
    this->sqheight = sqheight;
    this->sqwidth = sqwidth;
}

void Window::Render()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Window::CheckerDisplay(int numrows, int numcolumns)
{
    bool altbg = false;
    this->rows = numrows;
    this->columns = numcolumns;

    bufferx = ( winheight - (columns * sqwidth) )/2;
    buffery = ( winwidth - (rows * sqheight) )/2;

    for (int r = 0; r < numrows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            SDL_Rect bgsquare {c*sqwidth + bufferx, r*sqheight+buffery, sqwidth, sqheight};
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