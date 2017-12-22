#include "LedControlMS.h"
//GLOBAL VARIABLES
//too use with the button
int button_1;
int button_2;
int player_pos;
long game_speed;
//game loop variable
bool checker;
int enemy_level;
int score;
unsigned long game_time;
//byte values for enemy movement
byte enemy_bytes[]= 
  {
  //2 long enemies
  B00000011,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B11000000,
  //3 long enemies
  B00000111,
  B00001110,
  B00011100,
  B00111000,
  B01110000,
  B11100000,
  };
byte enemy_byte_clear;
//enemy initializes for random enemy spawning
int enemy_byte_random;

//set the LEDControl Variable to be using a single led matrix
//first three parameters are the pins connected to the arduino and then the number of led matrices 
LedControl lc = LedControl(12,11,10,1);

void setup() {
  randomSeed(analogRead(0));
  //setting up variables
  button_1 = 7;
  button_2 = 4;
  player_pos = 3;
  game_speed = 150;
  checker = true;
  enemy_level = 7;
  score = 0;
  enemy_byte_clear = B00000000;
  game_time = 0;
  //set up button input
  pinMode(button_1,INPUT);
  pinMode(button_2,INPUT);
  Serial.begin(9600);
  Serial.println("setup");
  //wake up led matrix
  lc.shutdown(0,false);
  //brightness at medium
  lc.setIntensity(0,8);
  //clear the display
  lc.clearDisplay(0);
  //setled arguments (coordinates(only rightmost (x,y) and true)
  //set up first random enemy
  enemy_byte_random = random(0,13);
  calibration();
}

  //MAIN GAME LOOP
void loop() {
  while (checker){
  
  //PLAYER INPUT 
  right_input();
  left_input();
  
  //MOVE ENEMIES
  move_enemies();
  
  //COLLISION TESTING
  collision(); 
  
  //MAKE GAME GO FASTER
  game_speed_up();
  
  //end of  MAIN WHILE loop
    }
    
  if (digitalRead(button_1) == HIGH){
    setup();
  }
  if (digitalRead(button_2) == HIGH){
    setup();
  }
 //end of void loop
}
void game_over(){ 
  String score_show = String(score);
  lc.writeString(0,"Score  ");

  //testing!
  /*for (char x = '1'; x<= '9'; ++x){
    for (int i = 0; i<score_show.size(); ++i){
      if (score_show.at(i) == x){
        lc.writeString
      }
    }
  }
  
  */
  if (score > 30){
    lc.writeString(0," Best ");
  }
  else if (score > 20){
    lc.writeString(0," Good ");
  }
  else if(score > 10){
    lc.writeString(0," Ok ");
  }
  else{
    lc.writeString (0, " Bad  " );
  }
  //lc.writeString(0,);
  lc.writeString(0,"Game ");
  
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
  /*
  //put in delay for when starting up the game
  int empty= '?';
  while(empty == '?'){
    if (digitalRead(button_1) == HIGH){
      empty = '!';
    }
    if (digitalRead(button_1) == HIGH){
      empty = '!';
    }
    //end of delay while loop 
  }
  */
  lc.setLed(0,player_pos,0,true);
  //end of calibration
}
//right input
  void right_input(){
    if (digitalRead(button_1) == HIGH){
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
  }
void left_input(){
  if (digitalRead(button_2) == HIGH){
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
}
void collision(){
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
    else if (enemy_bytes[enemy_byte_random] == B00000111 && (player_pos == 5 || player_pos == 6 || player_pos == 7)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00001110 && (player_pos == 4 || player_pos == 5 || (player_pos == 6))){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00011100 && (player_pos == 3 || player_pos == 4 || player_pos == 5)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B00111000 && (player_pos == 2 || player_pos == 3 || player_pos == 4)){
      game_over();
      checker = false;
    }   
    else if (enemy_bytes[enemy_byte_random] == B01110000 && (player_pos == 1 || player_pos == 2 || player_pos == 3)){
      game_over();
      checker = false;
    }
    else if (enemy_bytes[enemy_byte_random] == B11100000 && (player_pos == 0 || player_pos == 1 || player_pos == 2)){
      game_over();
      checker = false;
    }
    //end of collision testing
  }
}
void game_speed_up()
  {
  //increase game_speed based on time elapsed
  if (game_time % 20 == 0){
    game_speed = game_speed - 10;
  }
  if (game_speed < 55){
    game_speed = 55;
  }
  game_time ++;
  }
void move_enemies(){
  //Moving enemies

  //seting up the led enemy with random 
  lc.setColumn(0,enemy_level,enemy_bytes[enemy_byte_random]);
  lc.setLed(0,player_pos,0,true);
  //NEED THIS TO DECIDE GAME SPEED (delay between moving enemies 
  delay(game_speed);
  lc.setColumn(0,enemy_level,enemy_byte_clear);
  enemy_level --;
  //WHEN ENEMY OBJECTS GO OFF SCREEN HAVE THIS
  if (enemy_level < 0){
    enemy_level = 7;
    //make a new random enemy
    enemy_byte_random = random(0,13);
    score ++;
  }
}
//TO DO LIST
//ADD MORE GAMES
