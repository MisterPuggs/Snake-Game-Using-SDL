#pragma once

class SnakeBody
{
    private:
        // Visuals
        SDL_Rect selfRect {};
        SDL_Texture* texture {};
        std::string imgPath = "/Resources/PlaceholderImages/BluePlayerSquare.png";

        // Vars
        bool stiff = true;
        int x, y;
        int prevx, prevy;

    public:
        SnakeBody(int x, int y, int w, int h);
        void MoveTo(int x, int y);
        void Display();
        std::vector<int> GetPosition() { return {x, y}; }
        std::vector<int> GetPrevPosition() { return {prevx, prevy}; }
};
class Snake
{
    private:
        std::vector<SnakeBody> bodySegments {};
        int rectw, recth;
        int speed;
        std::vector<int> direction {0, -1};
    public:
        Snake(int x, int y, int squarelength = 32);
        void AddSegment();
        void Move();
        void SetDirection(int dirx, int diry);
        void Display();

};