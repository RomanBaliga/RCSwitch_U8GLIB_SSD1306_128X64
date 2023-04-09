#include "U8glib.h"
#include <RCSwitch.h>


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
RCSwitch RX = RCSwitch();

unsigned long ActualTime; 
unsigned long LastTime;

long TEXT = 0;

byte X = 0;

//*******************************************************************
void setup() {

  RX.enableReceive(0);
  Serial.begin(9600);

  pinMode(12, INPUT_PULLUP);

  LastTime = millis();
  
  u8g.drawBox(1, 1, 64, 128); //clear display
  DRAW();
}

//*******************************************************************
void DRAW() 
{
   u8g.firstPage();  
  do {
  u8g.setFont(u8g_font_osb18n);
  u8g.setPrintPos(0, 30); 
  u8g.print(TEXT); 

  u8g.setFont(u8g_font_5x8);
  u8g.setPrintPos(0, 55); 
  u8g.print(TEXT,BIN); 
  
   } while( u8g.nextPage() );
 }

//*******************************************************************
void loop() {

ActualTime = millis();

//*******************************************************************  

if (digitalRead(12) == 0) {
  DRAW();
  LastTime = millis();  
}

//*******************************************************************

if ( (ActualTime - LastTime) > 8000 ){ 

   u8g.drawBox(1, 1, 64, 128);   
   u8g.firstPage();  do { } while( u8g.nextPage() ); 
   //Serial.println( "MAZU DISPLEJ" );
    }  
    
//*******************************************************************    

if (RX.available()) {

  TEXT = RX.getReceivedValue();

  if (TEXT != 0) {
    Serial.println( TEXT );
    Serial.println( TEXT,BIN );
    Serial.println( RX.getReceivedBitlength() );
    RX.resetAvailable();

    LastTime = millis();

    DRAW();

    }   
  }
}
