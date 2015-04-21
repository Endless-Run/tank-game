#include "Game.h"
#include "Game_Variables.h"

int load_sound()
{
    //Load sound files from the sounds directory of the game
     background_music = Mix_LoadMUS("sounds\\title.wav");
     click_sound = Mix_LoadWAV("sounds\\button_click.wav");
     button_over_sound = Mix_LoadWAV("sounds\\button_over.wav");
     wall_explode = Mix_LoadWAV("sounds\\wall_explosion.wav");
     bullet_fire_sound = Mix_LoadWAV("sounds\\bullet_fire.wav");
     seal_explosion_sound = Mix_LoadWAV("sounds\\seal_explosion.wav");
     player_killed_sound = Mix_LoadWAV("sounds\\player_explosion.wav");
     
    //Check if all the files are loaded
    if( background_music == NULL ||
        click_sound == NULL ||
        wall_explode == NULL ||
        button_over_sound == NULL ||
        bullet_fire_sound == NULL ||
        seal_explosion_sound == NULL ||
        player_killed_sound == NULL
       ) return -1;
   
   gameLog("All the sounds were sucessfully loaded...");
   return 0;   
}

void unload_sound()
{
    //Unload all the sound files after the completetion of the game
    Mix_FreeMusic(background_music);
    Mix_FreeChunk(click_sound);
    Mix_FreeChunk(wall_explode);
    Mix_FreeChunk(button_over_sound);
    Mix_FreeChunk(bullet_fire_sound);
    Mix_FreeChunk(seal_explosion_sound);
    Mix_FreeChunk(player_killed_sound);
    gameLog("All the sounds were unloaded...");
   
}
