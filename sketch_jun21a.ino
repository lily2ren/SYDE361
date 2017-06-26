#include <Bounce2.h> // A library for debouncing switches

#define fingerPin1 A14 //fingerPins: valve/piston positions
#define fingerPin2 A8
#define fingerPin3 A9
#define notePin1 A15 //notePins: play different notes for same finger positions
#define notePin2 A12
#define notePin3 A13

int fingerPin1State = 0;
int fingerPin2State = 0;
int fingerPin3State = 0;
int notePin1State = 0;
int notePin2State = 0;
int notePin3State = 0;
int fingering = 0;
int note = 0;

// Instantiate a Bounce objects for notePins
Bounce noteBounce1 = Bounce();
Bounce noteBounce2 = Bounce();
Bounce noteBounce3 = Bounce();

// Set up integers to store the state of the note button and potentiometer value
int currNote = 0;
int prevNote = 0;

//midi setup
int channel = 1;
int velocity = 100;

void setup() {
  pinMode(fingerPin1, INPUT_PULLUP);
  pinMode(fingerPin2, INPUT_PULLUP);
  pinMode(fingerPin3, INPUT_PULLUP);
  pinMode(notePin1, INPUT_PULLUP);
  pinMode(notePin2, INPUT_PULLUP);
  pinMode(notePin3, INPUT_PULLUP);

  noteBounce1.attach(notePin1);
  noteBounce2.attach(notePin2);
  noteBounce3.attach(notePin3);
  noteBounce1.interval(5); // interval in ms
  noteBounce2.interval(5);
  noteBounce3.interval(5);
}

void loop() {
  // read note pins
  notePin1State = noteBounce1.read();
  notePin2State = noteBounce2.read();
  notePin3State = noteBounce3.read();
//  Serial.println(playPinState);
  fingerPin1State = analogRead(fingerPin1);
  fingerPin2State = analogRead(fingerPin2);
  fingerPin3State = analogRead(fingerPin3);
  notePin1State = analogRead(notePin1);
  notePin2State = analogRead(notePin2);
  notePin3State = analogRead(notePin3);
    Serial.print("notePin 3 is: ");
    Serial.println(notePin3State);
    Serial.print("notepin 2 is: ");
    Serial.println(notePin2State);
    Serial.print("notepin 1 is: ");
    Serial.println(notePin1State);
    Serial.print("play pin is: ");
  fingering = (fingerPin1State >= 1000)  * 4 + (fingerPin2State >= 1000) * 2 + (fingerPin3State >= 1000) * 1;
  Serial.println(fingering);
  if (notePin1State > 1000 && notePin2State < 1000 && notePin3State < 1000) {
    note = 0;
  } else if (notePin1State < 1000 && notePin2State > 1000 && notePin3State < 1000) {
    note = 1;
  } else if (notePin1State < 1000 && notePin2State < 1000 && notePin3State > 1000) {
    note = 2;
  } else {
    note = 3;
  }

  switch (fingering) {
    //C, G, E
    case 0:
      if (note == 0) {
        playNote(60);
      } else if (note == 1) {
        playNote(67);
      } else if (note == 2) {
        playNote(64);
      } else {
        playNote(0);
      }
      break;

    //NO NOTE MAPPED
    case 1:
      playNote(0);
      break;

    //B, F#, D#
    case 2:
      if (note == 0) {
        playNote(71);
      } else if (note == 1) {
        playNote(66);
      } else if (note == 2) {
        playNote(63);
      } else {
        playNote(0);
      }
      break;

    //G#, D#,
    case 3:
      if (note == 0) {
        playNote(68);
      } else if (note == 1) {
        playNote(63);
      } else {
        playNote(0);
      }
      break;

    //Bb, F, D
    case 4:
      if (note == 0) {
        playNote(71);
      } else if (note == 1) {
        playNote(65);
      } else if (note == 2) {
        playNote(62);
      } else {
        playNote(0);
      }
      break;

    //G, D
    case 5:
      if (note == 0) {
        playNote(67);
      } else if (note == 1) {
        playNote(62);
      } else {
        playNote(0);
      }
      break;

    //A, E, C#
    case 6:
      if (note == 0) {
        playNote(69);
      } else if (note == 1) {
        playNote(64);
      } else if (note == 2) {
        playNote(61);
      } else {
        playNote(0);
      }
      break;

    //F#, C#
    case 7:
      if (note == 0) {
        playNote(66);
      } else if (note == 1) {
        playNote(61);
      } else {
        playNote(0);
      }
      break;

    default:
      playNote(0);
      break;
  }

  delay(250);
}

void playNote(int note) {
  currNote = note;
  usbMIDI.sendNoteOn(note, velocity, channel); // Turn the note ON
  if (prevNote != currNote) {
    usbMIDI.sendNoteOff(prevNote, velocity, channel);
  }
  else if (note == 0) {
    usbMIDI.sendNoteOff(prevNote, 0, channel); // Turn the note OFF
  }
  prevNote = currNote;
}


