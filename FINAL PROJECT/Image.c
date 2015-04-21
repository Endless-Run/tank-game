#include "Game.h"
#include "Game_Variables.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
SDL_Surface *analyze_image(SDL_Surface *src)
{
     //Temporary sdl surfaces       
     SDL_Surface *loaded_image;     //to hold the loaded image
     SDL_Surface *optimized_image;  //to hold the optimized image
     
     loaded_image=src;      
     
     //optimize the image
     optimized_image = SDL_DisplayFormat(loaded_image);
     
     //Free the temporary buffer
     SDL_FreeSurface(loaded_image);
     
     //return the optimized image
     return optimized_image;
     
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ANALYZE IMAGES<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function will analyze all the images loaded by the game by calling
//another function analyze game
void analyze_images()
{
    int i=0,j=0;
    
    //analyze images to current format
    background = analyze_image(background);
    wall_image = analyze_image(wall_image);  
    brick_image = analyze_image(brick_image);

    for(i=1;i<5;++i)
    {
        for(j=1;j<5;++j)
        {
            player_image[i][j] = analyze_image(player_image[i][j]);
            SDL_SetColorKey(player_image[i][j],SDL_SRCCOLORKEY,SDL_MapRGB(player_image[i][j]->format,0,0,0));
    
        }
    }
            
    for(i=0;i<4;++i) enemy_image[i] = analyze_image(enemy_image[i]);

    explode = analyze_image(explode);
   // SDL_SetColorKey(explode,SDL_SRCCOLORKEY,SDL_MapRGB(explode->format,0,0,0));
    
    seal_image[1] = analyze_image(seal_image[1]);
    seal_image[2] = analyze_image(seal_image[2]);
    
    cracking = analyze_image(cracking);
    SDL_SetColorKey(cracking,SDL_SRCCOLORKEY,SDL_MapRGB(cracking->format,0,0,0));
       
    seal_exp_image = analyze_image(seal_exp_image);
    SDL_SetColorKey(seal_exp_image,SDL_SRCCOLORKEY,SDL_MapRGB(seal_exp_image->format,0,0,0));
    
    bullet_image = analyze_image(bullet_image);

    SDL_SetColorKey(bullet_image,SDL_SRCCOLORKEY,SDL_MapRGB(bullet_image->format,0,0,0));

    gameLog("Images analyzed...");  
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DRAW IMAGE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//Function to blit the given surface to the destination surface
//with the cliping specifiaction and the coordinates
void draw_image(SDL_Surface *source,SDL_Surface *destination,SDL_Rect *clipping,int posX, int posY)
{
     //a temporary SDL_rect structure that holds the desired location 
     //for placing the source surface 
     SDL_Rect location;
     location.x=posX;
     location.y=posY;
     
     //Blit the image to given destionation surface
     SDL_BlitSurface(source,clipping,destination,&location);
       
     
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//Image loader function for all the surfaces
int load_image()
{
    //Load the background image
    background = IMG_Load("images\\level1\\background.bmp");
    
    wall_image=IMG_Load("images\\level1\\wall.bmp");
    
    brick_image=IMG_Load("images\\level1\\brick.bmp");
    
    enemy_image[ENEMY_UP]=IMG_Load("images\\enemy_up.bmp");
    enemy_image[ENEMY_RIGHT]=IMG_Load("images\\enemy_right.bmp");
    enemy_image[ENEMY_DOWN]=IMG_Load("images\\enemy_down.bmp");
    enemy_image[ENEMY_LEFT]=IMG_Load("images\\enemy_left.bmp");
    
    
    
    player_image[0][0]=NULL;
    player_image[0][UP]=NULL;
    player_image[0][DOWN]=NULL;
    player_image[0][LEFT]=NULL;
    player_image[0][RIGHT]=NULL;
    
    player_image[1][0]=NULL;
    player_image[1][UP]=IMG_Load("images\\player1_up.bmp");
    player_image[1][DOWN]=IMG_Load("images\\player1_down.bmp");
    player_image[1][LEFT]=IMG_Load("images\\player1_left.bmp");
    player_image[1][RIGHT]=IMG_Load("images\\player1_right.bmp");
    
    player_image[2][0]=NULL;
    player_image[2][UP]=IMG_Load("images\\player2_up.bmp");
    player_image[2][DOWN]=IMG_Load("images\\player2_down.bmp");
    player_image[2][LEFT]=IMG_Load("images\\player2_left.bmp");
    player_image[2][RIGHT]=IMG_Load("images\\player2_right.bmp");
    
    player_image[3][0]=NULL;
    player_image[3][UP]=IMG_Load("images\\player2_up.bmp");
    player_image[3][DOWN]=IMG_Load("images\\player2_down.bmp");
    player_image[3][LEFT]=IMG_Load("images\\player2_left.bmp");
    player_image[3][RIGHT]=IMG_Load("images\\player2_right.bmp");
    
    player_image[4][0]=NULL;
    player_image[4][UP]=IMG_Load("images\\player1_up.bmp");
    player_image[4][DOWN]=IMG_Load("images\\player1_down.bmp");
    player_image[4][LEFT]=IMG_Load("images\\player1_left.bmp");
    player_image[4][RIGHT]=IMG_Load("images\\player1_right.bmp");
    


    bullet_image = IMG_Load("images\\bullet.bmp");
    
    explode = IMG_Load("images\\explosion.bmp");
    seal_image[1] = IMG_Load("images\\seal1.bmp");
    seal_image[2] = IMG_Load("images\\seal2.bmp");
    
    cracking = IMG_Load("images\\cracking.bmp");
    
    seal_exp_image = IMG_Load("images\\seal_explosion.bmp");
    
    //check if the all the images has been loaded or not
    //and return an error if fail to load the image
   if(    
    background==NULL ||
    
    wall_image==NULL || 
    
    brick_image==NULL|| 
    
    player_image[1][UP] == NULL ||
    player_image[1][DOWN] == NULL ||
    player_image[1][LEFT] == NULL ||
    player_image[1][RIGHT] == NULL ||
    
    player_image[2][UP] == NULL ||
    player_image[2][DOWN] == NULL ||
    player_image[2][LEFT] == NULL ||
    player_image[2][RIGHT] == NULL ||
    
    player_image[3][UP] == NULL ||
    player_image[3][DOWN] == NULL ||
    player_image[3][LEFT] == NULL ||
    player_image[3][RIGHT] == NULL ||
    
    player_image[4][UP] == NULL ||
    player_image[4][DOWN] == NULL ||
    player_image[4][LEFT] == NULL ||
    player_image[4][RIGHT] == NULL ||
    
    enemy_image[0] == NULL ||
    enemy_image[1] == NULL ||
    enemy_image[2] == NULL ||
    enemy_image[3] == NULL ||
    
    
    bullet_image == NULL || 
    
    explode == NULL ||
    seal_image[1] == NULL ||
    seal_image[2] == NULL ||
    cracking == NULL ||
    seal_exp_image == NULL
    
       
    )return error();
    
    gameLog("All the images were sucessfully loaded...");
    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to unload images after the completetion of the game inorder to free the memory resources 
void unload_images()
{
    int i=0;
    int j=0;
    SDL_FreeSurface(background);
    SDL_FreeSurface(wall_image);
    SDL_FreeSurface(brick_image);
   
    for(i=1;i<5;++i)
    {
        for(j=1;j<5;++j)
        {
            SDL_FreeSurface(player_image[i][j]);
        }
    }
    
    for(j=0;j<4;++j)
        {
            SDL_FreeSurface(enemy_image[j]);
        }
    
    SDL_FreeSurface(bullet_image);
    SDL_FreeSurface(explode);
    SDL_FreeSurface(seal_image[0]);
    SDL_FreeSurface(seal_image[1]);
    SDL_FreeSurface(seal_image[2]);
    SDL_FreeSurface(seal_exp_image);
    SDL_FreeSurface(cracking);
    
    gameLog("All images were sucessfully unloaded...");
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//This function pastes the clip of the background at the 'obj' location thus cleaning the old image
//of the obj at the location
//it is essentialy uselfull to remove the traces of bullet, player, explosion image, bricks etc
void clear_image(SDL_Rect obj)
{
     
    draw_image(background,screen,&obj,obj.x,obj.y);
}
