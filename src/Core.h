#pragma once

#define SDL_MAIN_HANDLED
#define rootpath "C:/Users/cew05/OneDrive/Documents/GitHub/Basic-GUI-in-CPP"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

// Define Renderer and Surface objects only once
extern SDL_Renderer* renderer;
extern SDL_Surface* surface;


class Window
{
    private:
        SDL_Window* win = nullptr;
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        int winwidth;
        int winheight;

        //Vars for creating grid visuals
        SDL_Color border {200, 255, 200, 255};
        SDL_Color lightBg {0, 200, 0, 255};
        SDL_Color darkBg {0, 155, 0, 255};

    public:
        explicit Window(const char* title = "New Window", int width = 500, int height = 500);
        void CheckerDisplay(int width, int height, int rows = 1, int columns = 1);
        SDL_Window* WinObject() { return win; }
        std::vector<int> GetWinSize() { return {winwidth, winheight}; }
};