#include "EssentialFunctions.hpp"
#include "RenderWindow.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(){
    
    RenderWindow window("RTD-Navigator");

    bool programRunning = true;

    SDL_Event event;

    while(programRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) programRunning = false;
        }

        window.clear();
        //window.render();
        window.display();
    }



    window.cleanUp();
    SDL_Quit();

    return 0;
}