#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include"timer.h"
#include"robin.cpp"

int main( int argc, char* args[] )
{

    quit = 0;
    Tile *tiles[ TOTAL_TILES ];

    Timer fps;    levelwon = 0;

     //Initialize
        if( init() == false )
        {
            return 1;
        }

        if( TTF_Init() == -1 )
        {
            return false;
        }


        //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            return false;
        }

 //Load the files
        if( load_files() == false )
        {
            return 1;
        }

        //Clip the tile sheeti
        if( Mix_PlayMusic( music, -1 ) == -1 ) { return 1; }

        clip_tiles();

        if(!welcome)return 1;
        SDL_BlitSurface(welcome, NULL, screen, NULL );
        SDL_Flip( screen );
        SDL_Delay(6000);

        robin robinp;

    while(quit ==false)
    {

        if(level!= 1)
        {
            SDL_BlitSurface( prepare, NULL, screen, NULL );
            SDL_Flip(screen);
            SDL_Delay(3000);
        }

        robinp.reset();

        //Set the tiles
        if( set_tiles( tiles ) == false )
        {
            return 1;
        }
       // SDL_Delay(3000);
        first=1;
    /////////////////////////////////////////////////////////////////////////////////////
        while( quit == false && levelwon == 0)///////////////////////////////////
        {

            //Start the frame timer
            fps.start();

            //While there's events to handle
            while( SDL_PollEvent( &event ) )
            {

              robinp.handle_events();


                //If the user has Xed out the window
                if( event.type == SDL_QUIT )
                {
                    //Quit the program
                    quit = true;
                }
            }

            SDL_BlitSurface( background, NULL, screen, NULL );


            robinp.move(tiles);
            robinp.set_camera();

         for( int t = 0; t < TOTAL_TILES; t++ )
            {
                tiles[ t ]->show();
            }


        for(int i=0;i< en_num;i++)
        {
            enemys[en_num]->show();        //robinp.reset();
        }


            robinp.show();
            showscore();

            //Update the screen
            if( SDL_Flip( screen ) == -1 )
            {
                return 1;
            }

            //Cap the frame rate
            if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            {
                SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
            }


        }

        clean_up(tiles);
        level++;
        levelwon = 0;
    /////////////////////////////////////////////////////////////////////////////////////
        //cout<<"out of level";
    }


        SDL_FreeSurface( background );
        SDL_FreeSurface( gameover );
         SDL_FreeSurface( tileSheet );

        //Free the music
        Mix_FreeMusic( music );
        Mix_FreeChunk( jumpsou );
        Mix_FreeChunk( coinsou );
        Mix_FreeChunk( hitsou );
        Mix_FreeChunk( diamoundsou );

        //Close the font
        TTF_CloseFont( font );

        //Quit SDL_mixer
        Mix_CloseAudio();
          SDL_Quit();
        //Quit SDL_ttf
        TTF_Quit();

    return 0;

    }
