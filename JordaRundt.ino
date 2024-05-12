//Biblioteker for lcd-skjermen og ledstripen
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

//definerer neopixel ledstipen
#define LED_STRIP 3
#define NUM_PIXELS 40
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_PIXELS];
Adafruit_NeoPixel ledStrip(NUM_PIXELS, LED_STRIP, NEO_GRB + NEO_KHZ800);

//definerer lcd-skjermen
LiquidCrystal lcd(7, 6, 13, 12, 11, 10);

//Analogportene for halleffekt sensorene
const int sensor1 = A0; 
const int sensor2 = A1; 
const int sensor3 = A2; 
const int sensor4 = A3; 

//Arkadeknappen med integrert ledlys
const int buttonPin = 4; 
const int ledPin = 5; 

//Fargevariablene er hue-verdier
const int RED = 0;          
const int GREEN = 21845;     
const int BLUE = 43690;     
const int YELLOW = 10922;    
const int CYAN = 33690;


bool buttonPressed = false;
bool programStarted = false;

//sensorverdier og bools for å kunne lagre om magneten har passert eller ikke
int sensorVal1 = 0;
int sensorVal2 = 0;
int sensorVal3 = 0;
int sensorVal4 = 0;

bool pass0 = false;
bool pass1 = false;
bool pass2 = false;
bool pass3 = false;
bool pass4 = false;

//variabler for å måle tiden
unsigned long startTime;
unsigned long elapsedTime; 

/* Ikke mye som skjer i setup. 

*/
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //knappen lyser hele tiden
  digitalWrite(ledPin, HIGH);

  FastLED.addLeds<LED_TYPE, LED_STRIP, COLOR_ORDER>(leds, NUM_PIXELS);
  ledStrip.begin();

  Serial.begin(9600); 

  //Printer "TRYKK KNAPPEN FOR SPILL" til lcd-skjermen
  lcd.begin(16, 2);
  startScreen();
}



/*hovedloopen kjører kontinuerlig uten at sensorene er aktivert.
I hviletilstand lyser ledstripen rolig i alle farger.
Dersom man trykker på start-knappemn starter programet.
Da går programmet inn i en while løkke som sjekker om magneten passerer sensorene
Når alle sensorene er passert lyser ledstripen grønt og tiden blir printet til skjermen

Hovedloopen er bygget opp av flere funksjoner med passende navn for lett lesbarhet 
*/


void loop() {

  rainbow();

  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    buttonPressed = true;
  }

  if (buttonPressed) {
    programStarted = true;
    buttonPressed = false;

    ledBlink();

    //Lyser cyan
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    ledStrip.setPixelColor(pixel, ledStrip.ColorHSV(33690, 250, 100)); 
    ledStrip.show();}
  }

  while(programStarted) {

    //Sjekker om knappen trykkes inni løkken for å kunne avbryte spillet underveis
    int buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
        pass0 = false;
        pass1 = false;
        pass2 = false;
        pass3 = false;
        pass4 = false;
        programStarted = false;
        buttonPressed = false;

        //Da lysere ledstripen rødt og koden går tilbake til "hviletilstand"
        ledLight(RED);
        delay(1000);
        ledClear();
        startScreen();
        break;
      }

    //leser av sensorene og lagrer i variabler
    sensorVal1 = analogRead(sensor1);
    sensorVal2 = analogRead(sensor2);
    sensorVal3 = analogRead(sensor3);
    sensorVal4 = analogRead(sensor4);

    /* 
    Hvis sensorVal går utenfor rangen vi har satt blir sensoren "aktivert" og vi setter pass til true
    For å sikre at man må gjennom alle sensorene har vi også lagt inn en && betingelse som sjekker om forrige sensor er passert

    Vi har testet verdiene til hver sensor og justert rangen for når de aktiveres basert på testene
    Hver sensor har litt ulike verdier og range, muligens pga fysiske faktorer som vi ikke er helt sikre på

    I ettertid ser vi at det hadde vært lurere å bruke switchcases istedenfor if-setninger, 
    men det ble litt liten tid til å endre på hele koden når innlevering nærmet seg 
    */


    if (200 > sensorVal1 || sensorVal1 > 540 && !pass0) {
      elapsedTime = 0;
      startTime = millis(); //starter tiden når første sensor er passert
      pass0 = true;
      pass1 = true;
      Serial.println("SENSOR 1"); //printer til monitor for å få oversikt fra pcen
    }
    
    if ((530 > sensorVal2 || sensorVal2 > 900) && pass1) {
      pass2 = true;
      Serial.println("SENSOR 2");
    }

    if ((455 > sensorVal3 || sensorVal3 > 1000) && pass2) {
      pass3=true;
      Serial.println("SENSOR 3");
    }

    if ((400 > sensorVal4 || sensorVal4 > 500) && pass3) {
      elapsedTime = millis()-startTime; //slutter tiden når siste sensor er passert
      pass4=true;
      Serial.println("SENSOR 4");            
    }


    if (pass1 && pass2 && pass3 && pass4) { 
      //Når alle sensorene er passert 
      ledLight(GREEN);
      printTime(); //printer tiden og hvor tiden sammenliknet med lyset

      //resetter variablene
      pass0 = false;
      pass1 = false;
      pass2 = false;
      pass3 = false;
      pass4 = false;
      programStarted = false; 
  
      startScreen(); //tilbake til startskjermen      
    }
  }
}


//Funksjon som lyser opp hele stripen med et delay mellom hver piksel. Tar inn farge(hue verdi) som input
void ledLight(int color) {
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    ledStrip.setPixelColor(pixel, ledStrip.ColorHSV(color, 250, 100)); 
    ledStrip.show();
    delay(10);
  } 
}

void ledClear() {
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    ledStrip.setPixelColor(pixel, ledStrip.ColorHSV(0, 0, 0)); 
    ledStrip.show();
  } 
}

//Nedtelling før spillet starter
void ledBlink() {
    delay(500);
    ledLight(RED);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("3");

    delay(500);
    ledClear();
    delay(500);
    ledLight(YELLOW);

    lcd.clear();
    lcd.print("2");

    delay(500);
    ledClear();
    delay(500);
    ledLight(GREEN);
    

    lcd.clear();
    lcd.print("1");
    
    delay(500);
    ledClear();
    delay(500);
    ledLight(CYAN);

    lcd.clear();
    lcd.print("GOOOOO");
  }


//Regner om tiden til sekunder og printer til lcd-skjermen m/ melding
void printTime() {
  Serial.print("Du brukte "); 
  float seconds = elapsedTime/1000.0;
  Serial.print(seconds, 3); 
  Serial.println(" sekunder"); 

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Tid: ");
  lcd.print(seconds);
  lcd.print(" sek");

  delay(4000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lyset er ");
  lcd.print(int(seconds/0.13));
  lcd.setCursor(0, 1);
  lcd.print("ganger raskere");
  delay(3000);

  
}

//startskjermen 
void startScreen(); {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TRYKK KNAPPEN");
  lcd.setCursor(0, 1);
  lcd.print("FOR SPILL");
}

//Regnbuelys som fader
void rainbow() {
  static uint8_t hue = 0; 

  for (int i = 0; i < NUM_PIXELS; i++) {
    leds[i] = CHSV(hue + (i * 255 / NUM_PIXELS), 255, 255);
  }

  hue++;
  delay(20);
  FastLED.show();
}
