#pragma once

class Player {
    private:
        // Visuals Variables
        SDL_Rect selfRect{};
        SDL_Texture *texture;
        std::string imgPath = "/Resources/PlaceholderImages/BluePlayerSquare.png";

        //
        int speed = 20;
        std::vector<int> position{};


    public:
        explicit Player(std::vector<int> initpos);
        void UpdatePos(std::vector<int> const &moveby, std::vector<int> const &bounds);
        void Display();
        [[maybe_unused]] std::vector<int> GetPos() { return {selfRect.x, selfRect.y}; }
        [[maybe_unused]] void SetRectDimensions() { selfRect.w = 50; selfRect.h = 50; }

};