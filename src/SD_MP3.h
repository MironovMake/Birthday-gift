#include <SD.h> // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 53 // using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>         //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm; // create an object for use in this sketch

unsigned long time = 0;
int musicFlag = 0;
bool buttonflag = 0;
int SensorButton = 8;
const char *playList[] = {
    "Repress.wav",
    "New Year.wav",
    "third.wav",
    "foth.wav",
    "five.wav",
    "thix.wav",
    "seven.wav",
    "eqth.wav",
    "nine.wav",
    "ten.wav",
};

void setup_MP3()
{

  tmrpcm.speakerPin = 46; // 5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  pinMode(SensorButton, INPUT);
  Serial.begin(115200);
  if (!SD.begin(SD_ChipSelectPin))
  { // see if the card is present and can be initialized:
    Serial.println("SD fail");
    return; // don't do anything more if not
  }
  else
  {
    Serial.println("SD ok");
  }
  // tmrpcm.play("Repress.wav"); // the sound file "song" will play each time the arduino powers up, or is reset
}

void lisen_button()
{
  if (buttonflag == 0 && digitalRead(SensorButton))
  {
    (musicFlag == 0) ? tmrpcm.play("song.wav") : tmrpcm.disable();
    buttonflag = 1;
    musicFlag = !musicFlag;
  }
  if (buttonflag == 1 && !digitalRead(SensorButton))
  {
    buttonflag = 0;
  }
}
