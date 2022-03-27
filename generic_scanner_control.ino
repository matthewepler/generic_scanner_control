#include <HardwareSerial.h>
#include <ezButton.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#include "FrequencyCounter.hpp"
#include "ReelController.hpp"
#include "Regulator.hpp"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

FrequencyCounter freqCounter(23); // measure frequency on pin 23

HardwareSerial &odrive_serial = Serial8;
ReelController reelController(odrive_serial);

Regulator regulator;

ezButton butt_idle(30); // create ezButton object that attach to pin 30
ezButton butt_play(29); // create ezButton object that attach to pin 29
ezButton butt_stop(28); // create ezButton object that attach to pin 28
ezButton butt_rew(27);  // create ezButton object that attach to pin 27
ezButton butt_ff(26);   // create ezButton object that attach to pin 26

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  freqCounter.begin();

  regulator.setOutputRange(-1.4, -0.3);
  
  //Scanner speed on playback for regulation. 38 = approx 12fps / 18 = approx 6fps
  regulator.setSetpoint(18);

  odrive_serial.begin(115200);
  Serial.begin(115200);
  Serial2.begin(9600);

  // required by EZbutton library
  butt_idle.setDebounceTime(20); // set debounce time to 20 milliseconds
  butt_play.setDebounceTime(20); // set debounce time to 20 milliseconds
  butt_stop.setDebounceTime(20); // set debounce time to 20 milliseconds
  butt_rew.setDebounceTime(20);  // set debounce time to 20 milliseconds
  butt_ff.setDebounceTime(20);   // set debounce time to 20 milliseconds
}

void loop() {
  butt_idle.loop(); // MUST call the loop() function first
  butt_play.loop(); // MUST call the loop() function first
  butt_stop.loop(); // MUST call the loop() function first
  butt_rew.loop();  // MUST call the loop() function first
  butt_ff.loop();   // MUST call the loop() function first

  if (reelController.isPlaying()) {
    double currentSpeed = reelController.getPlaySpeed();
    double newSpeed = regulator.compute(currentSpeed, freqCounter.getFrequency());
   
   //comment this out to disable speed regulation
   reelController.setPlaySpeed(newSpeed);
  }

  // Print the measured frequency and the reported speed every 100 ms
  static unsigned long lastPrintTime;
  unsigned long elapsedSinceLastPrint = millis() - lastPrintTime;
  if (elapsedSinceLastPrint > 100) {
    Serial.printf("freq:%f\tspeed:%f\n", freqCounter.getFrequency(), reelController.getPlaySpeed());
    lastPrintTime = millis();
  }

  /////////////////////////////////////////// IDLE

  if (butt_idle.isPressed()) {

    display.clearDisplay();
    display.setCursor(15, 1);
    display.println("IDLE");
    display.display();

    reelController.setIdle();
  }

  ////////////////////////////////////////// PLAY

  if (butt_play.isPressed()) {

    display.clearDisplay();
    display.setCursor(15, 1);
    display.println("PLAY");
    display.display();

    reelController.play();
  }

  //////////////////////////////////////////////// STOP

  if (butt_stop.isPressed()) {

    display.clearDisplay();
    display.setCursor(15, 1);
    display.println("STOP");
    display.display();

    reelController.stop();
  }

  /////////////////////////////////////////////////// REW

  if (butt_rew.isPressed()) {

    display.clearDisplay();
    display.setCursor(15, 1);
    display.println("REWIND");
    display.display();

    reelController.rewind();
  }

  /////////////////////////////////////////////////// FF

  if (butt_ff.isPressed()) {

    display.clearDisplay();
    display.setCursor(15, 1);
    display.println("FF");
    display.display();

    reelController.fastForward();
  }
}
