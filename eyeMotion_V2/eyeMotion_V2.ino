//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

int pos = 0; 
int tapNum = 15; // logged number of taps
    byte mood = 0; // current mood
  //const byte vibration PROGMEM = A0; // vibration sensor
    const int tapLevel PROGMEM = 512;
    long previousMillis = 0;        // will store last time LED was updated
    const int decay PROGMEM = 30000;      

     unsigned long 
     checkMillis,
     tapMillis,
     songMillis,
     currentMillis;

uint8_t
    blinkIndex[] = { 
      1, 2, 3, 4, 3, 2, 1 },
    // Blink bitmap sequence
    blinkCountdown = 100, // Countdown to next blink (in frames)
    gazeCountdown  =  75, // Countdown to next eye movement
    gazeFrames     =  50; // Duration of eye movement (smaller = faster)
    int8_t
    eyeX = 3, eyeY = 3,   // Current eye position
    newX = 3, newY = 3,   // Next eye position
    dX   = 0, dY   = 0;   // Distance from prior to new position

    
/* we always wait a bit between updates of the display */
unsigned long delaytime=100;
unsigned long delaylong=700;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
static const uint8_t  PROGMEM writeArduinoOnMatrix() {
  /* here is the data for the characters */
byte a[8]={B00100100,B01000010,B10000001,B00111100,B01111110,B11111111,B11100111,B11100111};
byte r[8]={B00100100,B01000010,B10000001,B00000000,B01111110,B11111111,B11100111,B11100111};
byte d[8]={B00100100,B01000010,B10000001,B00000000,B00000000,B01111110,B11100111,B11100111};
byte u[8]={B00100100,B01000010,B10000001,B00000000,B00000000,B00000000,B01100110,B11100111};
byte i[8]={B00100100,B01000010,B10000001,B00000000,B00000000,B00000000,B00000000,B11100111};

  // n e o t l, sao os frames de animacao neutra 
byte n[8]={B00111100,B01111110,B11111111,B11100111,B11100111,B11111111,B01111110,B00111100};
byte e[8]={B00000000,B01111110,B11111111,B11111111,B11100111,B11100111,B01111110,B00111100};
byte o[8]={B00000000,B00000000,B00111100,B11111111,B11111111,B11100111,B00100100,B00000000};
byte t[8]={B00000000,B00000000,B00000000,B00000000,B11111111,B01111110,B00011000,B00000000};
byte l[8]={B00000000,B00000000,B00000000,B00000000,B10000001,B01111110,B00000000,B00000000};


  // f z h p y, sao os frames de animacao feliz 
byte f[8]={B01111110,B11111111,B11100111,B01100110,B00111100,B10000001,B11000011,B01111110};
byte z[8]={B00111100,B11111111,B11100111,B01100110,B00111100,B10000001,B11000011,B01111110};
byte h[8]={B00000000,B11111111,B11111111,B01100110,B00100100,B10000001,B11000011,B01111110};
byte p[8]={B00000000,B11111111,B11111111,B01111110,B00100100,B10000001,B11000011,B01111110};
byte y[8]={B00000000,B11000011,B11111111,B01111110,B00111100,B10000001,B11000011,B01111110};

  // g b v q u, sao os frames de animacao feliz 
byte g[8]={B10000001,B01100110,B00000000,B11111111,B11100111,B11100111,B01111110,B00111100};
byte b[8]={B10000001,B01100110,B00000000,B11111111,B11100111,B11100111,B01111110,B00000000};
byte v[8]={B10000001,B01100110,B00000000,B11111111,B11100111,B01100110,B00000000,B00000000};
byte q[8]={B10000001,B01100110,B00000000,B11111111,B01100110,B00000000,B00000000,B00000000};
byte k[8]={B10000001,B01100110,B00000000,B10000001,B01111110,B00000000,B00000000,B00000000};

  /* Reproducao de todas as animacoes tristes*/ 
lc.setRow(0,0,a[0]);lc.setRow(0,1,a[1]);lc.setRow(0,2,a[2]);lc.setRow(0,3,a[3]);  lc.setRow(0,4,a[4]); lc.setRow(0,5,a[5]);lc.setRow(0,5,a[5]);lc.setRow(0,6,a[6]);lc.setRow(0,7,a[7]);
delay(delaytime);
lc.setRow(0,0,r[0]);lc.setRow(0,1,r[1]);lc.setRow(0,2,r[2]);lc.setRow(0,3,r[3]);lc.setRow(0,4,r[4]);lc.setRow(0,5,r[5]);lc.setRow(0,5,r[5]);lc.setRow(0,6,r[6]);lc.setRow(0,7,r[7]);
delay(delaytime);
lc.setRow(0,0,d[0]);lc.setRow(0,1,d[1]);lc.setRow(0,2,d[2]);lc.setRow(0,3,d[3]);lc.setRow(0,4,d[4]);lc.setRow(0,5,d[5]);lc.setRow(0,5,d[5]);lc.setRow(0,6,d[6]);lc.setRow(0,7,d[7]);
delay(delaytime);
lc.setRow(0,0,u[0]);lc.setRow(0,1,u[1]);lc.setRow(0,2,u[2]);lc.setRow(0,3,u[3]);lc.setRow(0,4,u[4]);lc.setRow(0,5,u[5]);lc.setRow(0,5,u[5]);lc.setRow(0,6,u[6]);lc.setRow(0,7,u[7]);
delay(delaytime);
lc.setRow(0,0,i[0]);lc.setRow(0,1,i[1]);lc.setRow(0,2,i[2]);lc.setRow(0,3,i[3]);lc.setRow(0,4,i[4]);lc.setRow(0,5,i[5]);lc.setRow(0,5,i[5]);lc.setRow(0,6,i[6]);lc.setRow(0,7,i[7]);
delay(delaytime);
lc.setRow(0,0,u[0]);lc.setRow(0,1,u[1]);lc.setRow(0,2,u[2]);lc.setRow(0,3,u[3]);lc.setRow(0,4,u[4]);lc.setRow(0,5,u[5]);lc.setRow(0,5,u[5]);lc.setRow(0,6,u[6]);lc.setRow(0,7,u[7]);
delay(delaytime);
lc.setRow(0,0,d[0]);lc.setRow(0,1,d[1]);lc.setRow(0,2,d[2]);lc.setRow(0,3,d[3]);lc.setRow(0,4,d[4]);lc.setRow(0,5,d[5]);lc.setRow(0,5,d[5]);lc.setRow(0,6,d[6]);lc.setRow(0,7,d[7]);
delay(delaytime);
lc.setRow(0,0,r[0]);lc.setRow(0,1,r[1]);lc.setRow(0,2,r[2]);lc.setRow(0,3,r[3]);lc.setRow(0,4,r[4]);lc.setRow(0,5,r[5]);lc.setRow(0,5,r[5]);lc.setRow(0,6,r[6]);lc.setRow(0,7,r[7]);
delay(delaytime);
lc.setRow(0,0,a[0]);lc.setRow(0,1,a[1]);lc.setRow(0,2,a[2]);lc.setRow(0,3,a[3]);lc.setRow(0,4,a[4]);lc.setRow(0,5,a[5]);lc.setRow(0,5,a[5]);lc.setRow(0,6,a[6]);lc.setRow(0,7,a[7]);
delay(delaytime);
lc.setRow(0,0,r[0]);lc.setRow(0,1,r[1]);lc.setRow(0,2,r[2]);lc.setRow(0,3,r[3]);lc.setRow(0,4,r[4]);lc.setRow(0,5,r[5]);lc.setRow(0,5,r[5]);lc.setRow(0,6,r[6]);lc.setRow(0,7,r[7]);
delay(delaytime);
lc.setRow(0,0,d[0]);lc.setRow(0,1,d[1]);lc.setRow(0,2,d[2]);lc.setRow(0,3,d[3]);lc.setRow(0,4,d[4]);lc.setRow(0,5,d[5]);lc.setRow(0,5,d[5]);lc.setRow(0,6,d[6]);lc.setRow(0,7,d[7]);
delay(delaytime);
lc.setRow(0,0,u[0]);lc.setRow(0,1,u[1]);lc.setRow(0,2,u[2]);lc.setRow(0,3,u[3]);lc.setRow(0,4,u[4]);lc.setRow(0,5,u[5]);lc.setRow(0,5,u[5]);lc.setRow(0,6,u[6]);lc.setRow(0,7,u[7]);
delay(delaytime);
lc.setRow(0,0,i[0]);lc.setRow(0,1,i[1]);lc.setRow(0,2,i[2]);lc.setRow(0,3,i[3]);lc.setRow(0,4,i[4]);lc.setRow(0,5,i[5]);lc.setRow(0,5,i[5]);lc.setRow(0,6,i[6]);lc.setRow(0,7,i[7]);
delay(delaytime);
lc.setRow(0,0,u[0]);lc.setRow(0,1,u[1]);lc.setRow(0,2,u[2]);lc.setRow(0,3,u[3]);lc.setRow(0,4,u[4]);lc.setRow(0,5,u[5]);lc.setRow(0,5,u[5]);lc.setRow(0,6,u[6]);lc.setRow(0,7,u[7]);
delay(delaytime);
lc.setRow(0,0,d[0]);lc.setRow(0,1,d[1]);lc.setRow(0,2,d[2]);lc.setRow(0,3,d[3]);lc.setRow(0,4,d[4]);lc.setRow(0,5,d[5]);lc.setRow(0,5,d[5]);lc.setRow(0,6,d[6]);lc.setRow(0,7,d[7]);
delay(delaytime);
lc.setRow(0,0,r[0]);lc.setRow(0,1,r[1]);lc.setRow(0,2,r[2]);lc.setRow(0,3,r[3]);lc.setRow(0,4,r[4]);lc.setRow(0,5,r[5]);lc.setRow(0,5,r[5]);lc.setRow(0,6,r[6]);lc.setRow(0,7,r[7]);
delay(delaytime);
lc.setRow(0,0,a[0]);lc.setRow(0,1,a[1]);lc.setRow(0,2,a[2]);lc.setRow(0,3,a[3]);lc.setRow(0,4,a[4]);lc.setRow(0,5,a[5]);lc.setRow(0,5,a[5]);lc.setRow(0,6,a[6]);lc.setRow(0,7,a[7]);
delay(delaytime);
delay(delaylong);
  /* Reproducao de todas as animacoes neutras*/  
lc.setRow(0,0,n[0]);lc.setRow(0,1,n[1]);lc.setRow(0,2,n[2]);lc.setRow(0,3,n[3]);lc.setRow(0,4,n[4]);lc.setRow(0,5,n[5]);lc.setRow(0,5,n[5]);lc.setRow(0,6,n[6]);lc.setRow(0,7,n[7]);
delay(delaytime);
lc.setRow(0,0,e[0]);lc.setRow(0,1,e[1]);lc.setRow(0,2,e[2]);lc.setRow(0,3,e[3]);lc.setRow(0,4,e[4]);lc.setRow(0,5,e[5]);lc.setRow(0,5,e[5]);lc.setRow(0,6,e[6]);lc.setRow(0,7,e[7]);
delay(delaytime);
lc.setRow(0,0,o[0]);lc.setRow(0,1,o[1]);lc.setRow(0,2,o[2]);lc.setRow(0,3,o[3]);lc.setRow(0,4,o[4]);lc.setRow(0,5,o[5]);lc.setRow(0,5,o[5]);lc.setRow(0,6,o[6]);lc.setRow(0,7,o[7]);
delay(delaytime);
lc.setRow(0,0,t[0]);lc.setRow(0,1,t[1]);lc.setRow(0,2,t[2]);lc.setRow(0,3,t[3]);lc.setRow(0,4,t[4]);lc.setRow(0,5,t[5]);lc.setRow(0,5,t[5]);lc.setRow(0,6,t[6]);lc.setRow(0,7,t[7]);
delay(delaytime);
lc.setRow(0,0,l[0]);lc.setRow(0,1,l[1]);lc.setRow(0,2,l[2]);lc.setRow(0,3,l[3]);lc.setRow(0,4,l[4]);lc.setRow(0,5,l[5]);lc.setRow(0,5,l[5]);lc.setRow(0,6,l[6]);lc.setRow(0,7,l[7]);
delay(delaytime);
lc.setRow(0,0,t[0]);lc.setRow(0,1,t[1]);lc.setRow(0,2,t[2]);lc.setRow(0,3,t[3]);lc.setRow(0,4,t[4]);lc.setRow(0,5,t[5]);lc.setRow(0,5,t[5]);lc.setRow(0,6,t[6]);lc.setRow(0,7,t[7]);
delay(delaytime);
lc.setRow(0,0,o[0]);lc.setRow(0,1,o[1]);lc.setRow(0,2,o[2]);lc.setRow(0,3,o[3]);lc.setRow(0,4,o[4]);lc.setRow(0,5,o[5]);lc.setRow(0,5,o[5]);lc.setRow(0,6,o[6]);lc.setRow(0,7,o[7]);
delay(delaytime);
lc.setRow(0,0,e[0]);lc.setRow(0,1,e[1]);lc.setRow(0,2,e[2]);lc.setRow(0,3,e[3]);lc.setRow(0,4,e[4]);lc.setRow(0,5,e[5]);lc.setRow(0,5,e[5]);lc.setRow(0,6,e[6]);lc.setRow(0,7,e[7]);
delay(delaytime);
lc.setRow(0,0,n[0]);lc.setRow(0,1,n[1]);lc.setRow(0,2,n[2]);lc.setRow(0,3,n[3]);lc.setRow(0,4,n[4]);lc.setRow(0,5,n[5]);lc.setRow(0,5,n[5]);lc.setRow(0,6,n[6]);lc.setRow(0,7,n[7]);
delay(delaytime);
lc.setRow(0,0,e[0]);lc.setRow(0,1,e[1]);lc.setRow(0,2,e[2]);lc.setRow(0,3,e[3]);lc.setRow(0,4,e[4]);lc.setRow(0,5,e[5]);lc.setRow(0,5,e[5]);lc.setRow(0,6,e[6]);lc.setRow(0,7,e[7]);
delay(delaytime);
lc.setRow(0,0,o[0]);lc.setRow(0,1,o[1]);lc.setRow(0,2,o[2]);lc.setRow(0,3,o[3]);lc.setRow(0,4,o[4]);lc.setRow(0,5,o[5]);lc.setRow(0,5,o[5]);lc.setRow(0,6,o[6]);lc.setRow(0,7,o[7]);
delay(delaytime);
lc.setRow(0,0,t[0]);lc.setRow(0,1,t[1]);lc.setRow(0,2,t[2]);lc.setRow(0,3,t[3]);lc.setRow(0,4,t[4]);lc.setRow(0,5,t[5]);lc.setRow(0,5,t[5]);lc.setRow(0,6,t[6]);lc.setRow(0,7,t[7]);
delay(delaytime);
lc.setRow(0,0,l[0]);lc.setRow(0,1,l[1]);lc.setRow(0,2,l[2]);lc.setRow(0,3,l[3]);lc.setRow(0,4,l[4]);lc.setRow(0,5,l[5]);lc.setRow(0,5,l[5]);lc.setRow(0,6,l[6]);lc.setRow(0,7,l[7]);
delay(delaytime);
lc.setRow(0,0,t[0]);lc.setRow(0,1,t[1]);lc.setRow(0,2,t[2]);lc.setRow(0,3,t[3]);lc.setRow(0,4,t[4]);lc.setRow(0,5,t[5]);lc.setRow(0,5,t[5]);lc.setRow(0,6,t[6]);lc.setRow(0,7,t[7]);
delay(delaytime);
lc.setRow(0,0,o[0]);lc.setRow(0,1,o[1]);lc.setRow(0,2,o[2]);lc.setRow(0,3,o[3]);lc.setRow(0,4,o[4]);lc.setRow(0,5,o[5]);lc.setRow(0,5,o[5]);lc.setRow(0,6,o[6]);lc.setRow(0,7,o[7]);
delay(delaytime);
lc.setRow(0,0,e[0]);lc.setRow(0,1,e[1]);lc.setRow(0,2,e[2]);lc.setRow(0,3,e[3]);lc.setRow(0,4,e[4]);lc.setRow(0,5,e[5]);lc.setRow(0,5,e[5]);lc.setRow(0,6,e[6]);lc.setRow(0,7,e[7]);
delay(delaytime);
lc.setRow(0,0,n[0]);lc.setRow(0,1,n[1]);lc.setRow(0,2,n[2]);lc.setRow(0,3,n[3]);lc.setRow(0,4,n[4]);lc.setRow(0,5,n[5]);lc.setRow(0,5,n[5]);lc.setRow(0,6,n[6]);lc.setRow(0,7,n[7]);
delay(delaytime);
delay(delaylong);

  /* Reproducao de todas as animacoes felizes*/ 
lc.setRow(0,0,f[0]);lc.setRow(0,1,f[1]);lc.setRow(0,2,f[2]);lc.setRow(0,3,f[3]);lc.setRow(0,4,f[4]); lc.setRow(0,5,f[5]);lc.setRow(0,5,f[5]);lc.setRow(0,6,f[6]);lc.setRow(0,7,f[7]);
delay(delaytime);
lc.setRow(0,0,z[0]);lc.setRow(0,1,z[1]);lc.setRow(0,2,z[2]);lc.setRow(0,3,z[3]);lc.setRow(0,4,z[4]);lc.setRow(0,5,z[5]);lc.setRow(0,5,z[5]);lc.setRow(0,6,z[6]);lc.setRow(0,7,z[7]);
delay(delaytime);
lc.setRow(0,0,h[0]);lc.setRow(0,1,h[1]);lc.setRow(0,2,h[2]);lc.setRow(0,3,h[3]);lc.setRow(0,4,h[4]);lc.setRow(0,5,h[5]);lc.setRow(0,5,h[5]);lc.setRow(0,6,h[6]);lc.setRow(0,7,h[7]);
delay(delaytime);
lc.setRow(0,0,p[0]);lc.setRow(0,1,p[1]);lc.setRow(0,2,p[2]);lc.setRow(0,3,p[3]);lc.setRow(0,4,p[4]);lc.setRow(0,5,p[5]);lc.setRow(0,5,p[5]);lc.setRow(0,6,p[6]);lc.setRow(0,7,p[7]);
delay(delaytime);
lc.setRow(0,0,y[0]);lc.setRow(0,1,y[1]);lc.setRow(0,2,y[2]);lc.setRow(0,3,y[3]);lc.setRow(0,4,y[4]);lc.setRow(0,5,y[5]);lc.setRow(0,5,y[5]);lc.setRow(0,6,y[6]);lc.setRow(0,7,y[7]);
delay(delaytime);
lc.setRow(0,0,p[0]);lc.setRow(0,1,p[1]);lc.setRow(0,2,p[2]);lc.setRow(0,3,p[3]);lc.setRow(0,4,p[4]);lc.setRow(0,5,p[5]);lc.setRow(0,5,p[5]);lc.setRow(0,6,p[6]);lc.setRow(0,7,p[7]);
delay(delaytime);
lc.setRow(0,0,h[0]);lc.setRow(0,1,h[1]);lc.setRow(0,2,h[2]);lc.setRow(0,3,h[3]);lc.setRow(0,4,h[4]);lc.setRow(0,5,h[5]);lc.setRow(0,5,h[5]);lc.setRow(0,6,h[6]);lc.setRow(0,7,h[7]);
delay(delaytime);
lc.setRow(0,0,z[0]);lc.setRow(0,1,z[1]);lc.setRow(0,2,z[2]);lc.setRow(0,3,z[3]);lc.setRow(0,4,z[4]);lc.setRow(0,5,z[5]);lc.setRow(0,5,z[5]);lc.setRow(0,6,z[6]);lc.setRow(0,7,z[7]);
delay(delaytime);
lc.setRow(0,0,f[0]);lc.setRow(0,1,f[1]);lc.setRow(0,2,f[2]);lc.setRow(0,3,f[3]);  lc.setRow(0,4,f[4]); lc.setRow(0,5,f[5]);lc.setRow(0,5,f[5]);lc.setRow(0,6,f[6]);lc.setRow(0,7,f[7]);
delay(delaytime);
lc.setRow(0,0,z[0]);lc.setRow(0,1,z[1]);lc.setRow(0,2,z[2]);lc.setRow(0,3,z[3]);lc.setRow(0,4,z[4]);lc.setRow(0,5,z[5]);lc.setRow(0,5,z[5]);lc.setRow(0,6,z[6]);lc.setRow(0,7,z[7]);
delay(delaytime);
lc.setRow(0,0,h[0]);lc.setRow(0,1,h[1]);lc.setRow(0,2,h[2]);lc.setRow(0,3,h[3]);lc.setRow(0,4,h[4]);lc.setRow(0,5,h[5]);lc.setRow(0,5,h[5]);lc.setRow(0,6,h[6]);lc.setRow(0,7,h[7]);
delay(delaytime);
lc.setRow(0,0,p[0]);lc.setRow(0,1,p[1]);lc.setRow(0,2,p[2]);lc.setRow(0,3,p[3]);lc.setRow(0,4,p[4]);lc.setRow(0,5,p[5]);lc.setRow(0,5,p[5]);lc.setRow(0,6,p[6]);lc.setRow(0,7,p[7]);
delay(delaytime);
lc.setRow(0,0,y[0]);lc.setRow(0,1,y[1]);lc.setRow(0,2,y[2]);lc.setRow(0,3,y[3]);lc.setRow(0,4,y[4]);lc.setRow(0,5,y[5]);lc.setRow(0,5,y[5]);lc.setRow(0,6,y[6]);lc.setRow(0,7,y[7]);
delay(delaytime);
lc.setRow(0,0,p[0]);lc.setRow(0,1,p[1]);lc.setRow(0,2,p[2]);lc.setRow(0,3,p[3]);lc.setRow(0,4,p[4]);lc.setRow(0,5,p[5]);lc.setRow(0,5,p[5]);lc.setRow(0,6,p[6]);lc.setRow(0,7,p[7]);
delay(delaytime);
lc.setRow(0,0,h[0]);lc.setRow(0,1,h[1]);lc.setRow(0,2,h[2]);lc.setRow(0,3,h[3]);lc.setRow(0,4,h[4]);lc.setRow(0,5,h[5]);lc.setRow(0,5,h[5]);lc.setRow(0,6,h[6]);lc.setRow(0,7,h[7]);
delay(delaytime);
lc.setRow(0,0,z[0]);lc.setRow(0,1,z[1]);lc.setRow(0,2,z[2]);lc.setRow(0,3,z[3]);lc.setRow(0,4,z[4]);lc.setRow(0,5,z[5]);lc.setRow(0,5,z[5]);lc.setRow(0,6,z[6]);lc.setRow(0,7,z[7]);
delay(delaytime);
lc.setRow(0,0,f[0]);lc.setRow(0,1,f[1]);lc.setRow(0,2,f[2]);lc.setRow(0,3,f[3]);  lc.setRow(0,4,f[4]); lc.setRow(0,5,f[5]);lc.setRow(0,5,f[5]);lc.setRow(0,6,f[6]);lc.setRow(0,7,f[7]);
delay(delaytime);
delay(delaylong);

  /* Reproducao de todas as animacoes bravas*/ 
lc.setRow(0,0,g[0]);lc.setRow(0,1,g[1]);lc.setRow(0,2,g[2]);lc.setRow(0,3,g[3]);lc.setRow(0,4,g[4]); lc.setRow(0,5,g[5]);lc.setRow(0,5,g[5]);lc.setRow(0,6,g[6]);lc.setRow(0,7,g[7]);
delay(delaytime);
lc.setRow(0,0,b[0]);lc.setRow(0,1,b[1]);lc.setRow(0,2,b[2]);lc.setRow(0,3,b[3]);lc.setRow(0,4,b[4]);lc.setRow(0,5,b[5]);lc.setRow(0,5,b[5]);lc.setRow(0,6,b[6]);lc.setRow(0,7,b[7]);
delay(delaytime);
lc.setRow(0,0,v[0]);lc.setRow(0,1,v[1]);lc.setRow(0,2,v[2]);lc.setRow(0,3,v[3]);lc.setRow(0,4,v[4]);lc.setRow(0,5,v[5]);lc.setRow(0,5,v[5]);lc.setRow(0,6,v[6]);lc.setRow(0,7,v[7]);
delay(delaytime);
lc.setRow(0,0,q[0]);lc.setRow(0,1,q[1]);lc.setRow(0,2,q[2]);lc.setRow(0,3,q[3]);lc.setRow(0,4,q[4]);lc.setRow(0,5,q[5]);lc.setRow(0,5,q[5]);lc.setRow(0,6,q[6]);lc.setRow(0,7,q[7]);
delay(delaytime);
lc.setRow(0,0,k[0]);lc.setRow(0,1,k[1]);lc.setRow(0,2,k[2]);lc.setRow(0,3,k[3]);lc.setRow(0,4,k[4]);lc.setRow(0,5,k[5]);lc.setRow(0,5,k[5]);lc.setRow(0,6,k[6]);lc.setRow(0,7,k[7]);
delay(delaytime);
lc.setRow(0,0,q[0]);lc.setRow(0,1,q[1]);lc.setRow(0,2,q[2]);lc.setRow(0,3,q[3]);lc.setRow(0,4,q[4]);lc.setRow(0,5,q[5]);lc.setRow(0,5,q[5]);lc.setRow(0,6,q[6]);lc.setRow(0,7,q[7]);
delay(delaytime);
lc.setRow(0,0,v[0]);lc.setRow(0,1,v[1]);lc.setRow(0,2,v[2]);lc.setRow(0,3,v[3]);lc.setRow(0,4,v[4]);lc.setRow(0,5,v[5]);lc.setRow(0,5,v[5]);lc.setRow(0,6,v[6]);lc.setRow(0,7,v[7]);
delay(delaytime);
lc.setRow(0,0,b[0]);lc.setRow(0,1,b[1]);lc.setRow(0,2,b[2]);lc.setRow(0,3,b[3]);lc.setRow(0,4,b[4]);lc.setRow(0,5,b[5]);lc.setRow(0,5,b[5]);lc.setRow(0,6,b[6]);lc.setRow(0,7,b[7]);
delay(delaytime);
lc.setRow(0,0,g[0]);lc.setRow(0,1,g[1]);lc.setRow(0,2,g[2]);lc.setRow(0,3,g[3]);lc.setRow(0,4,g[4]); lc.setRow(0,5,g[5]);lc.setRow(0,5,g[5]);lc.setRow(0,6,g[6]);lc.setRow(0,7,g[7]);
delay(delaytime);
lc.setRow(0,0,b[0]);lc.setRow(0,1,b[1]);lc.setRow(0,2,b[2]);lc.setRow(0,3,b[3]);lc.setRow(0,4,b[4]);lc.setRow(0,5,b[5]);lc.setRow(0,5,b[5]);lc.setRow(0,6,b[6]);lc.setRow(0,7,b[7]);
delay(delaytime);
lc.setRow(0,0,v[0]);lc.setRow(0,1,v[1]);lc.setRow(0,2,v[2]);lc.setRow(0,3,v[3]);lc.setRow(0,4,v[4]);lc.setRow(0,5,v[5]);lc.setRow(0,5,v[5]);lc.setRow(0,6,v[6]);lc.setRow(0,7,v[7]);
delay(delaytime);
lc.setRow(0,0,q[0]);lc.setRow(0,1,q[1]);lc.setRow(0,2,q[2]);lc.setRow(0,3,q[3]);lc.setRow(0,4,q[4]);lc.setRow(0,5,q[5]);lc.setRow(0,5,q[5]);lc.setRow(0,6,q[6]);lc.setRow(0,7,q[7]);
delay(delaytime);
lc.setRow(0,0,k[0]);lc.setRow(0,1,k[1]);lc.setRow(0,2,k[2]);lc.setRow(0,3,k[3]);lc.setRow(0,4,k[4]);lc.setRow(0,5,k[5]);lc.setRow(0,5,k[5]);lc.setRow(0,6,k[6]);lc.setRow(0,7,k[7]);
delay(delaytime);
lc.setRow(0,0,q[0]);lc.setRow(0,1,q[1]);lc.setRow(0,2,q[2]);lc.setRow(0,3,q[3]);lc.setRow(0,4,q[4]);lc.setRow(0,5,q[5]);lc.setRow(0,5,q[5]);lc.setRow(0,6,q[6]);lc.setRow(0,7,q[7]);
delay(delaytime);
lc.setRow(0,0,v[0]);lc.setRow(0,1,v[1]);lc.setRow(0,2,v[2]);lc.setRow(0,3,v[3]);lc.setRow(0,4,v[4]);lc.setRow(0,5,v[5]);lc.setRow(0,5,v[5]);lc.setRow(0,6,v[6]);lc.setRow(0,7,v[7]);
delay(delaytime);
lc.setRow(0,0,b[0]);lc.setRow(0,1,b[1]);lc.setRow(0,2,b[2]);lc.setRow(0,3,b[3]);lc.setRow(0,4,b[4]);lc.setRow(0,5,b[5]);lc.setRow(0,5,b[5]);lc.setRow(0,6,b[6]);lc.setRow(0,7,b[7]);
delay(delaytime);
lc.setRow(0,0,g[0]);lc.setRow(0,1,g[1]);lc.setRow(0,2,g[2]);lc.setRow(0,3,g[3]);lc.setRow(0,4,g[4]); lc.setRow(0,5,g[5]);lc.setRow(0,5,g[5]);lc.setRow(0,6,g[6]);lc.setRow(0,7,g[7]);
delay(delaytime);
delay(delaylong);
}

void loop(){  
  while(mood==0) // sad mood
  {
    //SoftwareServo::refresh(); //The software servo needs this to be calles every 50ms to update the servos
    lc.clearDisplay(0);
    writeArduinoOnMatrix();
    delay(delaytime);
  }
}
