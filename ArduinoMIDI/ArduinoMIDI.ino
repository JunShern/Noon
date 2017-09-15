#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

static const unsigned ledPin = 3;
static const unsigned leftProgramButton = 1;
static const unsigned rightProgramButton = 2;

static const unsigned channelNumber = 1;

int buttonStates[16];
int program = 0;
int leftProgramButtonState = 0;
int rightProgramButtonState = 0;

void setup()
{
  for (int i=0; i<16; i++)
  {
    pinMode(4+i, INPUT);
    buttonStates[i] = 0;
  }
  pinMode(leftProgramButton, INPUT);
  pinMode(rightProgramButton, INPUT);
  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600);
  MIDI.begin(4);                      // Launch MIDI and listen to channel 4
}

void loop()
{
  int ledState = 0;
  // Check 16 normal buttons
  for (int i=0; i<16; i++)
  {
    bool pressed = digitalRead(4+i);
    if (pressed && buttonStates[i] == 0)
    {
      buttonStates[i] = 1;
//      Serial.println(i);
      MIDI.sendNoteOn(42 + i, 127, channelNumber);    // Send a Note (pitch 42, velo 127 on channel 1)

      ledState = 1;
    }
    else if (!pressed && buttonStates[i] == 1)
    {
      buttonStates[i] = 0;
//      Serial.println(i);
      MIDI.sendNoteOff(42 + i, 0, channelNumber);
    }
    ledState = constrain(ledState + pressed*50, 0, 255);
  }



  // Check two special program buttons
  if (leftProgramButtonState == 0 && digitalRead(leftProgramButton) == 1)
  {
    leftProgramButtonState = 1;
    program = constrain(program - 1, 0, 127);
    MIDI.sendProgramChange(program, channelNumber);
    ledState = 255;
  } else {
    leftProgramButtonState = digitalRead(leftProgramButton);
  }
  if (rightProgramButtonState == 0 && digitalRead(rightProgramButton) == 1)
  {
    rightProgramButtonState = 1;
    program = constrain(program + 1, 0, 127);
    MIDI.sendProgramChange(program, channelNumber);
    ledState = 255;
  } else {
    rightProgramButtonState = digitalRead(rightProgramButton);
  }



  // Set LED status
  ledState = constrain(ledState - 1, 0, 255);
  analogWrite(ledPin, ledState);
}
