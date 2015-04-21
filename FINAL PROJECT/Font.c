#include "game.h"
#include "Game_Variables.h"

// These variables are local to this file only
static TTF_Font *large_font = NULL;                         //Large font type
static TTF_Font *small_font = NULL;                         //Small font type
static SDL_Color large_font_color = {0,255,0};              //Lage font color
static SDL_Color small_font_color = {255,255,255};          //Small font color

static SDL_Surface *score_back=NULL;                        //Score board background image
static SDL_Surface *message = NULL;                         //message display

/////////////////////////////////////////////////////////////////////////////////////////////////////
//This function loads fonts from the 'fonts' folder of the game
int load_font()
{
    score_back = IMG_Load("images\\score_back.bmp");
    score_back = analyze_image(score_back);
    
    large_font = TTF_OpenFont("fonts\\lfont1.ttf",20);
    small_font = TTF_OpenFont("fonts\\sfont1.ttf",25);
    if(large_font ==NULL || small_font == NULL || score_back == NULL) return -1;
  
    gameLog("All fonts sucessfull loaded...");
    return 0;       
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This function unload fonts at the end of the game
void unload_font()
{
    TTF_CloseFont(large_font);
    TTF_CloseFont(small_font);
    SDL_FreeSurface(score_back);
    SDL_FreeSurface(message);
    gameLog("All fonts sucessfull closed...");
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//This function is called everytime when the scores in the score board is to be updated
void update_scoreboard()
{
    //To display level no
    char level_text[15] = "Level: ";
    char c_level[5];

    //To display team player lives and scores
    char team1_player1_lives[20] = "Player 1 Lives: ";
    char team1_player2_lives[20] = "Player 2 Lives: ";
    char team1_score [30] = "Score: ";
    char c_t1_p1_lives[5];
    char c_t1_p2_lives[5];
    char c_t1_score[20];
    
    
    
    char team2_player1_lives[20] = "Player 1 Lives: ";
    char team2_player2_lives[20] = "Player 2 Lives: ";
    char team2_score[30] = "Score: ";   
    char c_t2_p1_lives[5];
    char c_t2_p2_lives[5];
    char c_t2_score[20];
    
    
    //convert level no to char array and from a concatened string
    itoa(current_level,c_level,10);
    strcat(level_text,c_level);

    //Similary convert players lives and scores to character array and concatened with their respective strings
    itoa(player[1].lives,c_t1_p1_lives,10);
    itoa(player[4].lives,c_t1_p2_lives,10);
    itoa(team_score[1],c_t1_score,10);
    
    itoa(player[2].lives,c_t2_p1_lives,10);
    itoa(player[3].lives,c_t2_p2_lives,10);
    itoa(team_score[2],c_t2_score,10);
    
    //Do the same with team1 and team2 lives and scores
    strcat(team1_player1_lives,c_t1_p1_lives);
    strcat(team1_player2_lives,c_t1_p2_lives);
    strcat(team1_score,c_t1_score);

    strcat(team2_player1_lives,c_t2_p1_lives);
    strcat(team2_player2_lives,c_t2_p2_lives);
    strcat(team2_score,c_t2_score);
    
    //clean the previous score board
    clear_scoreboard();
    
    //Display the new scoreboard
    message = TTF_RenderText_Blended(large_font,"SCORE BOARD",large_font_color);
    SDL_FreeSurface(message);
    message = NULL;

    draw_image(message,screen,NULL,1100,0);
    
    message = TTF_RenderText_Blended(large_font,"TEAM 1",large_font_color);

    draw_image(message,screen,NULL,1150,30);
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Blended(small_font,team1_player1_lives,small_font_color);
    
    draw_image(message,screen,NULL,1100,70);
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Blended(small_font,team1_player2_lives,small_font_color);
    
    draw_image(message,screen,NULL,1100,120);
    SDL_FreeSurface(message);
    message = NULL;

    message = TTF_RenderText_Blended(small_font,team1_score,small_font_color);
    
    draw_image(message,screen,NULL,1100,170);
    SDL_FreeSurface(message);
    message = NULL;
    
    
    message = TTF_RenderText_Blended(large_font,"TEAM 2",large_font_color);
    
    draw_image(message,screen,NULL,1150,330);
    SDL_FreeSurface(message);
    message = NULL;

    message = TTF_RenderText_Blended(small_font,team2_player1_lives,small_font_color);
    
    draw_image(message,screen,NULL,1100,370);
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Blended(small_font,team2_player2_lives,small_font_color);
    
    draw_image(message,screen,NULL,1100,420);
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Blended(small_font,team2_score,small_font_color);
    
    draw_image(message,screen,NULL,1100,470);
    SDL_FreeSurface(message);
    message = NULL;
        
    message = TTF_RenderText_Blended(large_font,level_text,large_font_color);
    
    draw_image(message,screen,NULL,1100,550);
    SDL_FreeSurface(message);
    message = NULL;

  //  SDL_Flip(screen);    
    
}
//Function cleans out the score board before updating
void clear_scoreboard()
{
    draw_image(score_back,screen,NULL,1100,0);
}
