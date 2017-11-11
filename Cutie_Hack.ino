#include "LedControlMS.h"
#define NBR_MTX 1
//too use with the button
int led_input_1 = 7;
int led_input_2 = 4;

int player_pos = 0;

//game loop variable
bool checker = true;

int enemy_level = 7;


//byte values for enemy movement
byte enemy_bytes[] = 
{
B00000011,
B00000110,
B00001100,
B00011000,
B00110000,
B01100000,
B11000000,
};

byte enemy_byte_clear = B00000000;

//enemy initializes
int enemy_byte_random;

//seeding random



//set the LEDControl Variable to be using a single led matrix
LedControl lc = LedControl(12,11,10,1);

void setup() {
  randomSeed(analogRead(0));
  //LedControl lc = LedControl(12,11,10,NBR_MTX);
 
  //set up button input
  pinMode(led_input_1,INPUT);
  pinMode(led_input_2,INPUT);
  

  //enemy setups


  
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
  //NEED THIS
  delay(100);
  
  lc.setColumn(0,enemy_level,enemy_byte_clear);
  
  enemy_level --;
  //WHEN ENEMY OBJECTS GO OFF SCREEN HAVE THIS
  if (enemy_level < 0){
    enemy_level = 7;
    enemy_byte_random = random(0,7);
  }

  //COLLISION TESTING
  
  if (enemy_level == 1){
    
    if (enemy_bytes[enemy_byte_random] == B00000011 && player_pos == 6 || player_pos == 7){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00000110 && player_pos == 5 || player_pos == 6){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00001100 && player_pos == 4 || player_pos == 5){
      game_over();
      checker = false;
    }

    else if (enemy_bytes[enemy_byte_random] == B00011000 && player_pos == 3 || player_pos == 4){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00110000 && player_pos == 2 || player_pos == 3){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B01100000 && player_pos == 1 || player_pos == 2){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B11000000 && player_pos == 0 || player_pos == 1){
      game_over();
      checker = false;
    }

    //end of collision testing
  }
  
    //end of while loop
  }
  
 //end of void loop
}


void game_over(){
  lc.writeString(0,"Game Over");
 
}

//TO DO LIST
//DETECT COLLISION CHECKMATE 
//

//STRECTCH GOALS
//POLISH

