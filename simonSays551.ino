#include <NewhavenLCDSerial.h>
/*************************************************
* Public Constants
*************************************************/
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 5

#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_3 8
#define BUTTON_4 9

#define BUZZER  10

int ROUNDS_TO_WIN = 8;  //Controls Number of rounds (elements in sequence)
int WAIT_TIME = 3000; // Wait Time for User entry
int playSpeed = 150; // Speed of playback of sequence: less value means faster and hence tougher

NewhavenLCDSerial lcd(11);

byte gameBoard[32]; // Moves Array
byte gameRound = 0; // Keeps track of current round
int rows = 2;      // number of rows
int cols = 16;     // number of columns
char letter;

// Array for Game Load Graphics
int initLine0[16] = {255, 255, ' ', 'S', 'i', 'm', 'o', 'n', ' ', 'S', 'a', 'y', 's', ' ', 255, 255};
int initLine1[16] = {255, 255, 255,  ' ', 'B', 'y', ' ', 'A', 'n', 'a', 'y', ' ', ' ', 255, 255,255};


void setup() {
  // put your setup code here, to run once:
lcd.clear();
lcd.setContrast(38);
lcd.setBrightness(4);


  //Enable pull ups on inputs
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  pinMode(BUZZER, OUTPUT);

 
  lcd.clear();
  
  
}

void loop() {

game_init();
waitForStart();


}


void game_init() {

// Game Start Animation - Splash Screen
 
    for (int j = 0; j<cols; j++) {
      lcd.setCursor(0,j);
      lcd.write(initLine0[j]);
      lcd.setCursor(1,j);
      lcd.write(initLine1[j]);
      delay(50);
     
      //lcd.clear();
    }
    initMusic();
delay(500);

    for(int i=0; i<3; i++)
    {lcd.clear();
    delay(100);
    display_intro();
    delay(100);}
  
}

void display_intro()
{
//Supplement to Game Start Animation
  
   for (int j = 0; j<cols; j++) {
      lcd.setCursor(0,j);
      lcd.write(initLine0[j]);
      lcd.setCursor(1,j);
      lcd.write(initLine1[j]);
      
      //lcd.clear();
    }
  }
void waitForStart(void)
{
// Waits for user entry to select game mode.
  lcd.clear();

  lcd.setCursor(0,0);
      lcd.print("Level:   1:Easy");
      lcd.setCursor(1,0);
      lcd.print("2.Medium 3:Hard");

      long startTime = millis(); 
// Changes value for the 3 parameters based on user choice.
  while ( (millis() - startTime) < 600000)

  {
     int diffi = wait_for_input();
        switch(diffi){
          case 1:
           ROUNDS_TO_WIN = 8;
 WAIT_TIME = 3000;
 playSpeed = 150;
break;
case 2:
 ROUNDS_TO_WIN = 12;
 WAIT_TIME = 2500;
playSpeed = 100;
break;
case 3:
 ROUNDS_TO_WIN = 16;
 WAIT_TIME = 2000;
 playSpeed = 75;
break;
}
         if(diffi == 1 || diffi == 2 || diffi == 3) 
  {
    delay(200);
if (play_memory() == true) 
      {
       play_winner(); // Player Won!
      break;
      }
    else 
      play_loser(); // Player lost :(
      break;
      
 

}
  }

}

 void play_winner()
 {
   lcd.clear();    
      lcd.setCursor(0,0);      // row 0, column 5
      lcd.print("CONGRATULATIONS");    // display text
      lcd.setCursor(1,3);      // row 0, column 5
      lcd.print("=)  YOU WON!  =)");    // display text
      playWinTune(); // Win Tune - Star WARS!
  }

void play_loser(void)
{
  //Function to take care of incorrect moves
 lcd.clear();
 lcd.setCursor(0,0);      
      lcd.print("   Wrong Move   ");    
      lcd.setCursor(1,0);      
      lcd.print(":( TRY AGAIN!");    
    
 tone(BUZZER, NOTE_C2);
 delay(2000);
 noTone(BUZZER);
 delay(200);
 
 }

void playWinTune(void)

{
//Star Wars Tone
 tone(BUZZER, NOTE_C4);
 delay(1000);
 tone(BUZZER, NOTE_G4);
 delay(1000);
 tone(BUZZER, NOTE_F4);
 delay(250);
 tone(BUZZER, NOTE_E4);
 delay(250);
 tone(BUZZER, NOTE_D4);
 delay(250);
 tone(BUZZER, NOTE_C5);
 delay(1000);
 tone(BUZZER, NOTE_G4);
 delay(500);
 tone(BUZZER, NOTE_F4);
 delay(250);
 tone(BUZZER, NOTE_E4);
 delay(250);
 tone(BUZZER, NOTE_D4);
 delay(250);
 tone(BUZZER, NOTE_C5);
 delay(1000);
 tone(BUZZER, NOTE_G4);
 delay(500);
 tone(BUZZER, NOTE_F4);
 delay(250);
 tone(BUZZER, NOTE_E4);
 delay(250);
 tone(BUZZER, NOTE_F4);
 delay(250);
 tone(BUZZER, NOTE_D4);
 delay(2000);
  
 noTone(BUZZER);

 delay(250);
 
  }


void initMusic()
{
  // Game Start Music
  // notes in the melody: 
  int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4}; 
// note durations: 4 = quarter note, 8 = eighth note, etc.: 
  int noteDurations[] = {4, 8, 8, 4,4,4,4,4 }; 


  for (int thisNote = 0; thisNote < 8; thisNote++) { 
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(BUZZER, melody[thisNote],noteDuration); 
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
    
  
  }

}
  byte checkButton(void)
{
  if (digitalRead(BUTTON_1) == 0) return(1); 
  else if (digitalRead(BUTTON_2) == 0) return(2); 
  else if (digitalRead(BUTTON_3) == 0) return(3); 
  else if (digitalRead(BUTTON_4) == 0) return(4);

  return(0);
}

byte wait_for_button(void)
{
  long startTime = millis(); 

  while ( (millis() - startTime) < WAIT_TIME) // Loop until wait time to wait for user input
  {
    byte button = checkButton();

    if (button != 0)
    { 
      toner(button, 150); // Play tone for pressed button

      while(checkButton() != 0) ;  // Waiting for user to release button

      delay(10); // Debouncing

      return button;
    }

  }
  
   return 0; // User timed out
}

byte wait_for_input(void)
{
// An alternate method similar to wait_for_button method above but without the constraint of wait time

  while (1) 
  {
    byte button = checkButton();

    if (button != 0)
    { 
      toner(button, 150); // Play tone for pressed button

      while(checkButton() != 0) ;  // Waiting for user to release button

      delay(10); // Debouncing

      return button;
    }

  }
  
   return 0; // If we get here, we've timed out!
}

void toner(byte which, int buzz_length_ms)
{//This Function is to play the tone and light up the corresponding LED when user presses a button
  setLED(which); //Turn on a given LED

  //Play the sound associated with the given LED
  switch(which) 
  {
  case 1:
    tone(BUZZER, NOTE_D6);
    delay(buzz_length_ms);
    noTone(BUZZER);    
    break;
  case 2:
    tone(BUZZER, NOTE_CS5);
    delay(buzz_length_ms);
    noTone(BUZZER);   
    break;
  case 3:
    tone(BUZZER, NOTE_GS5);
    delay(buzz_length_ms);
    noTone(BUZZER); 
    break;
  case 4:
    tone(BUZZER, NOTE_DS5);
    delay(buzz_length_ms);
    noTone(BUZZER); 
    break;
  }

 setLED(0); // Turn off all LEDs
}

void setLED(int num)
{
  //Function to handle LED lights turning on and off
  switch(num) 
  {
  case 0:
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);    
    break;
  case 1:
    digitalWrite(LED_1, HIGH);    
    break;
  case 2:
    digitalWrite(LED_2, HIGH);   
    break;
  case 3:
    digitalWrite(LED_3, HIGH); 
    break;
  case 4:
    digitalWrite(LED_4, HIGH); 
    break;
  }
  
  
  }


  boolean play_memory(void)
{
  //Game Function
  randomSeed(millis()); // Seed the random generator with random amount of millis()
lcd.clear();
lcd.setCursor(0,0);      
      lcd.print(" Game Begins In ");  

        for(int i=3;i>0;i--)
        {
          lcd.setCursor(1,7);      
      lcd.print(i);
      tone(BUZZER, NOTE_C4,400);
       delay(800);
      }
      
lcd.setCursor(1,7);      
      lcd.print("GO!");
      tone(BUZZER, NOTE_C6,400);
      delay(1000);
      lcd.clear();
  gameRound = 0; // Reset the gameround to 0
//Loop through rounds
  while (gameRound < ROUNDS_TO_WIN) 
  {

    lcd.setCursor(0,0);      
      lcd.print("Turn: ");
      lcd.print(gameRound+1);
      lcd.print(" of ");
      lcd.print(ROUNDS_TO_WIN);
    add_to_moves(); // Add a key to the current moves, then play them back

    playMoves(); // Play back the current sequence of moves
lcd.setCursor(1, 0);
    lcd.print("                ");
    // Then require the player to repeat the sequence.
    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      lcd.setCursor(0,7);
      
      byte choice = wait_for_button(); // wait for user input

      if (choice == 0) return false; // If wait timed out, player loses

      if (choice != gameBoard[currentMove]) return false; // If the choice is wrong, player loses
    }
    lcd.setCursor(1, 0);
    lcd.print("                ");
    delay(1000); // Player is correct, move to next round
  }

  return true; // Player successfully enetered all moves correctly. Player Wins!
}


void add_to_moves(void)
{
  //Add a number from 1 to 5 to moves array
  byte newButton = random(1, 5); //min (included), max (exluded)
  gameBoard[gameRound++] = newButton; // Add this new button to the game array
}

void playMoves(void)
{
  //Playback moves currently stored in array

  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) 
  {
    toner(gameBoard[currentMove], 150);
    lcd.setCursor(1,currentMove);
    lcd.print(gameBoard[currentMove]);
        
    delay(playSpeed);
    
  }  
}

