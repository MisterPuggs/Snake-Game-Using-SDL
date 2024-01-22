#pragma once

class SnakeBody
{
    private:
        // Visuals
        SDL_Rect selfRect {};
        SDL_Texture* texture {};
        std::string imgPath = "/Resources/PlaceholderImages/BluePlayerSquare.png";

        // Vars
        int stall;
        int x, y;
        int prevx, prevy;

    public:
        SnakeBody(int x, int y, int stall);
        void MoveTo(int x, int y);
        void Display(Window &win);
        std::vector<int> GetPrevPosition() { return {prevx, prevy}; }
        std::vector<int> GetPosition() { return {x, y}; }
};

class Snake
{
    private:
        std::vector<SnakeBody> bodySegments {};

        bool dead = false;
        int maxdelay = 300;
        std::vector<int> nextdirection {0, -1}, currdirection {0, -1};
        Uint64 prevmovecalltick {}, movedelayticks = SDL_GetTicks64() + maxdelay;

    public:
        Snake(int x, int y, int segments);
        void AddSegment();
        void Move(int movx, int movy);
        bool GetDead() { return dead; }
        void SetDirection(int dirx, int diry);
        void Display();
        void SetSpeed(int newdelay) { maxdelay = newdelay; }
        std::vector<SnakeBody> GetSegments() { return bodySegments; }
};