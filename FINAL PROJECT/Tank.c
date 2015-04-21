// Here  we include our main header file. This header file contains all necessary structure 
// definitions and function prototype require for our game along with other important header
//file

#include "Game.h"

//**************************************************************************************************

//-------------------------------------GLOBAL VAIRABLES---------------------------------------------

//**************************************************************************************************
//IMAGES USED IN THE GAME
SDL_Surface *screen = NULL;                                            //Main screen
SDL_Surface *seal_exp_image = NULL;                              //Images of seal explosion;
SDL_Surface *background= NULL;                                         //Background image
SDL_Surface *wall_image = NULL;                                        //Image of the wall
SDL_Surface *brick_image= NULL;                                        //Image of the bricks
SDL_Surface *player_image[5][5]={{NULL,NULL,NULL,NULL,NULL},           //Player Images set
                                 {NULL,NULL,NULL,NULL,NULL},
                                 {NULL,NULL,NULL,NULL,NULL},
                                 {NULL,NULL,NULL,NULL,NULL},
                                 {NULL,NULL,NULL,NULL,NULL}};

SDL_Surface *bullet_image = NULL;                                      //Image of the bullet     
SDL_Surface *explode = NULL;                                           //Images of the explosion
SDL_Surface *seal_image[3] = {NULL,NULL,NULL};                         //Images of player seals
SDL_Surface *cracking = NULL;                                          //Images of wall cracking
SDL_Surface *enemy_image[4] = { NULL,NULL,NULL,NULL};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// JOYSTICKS USED IN THE GAME

SDL_Joystick *player3_stick = NULL;                                    //PLAYER 3 Joystick control
int player3_active = false;

SDL_Joystick *player4_stick = NULL;                                    //PLAYER 3 Joystick control
int player4_active = false;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//MUSIC AND SOUND EFFECTS USED IN THE GAME

Mix_Music *background_music = NULL;                                   //Main background music
Mix_Chunk *click_sound = NULL;                                        //Sound for mouse clicking
Mix_Chunk *wall_explode = NULL;                                       //Sound for wall explosion
Mix_Chunk *button_over_sound = NULL;
Mix_Chunk *bullet_fire_sound = NULL;
Mix_Chunk *seal_explosion_sound = NULL;
Mix_Chunk *player_killed_sound = NULL;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//FONTS USED IN THE PROGRAM

TTF_Font *large_font = NULL;                                        //Large type font
TTF_Font *small_font = NULL;                                        //Small type font

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//SOME MORE VARIABLE USED IN THE GAME

int team_score[3] = {0,0,0};                                      //Variable to store team scores
SCORES score[12];
SDL_Event event;                                                    //A SDL Event handler

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//MAIN VARIABLES OF THE GAME

CELL cell[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];                //Basic cell structure
CELL wall[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];                //Wall structure
CELL brick[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];               //Brick structure
CELL seal[3];                                                             //Seals structure
BULLET bullet[5];                                                          //Bullet structure         
PLAYER player[5];                                                          //Player structure
ENEMYY enemy[5];

EXPLOSION_SLOT explosion_slot[TOTAL_NO_SLOT];                              //Slots for playing
                                                                           //Explosion animation             

SDL_Rect explosion[9];                                                     //Explosion animation clip
SDL_Rect explosion_player[9];                                              //Explosion clip for player 
SDL_Rect crack[2];                                                         //Cracking image clip
SDL_Rect seal_explosion_clip[9];                                           //Seal explosion clips 

int game_quit=false;                                                        //Main loop variable
int sound = true;                                        //Variable to enable or diasble sound
int current_level = 1;                                   //Indicated current Level of the game

FILE *game_log;                                           //A file to keep the log for the game

//**************************************************************************************************

int PLAYER_SPEED;
int BULLET_SPEED;
int GAME_SPEED;

//------------------------------------------ERROR HANDLER-------------------------------------------

//**************************************************************************************************

/*                   This function handles any error that occured during the
                     execution of the program and prints the error message to
                     the file and exits with error
                                                                                                  */                                                                                     
void packUP()
{
    int i;
    Mix_HaltMusic();
    
    for(i=0;i<5;++i)
    {
         player[i].isActive = false;
         bullet[i].isActive = false;
         enemy[i].my_bullet.isActive = false;
         enemy[i].isActive = false;
    }    
    clean_cells();
    
    unload_images();
    unload_font();
    unload_sound();
    SDL_JoystickClose(player3_stick);
    SDL_JoystickClose(player4_stick);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    fclose(game_log);

}
int error(char a[])
{
    int i=0;
    fprintf(game_log,"\nERROR: %s",a);
    packUP();
    exit(1);
}

//**************************************************************************************************

//--------------------------------------MAIN FUNCTION-----------------------------------------------

//**************************************************************************************************

int main(int args, char *argc[])
{
    //Game variables
    int i=0;
    int game_pause = false;                 //Variable to toggle play and pause of the game
    
    Sint16 p3_x_move,p3_y_move;             //Variable to handle x and y movement of player 3
    Uint8 player3_fire;                     //Variable to detect fire button press of player 3
    
    Sint16 p4_x_move,p4_y_move;             //Variable to handle x and y movement of player 4
    Uint8 player4_fire;                     //Variable to detect fire button press of player 4

    CELL temp_cell;                         //A temporary CELL structure used in program
    int row, col;                           //Temporary integer variables
    
    Uint8 *keys;                            //Variable to store keyboard map
    FILE *speed_file;                       //GAME SPEED information is stored in this file
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    game_log = fopen("log.txt","w");        //Open the log file
    if(game_log == NULL )return -1;         //Detect error opening the file
    gameLog("Main function started...");
    
    speed_file = fopen("speed.txt","r");
    if(speed_file !=NULL)
    {
        fscanf(speed_file,"%d %d %d",&PLAYER_SPEED,&BULLET_SPEED,&GAME_SPEED);
    }
    else
    {
        PLAYER_SPEED = 1;
        BULLET_SPEED = 2;
        GAME_SPEED = 5;
    }
    fclose(speed_file);
    gameLog("Game speed information read from the file...");
    
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //INITIALIZATION
    
    //Initialize the SDL package with all its feature 
    //Features include : Video Window Manager Event Handling Joystick Audio
    //CDROM Threads Timers
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
       error("Unable to initialize SDL package");
    
    //Initialize SDL font package
    if(TTF_Init() == -1 )
       error("Unable to initialize Font packeage");
    
    //Initialize SDL music package
    if(Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
       error("Unable to initialize SDL_Mixer");
    
    //Detect any joystick connected
    if(SDL_NumJoysticks()> 0)
    {
        //Assign the first joystick to player 3
        player3_stick = SDL_JoystickOpen(0);
    
        //If no joystick found, than disable player 3
        if(player3_stick == NULL)
        {
            player3_active = false;
            player[3].isActive = false;
        }
        else
        {
            player3_active = true;
            player[3].isActive = true;
        }
    
        //Assign the first joystick to player 3
        player4_stick = SDL_JoystickOpen(1);
    
    //If no joystick found, than disable player 3
        if(player4_stick == NULL)
        {
            player4_active = false;
            player[4].isActive = false;
        }
        else
        {
            player4_active = true;
            player[4].isActive = true;
        }
        gameLog("Joysticks found and connected...");
    }
    else gameLog("No joysticks found...");

    
    //Initialize the main screen window of the game     
    screen = SDL_SetVideoMode(GAME_SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BBP,SDL_DOUBLEBUF | SDL_HWSURFACE);
    if(screen==NULL)
       error("Unable to initialize SDL video mode"); 
    
    
    //set the window caption
    SDL_WM_SetCaption("Tank",NULL);    
    
    //Initialize the cell structure of the game
    init_cells();
    
    //Load the images from file to the game
    if(load_image() == -1 )
       error(strcat("Unable to Load Images \" %s \"",SDL_GetError()));
    
    //Load sounds from file to game
    if(load_sound() == -1 ) 
       error(strcat("Unable to load sounds \" %s \"",SDL_GetError()));
   
   //Load fonts from file to game
    if(load_font() == -1 )
        error(strcat("Unable to load fonts \" %s \"",SDL_GetError()));
            
    //Analaze all loaded images to current display format of the game
    analyze_images();
    
    //reset_scores();
    
    //Read score information from the file
    read_score();
    
    //Call the main welcome screen
    if(welcome_main()<0){
       gameLog("Game exited from the welcome screen."); 
       game_quit = true;
    }
    else
    {
        //Load current level
        load_object_once();
        new_level(current_level);
    }

    //Master Loop of the game
    while(game_quit==false)
    {
        
        
           //get the current event information                
           while(SDL_PollEvent(&event))
           {
                  switch(event.type)
                  {
                        case SDL_QUIT:
                             game_quit=true;
                             break;
                  
                        case SDL_KEYDOWN:
                            
                            switch(event.key.keysym.sym)
                            {
                               case SDLK_x:
                                    game_over();
                                   //  game_quit = true;
                                     break;
                                
                               case SDLK_p:
                                     game_pause = true;
                                     break;
                        
                               case SDLK_1:
                                    if(Mix_PlayingMusic() == 0)
                                    {
                                            sound = true;
                                            Mix_PlayMusic(background_music,-1);
                                    }
                                    else
                                    {
                                        if(Mix_PausedMusic() == 1)
                                        {
                                                sound = true;
                                                Mix_ResumeMusic();
                                        }
                                        else
                                        {
                                                sound = false;
                                                Mix_PauseMusic();
                                        }
                                    }
                                    break;

                                case SDLK_0:
                                    Mix_HaltMusic();
                                    break;
                           }
                    }        
            }

           //get the current keyboard map
           keys = SDL_GetKeyState(NULL);

         // A pause play loop
         while(game_pause)
         {
              SDL_PollEvent(&event);
              if(event.type == SDL_KEYDOWN)
              {
                   if(event.key.keysym.sym == SDLK_r) game_pause = false;
               }
         }                               
         
         ///////////////////////////////////////////////////////////////////////////////////////////
         // PLAYER 1 movements  
         if(player[1].isActive)
         {
           if ( keys[SDLK_UP] ) 
           {
                move_player(&player[1],UP);
           }
           else if ( keys[SDLK_DOWN] )
           {
                move_player(&player[1],DOWN);
           }
           else if ( keys[SDLK_LEFT] )
           {
                move_player(&player[1],LEFT);
           }
           else if ( keys[SDLK_RIGHT] )
           {
                move_player(&player[1],RIGHT);
           }
           if(keys[SDLK_l])
           {
                if(bullet[1].isActive==false)
                {
                        if(sound)Mix_PlayChannel(-1,bullet_fire_sound,0);
                         activate_bullet(&bullet[1], player[1]);                                 
                }                             
           }
        }
           
                           
         ///////////////////////////////////////////////////////////////////////////////////////////
         // PLAYER 2 movements
        if(player[2].isActive)
        {
           if ( keys[SDLK_w] ) 
           {
                move_player(&player[2],UP);
           }
           else if ( keys[SDLK_s] ) 
           {
                move_player(&player[2],DOWN);
           }
           else if ( keys[SDLK_a] ) 
           {
                move_player(&player[2],LEFT);
           }
           else if ( keys[SDLK_d] ) 
           {
                move_player(&player[2],RIGHT);
           }
           if(keys[SDLK_f])
           {
                if(bullet[2].isActive==false)
                {
                        if(sound)Mix_PlayChannel(-1,bullet_fire_sound,0);
                         activate_bullet(&bullet[2], player[2]);                                 
                }                             
           }

        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////
        // PLAYER 3 movements
        if(player[3].isActive)
        {
        p3_x_move = SDL_JoystickGetAxis(player3_stick,0);
        p3_y_move = SDL_JoystickGetAxis(player3_stick,1);
        player3_fire = SDL_JoystickGetButton(player3_stick,1);

        if(player3_fire)
        {
             //Check to see if the bullet is already active or not
             if(bullet[3].isActive==false)
             {
                   if(sound)Mix_PlayChannel(-1,bullet_fire_sound,0);
                   activate_bullet(&bullet[3], player[3]);
             }                             
        }

        if((p3_x_move < -8000) || (p3_x_move > 8000))
        {
                  if(p3_x_move<0)
                  {
                      move_player(&player[3],LEFT);
                  }
                  else
                  {
                      move_player(&player[3],RIGHT);
                  }
         }   
        else if((p3_y_move < -8000) || (p3_y_move > 8000))
        {
                 if(p3_y_move<0)
                 {
                      move_player(&player[3],UP);
                 }
                 else
                 {
                      move_player(&player[3],DOWN);
                 }
        }
        }

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
        // PLAYER 4 movements
        if(player[4].isActive)
        {
        p4_x_move = SDL_JoystickGetAxis(player4_stick,0);
        p4_y_move = SDL_JoystickGetAxis(player4_stick,1);
        player4_fire = SDL_JoystickGetButton(player4_stick,1);

        if(player4_fire)
        {
             //Check to see if the bullet is already active or not
             if(bullet[4].isActive==false)
             {
                   if(sound)Mix_PlayChannel(-1,bullet_fire_sound,0);
                   activate_bullet(&bullet[4], player[4]);
             }                             
        }

        if((p4_x_move < -8000) || (p4_x_move > 8000))
        {
                  if(p4_x_move<0)
                  {
                      move_player(&player[4],LEFT);
                  }
                  else
                  {
                      move_player(&player[4],RIGHT);
                  }
         }   
        else if((p4_y_move < -8000) || (p4_y_move > 8000))
        {
                 if(p4_y_move<0)
                 {
                      move_player(&player[4],UP);
                 }
                 else
                 {
                      move_player(&player[4],DOWN);
                 }
        }
        }

///////////////////////////////////////////////////////////////////////////////////////////////
    for(i=0;i<5;++i) if(enemy[i].isActive) operate_enemy(&enemy[i]);

////////////////////////////////////////////////////////////////////////////////////////////////  
    //This snippet move the bullet if it is active
    if(bullet[1].isActive)
    {
        move_bullet(&bullet[1]);
        if(collision(bullet[1].dimension,player[2].dimension) == true)
        {
            if(player[2].isActive){
            bullet[1].isActive = false;
            clear_image(bullet[1].dimension);
            bullet[1].dimension.x = 1300;
            bullet[1].dimension.y = 0;
            player_killed(&player[2]);}
            
        }
        else if(collision(bullet[1].dimension,player[3].dimension) == true)
        {
            if(player[3].isActive){
            bullet[1].isActive = false;
            clear_image(bullet[1].dimension);
            bullet[1].dimension.x = 1300;
            bullet[1].dimension.y = 0;
            player_killed(&player[3]);}
            
        }
    }
            
    if(bullet[2].isActive)
    {
        move_bullet(&bullet[2]);        
        if(collision(bullet[2].dimension,player[1].dimension) == true)
        {
            if(player[1].isActive){
            bullet[2].isActive = false;
            clear_image(bullet[2].dimension);
            bullet[2].dimension.x = 1300;
            bullet[2].dimension.y = 0;
            player_killed(&player[1]);}
            
        }
        if(collision(bullet[2].dimension,player[4].dimension) == true)
        {
            if(player[4].isActive){
            bullet[2].isActive = false;
            clear_image(bullet[2].dimension);
            bullet[2].dimension.x = 1300;
            bullet[2].dimension.y = 0;
            player_killed(&player[4]);}
            
        }
 
    }
////////////////////////////////////////////////////////////////////////////////////////////////
    if(bullet[3].isActive)
    {
        move_bullet(&bullet[3]);
        
        if(collision(bullet[3].dimension,player[1].dimension) == true)
        {
            if(player[1].isActive){
            bullet[3].isActive = false;
            clear_image(bullet[3].dimension);
            bullet[3].dimension.x = 1300;
            bullet[3].dimension.y = 0;
            player_killed(&player[1]);}
            
        }
        if(collision(bullet[3].dimension,player[4].dimension) == true)
        {
            if(player[4].isActive){
            bullet[3].isActive = false;
            clear_image(bullet[3].dimension);
            bullet[3].dimension.x = 1300;
            bullet[3].dimension.y = 0;
            player_killed(&player[4]);}
            
        }

 
    }
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    if(bullet[4].isActive)
    {
        move_bullet(&bullet[4]);
        
        if(collision(bullet[4].dimension,player[2].dimension) == true)
        {
            if(player[2].isActive){
            bullet[4].isActive = false;
            clear_image(bullet[4].dimension);
            bullet[4].dimension.x = 1300;
            bullet[4].dimension.y = 0;
            player_killed(&player[2]);}
            
        }
        if(collision(bullet[4].dimension,player[3].dimension) == true)
        {
            if(player[3].isActive){
            bullet[4].isActive = false;
            clear_image(bullet[4].dimension);
            bullet[4].dimension.x = 1300;
            bullet[4].dimension.y = 0;
            player_killed(&player[3]);}
            
        }

 
    }
///////////////////////////////////////////////////////////////////////////////////////////////
    for(i=0;i<10;++i)
    {
        if(explosion_slot[i].isActive)
        {
            draw_image(explode,screen,&explosion[explosion_slot[i].count],explosion_slot[i].location.x,explosion_slot[i].location.y);
            explosion_slot[i].count++;
            if(explosion_slot[i].count>9){ 
            clear_image(explosion_slot[i].location);deactivate_slot(i);}
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////          
////////////////////////////////////////////////////////////////////////////////////////////////////
    if(player[1].isActive)draw_image(player_image[1][player[1].Direction],screen,NULL,player[1].dimension.x,player[1].dimension.y);
    if(player[2].isActive)draw_image(player_image[2][player[2].Direction],screen,NULL,player[2].dimension.x,player[2].dimension.y);
    if(player[3].isActive)draw_image(player_image[3][player[3].Direction],screen,NULL,player[3].dimension.x,player[3].dimension.y);
    if(player[4].isActive)draw_image(player_image[4][player[4].Direction],screen,NULL,player[4].dimension.x,player[4].dimension.y);                  
           SDL_Flip(screen); 
           SDL_Delay(GAME_SPEED); 
           
    }
    
    packUP();
    gameLog("Exit from main...");    
    return 0;  //exit
                                             
}


void play_explosion(int x, int y)
{
     int slot_no;
     
     slot_no = get_active_slot();
     
     activate_slot(slot_no,x,y);
     
}
void play_explosion_player(int x, int y,int player_no)
{
     int i,j;
     for(i=0;i<9;++i)
     {
            
         for(j=1;j<5;++j)
         {
            if( j != player_no )
            {
                if(player[j].isActive)draw_image(player_image[j][player[j].Direction ],screen,NULL,player[j].dimension.x,player[j].dimension.y);
            }
         }
         
         draw_image(explode,screen,&explosion_player[i],x,y);
         SDL_Flip(screen);
         SDL_Delay(20);
         
     }
}

void gameLog(char *message)
{
    static int count =0;
    ++count;
    fprintf(game_log,"\n%d. %s",count,message);
}
