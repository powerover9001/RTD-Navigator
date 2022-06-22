#include "RenderWindow.hpp"
#include <iostream>

RenderWindow::RenderWindow(const char* p_title) : window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640, 360,
                                SDL_WINDOW_SHOWN |
                                SDL_WINDOW_FULLSCREEN_DESKTOP |
                                SDL_WINDOW_BORDERLESS |
                                SDL_WINDOW_ALWAYS_ON_TOP
    );

    if(window == NULL){
        std::cout << "Window failed to run. Error: " << SDL_GetError() << "\n";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

/*
SDL_Texture *RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL) std::cout << "Failed to load texture. Error" << SDL_GetError() << "\n";


    return texture;
}*/


void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

/*
void RenderWindow::render(SDL_Texture* p_tex){
    //NULL, NULL FILLS THE ENTIRE SCREEN
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}*/


void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}


void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}
