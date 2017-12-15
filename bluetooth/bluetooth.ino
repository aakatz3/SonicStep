#include <SoftwareSerial.h>
SoftwareSerial  BTSerial(2, 3); //TX RX
 
#include "pitches.h"
int Ba = 5;
const int B2 = 6;
const int B3 = 7;
// notes in the melody:
int redAndBlue[] = {
 NOTE_G3, NOTE_C4, NOTE_C4, NOTE_B4, NOTE_A4, 0, NOTE_G3, NOTE_D3, NOTE_C3, 
 NOTE_C3, NOTE_D3, NOTE_G3, NOTE_G3, 0, NOTE_D3, NOTE_G3, 0,
 NOTE_G3, NOTE_C4, NOTE_C4, NOTE_DS4, NOTE_DS4, 0, NOTE_G3, NOTE_E3, NOTE_FS3, 
 NOTE_FS3, NOTE_G3, NOTE_G3, NOTE_A4, 0, NOTE_B4, NOTE_C4, NOTE_C4, NOTE_C4
};
int studio[] = {
 NOTE_A4, 0, NOTE_A4, 0, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A4, NOTE_A4, 0,
 NOTE_D3, NOTE_C3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_G3, NOTE_D3, NOTE_E3, 0
};
int killEverybody[] = {
  NOTE_D4, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D3, NOTE_D4, 
  NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G3, NOTE_A4,
  NOTE_D4, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D3,
  NOTE_D4, NOTE_D3, NOTE_D3, NOTE_D3, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_A4, 0
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsR[] = {
  4, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 4, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8
};
int noteDurationsK[] = {
  4, 8, 8, 8, 8, 4, 2+8, 8, 4, 4, 8, 8, 8, 8, 4, 2, 8, 16, 16, 8, 8,
  4, 8, 8, 8, 8, 4, 2+8, 8, 4, 4, 8, 8, 8, 8, 4, 8, 8, 4, 2
};
int noteDurationsS[] = {
	16, 16, 16, 16, 16, 16, 16, 16, 16, 4, 16, 8, 16, 16, 16, 16, 8, 16, 8
};


void setup() {
  BTSerial.begin(9600); 
  Serial.begin(9600);
  while(!BTSerial.available() || BTSerial.read() != '\n');
  pinMode(Ba, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
}
int thisNoteA = 21;
int thisNoteB = 19;
int thisNoteC = 35;
int thisNote  = 0;
long nextNoteTime = 0;
long nextStopTime = 0;
int mode = 0;
int thisNoteMax = 21;

void loop() {
  if(digitalRead(Ba) == HIGH){
    mode = 0;
    thisNote = 0;
    thisNoteMax = 21;
    Serial.println("A");
  } else if(digitalRead(B2) == HIGH){
    mode = 1;
    thisNote = 0;
    thisNoteMax = 19;
    Serial.println("B");
  } else if(digitalRead(B3) == HIGH){
    mode = 2;
    thisNote = 0;
    thisNoteMax = 35;
    Serial.println("C");
  }
  if(BTSerial.available()){
      int x = BTSerial.parseInt();
      int y = BTSerial.parseInt();
      int z = BTSerial.parseInt();
        Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
    Serial.print(",");
  Serial.println(nextNoteTime);
  if(y > 700 || x > 500 || z > 1300 || y < 500 || x < 200 || z < 800){
    if(nextNoteTime < millis()){
      switch(mode){
        case 0:
          playThing(killEverybody[thisNote], noteDurationsK[thisNote]);
          break;
          case 1:
          playThing(redAndBlue[thisNote], noteDurationsR[thisNote]);
          break;
          case 2:
          playThing(studio[thisNote], noteDurationsS[thisNote]);
          break;
          
      }
    }

   
  
  }
  if(nextStopTime < millis()){
        // stop the tone playing:
    noTone(9);
  }
  }
}

void playThing(int note, int duration){
  
       // to calculate the note duration, take one second divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1100 / duration;
       tone(8, note, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 10% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.20;
    nextNoteTime = pauseBetweenNotes + millis();
    nextStopTime = noteDuration + millis();

    thisNote++;
    thisNote %= thisNoteMax;
}


// stub functions for analog write to set 3 different analog write pins to 3 different values
// read the x y and z of the accelerometer (done in 111 final sketch sent) send separately ...
// separated by commas over both usb serial and bluetooth serial
// processing will be done on ground station
