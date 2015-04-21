#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
#define GAME_SCREEN_WIDTH 1300              //The main window dimension
#define SCREEN_WIDTH 1100                   //Game play area width
#define SCREEN_HEIGHT 600                   //Game play area height
#define SCREEN_BBP 32                       //Bit Per Pixel for the main screen

#define CELL_SIZE 50                        //Dimension of each cell

#define WALL_WIDTH 50                       //The wall dimension  
#define WALL_HEIGHT 50

#define BRICK_WIDTH 50                      //Brick dimension
#define BRICK_HEIGHT 50

#define PLAYER_WIDTH 30                     //Player size
#define PLAYER_HEIGHT 30

#define BULLET_WIDTH 5                      //Bullets dimension
#define BULLET_HEIGHT 5

#define true 1                              //These are the defination for true false constants
#define false 0

//These are the constants that define how much score is assigned for each elements of the game
//destroyed by the player
#define WALL_POINT 10                       
#define SEAL_POINT 1000
#define PLAYER_POINT 100
#define ENEMY_POINT 500

//These constants define the code set for each game elements used in the game
//so the it helps us to replace numbers with game elements name for enhancing
//the code readability
#define EMPTY 0
#define WALL 1              
#define BRICK 2
#define PLAYER1 3
#define PLAYER2 4
#define PLAYER3 7
#define PLAYER4 8
#define SEAL1 5
#define SEAL2 6
#define ENEMY 9

//the symbolic no representing directions reason for this is same as above
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//These are the symbolic representation for the direction of enemy
#define ENEMY_UP 0
#define ENEMY_RIGHT 1
#define ENEMY_DOWN 2
#define ENEMY_LEFT 3

//this is the total no of maximum solts allowed for the explosion animation
#define TOTAL_NO_SLOT 10

//Total number of levels supported by the game
#define TOTAL_LEVELS 5

//Maximum number of enemies possible at any level in the game
#define TOTAL_ENEMIES 5
///////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
//Structures
//------------------------------------------------------------------------------

//This is a structure representing a single cell(block) in the game level display
//Each cell has following properties;

//CELL STRUCTURE
typedef struct{
        SDL_Rect dimension;                     //Diemsion of cell
        int isWhat;                             //What is in that cell
        int hits;                               //How many hits cell suffered
}CELL;

//PLAYER STRUCTURE
typedef struct{   
        SDL_Rect dimension;                     //Dimension of the player
        int id;                                 //PLayer Identification Number
        int Direction;                          //Direction at which the player is facing in the game
        int lives;                              //Number of lives player has
        int isActive;                           //For enabling and disabling a player in the game
}PLAYER;

//BULLET STRUCTURE
typedef struct{
        SDL_Rect dimension;                     //Dimension of the bullet
        int id;                                 //Identification number of the bullet
        int Direction;                          //Direction in which the bullet is moving
        int isActive;                           //For enabling and disabling the bullet
}BULLET;

//BUTTON STRUCTURE
typedef struct{
        int state;
        SDL_Rect dimension;                     //Dimension of the bullet
}BUTTON;

//EXPLOSION SLOT STRUCTURE
typedef struct{
    int count;                                  //Counts the current frame player by the slot
    int isActive;                               //For enabling and disabling the slot
    SDL_Rect location;                          //Location where the animation is played
    
} EXPLOSION_SLOT;

//ENEMY STRUCTURE
typedef struct {    
    int id;
    int direction;                              //Direction in which the enemy is firing
    int isActive;                               //For enabling the disabling enemy
    BULLET my_bullet;                           //Bullet of the enemy
    SDL_Rect dimension;                         //Dimension of enemy
    
}ENEMYY;

//Scores structure
typedef struct
{
        char name[50];                          //Player name
        long int score;                         //Player score

}SCORES;


//------------------------------------------------------------------------------
//Global constants and variables
//------------------------------------------------------------------------------

//row and cols
static const int MAX_ROW=SCREEN_HEIGHT/CELL_SIZE;
static const int MAX_COL=SCREEN_WIDTH/CELL_SIZE;



//--------------------------------------------------------------------------------------------------
//Prototypes for the game functions
//--------------------------------------------------------------------------------------------------

//This function initialized current level to the given level
void new_level(int which_level);           

//This function assign each cell structure its unique coordinates in the game 
void init_cells();

//This function loads the objects of the game like player,bullets,enemies each time a new level is
//loaded
void load_object();

//This function initalizes all structure variable with their default values
void load_object_once();

//This function draws out the particular level in the game screen
void draw_level();

//This function writes given message to the game log.txt file
void gameLog(char *message);

//This function load all necessary images from the file
int load_image();

//This function unloads all images after the completetion of the game
void unload_images();

//This function optimizes the given image to the display format of the game
SDL_Surface* analyze_image(SDL_Surface *source);

//This function analyzes all the loaded images of the game one by one
void analyze_images();

//This function puts a blank image in the given location. Especially used to clear the 
//traces of the p;ayer movement, bullet movement
void clear_image(SDL_Rect object);

//This function draws the given image in the given location of the screen
void draw_image(SDL_Surface *which_image, SDL_Surface *where, SDL_Rect *how_much, int PosX, int PosY);

//This function detects collision between object A and Object B and return true of false
int collision(SDL_Rect objectA, SDL_Rect objectB);

//This function moves the given player in given direction
int move_player(PLAYER *which_player, int Direction);

//This functon moves the given active bullet
CELL move_bullet(BULLET *which_bullet);

///This function finds the object that is located juct ahead of the given object in specified direction
CELL check_collision(SDL_Rect object ,int direction);

//This function is called each times the player fires a bullet. It initializes the bullet with new
//direction and location of fire
void activate_bullet(BULLET *which_bullet, PLAYER to_which_player);

//This function especially checks the collsion between the players in the specified direction
int check_player_collsion(PLAYER player1, PLAYER player2, int direction);

//This function loads the sound file from the file to the game
int load_sound();

//This function unloads all the sounds after the completetion of the game
void unload_sound();

//This function players the explosion animation at the specified location
void play_explosion(int x, int y);

//This function loads the score board for the game
void load_scoreboard();

//This function is called everytime to upadate the socre board with new scores in the game
void update_scoreboard();

//This function loads all the fonts required in the game from the file
int load_font();

//This function unloads all fonts after the completetion of the game
void unload_font();

//This funtion clears the scoreboard containing old score and updates it with new scores
void clear_scoreboard();

//This function is called each time a player is killed in the game.
//It reduces their lives by one and if all lives are finished then the player is completely 
//disabled.
int player_killed(PLAYER *which_player);

//It returns the currently disactive slot for playing the animation
int get_active_slot();

//This function activates the given slot for playing the explosion animation at the specified location
int activate_slot(int slot_no, int x, int y);

//This function deactivates the slot after the explosion animation is complete for the given slot
int deactivate_slot(int slot_no);

//This function plays the explosion animation for the player only
void play_explosion_player(int x, int y,int which_player);

//This function is called each time a seal is hit by the bullet. The seal no denotes which seal has
//been hit and bullet id denotes which object's bullet has hit the seal.
void seal_got_hit(int seal_no, int bullet_id);

//This function writes the score array to the file
void write_score(SCORES []);

//Function for sorting scores
void sort_score();

//Function that add new scores to the existing scores information 
void add_score(char *name, long int scoreVal);

//Function to master reset the scores
void reset_scores();

