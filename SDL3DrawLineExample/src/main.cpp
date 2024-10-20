
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
/*
* Modified the code from using pen to mouse, to draw lines in the window
*/


/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *render_target = NULL;
static bool bMouseDown = false;
static float previous_touch_x = -1.0f;
static float previous_touch_y = -1.0f;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
    //std::cout<<"SDL_AppInit"<<std::endl;
    SDL_SetAppMetadata("Example Pen Drawing Lines", "1.0", "com.example.pen-drawing-lines");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/pen/drawing-lines", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* we make a render target so we can draw lines to it and not have to record and redraw every pen stroke each frame.
       Instead rendering a frame for us is a single texture draw. */
    render_target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
    if (!render_target) {
        SDL_Log("Couldn't create render target: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* just blank the render target to gray to start. */
    SDL_SetRenderTarget(renderer, render_target);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    //std::cout<<"SDL_AppEvent, event->type = "<< event->type <<std::endl;
    if (event->type == SDL_EVENT_QUIT) {
        std::cout<<"SDL_EVENT_QUIT"<<std::endl;
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        bMouseDown = true;
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        bMouseDown = false;
    }


    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        //std::cout<<"SDL_EVENT_MOUSE_MOTION"<<std::endl;
        if(bMouseDown){
            SDL_SetRenderTarget(renderer, render_target);
            SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 255);
            SDL_RenderLine(renderer, previous_touch_x, previous_touch_y, event->pmotion.x, event->pmotion.y);
        }

        previous_touch_x = event->pmotion.x;
        previous_touch_y = event->pmotion.y;
    } 

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate){
    //std::cout<<"SDL_AppIterate"<<std::endl;
    /* make sure we're drawing to the window and not the render target */
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);  /* just in case. */
    SDL_RenderTexture(renderer, render_target, NULL, NULL);
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result){
    std::cout<<"SDL_AppQuit"<<std::endl;
    SDL_DestroyTexture(render_target);
    /* SDL will clean up the window/renderer for us. */
}

/*
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[])
{
    SDL_Log("Hello, SDL3!");
    return 0;
}*/
