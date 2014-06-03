
#include <fstream>

SDL_Rect clips[ TILE_SPRITES ];
SDL_Rect clipscoin[ 15 ];
SDL_Rect clipsdiamound[13];
SDL_Rect clipsheart[ TILE_SPRITES ];


class Tile
{
    private:
    //The attributes of the tile
    SDL_Rect box;

    //The tile type




    public:

        bool isanim;
        int frame;
        int frames;
        int collisionframe;
        bool collided;
        bool exausted;
        int type;
        bool isvisible;
    //Initializes the variables
    Tile( int x, int y, int tileType );

    //Shows the tile
    void show();

    //Get the tile type
    int get_type();

    //Get the collision box
    SDL_Rect get_box();
};


void clean_up( Tile *tiles[] )
{



    //Free the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];
    }

    //Quit SDL

}


void clip_tiles()
{

    int  num =0;

    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<row; j++,num++)
        {
            clips[ num ].x = TILE_WIDTH *i;
            clips[ num ].y = TILE_HEIGHT*j;
            clips[ num ].w = TILE_WIDTH;
            clips[ num ].h = TILE_HEIGHT;
        }
    }


    num=0;
    for(int i1=0;i1<coin_row;i1++)
    {
        for(int j1=0;j1<coin_col; j1++,num++)
        {
            clipscoin[ num ].x = TILE_WIDTH *j1;
            clipscoin[ num ].y = TILE_HEIGHT*i1;
            clipscoin[ num ].w = TILE_WIDTH;
            clipscoin[ num ].h = TILE_HEIGHT;
        }
    }

    num=0;
    for(int i1=0;i1<diamound_row;i1++)
    {
        for(int j1=0;j1<diamound_col; j1++,num++)
        {
            clipsdiamound[ num ].x = TILE_WIDTH *j1;
            clipsdiamound[ num ].y = 0;
            clipsdiamound[ num ].w = TILE_WIDTH;
            clipsdiamound[ num ].h = TILE_HEIGHT;
        }
    }


}

bool set_tiles( Tile *tiles[] )
{
    //The tile offsets
    int x = 0, y = 0;
std::ifstream map;
    //Open the map

    char levfile[20]="levels/robin";
    int i=13;

    if(level < 10)
    {
        levfile[12]=(level) +48 ;
    }else
    {
        levfile[13]=48+(level%10);
        levfile[12]=48+((level-level%10)/10);
        i++;
    }
        levfile[i] = '.';levfile[i+1] = 'm';
        levfile[i+2] = 'a';levfile[i+3] = 'p';

   map.open( levfile );


    if( map == NULL )
    {
        return false;
    }

    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {

        //Determines what kind of tile will be made
        int tileType = -1;

        //Read tile from map file
        map >> tileType;

        //cout<<tileType<<endl;

        //If the was a problem in reading the map
        if( map.fail() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            //cout<<"in tyile"<<endl;
            if(tileType==25)
            {   tiles[ t ] = new Tile( x, y, 0 );

                load_enemy(x,y,1);

            }
            else if(tileType==26)
            {
                tiles[ t ] = new Tile( x, y, 0 );
                 load_enemy(x,y,2);

            }
            else
            {
                tiles[ t ] = new Tile( x, y, tileType );
            }
        }
        //If we don't recognize the tile type
        else
        {
            //Stop loading map
            map.close();
            return false;
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return true;
}

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;

    isanim =0;
   // cout<<type;

    if(type == coin_type )
    {
        isanim =1;
        frames = coin_col*coin_row;
        frame =0;
        collided =0;
        exausted =0;
        collisionframe =11;
    }
    else if(type == diamound_type)
    {
         isanim =1;
        frames = diamound_col*diamound_row;
        frame =0;
        collided =0;
        exausted =0;
        collisionframe =12;
    }

}

void Tile::show()
{
    isvisible =0;
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        isvisible = 1;
        if(!isanim)
        {//Show the tile
           // cout<<"shown"<<endl;
            apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ type ] );

        }
        else
       {   if(type == coin_type)
             {//cout<<"innn"<<endl;
                 if(!collided)
                  {

                     apply_surface( box.x - camera.x, box.y - camera.y, coin, screen, &clipscoin[ frame] );
                     frame++;
                     if(frame>=collisionframe-1)
                     frame =0;
                 }else if(!exausted)
                 {
                     apply_surface( box.x - camera.x, box.y - camera.y, coin, screen, &clipscoin[ frame ] );
                     frame++;
                     if(frame>=frames)
                     exausted = 1;
                     type = blank;

                 }else
                 {
                      apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ blank ] );
                 }
            }
            if(type == diamound_type)
            {
                if(!collided)
                  {
                        //if(!diamound) cout<<"nillll";
                     apply_surface( box.x - camera.x, box.y - camera.y, diamound, screen, &clipsdiamound[ frame] );
                     //frame++;
                     //if(frame>= 12 -1 )
                     frame =0;
                 }else if(!exausted)
                 {

                     exausted = 1;
                     type = blank;

                 }else
                 {
                      apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clipsdiamound[ blank ] );
                 }
            }
        }
    }
}

int Tile::get_type()
{
    return type;
}

SDL_Rect Tile::get_box()
{

    return box;
}


bool hit_brick( SDL_Rect box, Tile *tiles[] )
{   bool t;

    ontop =0;
    below=0;
    toleft=0;
    toright=0;
    //std::cout<<"col val"<<ontop<<toleft<<toright<<below<<std::endl;
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {   if(tiles[t]->isvisible)
        {

                if( ( tiles[ t ]->get_type() >= 1 ) && ( tiles[ t ]->get_type() <= 15 ) ) //If the tile is a wall type tile
                {
                    //If the collision box touches the wall tile
                   if( isCollision( box, tiles[ t ]->get_box() ) )
                    {


                    }
                }
                else if( (tiles[ t ]->get_type() >= 20 ) && ( tiles[ t ]->get_type() <= 24 )) //////// intractive tile
                {
                        if( check_collision( box, tiles[ t ]->get_box() ) )
                        {
                            if(!coinsou)cout<<"null"<<endl;
                            //if(tiles[t]->isanim)
                            {
                                    if(tiles[ t ]->get_type()==22   )
                                    {
                                     //
                                      tiles[t]->frame =  tiles[t]->collisionframe;
                                      score += coin_score;
                                      tiles[t]->collided=1;
                                      tiles[t]->exausted=0;

                                    }else if(tiles[ t ]->get_type()==21)
                                    {
                                     //t= Mix_PlayChannel( -1, diamoundsou, 0 );
                                      tiles[t]->frame =  tiles[t]->collisionframe;
                                      score += diamound_score;
                                      lives++;
                                      tiles[t]->collided=1;
                                      tiles[t]->exausted=0;
                                    }
                                    else if(tiles[ t ]->get_type()==20) // spike
                                    {
                                        if(isCollision( box, tiles[ t ]->get_box(),45,1) && ontop == 1)
                                        {

                                         //t= Mix_PlayChannel( -1, hitsou, 0 );
                                                //uvelocity=0;
                                                robindead =1;

                                        }
                                    }
                                    else if(tiles[ t ]->get_type()==23 ||tiles[ t ]->get_type()==24)//door
                                    {
                                        cout<<"collide";
                                        if(level == no_of_levels)
                                        {
                                            levelwon = 1;
                                            gamewon();

                                        }
                                         else
                                        {
                                            levelwon=1;

                                            quit= 0;
                                        }


                                    }
                             }

                          }
                }
        }

    }
   // std::cout<<"col val"<<ontop<<toleft<<toright<<below<<std::endl;
   // cout<<"-------------------------------------------------"<<endl;

    if(toleft==1 || toright==1)
    return 1 ;
    else
    return 0;
}



