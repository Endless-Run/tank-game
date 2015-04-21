#include "Game.h"
#include "Game_Variables.h"

//This function gets the enemy no present in the given cell
int get_enemy_no(CELL cell);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Plays the seal explosion at the given x and y coordinates
void play_seal_explosion(int x, int y)
{
    int i=0;
    int j=0;
    for(i=0;i<9;++i)
    {
        for(j=1;j<5;++j)
        {
            if(player[j].isActive) draw_image(player_image[j][0],screen,NULL,player[j].dimension.x, player[j].dimension.y);
        }
        draw_image(seal_exp_image,screen,&seal_explosion_clip[i],x,y);
        SDL_Flip(screen);
        SDL_Delay(35);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// A function to check collision for 'obj' moving in the given 'direction' in the game with the walls
// bricks 
CELL check_collision(SDL_Rect obj, int direction)
{
    //Get x and y coordinates of the obj and also the width and height
    int x = obj.x;
    int y = obj.y;
    int width = obj.w;
    int height = obj.h;
    
    //determine the current row and col of the obj based on the coordinates
    int curr_r = y/CELL_SIZE;
    int curr_c = x/CELL_SIZE;
    
    //variables that hold next row and col information for the obj moving in given 'direction'
    int next_r1,next_c1;
    int next_r2,next_c2;
      
    //switch the direction of motion of the object 
    switch(direction)
    {
           //In case the object is moving in the UPward direction
           case UP:
                //Determing next row and col information ahead of the object
                next_r1 = (y-1)/CELL_SIZE;
                next_c1 = x/CELL_SIZE;
                next_c2 = (x + width)/CELL_SIZE;
                
                //check what is present in cell located at those rows and col ahead of the obj
                if (cell[next_r1][next_c1].isWhat==EMPTY && cell[next_r1][next_c2].isWhat== EMPTY)
                {
                    //return the cell object if it is not empty
                      return cell[next_r1][next_c1];
                }
                else
                {
                    //if cells are empty return EMPTY cell information
                    if(cell[next_r1][next_c1].isWhat != EMPTY) return cell[next_r1][next_c1];
                    else return cell[next_r1][next_c2];
                }
                
                
         case DOWN:
                next_r1 = (y + height + 1)/CELL_SIZE;
                next_c1 = x/CELL_SIZE;
                next_c2 = (x + width)/CELL_SIZE;
                if (cell[next_r1][next_c1].isWhat == EMPTY && cell[next_r1][next_c2].isWhat== EMPTY)
                {
                      return cell[next_r1][next_c1];
                }
                else
                {
                    if(cell[next_r1][next_c1].isWhat != EMPTY) return cell[next_r1][next_c1];
                    else return cell[next_r1][next_c2];
                }
                break;
                
           case LEFT:
                next_c1 = (x - 1)/CELL_SIZE;
                next_r1 = y/CELL_SIZE;
                next_r2 = (y + height)/CELL_SIZE;
                if (cell[next_r1][next_c1].isWhat == EMPTY && cell[next_r2][next_c1].isWhat == EMPTY)
                {
                      return cell[next_r1][next_c1];
                }
                else
                {
                    if(cell[next_r1][next_c1].isWhat != EMPTY) return cell[next_r1][next_c1];
                    else return cell[next_r2][next_c1];
                }
                break;
           
           case RIGHT:
                next_c1 = (x + width + 1)/CELL_SIZE;
                next_r1 = y/CELL_SIZE;
                next_r2 = (y + height)/CELL_SIZE;
                if (cell[next_r1][next_c1].isWhat == EMPTY && cell[next_r2][next_c1].isWhat == EMPTY)
                {
                      return cell[next_r1][next_c1];
                }
                else
                {
                    if(cell[next_r1][next_c1].isWhat != EMPTY) return cell[next_r1][next_c1];
                    else return cell[next_r2][next_c1];
                }
                break;
                     
                
    }    
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that determines collision between two objects A and B
int collision(SDL_Rect objA, SDL_Rect objB)
{
    
    //dimension variables of the two objects colliding
    int leftA,rightA,topA,bottomA;
    int leftB,rightB,topB,bottomB;
    
    //initialize dimensions variables
    leftA= objA.x;
    rightA =objA.x + objA.w;
    topA = objA.y;
    bottomA = objA.y + objA.h;
    
    leftB= objB.x;
    rightB = objB.x + objB.w;
    topB = objB.y;
    bottomB = objB.y + objB.h;
    
    //see if the object A is above object  return  no collision if true
    if(bottomA < topB ) return false;
    
    //see if the object A is below object B return no collision if true
    if(topA > bottomB) return false;
    
    //see fi the object A is to the left of object B return no collision if true
    if(rightA < leftB) return false;
    
    //see if the object A is to the right of object B return no collsion if true
    if(leftA > rightB) return false;
   
   //finally if all conditions are met return true ie the collision has occured
    
    return true;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>MOVE THE PLAYER<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function move the specified player in the derection specified
int move_player(PLAYER *playerPtr,int Direction)
{

   //For looping
   int i=0;
   
   //Determine the player id
   int idd = playerPtr->id;
   
   //Clear out player previous image
   clear_image(playerPtr->dimension);

    //assign new direction to the player
   playerPtr->Direction = Direction;   
      
   //This loops checks the collision of given player with all other REMAINING players of the game
   //except itself.
   for(i=1;i<5;++i)
   {
        if(i != idd)
        {
            if(player[i].isActive)
            {
                if(check_player_collision(player[idd], player[i],Direction) == true)
                {
                    return 0;
                }
            }
                           //If the collsion is detected than stop moving the player
        }
   }
   
   //This parts checks the collision of player with wall or bricks and if no collsion is detected
   //than it moves the player in the given direction         
   if(check_collision(playerPtr->dimension,Direction).isWhat == EMPTY)                  
   {
            //verify the direction of movement and move accordingly
            switch(Direction)
            {
                case UP:
                    playerPtr->dimension.y -= PLAYER_SPEED;
                    break;
                case DOWN:
                    playerPtr->dimension.y += PLAYER_SPEED;
                    break;
                case RIGHT:
                    playerPtr->dimension.x +=PLAYER_SPEED;
                    break;
                case LEFT:
                    playerPtr->dimension.x -= PLAYER_SPEED;
                    break;
            }
   } 
    return 0;
 
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MOVE BULLET<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function moves the given bullet in the game
CELL move_bullet(BULLET *bulletPtr)
{
    //Temporary cell structure to determine which object is located infront of the bullet
    CELL temp_cell;
    //Determine the row and column of the object to check collision with
    int row,col;   
    
    //This variable has the number for the enemy with which the bullet had made collsion with
    int enemy_no =0;
    
    //This variable has the identification number of the bullet
    int idd = bulletPtr->id;
    
    //For looping
    int i=0;
    
    //This variable store the id of the team whose player has fired the bullet.
    //This is used to increment the team score when ever the bullet hits any object
    int team_idd = (idd == 1 || idd == 4)? 1 : 2;
    
    //Clear out the previous image of the bullet
    clear_image(bulletPtr->dimension);

    //get the object that is located right infront of the bullet in the direction in which the 
    //bullet is moving
    temp_cell = check_collision(bulletPtr->dimension,bulletPtr->Direction);
       
       //check what is infront of the bullet
       if(temp_cell.isWhat!=EMPTY)
       {
            //Get the row and col for the object
           row = temp_cell.dimension.y / CELL_SIZE;
           col = temp_cell.dimension.x / CELL_SIZE;
            
            //If  the object is a bricks
           switch(temp_cell.isWhat)
           {
                case BRICK:
                    
                //Increase the brick hit count by one
               ++brick[row][col].hits;
                           
                //check how many hits have the given brick suffered and if it is equal to three than
                //destroy the brick
               if(brick[row][col].hits == 3)
               {
                    //Increase the team score by wall points
                    team_score[team_idd] += WALL_POINT;
                    
                    //Set the location as vacant or empty
                   cell[row][col].isWhat= EMPTY;
                   
                   //Play the explosion sound for the wall explosion
                   if(sound)Mix_PlayChannel(-1,wall_explode,0);
                   
                   //play the explosion animation at the location of the brick
                   play_explosion(cell[row][col].dimension.x,cell[row][col].dimension.y);
                   
                   //finally clear all the images of explosion at the place of the object and 
                   //make it clear
                   clear_image(cell[row][col].dimension);
               }
               else     //If the bricks hits has not exceeded 3 hits than
               {
                    //Draw the cracking image for the bricks
                   draw_image(cracking,
                   screen,&crack[brick[row][col].hits-1],brick[row][col].dimension.x,brick[row][col].dimension.y);
               }
               break;
               
           case SEAL1:
           
                //call the seal_got_hit function with seal no 1 and given bullet's id.
                seal_got_hit(1,idd);          
                break;
                
           case SEAL2:
                     seal_got_hit(2,idd);
                     break;
           
           
           case ENEMY:
                    //Get the enemy no which has been hit to uniquely identify the enemy
                    enemy_no = get_enemy_no(cell[row][col]);
                    
                    //Increase the team's score with enemy points
                   team_score[team_idd] += ENEMY_POINT;
                   
                   //Set that location as empty now
                   cell[row][col].isWhat= EMPTY;
                   
                   //Play the explosion sound 
                   if(sound)Mix_PlayChannel(-1,wall_explode,0);
                   
                   //Play the explosion animation at the location of the enemy
                   play_explosion(cell[row][col].dimension.x,cell[row][col].dimension.y);
                   
                   //finally clear the enemy place with a blank image
                   clear_image(cell[row][col].dimension);
                   
                   //clear the trace of the enemy bullet too
                   clear_image(enemy[enemy_no].my_bullet.dimension);
                   
                   //deactivate the enemy's bullet
                   enemy[enemy_no].my_bullet.isActive = false;
                   
                   //finally deactivate the enemy also
                   enemy[enemy_no].isActive = false;
           break;
        }
           //Since now the bullet has been destroyed due to its collision with the wall or brick or seal
           // or enemy now we destroy the bullet itself
           //clear out the bullet image
           clear_image(bulletPtr->dimension);              
           
           //remove the bullet from the game screen and send it outside of the screen area
           bulletPtr->dimension.x =1300;
           bulletPtr->dimension.y =0;
           
           //finally deactivate the bullet
           bulletPtr->isActive=false;
           
           
           return temp_cell;
       }//Upto this point we have detected bullet collision with only BRICKS,WALL,SEAL and ENEMY
       
       //This loop checks bullet collision with other player bullets in the game except itself
       for(i=1;i<5;++i)
       {
            if(i!=idd)
            {
                //check for the collsion with other bullet
                if(collision(bulletPtr->dimension,bullet[i].dimension) == true)
                {
                    //Clear the bullet image if the collsion has been detected
                    clear_image(bulletPtr->dimension);              
                    
                    //clear other player bullet too               
                    clear_image(bullet[i].dimension);  
                    
                    //remove the bullet from the main game screen for both players
                    bulletPtr->dimension.x =1300;
                    bulletPtr->dimension.y =0;
                    bullet[i].dimension.x =1300;
                    bullet[i].dimension.y =0;
                    
                    //finally deativate both the bullets
                    bullet[i].isActive=false;
                    bulletPtr->isActive=false;
                }
            }
       }
       
   //move the bullet to new location
    switch(bulletPtr->Direction)
    {
        case UP:
            bulletPtr->dimension.y -= BULLET_SPEED;
            break;
        case DOWN:
            bulletPtr->dimension.y += BULLET_SPEED;
            break;
        case RIGHT:
            bulletPtr->dimension.x += BULLET_SPEED;
            break;
        case LEFT:
            bulletPtr->dimension.x -= BULLET_SPEED;
            break;
    }
    //The the image of the bullet in new location
    draw_image(bullet_image,screen,NULL,bulletPtr->dimension.x,bulletPtr->dimension.y);

        
    
    return temp_cell;   //move bullet function ends by returinng the object with which it collided
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ACTIVATE THE BULLET<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This is called when ever the player presses the bullet fire button
void activate_bullet(BULLET *bulletPtr, PLAYER which_player)
{
    //Assign the bullet the direction to be fired                 
    bulletPtr->Direction = which_player.Direction;
                   
    //Align the bullet to nozle of the tank
    bulletPtr->dimension.x =(bulletPtr->Direction == UP || bulletPtr->Direction == DOWN)? (which_player.dimension.x + PLAYER_WIDTH/2 -3) : which_player.dimension.x;
    bulletPtr->dimension.y =(bulletPtr->Direction == LEFT || bulletPtr->Direction == RIGHT)? (which_player.dimension.y + PLAYER_HEIGHT/2-3) : which_player.dimension.y;
                   
    //set the bullet on motion
    bulletPtr->isActive = true;   
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>CHECK PLAYER COLLSION<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function checks the collsion between the two players
int check_player_collision(PLAYER p1, PLAYER p2, int direction)
{
    //This switch case incease the player coordinates based on the direction of movement of the 
    //player
    switch(direction)
    {
        case UP:
            p1.dimension.y -=PLAYER_SPEED;
            break;

        case DOWN:
            p1.dimension.y +=PLAYER_SPEED;
            break;

        case LEFT:
            p1.dimension.x -=PLAYER_SPEED;
            break;

        case RIGHT:
            p1.dimension.x +=PLAYER_SPEED;
            break;

    }
    
    //This parts check the colliison between the two player and return true if the collsion is 
    //detected
    if(collision(p1.dimension,p2.dimension) == true) return true;
    
    //else return false indicating no collsion detected
    else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>PLAYER KILLED<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function is called whenever a player is hit by the bullet
int player_killed(PLAYER *playerPtr)
{
    //Get the player id which has been hit
    int idd = playerPtr->id;
    
    //Get the opponent team id which fired the bullet inorder to increase their score
    int opnt_idd = (idd == 1 || idd == 4)? 2 : 1;
    
    //Checks if the player has lives greater than one
    if((playerPtr->lives)>1)
    {
        //In that case increase the other teams score by the player points
        team_score[opnt_idd] += PLAYER_POINT;
        
        //derease the player lives by one
        playerPtr->lives -= 1;
          
         if(sound) Mix_PlayChannel(-1,player_killed_sound,0);
           
        //play the explosion animation for the player
        play_explosion_player(playerPtr->dimension.x,playerPtr->dimension.y,idd);
        
        //clear out the player image at the given location
        clear_image(playerPtr->dimension);
        
        //reset the location of the player based on the location of the player
        switch(idd)
        {
            case 1:     //reset player one location
                playerPtr->dimension.x = 20 * CELL_SIZE;
                playerPtr->dimension.y = 3 * CELL_SIZE;
                break;
                
            case 2:     //reset player two location
                playerPtr->dimension.x = 1 * CELL_SIZE;
                playerPtr->dimension.y = 3 * CELL_SIZE;
                break;
                    
            case 3:     //reset player two location
                playerPtr->dimension.x = 1 * CELL_SIZE;
                playerPtr->dimension.y = 7 * CELL_SIZE;
                break;
                
            case 4:     //reset player two location
                playerPtr->dimension.x = 20 * CELL_SIZE;
                playerPtr->dimension.y = 7 * CELL_SIZE;
                break;
        }
    }
    else            //Id the players has no more lives remaining then
    {
            //Increase the opponent team score by the player points
            team_score[opnt_idd] += PLAYER_POINT;
            
            //play the explosion animation at the player location
            play_explosion_player(playerPtr->dimension.x,playerPtr->dimension.y,2);
            
            //finally clear out the player image
            clear_image(playerPtr->dimension);

          //Then deactivate the player
            playerPtr->isActive = false;
      }
      if(player3_active == false && player4_active == false)
      {
            if(player[1].lives == 1 && player[2].lives == 1) new_level(current_level);
        }
        else
        {
            if(player[1].lives == 1 &&
               player[2].lives == 1 &&
               player[3].lives == 1 &&
               player[4].lives == 1 ) new_level(current_level);
        }
    
      update_scoreboard();

}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GET ACTIVE SLOT NO<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function returns the currently non active slot's number 
int get_active_slot()
{
    int i=0;
    //scan all the slots
    for(i=0;i<TOTAL_NO_SLOT;++i)
    {
        //check if the particular slot is active or not
        //If not active then return the slot no
        if(explosion_slot[i].isActive == false) return i;
    }
    
    //else return the slot no 0 by default
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ACTIVATE SLOT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function activates the given slot to play the explosion animation

int activate_slot(int slot_no,int x,int y)
{
    //Set the location where to play the explosion animation
    explosion_slot[slot_no].location.x = x;
    explosion_slot[slot_no].location.y = y;
    
    //finally activate the slot to play the explosion
    explosion_slot[slot_no].isActive = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEACTIVATE SLOT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function deactivates the slot after it has completed playing the explosion animation

int deactivate_slot(int slot_no)
{
    //Set the explsoion frame number to  0
    explosion_slot[slot_no].count = 0;
    
    //move the slot out of the screen
    explosion_slot[slot_no].location.x = 1300;
    explosion_slot[slot_no].location.y = 0;
    
    //Give the default dimension to the slot
    explosion_slot[slot_no].location.w = 50;
    explosion_slot[slot_no].location.h = 50;
    
    //finally deactivate the slot
    explosion_slot[slot_no].isActive = false;

}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>SEAL GOT HIT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function is called whenever particular seal is hit by the bullet

void seal_got_hit(int seal_no, int ide)
{
    //Variable to store the location of the seal that has been hit
    int row,col;
    
    //Check which teams and which player bullet has hit which seal
    switch(ide)
    {
            //This is the case for team 1 hitting the seal
            case 1:             //Player 1
            case 4:             //PLayer 4
            
                //This switch case which seal has been hit by the team 1
                switch(seal_no)
                {
                    //team 1 has hit their own seal
                    case 1:             //Seal 1
                        
                        //Get the location of the seal
                        row = seal[1].dimension.y / CELL_SIZE;
                        col = seal[1].dimension.x / CELL_SIZE;
                        
                        //Increase the seal hit count by 1
                        ++seal[1].hits;
                        
                        //Checks if the seal has been hit 3 times
                        if(seal[1].hits == 3)
                        {
                            //In that case set that place as empty
                            cell[row][col].isWhat = EMPTY;
                            
                            //play explosion sound
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            
                            //Play the explosion animation at the place
                            play_seal_explosion((col-1)*50,(row-1)*50);
                             
                            //record the event in the game log file
                            gameLog("SEAL 1 destroyed by team 1...");
                            
                            //wait for sometime
                            SDL_Delay(2000);
                            
                            //restart the same level
                            new_level(current_level);
                        } 
                        else    //If seals hits is less than 3 then
                        {
                            //Draw the cracking image at the seal location
                            draw_image(cracking,
                            screen,&crack[seal[1].hits-1],seal[1].dimension.x,seal[1].dimension.y);
                        }
    
                        break;
                        
                    //If team one hit other teams seal than        
                    case 2:
                        
                        //get the location of the seal
                        row = seal[2].dimension.y / CELL_SIZE;
                        col = seal[2].dimension.x / CELL_SIZE;
                        
                        //increase the seal hits count by one
                        ++seal[2].hits;
                        
                        //check if the seal has been hit 3 times 
                        if(seal[2].hits == 3)
                        {
                            //increase team1 score by the seal points
                            team_score[1] += SEAL_POINT;
                            
                            //set the seal location as empty
                            cell[row][col].isWhat = EMPTY;
                            
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            
                            //play the eplosion animation at the location of the seal
                             play_seal_explosion((col-1)*50,(row-1)*50);
                            
                            //wait for some time
                            SDL_Delay(2000);
                            
                            //record the event on the game log
                            gameLog("SEAL 2 destroyed by team 1...");
                            
                            //increase the new level
                            ++current_level;
                            
                            //load the new level
                            new_level(current_level);
                        }
                        else        //If the hits is less than 3 then
                        {
                            //Draw the cracking image at the location of the seal
                            draw_image(cracking,
                            screen,&crack[seal[2].hits-1],seal[2].dimension.x,seal[2].dimension.y);
                        }
                        break;
                }
                break;
                
        //This is the case for the bullet fired by team 2 and the process is same as above
        case 2:
        case 3:
            
                switch(seal_no)
                {
                    case 2:
                        
                        row = seal[2].dimension.y / CELL_SIZE;
                        col = seal[2].dimension.x / CELL_SIZE;
                            
                        ++seal[2].hits;

                        if(seal[2].hits == 3)
                        {
                            
                            cell[row][col].isWhat = EMPTY;
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            play_seal_explosion((col-1)*50,(row-1)*50);
                            gameLog("SEAL 2 destroyed by team 2...");
                            SDL_Delay(2000);
                            new_level(current_level);
                        } 
                        else
                        {
                            draw_image(cracking,
                            screen,&crack[seal[2].hits-1],seal[2].dimension.x,seal[2].dimension.y);
                        }
    
                        break;
        
                    case 1:
                        
                        row = seal[1].dimension.y / CELL_SIZE;
                        col = seal[1].dimension.x / CELL_SIZE;
                        
                        ++seal[1].hits;
                        if(seal[1].hits == 3)
                        {
                            team_score[2] += SEAL_POINT;
                            cell[row][col].isWhat = EMPTY;
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            play_seal_explosion((col-1)*50,(row-1)*50);
                            SDL_Delay(2000);
                            gameLog("SEAL 1 destroyed by team 2...");
                            ++current_level;
                            new_level(current_level);
                        }
                        else
                        {
                            draw_image(cracking,
                            screen,&crack[seal[1].hits-1],seal[1].dimension.x,seal[1].dimension.y);
                        }
                        break;
                }
                break;
                
        //In case enemy bullet hits the seal
        case 0:
            
                switch(seal_no)
                {
                    case 2:
                        
                        row = seal[2].dimension.y / CELL_SIZE;
                        col = seal[2].dimension.x / CELL_SIZE;
                            
                        ++seal[2].hits;

                        if(seal[2].hits == 3)
                        {
                            
                            cell[row][col].isWhat = EMPTY;
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            play_seal_explosion((col-1)*50,(row-1)*50);
                            gameLog("SEAL 2 destroyed by enemy bullet...");
                            SDL_Delay(2000);
                            new_level(current_level);
                        } 
                        else
                        {
                            draw_image(cracking,
                            screen,&crack[seal[2].hits-1],seal[2].dimension.x,seal[2].dimension.y);
                        }
    
                        break;
        
                    case 1:
                        
                        row = seal[1].dimension.y / CELL_SIZE;
                        col = seal[1].dimension.x / CELL_SIZE;
                        
                        ++seal[1].hits;
                        if(seal[1].hits == 3)
                        {
                            cell[row][col].isWhat = EMPTY;
                            if(sound) Mix_PlayChannel(-1,seal_explosion_sound,0);
                            play_seal_explosion((col-1)*50,(row-1)*50);
                            SDL_Delay(2000);
                            gameLog("SEAL 1 destroyed by enemy bullet...");
                            new_level(current_level);
                        }
                        else
                        {
                            draw_image(cracking,
                            screen,&crack[seal[1].hits-1],seal[1].dimension.x,seal[1].dimension.y);
                        }
                        break;
                }
                break;
            
    }
    
   
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>OPERATE ENEMY<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function operates the enemy in the game
int operate_enemy(ENEMYY *enemyPtr)
{
    //check is the enemy bullet is active or not
   if(enemyPtr->my_bullet.isActive == true)
   {
        //if active then move the enemy bullet
        move_enemy_bullet(&(enemyPtr->my_bullet),enemyPtr->id);
   }
   else
   {    
        //if not active than rotate the enemy anticlock wise
        --enemyPtr->direction;
        if(enemyPtr->direction < 0 )
        {
            //if rotation is complete than reset the location of enemy
            enemyPtr->direction = 4;
        }
            //assign the enemy bullet the direction the enemy
            enemyPtr->my_bullet.Direction = enemyPtr->direction;
            
            //align the enemy bullet according the the direction assigned to it
            switch(enemyPtr->my_bullet.Direction)
            {
                case ENEMY_UP:
                    enemyPtr->my_bullet.dimension.x = enemyPtr->dimension.x + 25;
                    enemyPtr->my_bullet.dimension.y = enemyPtr->dimension.y;
                    break;

                case ENEMY_DOWN:
                    enemyPtr->my_bullet.dimension.x = enemyPtr->dimension.x + 25;
                    enemyPtr->my_bullet.dimension.y = enemyPtr->dimension.y + 15;
                    break;

                case ENEMY_LEFT:
                    enemyPtr->my_bullet.dimension.x = enemyPtr->dimension.x;
                    enemyPtr->my_bullet.dimension.y = enemyPtr->dimension.y + 25;
                    break;

                case ENEMY_RIGHT:
                    enemyPtr->my_bullet.dimension.x = enemyPtr->dimension.x + 15;
                    enemyPtr->my_bullet.dimension.y = enemyPtr->dimension.y+ 25;
                    break;
                     
            }       
             
             if(sound) Mix_PlayChannel(-1,bullet_fire_sound,0);  
            //set the bullet on motion
            enemyPtr->my_bullet.isActive = true;   
        
   }
   
   //finally draw the enemy image
   draw_image(enemy_image[enemyPtr->direction],screen,NULL,enemyPtr->dimension.x,enemyPtr->dimension.y);   
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MOVE ENEMY BULLET<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This function moves the enemy bullet only.

int move_enemy_bullet(BULLET *bulletPtr, int enemy_id)
{
    CELL temp_cell;                             //A temporary cell structure variable
    int row,col,i=0;                            //variables to hold rows and cols information
    int other_enemy_no =0;                      //Determine other enemy no
    int direct;                                 //Direction variable

    //Wipe out old image
    clear_image(bulletPtr->dimension);
    
    //Check for the direction to move and assign the direction variable appropriate value
    switch(bulletPtr->Direction)
    {
        case ENEMY_UP:
            direct = UP;
            break;
            
        case ENEMY_DOWN:
            direct = DOWN;
            break;
            
        case ENEMY_RIGHT:
            direct = RIGHT;
            break;
            
        case ENEMY_LEFT:
            direct = LEFT;
            break;
    }
    
   //move the bullet to new location
    if(direct==UP) bulletPtr->dimension.y -= BULLET_SPEED;
    if(direct==DOWN) bulletPtr->dimension.y += BULLET_SPEED;
    if(direct==LEFT) bulletPtr->dimension.x -= BULLET_SPEED;
    if(direct==RIGHT) bulletPtr->dimension.x += BULLET_SPEED;

    //draw image of bullet at new location
    draw_image(bullet_image,screen,NULL,bulletPtr->dimension.x,bulletPtr->dimension.y);

    //check of the collision of the bullet
    temp_cell = check_collision(bulletPtr->dimension,direct);
       //check if the bullet has made collision or not
       if(temp_cell.isWhat!=EMPTY)
       {
            //if collision is made
            //get row and col information for the object colliding with the bulet
           row = temp_cell.dimension.y / CELL_SIZE;
           col = temp_cell.dimension.x / CELL_SIZE;

            //determine with what the bullet has made collision with
           switch(temp_cell.isWhat)
           {
                //collision with the brick
                case BRICK:
           
                    ++brick[row][col].hits;
                    
                    //destroy the brick if it has made more the three hits
                    if(brick[row][col].hits == 3)
                    {
                        cell[row][col].isWhat= EMPTY;
                        if(sound)Mix_PlayChannel(-1,wall_explode,0);
                        play_explosion(cell[row][col].dimension.x,cell[row][col].dimension.y);
                        clear_image(cell[row][col].dimension);
                    }
                    else
                    {
                        //else paste the cracking image over the brick
                        draw_image(cracking,
                        screen,&crack[brick[row][col].hits-1],brick[row][col].dimension.x,brick[row][col].dimension.y);
                    }
                    break;
                    
                case SEAL1:
                    //collision with the seal 1
                    seal_got_hit(1,0);
                    break;
                case SEAL2:
                    
                    //collision with seal 2
                    seal_got_hit(2,0);
                    break;
                    
                case ENEMY:
                    //collision with other enemy
                    
                    //get other enemy id no
                        other_enemy_no = get_enemy_no(temp_cell);
                        
                    //if the id of enemy doesnt match with the enemy firing the bullet
                    //wipe out the bullet 
                       if(enemy[other_enemy_no].id != enemy_id)
                        {
                            
                            clear_image(bulletPtr->dimension);              
                            bulletPtr->dimension.x =1300;
                            bulletPtr->dimension.y =0;
                            bulletPtr->isActive=false;
                            bulletPtr->isActive = false;
                        
                        }
                        return 0;
                    break;
                
            } 
            //Since the bullet has made collision
            //remove the bullet after the collision is made
            clear_image(bulletPtr->dimension);              
            bulletPtr->dimension.x =1300;
            bulletPtr->dimension.y =0;
            bulletPtr->isActive=false;
            bulletPtr->isActive = false;
            return 0;
       }
       for(i=1;i<5;++i)
       {
            //check to see if the bullet has made collision with players bullet
            if(bullet[i].isActive)
            {
                //if true that remove both the bullets
                if(collision(bulletPtr->dimension,bullet[i].dimension) == true)
                {
                    clear_image(bulletPtr->dimension);              
                    clear_image(bullet[i].dimension);  
                    bulletPtr->dimension.x =1300;
                    bulletPtr->dimension.y =0;
                    bullet[i].dimension.x =1300;
                    bullet[i].dimension.y =0;
                          
                    bullet[i].isActive=false;
                    bulletPtr->isActive=false;
                }
            }
            //check to see if the bullet has made collision with a player
            if(player[i].isActive)
            {
                //if true that kill the player and remove the bullet
                if(collision(bulletPtr->dimension,player[i].dimension) == true)
                {
                    player_killed(&player[i]);
                    clear_image(bulletPtr->dimension);              
                    bulletPtr->dimension.x =1300;
                    bulletPtr->dimension.y =0;
                    bulletPtr->isActive=false;
                
                }
            }
       }
       
       
        
    //verify the direction of movement and move accordingly
    return 0;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>GET ENEMY NO<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//This funtion return the enemy number present in the given cell
int get_enemy_no(CELL cell)
{
    //Get x and y cordinates of the cell
    int x = cell.dimension.x;
    int y = cell.dimension.y;
    
    //Loop
    int i=0;
    for(i=0;i<5;++i)
    {   
        //Check each enemy coordinates with given x and y coordinates
        //if coordinates match then return the enemy number i
        if(enemy[i].dimension.x == x && enemy[i].dimension.y == y) return i;
    }
    
    //by default return enemy number 0
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
