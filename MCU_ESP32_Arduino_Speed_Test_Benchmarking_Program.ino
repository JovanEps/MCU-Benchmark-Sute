// Arduino Speed Test Benchmarking Program
// Original Program Credit: Arduino.cc
// Modified By: Dan Watson
// synchannel.blogspot.com
// 1-29-2015

// Modified By: Chester Lowrey
// easybotics.com hilo90mhz.com
// 2016-12-1

//Benchmark Sute based on Arduino speed bench. adapted and modified for ESP32 - Xtensa LX6 MCU's
//By: Jovan ivković
//20.02.2017.
//https://hackaday.io/JovanE
  

// This sketch is the speed test portion of the Arduino Show Info program
// http://playground.arduino.cc/Main/ShowInfo

// Certain tests may not compile/run for all boards. Comment them out as necessary:
//  * analogReference()
//  * dtostrf()
//  * bitSet()
//  * y |= (1<<x)

// For the Arduino Zero, "Serial." needs to be "SerialUSB.". A find and replace is the easiest way
// to fix this. The program may also run in forked IDEs (such as Mpide for the chipKIT boards).

// All configuration options listed below for reference

// PIN_1 is used for digitalRead
// PIN_2 is used for digitalWrite / pinMode / analogWrite (PWM)
// Analog read is hardcoded to 0/1

//#define noTitle        // define to remove titles - easier to paste results into comparison spreadsheet
///#define noAnalog       // define to remove analog read/write for ICs without this function
//#define noAnalogRef    // define to remove analogRef test that some cores do not support
//#define noDtostrfTest  // define to remove the dtostrf test that some cores do not support
//#define noBvTest       // define to remove bv test that some cores do not support
//#define USBserialWait  // define to force the main sketch to wait for USB to Serial connection - needed on some native serial boards
//#define noLtoaTest     // define to remove Itoa test that some cores do not support

// Uncomment only one of the below configurations for your specifc board, or make a new one

/*
  // Arduino ATMEGA328
  #define PIN_1 3
  #define PIN_2 4
*/

/*
  // Arduino Leonardo
  #define PIN_1 2
  #define PIN_2 3
  #define noBvTest
  #define USBserialWait
*/

/*
  // Nucleo STM32F103RB - not tested yet
  #define PIN_1 12
  #define PIN_2 13
  #define noAnalog
  #define noBvTest
  #define noLtoaTest
*/

/*
  // Arduino Due
  #define PIN_1 2
  #define PIN_2 3
  #define noDtostrfTest
  #define noBvTest
  #define USBserialWait
*/

/*
  // Arduino Zero Pins
  #define PIN_1 2
  #define PIN_2 3
  #define noBvTest
  #define noDtostrfTest
  #define USBserialWait
*/

/*
  // ESP8266 Pins
  #define PIN_1 4
  #define PIN_2 5
  #define PIN_3 12
*/


// ESP32 Pins
#define PIN_1 25
#define PIN_2 26
#define PIN_3 27
//#define noAnalog


/*
  // NRF52/51 Pins
  #define PIN_1 17
  #define PIN_2 18
  #define PIN_3 19
  #define noDtostrfTest
  #define noBvTest
*/

void setup() {
  //FOR ESP32
  //setup channel 0 with frequency 312500 Hz
  sigmaDeltaSetup(0, 312500);
  //attach pin 18 to channel 0
  sigmaDeltaAttachPin(18, 0);
  //initialize channel 0 to off
  sigmaDeltaWrite(0, 0);
  //---------
  Serial.begin(9600);

#ifdef USBserialWait
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

#endif

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, INPUT);
}

//*********************
//***     MAIN      ***
//*********************
void loop() {
  Serial.println("\n\r");
  Serial.println("Speed Test will begin momentarily.");
  Serial.println("");
  delay(500);

  speedTest();// Do test
  delay(7000);
}

//****** Benchmark *********
void speedTest(void) {
  register int i, j;
  volatile unsigned char c1, c2;
  volatile int v;
  volatile long l1, l2;
  volatile float f1, f2;
  int p, q;
  long int r;
  unsigned long m, n;
  float d, overhead;
  char buffer[30];

#ifndef noTitle
  Serial.println(F(""));
  Serial.println(F("Speed test"));
  Serial.println(F("----------"));
  Serial.print(F("F_CPU = "));
#endif
  Serial.print(F_CPU / 1000000, DEC);
  Serial.println(F(" MHz"));
#ifndef noTitle
  Serial.print(F("1/F_CPU = "));
#endif
  Serial.print((1000000.0 / (float)F_CPU), 4);
  Serial.println(F(" us"));

  delay(800);    // Allow the Serial text to be transmitted
#ifndef noTitle
  Serial.print(F("  nop                       : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
      asm volatile ("nop");
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;           // in micro seconds
  // Calculate overhead with 'nop' instruction per loop in microseconds
  overhead = d - (20.0 * (1000000.0 / (float)F_CPU));
  d -= overhead;
  d /= 20.0;             // per instruction
  Serial.print (d, 3);
  Serial.println (F(" us"));

#ifndef noTitle
  Serial.print(F("  digitalRead               : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);

      digitalRead(PIN_1);
      digitalRead(PIN_1);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  digitalWrite              : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);

      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_2, LOW);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  pinMode                   : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);

      pinMode(PIN_2, INPUT);
      pinMode(PIN_2, OUTPUT);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  multiply byte             : "));
#endif
  c1 = 2;
  c2 = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
      c1 *= c2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  divide byte               : "));
#endif
  c1 = 253;
  c2 = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
      c1 /= c2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  add byte                  : "));
#endif
  c1 = 1;
  c2 = 2;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
      c1 += c2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  multiply integer          : "));
#endif
  volatile int x, y;
  x = 2;
  y = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
      x *= y;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  divide integer            : "));
#endif
  x = 31415;
  y = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
      x /= y;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  add integer               : "));
#endif
  x = 1;
  y = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
      x += y;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  multiply long             : "));
#endif
  l1 = 2;
  l2 = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
      l1 *= l2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  divide long               : "));
#endif
  l1 = 2000000000L;
  l2 = 3;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 2000; j++)
    {
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
      l1 /= l2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  add long                  : "));
#endif
  l1 = 500000000L;
  l2 = 123;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
      l1 += l2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  multiply float            : "));
#endif
  f1 = 3.24;
  f2 = 1.25;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
      f1 *= f2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  divide float              : "));
#endif
  f1 = 312645.24;
  f2 = 1.21;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 2000; j++)
    {
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
      f1 /= f2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  add float                 : "));
#endif
  f1 = 9876.54;
  f2 = 1.23;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
      f1 += f2;
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));



#ifndef noTitle
  Serial.print(F("  itoa()                    : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
      itoa(i, buffer, 10);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noLtoaTest
  long int l = 314159L;
#ifndef noTitle
  Serial.print(F("  ltoa()                    : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 500; j++)
    {
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
      ltoa(l, buffer, 10);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));
#endif


#ifndef noDtostrfTest
#ifndef noTitle
  Serial.print(F("  dtostrf()                 : "));
#endif
  float d3;
  d3 = 3.14159265;
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
      dtostrf (d3, 6, 2, buffer);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));
#endif

#ifndef noTitle
  Serial.print(F("  random()                  : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
      r = random(-2147483647, 2147483647);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));

#ifndef noBvTest
#ifndef noTitle
  Serial.print(F("  y |= (1<<x)               : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
      v |= _BV(12);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));
#endif

#ifndef noTitle
  Serial.print(F("  bitSet()                  : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
      bitSet (v, 12);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));

  /*
    #ifndef noAnalogRef
    #ifndef noTitle
    Serial.print(F("  analogReference()         : "));
    #endif
    delay(70);     // Allow the Serial text to be transmitted
    m=millis();
    for (i=0; i<20; i++)
    {
      for (j=0; j<10000; j++)
      {
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
        analogReference (EXTERNAL);
        analogReference (DEFAULT);
      }
    }
    n=millis();
    d = ((float)n - (float)m) / ((float)i * (float)j);
    d *= 1000.0;
    d -= overhead;
    d /= 20.0;
    Serial.print (d,3);
    Serial.println (F(" us"));
    #endif
  */


#ifndef noAnalog
#ifndef noTitle
  Serial.print(F("  analogRead()              : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
      analogRead (0);
      analogRead (1);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));

  //***************** ESP32 Only  *un-comment for others
  /*
    #ifndef noTitle
    Serial.print(F("  analogWrite() PWM         : "));
    #endif
    // Using pin 13 (system led) for output.
    delay(70);     // Allow the Serial text to be transmitted
    m = millis();
    for (i = 0; i < 1; i++)
    {
      for (j = 0; j < 10000; j++)
      {
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
        analogWrite (PIN_2, 100);
        analogWrite (PIN_2, 200);
      }
    }
    n = millis();
    d = ((float)n - (float)m) / ((float)i * (float)j);
    d *= 1000.0;
    d -= overhead;
    d /= 20.0;
    Serial.print (d, 3);
    Serial.println (F(" us"));
    #endif
  */

 //***************** ESP32 Only  *comment for others 
#ifndef noTitle
    Serial.print(F("  analogWrite DAC \n\r - ESP32 dacWrite()         : ")); //DacWrite function work only on PIN25,PIN26 
#endif 
    delay(70);     // Allow the Serial text to be transmitted
    m = millis();
    for (i = 0; i < 1; i++)
      {
        for (j = 0; j < 10000; j++) {
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
          dacWrite(25, 100);
          dacWrite(25, 200);
        }
      }
      n = millis();
      d = ((float)n - (float)m) / ((float)i * (float)j);
      d *= 1000.0;
      d -= overhead;
      d /= 20.0;
      Serial.print (d, 3);
      Serial.println (F(" us"));
#endif
  
 //*****************  ESP32 Only  *comment for others   
#ifndef noTitle
  Serial.print(F("  analogWrite \n\r - ESP32 SigmaDeltaWr.      : "));  // Based on SigmaDelta example 312500
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 10000; j++)
    {
      //analogWrite (PIN_2, 100);
      //analogWrite (PIN_2, 200);

      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
      sigmaDeltaWrite(0, 100);
      sigmaDeltaWrite(0, 200);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));



#ifndef noTitle
  Serial.print(F("  delay(1)                  : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 100; j++)
    {
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
      delay(1);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  delay(100)                : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 2; j++)
    {
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
      delay(100);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  delayMicroseconds(2)      : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 30; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
      delayMicroseconds(2);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  delayMicroseconds(5)      : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      //Serial.println ("Working");
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
      delayMicroseconds(5);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


#ifndef noTitle
  Serial.print(F("  delayMicroseconds(100)    : "));
#endif
  delay(70);     // Allow the Serial text to be transmitted
  m = millis();
  for (i = 0; i < 1; i++)
  {
    for (j = 0; j < 1000; j++)
    {
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
      delayMicroseconds(100);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  d *= 1000.0;
  d -= overhead;
  d /= 20.0;
  Serial.print (d, 3);
  Serial.println (F(" us"));


  Serial.println(F("-----------"));
}

