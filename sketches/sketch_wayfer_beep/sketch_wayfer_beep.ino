 #include "pitches.h"

// notes in the melody:
int D;
//왼쪽일 경우의 비프음높이
int melodyl[] = {

  NOTE_C4, 0, NOTE_C4, 0, NOTE_C4, 0, NOTE_C4, 0
};

//전방일 경우의 비프음높이
int melodyf[] = {

  NOTE_D4, 0, NOTE_D4, 0, NOTE_D4, 0, NOTE_D4, 0
};

//오른쪽일 경우의 비프음높이
int melodyr[] = {

  NOTE_E4, 0, NOTE_E4, 0, NOTE_E4, 0, NOTE_E4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int F, L, R, x;
int noteDurations[] {x, x, x, x, x, x, x, x};

void setup() {

  // iterate over the notes of the melody:
 
  for (int thisNote = 0; thisNote < 8; thisNote++) {
 
    // to calculate the note duration, take one second divided by the note type.
   
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
   
    int noteDuration = 1000 / noteDurations[thisNote];
    if (D == 1){
    tone(8, melodyf[thisNote], noteDuration);
    }
    if (D == 2){
    tone(8, melodyf[thisNote], noteDuration);
    }
    if (D == 3){
    tone(8, melodyf[thisNote], noteDuration);
    }
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }
}

void loop() {
//앞, 왼쪽, 오른쪽 미터값, x는 박자. ex) 물체와의 거리 및 방향이 4미터 왼쪽, 4박자의 C4 비프음 출력

if (F == 4||L == 4||R == 4) {x = 4;}
if (F == 3||L == 3||R == 3) {x = 6;}
if (F == 2||L == 2||R == 2) {x = 8;}
if (F == 1||L == 1||R == 1) {x = 16;}

}-
