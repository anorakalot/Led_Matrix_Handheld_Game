#include "LedControlMS.h"
LedControl lc = LedControl(12,11,10,1);
//GLOBAL VARIABLES
int player_pos_y= 0;
int player_pos_x = 1;
bool runner = true;
int enemy_1_y = 1;
int enemy_1_x = 7;
int enemy_2_y = 0;
int enemy_2_x = 12;
int jump_button = 9;
int counter = 1;
int game_speed = 90;
void setup() {
  lc.shutdown(0,false);
  //brightness at medium
  lc.setIntensity(0,8);
  //clear the display
  lc.clearDisplay(0);
  pinMode(jump_button,INPUT);
}
//setled variables (idk,x,y,true);

void loop() {
  counter = 0;
   while(runner){
  // put your main code here, to run repeatedly:
  lc.setLed(0,player_pos_x,player_pos_y,true);

  //PLAYER MOVEMENT
  //IF BUTTON IS PRESSED
  if (digitalRead(jump_button) == HIGH){
    lc.setLed(0,player_pos_x,player_pos_y,false);  
    player_pos_y =1;
    lc.setLed(0,player_pos_x,player_pos_y,true);
  }  
  else{
  lc.setLed(0,player_pos_x,player_pos_y,false);
  player_pos_y = 0;
  lc.setLed(0,player_pos_x,player_pos_y,true);
  }
  
  //ENEMY MOVEMENT
  if (counter % game_speed == 0){
    lc.setLed(0,enemy_1_x,enemy_1_y,false);
    enemy_1_x -= 1;
    if (enemy_1_x == -1){
      enemy_1_y = rand()%2;
      enemy_1_x = 10+rand()%(20-10+1);
    }
    lc.setLed(0,enemy_1_x,enemy_1_y,true);
  }
/*
  if (counter % 70 == 0){
    lc.setLed(0,enemy_2_x,enemy_2_y,false);
    enemy_2_x -= 1;
    if (enemy_2_x == -1){
      enemy_2_x =  + rand()% (22-15+1);
    }
    lc.setLed(0,enemy_2_x,enemy_2_y,true);
  }
  */
  
  //COLLISION
  if (enemy_1_x == player_pos_x && enemy_1_y == player_pos_y){
  game_over();
  runner = false;  
  }
  /*
  if (enemy_2_x == player_pos_x && enemy_2_y == player_pos_y){
  game_over();
  runner = false;  
  }
  */
  
  counter ++;
  //GAME SPEED CHANGES
  if (counter % 4000 == 0){
  if (game_speed > 50){
    game_speed -=10;
  }
    else{
      game_speed = 50;
    }
  }

  //end of while loop
  }
  
  //outside main game while loop
   if (digitalRead(jump_button) == HIGH){
    runner = true;
   }
}

void game_over(){
  lc.writeString(0,"Game over");
}

//add enemis that you have to jump and stay still for
//make it so it gets faster when time goes past
