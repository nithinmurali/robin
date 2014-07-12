#include"robin.h"


robin::robin()
{
	robins = load_image( "res/robin.png" );


    //Initialize movement variables
    offSet = 0;
    voffset= 80;
    uvelocity = 0;
    velocity =0;
    robin_Jump = 0;
    robindead = 0;


    //Initialize animation variables
    frame = 0;
    status = robin_RIGHT;

    //collisionbox
    robincb.x= offSet;
    robincb.y= voffset;
    robincb.w=robin_WIDTH ;
    robincb.h=robin_HEIGHT;

    set_clips();
}


void robin::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity += robin_WIDTH / 4; key_r=1;frame++;break;
            case SDLK_LEFT: velocity -= robin_WIDTH / 4;key_l = 1;frame++;break;
            case SDLK_UP: {
                                if(! robin_Jump)
                                {robin_Jump=1;
                                bool t= Mix_PlayChannel( -1, jumpsou, 0 );
                                 uvelocity = jvelocity;
                                frame=2;
                                break;
                                }
                           }
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
           case SDLK_RIGHT: velocity -= robin_WIDTH / 4 ;key_r=0; break;
           case SDLK_LEFT: velocity += robin_WIDTH / 4;key_l = 0; break;
           case SDLK_q:robindead=1;break;
        }
    }

    if(!key_l && !key_r) velocity=0;

}

void robin::move(Tile *tiles[])
{
    //Move
    offSet += velocity;


    if( ( offSet < 0 ) || ( offSet + robin_WIDTH > LEVEL_WIDTH ) || hit_brick(robincb,tiles)   )
    { if(!hit_brick(robincb,tiles))
        {offSet -= velocity;}

    }

if(robin_Jump)
{
    if(ontop == true && uvelocity < 0)
    {
      uvelocity=0;
      robin_Jump=false;

    }
    else
    {
        if(-uvelocity >= vterm)
        {uvelocity = -vterm;}
        else
        {uvelocity  -= g;

        }
    }

    if(below || voffset>LEVEL_HEIGHT)
    {
      uvelocity = - vterm;;
    }

    if(voffset - robin_HEIGHT < -80 && !robindead)
   {
        uvelocity = 0;
        robindead = 1;
        first =1;

    }
    //if(robindead)uvelocity=0;

}
    if(!ontop)
    robin_Jump=1;

    voffset+=uvelocity;

    ////////////////////////////// extra collision code here ///////////////////////////////
        for(int i=0;i<en_num;i++)
        {  if(enemys[i])
            {

                if(isCollision(robincb,enemys[i]->get_box()))
                {  // cout<<"collid"<<endl;
                    if(toleft || toright)
                    { // bool t= Mix_PlayChannel( -1, hitsou, 0 );
                        SDL_Delay(100);
                        handle_health(-20);
                       // robindead=1;


                    }
                    else if(ontop)
                    {  // bool t= Mix_PlayChannel( -1, diamoundsou, 0 );
                        enemys[i]->die();
                        score += 100;
                    }

                }
            }
        }



    ////////////////////////////////////////////////////////////////

    //move collision box
    robincb.x=offSet ;
    robincb.y=SCREEN_HEIGHT - robin_HEIGHT -voffset ;



}

void robin::show()
{

    if(!robindead)
              //If robin is moving left
    {

          if( velocity < 0 )
            {
                //Set the animation to left
                status = robin_LEFT;

                //Move to the next frame in the animation
                frame++;
            }
            //If robin is moving right
            else if( velocity > 0 )
            {
                //Set the animation to right
                status = robin_RIGHT;

                //Move to the next frame in the animation
                frame++;
            }
            //If robin standing
            else if(! robin_Jump)
            {
                //Restart the animation
                frame = 0;
            }

            if(!robin_Jump)

            {

            //Loop the animation
            if( frame >= nooffrms -1)
            {
                frame = 0;
            }

            //Show the stick figure
            if( status == robin_RIGHT )
            {  // std::cout<<"robincb.x"<<robincb.x<<" camera.x"<< camera.x<<std::endl;
                apply_surface( offSet - camera.x, SCREEN_HEIGHT - robin_HEIGHT -voffset-camera.y , robins , screen, &clipsRight[ frame ] );
            }
            else if( status == robin_LEFT )
            {  // std::cout<<"robincb.x "<<robincb.x<<" camera.x"<< camera.x<<std::endl;
                apply_surface( offSet - camera.x  , SCREEN_HEIGHT - robin_HEIGHT -voffset - camera.y , robins, screen, &clipsLeft[ frame ] );
            }
           }
           else
           {
          //frame++;

            //if( frame >= 4)
            {
                frame = 0;
            }
                 if( status == robin_RIGHT )
                {   //cout<<"uvel"<<uvelocity<<"voffset"<<voffset<<endl;
                    apply_surface( offSet - camera.x, SCREEN_HEIGHT - robin_HEIGHT -voffset - camera.y, robins , screen, &clipsjump[ frame ] );
                }
                else if( status == robin_LEFT )
                {
                    apply_surface( offSet-camera.x, SCREEN_HEIGHT - robin_HEIGHT -voffset -camera.y , robins, screen, &clipsjumpl[ frame ] );
                }
       }


    }
    else

    {       uvelocity =0;
            velocity = 0;
            apply_surface( offSet - camera.x  , SCREEN_HEIGHT - robin_HEIGHT -voffset - camera.y , robins, screen, &clipsdead[  frame] );

       //code for robin dead ... play anim
       if( frame >= 6)
            {   lives--;
                if(lives<=0)
                {
                    game_over(); // if anim over show gameover screen
                }
                else
                { frame = 5;
                  first = 1;
                  reset();
                }
            }
             else frame++;

             cout<<frame <<"frmz";
       // apply_surface( offSet - camera.x, SCREEN_HEIGHT - robin_HEIGHT -voffset - camera.y, robins , screen, &clipsdead[ frame ] );
    }

}

void robin::set_clips()
{
    int jl=30;
	for(int i=0;i<nooffrms;i++)
	{

        clipsRight[ i ].x =(robin_WIDTH)*i;
		clipsRight[ i ].y = 0;
		clipsRight[ i ].w = robin_WIDTH;
		clipsRight[ i ].h = robin_HEIGHT;

		clipsLeft[ i ].x = (robin_WIDTH) * i;
		clipsLeft[ i ].y = robin_HEIGHT*1;
		clipsLeft[ i ].w = robin_WIDTH;
		clipsLeft[ i ].h = robin_HEIGHT;

		clipsjump[ i ].x = (robin_WIDTH) * i;
		clipsjump[ i ].y = (robin_HEIGHT)*2;
		clipsjump[ i ].w = robin_WIDTH;
		clipsjump[ i ].h = robin_HEIGHT;

		clipsjumpl[ i ].x = (robin_WIDTH) * i ;
		clipsjumpl[ i ].y = (robin_HEIGHT)*3;
		clipsjumpl[ i ].w = robin_WIDTH;
		clipsjumpl[ i ].h = robin_HEIGHT;



        clipsdead[ i ].x = (robin_WIDTH) * i ;
		clipsdead[ i ].y = (robin_HEIGHT)*4 ;
		clipsdead[ i ].w = robin_WIDTH;
		clipsdead[ i ].h = robin_HEIGHT;


        //////////////////////add new clips here///////////

	}
}

void robin::set_camera()
{
    //Center the camera over the robin
    camera.x = ( offSet + robin_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    //camera.y = ( robincb.y + robin_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
    camera.y=0;
    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void robin::die()
{
    uvelocity =0;
    velocity=0;
    robindead = true;
    frame=0;

}

void robin::reset()
{
     offSet = 0;
    voffset= 80;
    uvelocity = 0;
    velocity =0;
    robin_Jump = 0;
    robindead = 0;


    //Initialize animation variables
    frame = 0;
    status = robin_RIGHT;

    //collisionbox
    robincb.x= offSet;
    robincb.y= voffset;
    robincb.w=robin_WIDTH ;
    robincb.h=robin_HEIGHT;

}

