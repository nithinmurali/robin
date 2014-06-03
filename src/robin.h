#pragma once

#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"init.h"
#include"enemy.cpp"
#include"tile.cpp"


const int robin_RIGHT = 0;
const int robin_LEFT = 1;

 const int nooffrms = 8;
 const int jvelocity = 50;
 const int vterm =15;




class robin
{
  private:



    int velocity;
    int uvelocity;
    int frame;
    int status;
	int jtime;
    bool robin_Jump;


	SDL_Surface * robins;

	SDL_Rect clipsRight[ 8];
	SDL_Rect clipsLeft[ 8];
    SDL_Rect clipsjump[8];
    SDL_Rect clipsjumpl[8];
    SDL_Rect clipsdead[8];




  public:

        SDL_Rect robincb;

     robin();
    ~robin(){ SDL_FreeSurface( robins ); };


    void set_clips();
    void set_camera();


    void handle_events();

    void move( Tile *tiles[] );
    void die();

    void show();
    void reset();
};




