//**************************************************************************************************
//-------------------------------------GLOBAL VAIRABLES---------------------------------------------
//**************************************************************************************************
//`````````````````````````````````````````IMAGES```````````````````````````````````````````````````
extern SDL_Surface *screen;                                 //Main screen
extern SDL_Surface *seal_exp_image;                         //Exlosion sequence image of the seal
extern SDL_Surface *background;                             //Background image
extern SDL_Surface *wall_image;                             //Image of the wall
extern SDL_Surface *brick_image;                            //Image of the bricks
extern SDL_Surface *player_image[5][5];                     //images of player 1

extern SDL_Surface *bullet_image;                           //image of the bullet     
extern SDL_Surface *explode;                                //Images of the explosion
extern SDL_Surface *seal_image[3];                          //Player 1 seal image
extern SDL_Surface *cracking;                               //Carcking sequence image
extern SDL_Surface *enemy_image[4];                         //Images of enemy in different direction

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//``````````````````````````````````````````SOUNDS``````````````````````````````````````````````````
extern Mix_Music *background_music;                         //background score music
extern Mix_Chunk *click_sound;                              //clicking sound
extern Mix_Chunk *wall_explode;                             //wall explosion sound
extern Mix_Chunk *button_over_sound;                        //button over sound
extern Mix_Chunk *bullet_fire_sound;                        //bullet fire sound
extern Mix_Chunk *seal_explosion_sound;                     //explosion sound for seal
extern Mix_Chunk *player_killed_sound;                      //player killed sound
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//``````````````````````````````````````````EVENT```````````````````````````````````````````````````
extern SDL_Event event;                                     //Event handler

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//```````````````````````````````````````GAME PLAY VARIABLES````````````````````````````````````````
extern CELL cell[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];           //Basic cell structure
extern CELL wall[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];           //Wall structure
extern CELL brick[SCREEN_HEIGHT/CELL_SIZE][SCREEN_WIDTH/CELL_SIZE];          //Brick structure
extern CELL seal[3];                                                         //Seals structure
extern BULLET bullet[5];                                                     //Bullet structure         
extern PLAYER player[5];                                                     //Player structure
extern ENEMYY enemy[5];                                                      //Enemy structure
extern SDL_Rect explosion[9];                                                //Animation clipping
extern SDL_Rect explosion_player[9];                                         //Explosion clip for player 
extern SDL_Rect seal_explosion_clip[9];                                      //Explosion clips strucure
extern SDL_Rect crack[2];                                                    //Cracking clip structure

extern int game_quit;                                                   //Decides the game play
extern int sound;                                                       //To enable and disable sound
extern int current_level;                                               //Stores current level no

////////////////////////////////////////////////////////////////////////////////////////////////

extern int team_score[3];                                     //Stores scores of each team
extern SCORES score[11];                                      //Array to hold top 10 scores and one is temporary
/////////////////////////////////////////////////////////////////////////////////////////////
extern EXPLOSION_SLOT explosion_slot[TOTAL_NO_SLOT];            //Explosion slots

//Players through joysticks
extern int player3_active;                                     //Determine the activeness of player 3
extern int player4_active;                                      

//File to maintain game_log during the entire game
extern FILE *game_log;                                           //A file to keep the log for the game

extern int PLAYER_SPEED;
extern int BULLET_SPEED;
extern int GAME_SPEED;

