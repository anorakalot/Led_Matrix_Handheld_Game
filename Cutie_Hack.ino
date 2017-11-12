#include <SimpleTimer.h>

#include <LiquidCrystal.h>

#include "LedControlMS.h"

#define NBR_MTX 1

LiquidCrystal lcd(13,9,6,8,3,2);

//too use with the button
int led_input_1;
int led_input_2;

int player_pos;
long game_speed;
//game loop variable
bool checker;

int enemy_level;

int score;

int game_time;

//byte values for enemy movement
byte enemy_bytes[]= 
  {
  B00000011,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B11000000,
  };

byte enemy_byte_clear;


//enemy initializes for random enemy spawning
int enemy_byte_random;

//making arduino timer
//SimpleTimer timer;




//set the LEDControl Variable to be using a single led matrix
LedControl lc = LedControl(12,11,10,1);

void setup() {
  randomSeed(analogRead(0));
  //LedControl lc = LedControl(12,11,10,NBR_MTX);
  
  //TESTING LCD SCREEN
  lcd.begin(16, 2);
  lcd.print("Hello World!");

  //setting up variables
  led_input_1 = 7;
  led_input_2 = 4;
  player_pos = 3;
  game_speed = 150;
  checker = true;
  enemy_level = 7;
  score = 0;
  enemy_byte_clear = B00000000;

  //set timers for increasing game speed
  //timer.setInterval(100,game_speed_increase(game_speed));

  //set up button input
  pinMode(led_input_1,INPUT);
  pinMode(led_input_2,INPUT);
  

  
  //LedControl lc = LedControl(12,11,10,NBR_MTX);
  Serial.begin(9600);
  Serial.println("setup");
  //wake up led matrix
  lc.shutdown(0,false);
  //brightness at medium
  lc.setIntensity(0,8);
  //clear the display
  lc.clearDisplay(0);
  //delay(600);
  //setled arguments (coordinates(only rightmost (x,y) and true)
  
  
  
  enemy_byte_random = random(0,7);

  calibration();
  //loop();
}

  
void calibration(){
  //calibration

  lc.setLed(0,0,0,true);
  delay(100);

  lc.setLed(0,0,7,true);
  delay(100);

  lc.setLed(0,7,0,true);
  delay(100);
  
  lc.setLed(0,7,7,true);
  delay(100);

  lc.setLed(0,0,0,false);
  delay(100);

  lc.setLed(0,0,7,false);
  delay(100);

  lc.setLed(0,7,0,false);
  delay(100);
  
  lc.setLed(0,7,7,false);
  delay(100);  
  //calibration ends
  Serial.println("Calibration ends");
  lc.setLed(0,player_pos,0,true); 

}





void loop() {
  
  //game loop
  //lc.setLed(0,player_pos,0,true);
  //lc.setLed(

  while (checker){
  //PLAYER INPUT CASES
  //move player right
  if (digitalRead(led_input_1) == HIGH){
    //out of bounds checking
    if (player_pos + 1 >7){
      NULL;
    }
    else{
    lc.setLed(0,player_pos,0,false);
    player_pos ++;
    lc.setLed(0,player_pos,0,true);
    }
  }

  //move player left
  if (digitalRead(led_input_2) == HIGH){
    //out of bounds checking
    if (player_pos - 1 < 0){
      NULL;
    }
    else{
    lc.setLed(0,player_pos,0,false);
    player_pos --;
    lc.setLed(0,player_pos,0,true);
    }
  }
  
 
  
  //Moving enemies and checking for collision
  
  
  lc.setColumn(0,enemy_level,enemy_bytes[enemy_byte_random]);
  lc.setLed(0,player_pos,0,true);
  //NEED THIS TO DECIDE GAME SPEED
  delay(game_speed);
  lc.setColumn(0,enemy_level,enemy_byte_clear);
  enemy_level --;
  
  //WHEN ENEMY OBJECTS GO OFF SCREEN HAVE THIS
  if (enemy_level < 0){
    enemy_level = 7;
    enemy_byte_random = random(0,7);
    score ++;
  }

  //COLLISION TESTING
  if (enemy_level == 0){
    
    if (enemy_bytes[enemy_byte_random] == B00000011 && (player_pos == 6 || player_pos == 7)){
      game_over();
      checker = false;
    }  
    else if (enemy_bytes[enemy_byte_random] == B00000110 && (player_pos == 5 || player_pos == 6)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00001100 && (player_pos == 4 || player_pos == 5)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00011000 && (player_pos == 3 || player_pos == 4)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00110000 && (player_pos == 2 || player_pos == 3)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B01100000 && (player_pos == 1 || player_pos == 2)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B11000000 && (player_pos == 0 || player_pos == 1)){
      game_over();
      checker = false;
    }
    //end of collision testing
  }

  game_time = millis() % 100;
  if (game_time == 0){
    game_speed -= 10;
  }
  /*
  if (game_time > 50000){
    game_speed = 30;
    }
    
   else if (game_time > 40000){
    game_speed = 50;
   }
   else if (game_time > 30000){
    game_speed = 75;
   }
   else if (game_time > 20000){
    game_speed = 90;
   }
   else if (game_time > 10000){
    game_speed = 115;
   }
   
   
   
   if (game_time > 3000){
    game_speed = 40;
   }
*/
    //end of while loop
  }
  
  if (digitalRead(led_input_1) == HIGH){
    setup();
  }
  if (digitalRead(led_input_2) == HIGH){
    setup();
  }
 //end of void loop
}


void game_over(){
  lc.writeString(0,"Game Over");
}

//TO DO LIST
//DETECT COLLISION CHECK!!! 
//RANDOM WORKS CHECK!!!!!
//REDO OPTION
//USE LCD SCREEN


//STRECTCH GOALS
//POLISH
