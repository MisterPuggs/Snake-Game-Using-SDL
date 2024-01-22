#pragma once

#define SDL_MAIN_HANDLED
#define rootpath "C:/Users/cew05/OneDrive/Documents/GitHub/Basic-GUI-in-CPP"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <ctime>

// Global Accessible
extern SDL_Renderer* renderer;
extern SDL_Surface* surface;
extern bool running;

class Window
{
    private:
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        int winwidth, winheight;
        int sqwidth, sqheight;
        int rows, columns;
        int bufferx, buffery;

        //Vars for creating grid visuals
        SDL_Color border {200, 255, 200, 255};
        SDL_Color lightBg {0, 200, 0, 255};
        SDL_Color darkBg {0, 155, 0, 255};

    public:
        Window(const char* title, int width, int height, int sqwidth, int sqheight);
        void CheckerDisplay(int rows = 1, int columns = 1);
        std::vector<int> GetWinSize() { return {winwidth, winheight}; }
        std::vector<int> GetSquareSize() {return {sqwidth, sqheight}; }
        std::vector<int> GetGridDimensions() { return {rows, columns}; }
        std::vector<int> GetBufferDimensions() { return {bufferx, buffery}; }
        static void Render();
};

// Global Accessible Window
extern Window win;