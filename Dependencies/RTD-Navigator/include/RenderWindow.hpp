#pragma once

#include <SDL.h>
#include <SDL_image.h>


class RenderWindow{
    public:
        RenderWindow(const char* p_title);
        
        void clear();
        //void render();
        void display();
        void cleanUp();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};