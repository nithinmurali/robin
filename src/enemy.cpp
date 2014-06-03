#include"enemy.h"

enemy *enemys[20];

int en_num=0;

enemy::enemy(int x1,int y1, int typ ,int v1 = 10 ,int v2= 0 )
{
    if(typ == 1)
    {
    enemysu = load_image( "res/enemy1.png" );

    height =64 ;
    width =93 ;

    }
    else
    {
    enemysu = load_image( "res/enemy2.png" );
    height =64 ;
    width =128 ;

    }

    //if(!enemysu)cout<<"null"<<endl;

    x0=x1;y0=y1;
    x=x0;y=y0;

    en_num++;
    frame = 0 ;
    noofframes = 5 ;
    rundistance = 200 ;
    xvelocity= v1 ;
    yvelocity= v2;
    en_id = en_num;
    state =1;

    box.x= x;
    box.y= y;
    box.w=width;
    box.h=height;
    set_clips();
    cout << "type"<<typ<< endl;
    //apply_surface( x, y, enemysu, screen, &clipsRight[ frame ] );
}

void enemy::set_clips()
{
    for(int j=0;j < noofframes ;j++)
	{
		clipsRight[ j ].x =(width)*j;
		clipsRight[ j ].y = 0;
		clipsRight[ j ].w = width;
		clipsRight[ j ].h = height;

		clipsLeft[ j ].x = (width) * j;
		clipsLeft[ j ].y = height*1;
		clipsLeft[ j ].w = width;
		clipsLeft[ j ].h = height;

  cout<<clipsRight[j].x<<" "<<clipsRight[j].y<<endl;

        //////////////////////add new clips here///////////
    }
     /*   clipsdead[ 0 ].x = (width) * 3;
		clipsdead[ 0 ].y = height*2;
		clipsdead[ 0 ].w = width;
		clipsdead[ 0 ].h = height;
*/

}


void load_enemy(int x1,int y1,int typ)
{
    enemys[en_num] = new enemy(x1,y1,typ,10,0);


}

void enemy::show()
{//&& check_collision( camera, box ) == true
    if(state != 3 )
    {
        x+=xvelocity;
        y+=yvelocity;
        box.x = x;
        box.y = y;

        if(state == 1)
        {   //cout<<"applied "<<endl;
            apply_surface( box.x -camera.x, box.y - camera.y +4, enemysu, screen, &clipsRight[ frame ] );
                frame++;
        }
        else if(state == 2)
        {
            apply_surface( box.x- camera.x, box.y - camera.y+4, enemysu, screen, &clipsLeft[ frame ] );
            frame++;
        }

        if(frame > noofframes)
        {
            frame =0;

       }
       /* else if(frame > 2* noofframes && state == 2)
        {
            frame = noofframes+1;
        }*/

        if( x >= rundistance + x0 || x <= x0)
        {
            if(state==1)
            state =2;
            else if(state==2)
            state =1;

            xvelocity = -xvelocity;
            yvelocity = -yvelocity;
       }


//cout<<state<<endl;
    }


}

void enemy::die()
{
    state=3;
    delete enemys[en_id];
    SDL_FreeSurface( enemysu );
    en_num--;

}

SDL_Rect enemy::get_box()
{

    return box;
}


bool enemy::isdead()
{
    if(state == 3)
    return 1;
    else
    return 0;

}

