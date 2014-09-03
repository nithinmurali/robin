#include<iostream>
#include<sstream>
#include"config.cfg"

TTF_Font *font = NULL;
SDL_Color textColor = { 100, 255, 0 };


    bool toright;
    bool toleft;
    bool ontop;
    bool below;

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *coinsou = NULL;
Mix_Chunk *hitsou = NULL;
Mix_Chunk *jumpsou = NULL;
Mix_Chunk *diamoundsou = NULL;


int level =1;
bool first=0; // for intial vvelocity problem
bool robindead;

bool key_r=0;
bool key_l=0;


////////////////////////////////
using namespace std;

SDL_Event event;
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *welcome = NULL;
SDL_Surface *tileSheet = NULL;
SDL_Surface *gameover = NULL;
SDL_Surface *coin = NULL;
SDL_Surface *heart = NULL;
SDL_Surface *message = NULL;
SDL_Surface *game_won = NULL;
SDL_Surface *diamound = NULL;
SDL_Surface *prepare = NULL;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        /*if(filename =="res/diamound.png")
        {
             optimizedImage = loadedImage;
        }*/
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,SDL_SWSURFACE | SDL_DOUBLEBUF);

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "ROBIN", NULL );


    //If everything initialized fine
    return true;
}

bool load_files()
{

     tileSheet = load_image( "res/tiles.png" );
     coin = load_image("res/coin.png");
     diamound = load_image("res/diamound.png");
     heart = load_image("res/heart.png");

    //If there was a problem in loading the tiles
    if( tileSheet == NULL)
    {
        return false;
    }

    prepare = SDL_LoadBMP( "res/next.bmp" );
    background = SDL_LoadBMP( "res/bg.bmp" );
    gameover = SDL_LoadBMP("res/gameover.bmp");
    welcome = SDL_LoadBMP("res/welcome.bmp");
    game_won = SDL_LoadBMP("res/won.bmp");
    font = TTF_OpenFont( "res/Terminus.ttf", 15 );

    music = Mix_LoadMUS( "res/Egypt.mp3" );
    hitsou= Mix_LoadWAV( "res/hit.wav" );
     jumpsou = Mix_LoadWAV( "res/jump.wav" );
     diamoundsou = Mix_LoadWAV( "res/powerup.wav" );
     coinsou = Mix_LoadWAV( "res/coin.wav" );



    return true;
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool collision(SDL_Rect *a, SDL_Rect *b)
{
     if( a->x < b->x + b->w &&
         a->x + a->w > b->x &&
         a->y < b->y + b->h &&
         a->y + a->h > b->y )
     {
         return true;
     }
     else
     return false;
}

bool isCollision( SDL_Rect playerPos , SDL_Rect B,int a = 0,bool non_bounce=0)
{

        //coming from LEFT
        if((playerPos.x + playerPos.w ) >= B.x +1 //if front of player is greater than the front of the box
           && playerPos.x + playerPos.w <= B.x +30 //if front of player is less than the front of the box + 10 px
           &&playerPos.y<= B.y + B.h//if top of player is higher than bottom of box
           &&playerPos.y + playerPos.h >= B.y+5)//if bottom of player if lower than top of box)
        {

            offSet=B.x-robin_WIDTH;
          /*  std::cout<<"left col vals"<<((playerPos.x + playerPos.w ) >= B.x +1 )
                    <<(playerPos.x + playerPos.w <= B.x +20)
                    <<(playerPos.y<= B.y + B.h)
                    <<(playerPos.y + playerPos.h >= B.y+5)<<std::endl;*/
            toleft = true;
            return 1;
        }

        //coming from right
        if(playerPos.x +1 <= B.x + B.w //if front of player is less than back of the box
           && playerPos.x >= B.x + B.w -30 //if front of player is greater than back of the box - 10 px
           &&playerPos.y<=B.y + B.h//if top of player is higher than bottom of box
           &&playerPos.y + playerPos.h >= B.y +5)//if bottom of player is lower than top of the box
        {
           // std::cout<<(playerPos.x +1 <= B.x + B.w) << (playerPos.x >= B.x + B.w -10)<<(playerPos.y<=B.y + B.h)<<(playerPos.y + playerPos.h >= B.y +5)<<std::endl;
            offSet=B.x + B.w ;
            toright = true;
            return 1;
        }

        //checks if player is on top of something
        if(playerPos.x + playerPos.w -15>= B.x
           && playerPos.x + 30 <= B.x + B.w
           && playerPos.y + playerPos.h  >= B.y + a
           && playerPos.y + playerPos.h <= B.y + 50)
        {
       /*     cout<<"exp "<<(playerPos.x + playerPos.w >= B.x)
           <<( playerPos.x <= B.x + B.w)
           <<( playerPos.y + playerPos.h  >= B.y)
           <<( playerPos.y + playerPos.h <= B.y + 20)<<endl;*/

            ontop = 1;

            if(!non_bounce)
            {
                voffset = -1*(B.y - SCREEN_HEIGHT );
            }

            return 1;
        }

        //checks if player is below something
        if((playerPos.x + playerPos.w -15 >= B.x)
           && (playerPos.x+ 20  <= B.x + B.w)
           && (playerPos.y <= B.y + B.h)
           && (playerPos.y >= B.y + B.h - 60))
        {
            below = true;
            voffset = SCREEN_HEIGHT-( B.y+ B.h+ 60);
            return 1;

        }

return 0;

}

void handle_health(int val)
{
            health  += val;
            if(health <=0)
            {
                lives--;
                if(lives <=0)
                robindead=1;
            }
            else if(health > 100)
            health = 100;
}

void show_writing(int x,int y,char s[])
{

     message = TTF_RenderText_Solid( font, s, textColor );

    //Show the message on the screen
    apply_surface ( x, y, message, screen );

}

void showscore(int x = 30,int y=30)
{

char str[20] ="Score : 000000";
char liv[20]="lives = 00";

for(int i= score, j=8 + 6 ; i>0 ;i =i/ 10,j--)
{
        str[j]= i%10 +48;
}

show_writing(x,y,str);

for(int k= lives , j=9 ; k>0 ;k =k/ 10,j--)
{
        liv[j]= k%10 +48;
}
show_writing(x,y+20,liv);

}

void game_over()
{
    Mix_HaltMusic();

    SDL_BlitSurface( gameover, NULL, screen, NULL );
    SDL_Flip( screen );
    showscore(300,220);
    SDL_Delay( 4000 );
    quit =true;
}



void gamewon()
{
     Mix_HaltMusic();
     SDL_BlitSurface( game_won, NULL, screen, NULL );

     showscore(280,380);
    SDL_Flip( screen );
    SDL_Delay( 4000 );
    quit =true;

}
