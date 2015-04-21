#include "Game.h"
#include "Game_Variables.h"
#define TOTAL_NO_BUTTON 5

SDL_Surface *button_image[TOTAL_NO_BUTTON][2]= { {NULL,NULL},
                                                 {NULL,NULL},
                                                 {NULL,NULL},
                                                 {NULL,NULL},
                                                 {NULL,NULL}  };
SDL_Surface *score_screen_image = NULL;
SDL_Surface *option_screen_image = NULL;
SDL_Surface *sound_icon[2]={NULL,NULL};
SDL_Surface *back_button_image = NULL;
SDL_Surface *backk = NULL;
     
BUTTON button[TOTAL_NO_BUTTON];    
BUTTON sound_button,back_button;

////////////////////////////////////////////////////////////////////////////////////////////////////
void init_buttons()
{
    int i,j;
    
    for(i=0,j=200;i<TOTAL_NO_BUTTON;++i,j+=50)
    {
          button[i].dimension.x = 1110;
          button[i].dimension.y = j;
          button[i].dimension.w = 180;
          button[i].dimension.h = 45;
          button[i].state = 0;
    }
    
    sound_button.dimension.x = 550;
    sound_button.dimension.y = 490;
    sound_button.dimension.w = 180;
    sound_button.dimension.h = 45;
    sound_button.state = 0;

    back_button.dimension.x = 550;
    back_button.dimension.y = 550;
    back_button.dimension.w = 180;
    back_button.dimension.h = 45;
    back_button.state =0;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void init_images()
{
    int i,j;
    
    button_image[0][0] = IMG_Load("images\\play_button.bmp");
    button_image[1][0] = IMG_Load("images\\option_button.bmp");
    button_image[2][0] = IMG_Load("images\\halloffame_button.bmp");
    button_image[3][0] = IMG_Load("images\\credits_button.bmp");
    button_image[4][0] = IMG_Load("images\\exit_button.bmp");
    
    
    button_image[0][1] = IMG_Load("images\\play_button2.bmp");
    button_image[1][1] = IMG_Load("images\\option_button2.bmp");
    button_image[2][1] = IMG_Load("images\\halloffame_button2.bmp");
    button_image[3][1] = IMG_Load("images\\credits_button2.bmp");
    button_image[4][1] = IMG_Load("images\\exit_button2.bmp");
    
    score_screen_image = IMG_Load("images\\option_screen.bmp");
    score_screen_image = analyze_image(score_screen_image);
    
    option_screen_image = IMG_Load("images\\controls.bmp");
    option_screen_image = analyze_image(option_screen_image);
    
    sound_icon[0] = IMG_Load("images\\sound_off.bmp");
    sound_icon[1] = IMG_Load("images\\sound_on.bmp");
    
    back_button_image = IMG_Load("images\\back_button.bmp");
    back_button_image = analyze_image(back_button_image);
    
    
    for(i=0;i<2;++i) sound_icon[i] = analyze_image(sound_icon[i]);
    
    for( i = 0 ; i < TOTAL_NO_BUTTON ; ++i)
    {
        for(j=0;j<2;++j)
        {
            button_image[i][j] = analyze_image(button_image[i][j]);
            
        }
    }
    
    backk = IMG_Load("images\\welcome_screen.bmp");
    backk = analyze_image(backk);
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int check_click(BUTTON b, int x , int y)
{
    if(x<(b.dimension.x+b.dimension.w) && x>b.dimension.x)
    {
          if(y>b.dimension.y && y<(b.dimension.y+b.dimension.h))
          {
                   return true;
          }
    }
    return false;
}
//******************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
void handle_mouseover(BUTTON *buttonPtr, int x, int y)
{
    if(check_click(*buttonPtr,x,y) == true)
    {
        buttonPtr->state = 1;
        if(sound)Mix_PlayChannel(-1,button_over_sound,0);
    }
    else
    {
        buttonPtr->state = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void animate_button(BUTTON b,int no)
{
    int i=0;
    int temp = 0;
    
    for(i=0;i<15;++i)
    {
        if(temp == 1) temp = 0;
        else temp = 1;
        
        draw_image(button_image[no][temp],screen,NULL,b.dimension.x,b.dimension.y);
        SDL_Delay(75);
        SDL_Flip(screen);
    }    
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
void show_scores()
{
    int i=0;
    char text_name[25];
    char text_score[25];
    
    TTF_Font *MyFont;
    SDL_Color MyColor = {255,255,255};
    SDL_Color MyColor2 = {255,0,0};
    SDL_Surface *message = NULL;
    
    MyFont = TTF_OpenFont("fonts\\sfont.ttf",20);
    message = TTF_RenderText_Blended(MyFont,"TEAM NAMES",MyColor2);
    draw_image(message,screen,NULL,150,170);
    
    SDL_FreeSurface(message);
    message = NULL;
    
    message = TTF_RenderText_Blended(MyFont,"SCORES",MyColor2);
    draw_image(message,screen,NULL,800,170);

    SDL_FreeSurface(message);
    message = NULL;
    
    read_score();
    sort_score();    

    for(i=0;i<10;++i)
    {
            strcpy(text_name,score[i].name);
            message = TTF_RenderText_Blended(MyFont,text_name,MyColor);
            draw_image(message,screen,NULL,150,200 + (30 * i));
            
            SDL_FreeSurface(message);
            message = NULL;
    
            itoa(score[i].score,text_score,10);
            message = TTF_RenderText_Blended(MyFont,text_score,MyColor);
            draw_image(message,screen,NULL,800,200 + (30 * i));
            
            SDL_FreeSurface(message);
            message = NULL;
    }
    
    SDL_Flip(screen);
    TTF_CloseFont(MyFont);
    SDL_FreeSurface(message);
    MyFont = NULL;
    message = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int welcome_main()
{
    int i,j;
    int mx,my;
    int welcome = true;
    int option_screen = false;
    int score_screen = false;
    int first_run = true;
    int credits_screen = false;
    SDL_Rect temp;
    TTF_Font *MyFont;
    SDL_Color GREEN = {0,255,0};
    SDL_Color WHITE = {255,255,255};
    SDL_Surface *message = NULL;
    
    int option = -1;
    
    init_buttons();
        
    init_images();
    
    draw_image(backk,screen,NULL,0,0);
    
    gameLog("Welcome screen initialized...");
    
    //draw_image(message,screen,NULL,0,0);
   //Mix_PlayMusic(background_music,-1);
    
    while(welcome)
    {
           while(SDL_PollEvent(&event))
           {
                switch(event.type)
                {
                    case SDL_MOUSEMOTION:
                        
                        for(i=0;i<TOTAL_NO_BUTTON;++i)
                        {
                            handle_mouseover(&button[i],event.motion.x,event.motion.y);
                            
                        }
                        break;
                        
                    case SDL_MOUSEBUTTONDOWN:
                
                         
                         
                         mx = event.button.x;
                         my = event.button.y;
                         for( i = 0; i < TOTAL_NO_BUTTON; ++i)
                         {
                               if(check_click(button[i],mx,my)==true)
                               {
                                    if(sound)Mix_PlayChannel(-1,click_sound,4);
                                    animate_button(button[i],i);
                                       
                                       
                                    first_run = true;
                                       switch(i)
                                       {
                                                case 0:
                                                       
                                                       option = 1;
                                                       welcome = false;
                                                       break;
                                                case 1:
                                                        option_screen = true;
                                                        break;
                                                case 2:
                                                        score_screen = true;
                                                        break;
                                                case 3:
                                                        credits_screen = true;
                                                        break;
                                                        
                                                case 4:
                                                       
                                                       option = -1;
                                                       welcome = false;
                                                       break;
                                       }
                                       
                               }
                         }
                         break;
                
                    case SDL_QUIT:
                        
                         welcome = false;
                         option = -1;
                         break;
                    
                    case SDL_KEYDOWN:
                         
                         switch(event.key.keysym.sym)
                         {
                                case SDLK_p:
                                    animate_button(button[0],0);
                                     welcome = false;
                                     option = 1;
                                     break;
                                
                                case SDLK_x:
                                    animate_button(button[4],4);
                                     welcome = false;
                                     option = -1;
                                     break;
                                
                                case SDLK_1:
                                    
                                    if(Mix_PlayingMusic() == 0)
                                    {
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
        //---=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        while(option_screen == true)
        {
            if(first_run)
            {
            draw_image(option_screen_image,screen,NULL,0,0);
            
            draw_image(back_button_image,screen,NULL,back_button.dimension.x, back_button.dimension.y);
            first_run = false;
            }
            draw_image(sound_icon[sound],screen,NULL,sound_button.dimension.x,sound_button.dimension.y);
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        
                        if(sound)Mix_PlayChannel(-1,click_sound,0);
                        mx = event.button.x;
                        my = event.button.y;
                         
                        if(check_click(sound_button,mx,my) == true)
                        {
                            if(sound == 0) sound = 1;
                            else sound =0;
                        }
                        if(check_click(back_button,mx,my)== true)
                        {
                           
                            draw_image(backk,screen,NULL,0,0);
                            option_screen = false;
                        }
                }
            }
            SDL_Flip(screen);
            
        }
        //==========================================================================================
        while(score_screen == true)
        {
            if(first_run)
            {
                draw_image(score_screen_image,screen,NULL,0,0);
                draw_image(back_button_image,screen,NULL,back_button.dimension.x, back_button.dimension.y);
                show_scores();
                first_run = false;
            }                                           
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        
                        if(sound)Mix_PlayChannel(-1,click_sound,0);
                        mx = event.button.x;
                        my = event.button.y;
                         
                        if(check_click(back_button,mx,my)== true)
                        {
                            draw_image(backk,screen,NULL,0,0);
                            score_screen = false;
                        }
                }
            }
            SDL_Flip(screen);
            
        }
        //==========================================================================================
        //==========================================================================================
        while(credits_screen == true)
        {
            if(first_run)
            {
                temp.x = 0;
                temp.y = 0;
                temp.w = 1100;
                temp.h = 600;
                clear_image(temp);
                
                
                MyFont  = TTF_OpenFont("fonts\\lfont.ttf",32);
                message  = TTF_RenderText_Blended(MyFont,"Developed By:",WHITE);
                draw_image(message,screen,NULL,100,100);
                SDL_FreeSurface(message);
                message = NULL;
                TTF_CloseFont(MyFont);
                
                MyFont = TTF_OpenFont("fonts\\sfont.ttf",20);
                message = TTF_RenderText_Blended(MyFont,"-> Bishruti Siku",GREEN);
                draw_image(message,screen,NULL,100,150);
                SDL_FreeSurface(message);
                message = NULL;
                
                message = TTF_RenderText_Blended(MyFont,"-> Nitish Dhaubhadel",GREEN);
                draw_image(message,screen,NULL,100,170);
                SDL_FreeSurface(message);
                message = NULL;
                
                message = TTF_RenderText_Blended(MyFont,"-> Iksha Gurung",GREEN);
                draw_image(message,screen,NULL,100,190);
                SDL_FreeSurface(message);
                message = NULL;
                
                message = TTF_RenderText_Blended(MyFont,"-> Pranaya Pradhananga",GREEN);
                draw_image(message,screen,NULL,100,210);
                SDL_FreeSurface(message);
                message = NULL;
                
                message = TTF_RenderText_Blended(MyFont,"-> Sandip Sahani",GREEN);
                draw_image(message,screen,NULL,100,230);
                SDL_FreeSurface(message);
                message = NULL;

                message = TTF_RenderText_Blended(MyFont,"Computer Engineering",WHITE);
                draw_image(message,screen,NULL,100,300);
                SDL_FreeSurface(message);
                message = NULL;
                
                message = TTF_RenderText_Blended(MyFont,"Kathmandu University",WHITE);
                draw_image(message,screen,NULL,100,320);
                SDL_FreeSurface(message);
                message = NULL;
                
                draw_image(back_button_image,screen,NULL,back_button.dimension.x, back_button.dimension.y);
                
                first_run = false;
                
            }                                           
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONDOWN:
                        
                        if(sound)Mix_PlayChannel(-1,click_sound,0);
                        mx = event.button.x;
                        my = event.button.y;
                         
                        if(check_click(back_button,mx,my)== true)
                        {
                            draw_image(backk,screen,NULL,0,0);
                            credits_screen = false;
                        }
                }
            }
            SDL_Flip(screen);
            
        }
        //==========================================================================================

        for(i=0;i<TOTAL_NO_BUTTON;++i)
        {
             draw_image(button_image[i][button[i].state],screen,NULL,button[i].dimension.x,button[i].dimension.y);
    
        }
           
           SDL_Flip(screen);
    }
    SDL_FreeSurface(option_screen_image);
    SDL_FreeSurface(score_screen_image);
    SDL_FreeSurface(back_button_image);
    SDL_FreeSurface(sound_icon[0]);
    SDL_FreeSurface(sound_icon[1]);
    SDL_FreeSurface(message);
    message = NULL;
    
    
    SDL_FreeSurface(backk);
    for(i=0;i<TOTAL_NO_BUTTON;++i)
    {
        for(j=0;j<2;++j)
        {
            SDL_FreeSurface(button_image[i][j]);
        }
    }
    
    //TTF_CloseFont(font);
    gameLog("Welcome screen closed...");
    return option;
        
}

