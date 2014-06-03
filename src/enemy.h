class enemy
{

    private:

    int x0,y0;
    int x,y;
    int height,width;
    int rundistance;
    int xvelocity,yvelocity;
    int state; // 1-right ,2 left , 3 dead
    int en_id;

    SDL_Rect box;
	SDL_Surface * enemysu;

	SDL_Rect clipsRight[ 6];
	SDL_Rect clipsLeft[ 6];
    SDL_Rect clipsdead[1];

    int frame;
    int noofframes;

    public:

    enemy();
    ~enemy(){ SDL_FreeSurface( enemysu ); };

    void set_clips();

    void show();
    void die();
    SDL_Rect get_box();
    bool isdead();
    enemy(int x1,int y1, int typ ,int v1  ,int v2 );


};

   enemy::enemy(){}
void load_enemy(int x1,int y1);
