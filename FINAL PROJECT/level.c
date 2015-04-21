#include "Game.h"
#include "Game_Variables.h"

static int net_enemy_count =0;
static char special_message[11][100] = { {"........................................"}, 
                                     {"It all begins here..."},
                                     {"Its time to blow up some tanks!!!"},
                                     {"You are not a coward..."},
                                     {"The battle is won but there is a war ahead..."},
                                     {"Dont let them get through you..."},
                                     {"supreme power comes with greater responsibility."},
                                     {"Its more fun another way"},
                                     {"Best Defence is the Greatest offence."},
                                     {"Its time for some revenge..."},
                                     {"Final Show Down..."}               };
        

////////////////////////////////////////////////////////////////////////////////////////////////////
void level_up_screen(int level)
{
    char inf[50] = "LEVEL : ";
    char level_no[5];

    SDL_Surface *message=NULL;
    TTF_Font *MyFont=NULL;

    SDL_Rect temp;

    SDL_Color MyColor = { 255,255,255 };
    SDL_Color MyColor2 = {0,255,0};
    
    temp.x = 0;
    temp.y = 0;
    temp.w = GAME_SCREEN_WIDTH;
    temp.h = SCREEN_HEIGHT;

    clear_image(temp);
    
    itoa(level,level_no,10);
    strcat(inf,level_no);
    
    MyFont = TTF_OpenFont("fonts\\lfont1.ttf",55);
    message = TTF_RenderText_Blended(MyFont,inf,MyColor);
    draw_image(message,screen,NULL,150,150);
    SDL_FreeSurface(message);
    message = NULL;
    TTF_CloseFont(MyFont);
    
    MyFont = TTF_OpenFont("fonts\\sfont1.ttf",28);
    message = TTF_RenderText_Blended(MyFont,special_message[level],MyColor2);
    draw_image(message,screen,NULL,150,300);
    SDL_FreeSurface(message);
    message = NULL;
    
    
    SDL_Flip(screen);
    SDL_Delay(4000);
    TTF_CloseFont(MyFont);
    SDL_FreeSurface(message);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void request_for_names(int team_no, char *required_team_name)
{
        char display_message[100] = "Please enter team ";
        char c[5];        
        int getting_name = true;
        int length_of_name =0;
        
        SDL_Event myEvent;

        SDL_Surface *message=NULL;
        TTF_Font *MyFont=NULL;

        SDL_Rect temp;

        SDL_Color MyColor = { 255,255,255 };
        SDL_Color MyColor2 = {0,255,0};

        temp.x = 0;
        temp.y = 0;
        temp.w = GAME_SCREEN_WIDTH;
        temp.h = SCREEN_HEIGHT;
        
        clear_image(temp);
        
        MyFont = TTF_OpenFont("fonts\\lfont.ttf",30);
        
        itoa(team_no,c,10);
        strcat(display_message,c);
        strcat(display_message, " name");
        message = TTF_RenderText_Blended(MyFont,display_message,MyColor);
        draw_image(message,screen,NULL,150,130);
        SDL_FreeSurface(message);
        message = NULL;
        TTF_CloseFont(MyFont);
        
        MyFont = TTF_OpenFont("fonts\\sfont.ttf",20);
                
        while(getting_name)
        {
            while(SDL_PollEvent(&myEvent))
            {
                if(myEvent.type == SDL_KEYDOWN)
                {
                    switch(myEvent.key.keysym.sym)
                    {
                        case SDLK_a:
                            strcat(required_team_name,"A");

                            break;
                        case SDLK_b:
                            strcat(required_team_name,"B");

                            break;
                        case SDLK_c:
                            strcat(required_team_name,"C");

                            break;
                        case SDLK_d:
                            strcat(required_team_name,"D");

                            break;
                        case SDLK_e:
                            strcat(required_team_name,"E");

                            break;
                        case SDLK_f:
                            strcat(required_team_name,"F");

                            break;
                        case SDLK_g:
                            strcat(required_team_name,"G");

                            break;
                        case SDLK_h:
                            strcat(required_team_name,"H");

                            break;
                        case SDLK_i:
                            strcat(required_team_name,"I");

                            break;
                        case SDLK_j:
                            strcat(required_team_name,"J");

                            break;
                        case SDLK_k:
                            strcat(required_team_name,"K");

                            break;
                        case SDLK_l:
                            strcat(required_team_name,"L");

                            break;
                        case SDLK_m:
                            strcat(required_team_name,"M");

                            break;
                        case SDLK_n:
                            strcat(required_team_name,"N");

                            break;
                        case SDLK_o:
                            strcat(required_team_name,"O");

                            break;
                        case SDLK_p:
                            strcat(required_team_name,"P");

                            break;
                        case SDLK_q:
                            strcat(required_team_name,"Q");

                            break;
                        case SDLK_r:
                            strcat(required_team_name,"R");

                            break;
                        case SDLK_s:
                            strcat(required_team_name,"S");

                            break;
                        case SDLK_t:
                            strcat(required_team_name,"T");

                            break;
                        case SDLK_u:
                            strcat(required_team_name,"U");

                            break;
                        case SDLK_v:
                            strcat(required_team_name,"V");

                            break;
                        case SDLK_w:
                            strcat(required_team_name,"W");

                            break;
                        case SDLK_x:
                            strcat(required_team_name,"X");

                            break;
                        case SDLK_y:
                            strcat(required_team_name,"Y");

                            break;
                        case SDLK_z:
                            strcat(required_team_name,"Z");

                            break;
                        case SDLK_0:
                            strcat(required_team_name,"0");
                            break;
                        case SDLK_1:
                            strcat(required_team_name,"1");
                            break;
                        case SDLK_2:
                            strcat(required_team_name,"2");
                            break;
                        case SDLK_3:
                            strcat(required_team_name,"3");
                            break;
                        case SDLK_4:
                            strcat(required_team_name,"4");
                            break;
                        case SDLK_5:
                            strcat(required_team_name,"5");
                            break;
                        case SDLK_6:
                            strcat(required_team_name,"6");
                            break;
                        case SDLK_7:
                            strcat(required_team_name,"7");
                            break;
                        case SDLK_8:
                            strcat(required_team_name,"8");
                            break;
                        case SDLK_9:
                            strcat(required_team_name,"9");
                            break;
                            
                        case SDLK_SPACE:
                            strcat(required_team_name," ");

                            break;
                        case SDLK_TAB:
                            getting_name = false;
                            break;
                            
                    }
                    length_of_name++;
                }
            }
            message = TTF_RenderText_Blended(MyFont,required_team_name,MyColor2);
            draw_image(message,screen,NULL,150,200);
            
            SDL_Flip(screen);
            if(length_of_name>20) getting_name = false;
            
        }
        TTF_CloseFont(MyFont);
        SDL_FreeSurface(message);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void game_over()
{
    char winning_team_name[50]="";
    char team_score_c[100];
    int i=0;
    long int minimum_score;
    int final_score;
    int who_scored;
    int game_over_screen = true;
    
    SDL_Event myEvent;

    SDL_Surface *message=NULL;
    TTF_Font *MyFont=NULL;

    SDL_Rect temp;

    SDL_Color MyColor = { 255,255,255 };
    SDL_Color MyColor2 = {0,255,0};

    temp.x =0;
    temp.y =0;
    temp.w =1100;
    temp.h = 600;
    
    //get the high score and minimum score infromation already in the file
    minimum_score = score[9].score;
    
    //get the high score made in the current game by comparing two teams score
    final_score = (team_score[1] > team_score[2])? team_score[1] : team_score[2];
    
    //get the team id who made the high score
    who_scored = (team_score[1] > team_score[2])? 1 : 2;
    
    if(final_score>minimum_score) request_for_names(who_scored,winning_team_name);
    
    clear_image(temp);
 
    MyFont = TTF_OpenFont("fonts\\lfont.ttf",60);
    message = TTF_RenderText_Blended(MyFont,"GAME OVER",MyColor);
    draw_image(message,screen,NULL,150,150);
    SDL_FreeSurface(message);
    message = NULL;

    TTF_CloseFont(MyFont);
             
    if(final_score>minimum_score)
    {
            MyFont = TTF_OpenFont("fonts\\sfont.ttf",28);
            message = TTF_RenderText_Blended(MyFont,"Congragulation you made a high score",MyColor2);
            draw_image(message,screen,NULL,150,300);
            SDL_FreeSurface(message);
            message = NULL;

            //TTF_CloseFont(MyFont);
        
            add_score(winning_team_name,final_score);
            
            strcat(winning_team_name," : ");
            itoa(final_score,team_score_c,10);
            strcat(winning_team_name,team_score_c);
            
            message = TTF_RenderText_Blended(MyFont,winning_team_name,MyColor2);
            draw_image(message,screen,NULL,150,350);
                    SDL_FreeSurface(message);
                    message = NULL;

        
    }
    else
    {
            MyFont = TTF_OpenFont("fonts\\sfont.ttf",28);
            message = TTF_RenderText_Blended(MyFont,"Better luck next time",MyColor2);
            draw_image(message,screen,NULL,150,300);
                    SDL_FreeSurface(message);
                    message = NULL;

            TTF_CloseFont(MyFont);

    }
    while(game_over_screen)
    {
        while(SDL_PollEvent(&myEvent))
        {
            if(myEvent.type == SDL_KEYDOWN)
            {
                switch(myEvent.key.keysym.sym)
                {
                    case SDLK_x:
                        game_over_screen = false;
                        break;
                }
            }
        }
        SDL_Flip(screen);
    }
    
    
    
    
    //add_score("TERMINATOR",66L);
    SDL_Flip(screen);
    //SDL_Delay(4000);
    TTF_CloseFont(MyFont);
            SDL_FreeSurface(message);
            message = NULL;
    
    for(i=0;i<5;++i) player[i].isActive = false;
    for(i=0;i<5;++i) enemy[i].isActive = false;
    game_quit = true;
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void clean_cells()
{
     int i,j;     //for looping
     //assigining coordinates to the grids
     for(i=0;i<MAX_ROW;++i)
     {
             for(j=0;j<MAX_COL;++j)
             {
                  cell[i][j].isWhat = EMPTY;
             }
     }
     gameLog("Cell structures cleaned...");
}

void init_cells()
{
     int i,j;     //for looping
     int sx=0,sy=0; //Dummy coordinates variables
     
     //assigining coordinates to the grids
     for(i=0;i<MAX_ROW;++i)
     {
             for(j=0;j<MAX_COL;++j)
             {
                  cell[i][j].dimension.x = sx;
                  cell[i][j].dimension.y = sy;
                  cell[i][j].dimension.w = CELL_SIZE;
                  cell[i][j].dimension.h = CELL_SIZE;
                  
                  cell[i][j].isWhat = EMPTY;
                  cell[i][j].hits=0; 
                  sx += CELL_SIZE;
             }
             sx=0;
             sy += CELL_SIZE;                   
     }
     gameLog("Cell structures initialized...");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SET LEVEL<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function accertains the level information from the file and set its
//information in our level_map variable for analysis
int read_level_file(int level)
{
    int i,j;  //Looping variables
    int obj;
    char file_name[50] = "levels\\level";
    char extension[] = ".lvl";
    char level_char[5];
    
    itoa(level,level_char,10);
    
    strcat(file_name,level_char);
    strcat(file_name,extension);
    gameLog(file_name);
    
    FILE *fp;  //A file pointer to open you level information file
    
    
    fp=fopen(file_name,"r");  //opening the level file
    
    if(fp==NULL) 
       error("Unable to load the level file...");
    
    
    //This loop read each character form the file and set them accordingly
    //in our level_map variable so that we can place the objects of the game
    //according to the level
    for(i=0;i<MAX_ROW;++i)
    {
        for(j=0;j<MAX_COL;++j)
        {                  
            fscanf(fp,"%d",&obj); //scanning the characters                     
            switch(obj)
            {
                  case WALL:   //code 1
                            wall[i][j].dimension.x = cell[i][j].dimension.x;
                            wall[i][j].dimension.y = cell[i][j].dimension.y;
                            wall[i][j].dimension.w = WALL_WIDTH;
                            wall[i][j].dimension.h = WALL_HEIGHT;
                            wall[i][j].hits=0;
                            cell[i][j].isWhat = WALL;
                          
            
                            break;
                      
                  case BRICK:    //code 2
                            brick[i][j].dimension.x = cell[i][j].dimension.x;
                            brick[i][j].dimension.y = cell[i][j].dimension.y;
                            brick[i][j].dimension.w = BRICK_WIDTH;
                            brick[i][j].dimension.h = BRICK_HEIGHT;
                            brick[i][j].hits=0;
                            cell[i][j].isWhat=BRICK;
                          
                            
                            break; 
                  case SEAL1:
                            seal[1].dimension.x = cell[i][j].dimension.x;
                            seal[1].dimension.y = cell[i][j].dimension.y;
                            seal[1].hits=0;
                            seal[1].dimension.w = 50;
                            seal[1].dimension.h = 50;
                            cell[i][j].isWhat = SEAL1;
                            break;
                            
                  case SEAL2:
                            seal[2].dimension.x = cell[i][j].dimension.x;
                            seal[2].dimension.y = cell[i][j].dimension.y;
                            seal[2].hits = 0;
                            seal[2].dimension.w = 50;
                            seal[2].dimension.h = 50;
                            cell[i][j].isWhat = SEAL2;
                            break;
                            
                  case ENEMY:
                            enemy[net_enemy_count].dimension.x = cell[i][j].dimension.x;
                            enemy[net_enemy_count].dimension.y = cell[i][j].dimension.y;
                            enemy[net_enemy_count].dimension.w = 50;
                            enemy[net_enemy_count].dimension.h = 50;
                            
                            cell[i][j].isWhat = ENEMY;
                            ++net_enemy_count;
                            break;

                  case EMPTY:
                           cell[i][j].isWhat=EMPTY;
            }
            
        }
    }
    
    fclose(fp); //close the file after the reading has finished
    
    gameLog("Level sucessfully read from the file...");
    return 0; //indicate a sucessfull completetion of the function   
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INIT WALLS<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function initializes all the elements of the game and assign the 
//coordinates to them
void draw_level()
{
     int i,j;
     int e_count =0;
    //blit the background to the screen
    draw_image(background,screen,NULL,0,0); 
        
        
     for(i=0;i<MAX_ROW;++i)
     {
            for(j=0;j<MAX_COL;++j)
            {
                switch(cell[i][j].isWhat)
                {
                                         
                       case WALL:
                            draw_image(wall_image,screen,NULL,wall[i][j].dimension.x,wall[i][j].dimension.y);
                            break;
                            
                       case BRICK:
                            draw_image(brick_image,screen,NULL,brick[i][j].dimension.x,brick[i][j].dimension.y);
                            break;            

                       case SEAL1:
                            draw_image(seal_image[1],screen,NULL,seal[1].dimension.x,seal[1].dimension.y);
                            break;
                            
                       case SEAL2:
                            draw_image(seal_image[2],screen,NULL,seal[2].dimension.x,seal[2].dimension.y);
                            break;

                       case ENEMY:
                            
                            draw_image(enemy_image[enemy[e_count].direction],screen,NULL,enemy[e_count].dimension.x,enemy[e_count].dimension.y);
                            ++e_count;
                            break;
                            
                       case EMPTY:
                            clear_image(cell[i][j].dimension);
                            break;

                  }                
            }
     }   
     gameLog("Level was sucessfully drawn...");
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INIT GAME<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function initializes all the basic things required prior to the exectuion
//of the game
void load_object()
{
     int i=0,j=0;
     
     for(i=0;i<TOTAL_NO_SLOT;++i) deactivate_slot(i);
     
     for( i = 0; i<5 ; ++i)
     {
            enemy[i].id = i;
            enemy[i].direction = rand()%4;
            enemy[i].dimension.w = CELL_SIZE;
            enemy[i].dimension.h = CELL_SIZE;
            enemy[i].isActive = false;
            
            enemy[i].my_bullet.id = 0;
            enemy[i].my_bullet.dimension.x=1400;
            enemy[i].my_bullet.dimension.y=0;
            enemy[i].my_bullet.dimension.w=BULLET_WIDTH;
            enemy[i].my_bullet.dimension.h=BULLET_HEIGHT;
            enemy[i].my_bullet.Direction=RIGHT;
            enemy[i].my_bullet.isActive=false;
           
     }
     
     for( i=0;i<net_enemy_count;++i) enemy[i].isActive = true;
     
     player[1].dimension.x= 20 * CELL_SIZE;
     player[1].dimension.y= 3 * CELL_SIZE;
     player[1].Direction=LEFT;
        bullet[1].Direction=LEFT;
             
     player[2].dimension.x=1*CELL_SIZE;
     player[2].dimension.y=3*CELL_SIZE;
     player[2].Direction=RIGHT;
        bullet[2].Direction=RIGHT;
             
     player[3].dimension.x=1*CELL_SIZE;
     player[3].dimension.y=7*CELL_SIZE;
     player[3].Direction=RIGHT;
        bullet[3].Direction=RIGHT;
             
     player[4].dimension.x=20*CELL_SIZE;
     player[4].dimension.y=7*CELL_SIZE;
     player[4].Direction=LEFT;
        bullet[4].Direction=LEFT;
     for( i =1 ; i < 5 ; ++i) 
     {
            player[i].id = i;
            player[i].lives = 3;
     }
     player[1].isActive = true;
     player[2].isActive = true;
     if(player3_active) player[3].isActive = true;
     if(player4_active) player[4].isActive = true;
            
    for(i=0;i<5;++i)
    {
        bullet[i].id = i;
        bullet[i].dimension.x=1300;
        bullet[i].dimension.y=0;
        bullet[i].dimension.w=BULLET_WIDTH;
        bullet[i].dimension.h=BULLET_HEIGHT;
        bullet[i].isActive=false;
        
    }
     gameLog("Level Objects were initialized...");

}
void load_object_once()
{
     int i,j=0;
     
    for(i=0;i<TOTAL_NO_SLOT;++i)deactivate_slot(i);
    
    for(i=0;i<9;i++)
    {          
            explosion[i].x = i * 50;
            explosion[i].y = 0;
            explosion[i].w = 50;
            explosion[i].h = 50;
     }
     
     for(i=0;i<9;++i)
     {
              
            seal_explosion_clip[i].x = i * 150;
            seal_explosion_clip[i].y = 0;
            seal_explosion_clip[i].w = 150;
            seal_explosion_clip[i].h = 150;
     }

     for(i=0;i<9;++i)
     {
            explosion_player[i].x = 10 + (i * 50);
            explosion_player[i].y = 10;
            explosion_player[i].w = 30;
            explosion_player[i].h = 30;
     }

     for( i = 0 ; i<2 ; ++i)
     {
          crack[i].x = i*50;
          crack[i].y = 0;  
          crack[i].w = 50;
          crack[i].h = 50;
     }
     for( i =1 ; i < 5 ; ++i) 
     {
            player[i].id = i;
            player[i].lives = 3;
            player[i].dimension.w=PLAYER_WIDTH;
            player[i].dimension.h=PLAYER_HEIGHT;
     }
     player[1].isActive = true;
     player[2].isActive = true;
     if(player3_active) player[3].isActive = true;
     if(player4_active) player[4].isActive = true;
     
     gameLog("Objects were initialized...");

}

void new_level(int level)
{
    int i=0;
    if(level<TOTAL_LEVELS)
    {
        net_enemy_count = 0;
        clean_cells();
        level_up_screen(level);
        read_level_file(level);
        draw_level();
        load_object();
        update_scoreboard();
        fprintf(game_log,"\n NEW LEVEL INITIALIZED : %d",level);  
    }
    else
    {
        game_over();
    }

}


