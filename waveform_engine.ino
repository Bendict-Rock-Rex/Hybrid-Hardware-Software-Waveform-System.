// ===============================
// FINAL ARDUINO CODE
// ===============================

#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, A4);

// LED Pins
int leds[10] = {3,4,5,6,7,8,9,10,11,12};

// 74LS90 Inputs
#define QA A0
#define QB A1
#define QC A2
#define QD A3

char mode = 'S';

bool runningState = true;

int speedDelay = 120;

void setup()
{
  espSerial.begin(9600);

  for(int i=0;i<10;i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(QA, INPUT);
  pinMode(QB, INPUT);
  pinMode(QC, INPUT);
  pinMode(QD, INPUT);

  clearAll();

  randomSeed(analogRead(A5));
}

void loop()
{
  checkCommands();

  if(runningState == false)
  {
    clearAll();
    return;
  }

  // ===============================
  // READ REAL 74LS90 COUNT
  // ===============================

  int count =
      digitalRead(QA)
    + digitalRead(QB) * 2
    + digitalRead(QC) * 4
    + digitalRead(QD) * 8;

  // MOD-10

  count = count % 10;

  // ===============================
  // MODES
  // ===============================

  switch(mode)
  {
    case 'S':
      staircase(count);
      break;

    case 'R':
      running(count);
      break;

    case 'B':
      binaryMode(count);
      break;

    case 'T':
      triangleMode(count);
      break;

    case 'P':
      pingPongMode(count);
      break;

    case 'X':
      randomMode();
      break;
  }

  delay(speedDelay);
}

// ===============================
// COMMANDS
// ===============================

void checkCommands()
{
  if(espSerial.available())
  {
    char data = espSerial.read();

    if(data == 'S')
    {
      mode = 'S';
      runningState = true;
    }

    if(data == 'R')
    {
      mode = 'R';
      runningState = true;
    }

    if(data == 'B')
    {
      mode = 'B';
      runningState = true;
    }

    if(data == 'T')
    {
      mode = 'T';
      runningState = true;
    }

    if(data == 'P')
    {
      mode = 'P';
      runningState = true;
    }

    if(data == 'X')
    {
      mode = 'X';
      runningState = true;
    }

    // STOP

    if(data == 'Z')
    {
      runningState = false;
    }

    // FASTER

    if(data == 'F')
    {
      speedDelay -= 20;

      if(speedDelay < 20)
      {
        speedDelay = 20;
      }
    }

    // SLOWER

    if(data == 'L')
    {
      speedDelay += 20;

      if(speedDelay > 1000)
      {
        speedDelay = 1000;
      }
    }
  }
}

// ===============================
// STAIRCASE MODE
// ===============================

void staircase(int count)
{
  clearAll();

  for(int i=0;i<=count;i++)
  {
    digitalWrite(leds[i], HIGH);
  }
}

// ===============================
// RUNNING MODE
// ===============================

void running(int count)
{
  clearAll();

  digitalWrite(leds[count], HIGH);
}

// ===============================
// BINARY MODE
// ===============================

void binaryMode(int count)
{
  clearAll();

  digitalWrite(leds[0], bitRead(count,0));
  digitalWrite(leds[1], bitRead(count,1));
  digitalWrite(leds[2], bitRead(count,2));
  digitalWrite(leds[3], bitRead(count,3));
}

// ===============================
// TRIANGLE MODE
// ===============================

void triangleMode(int count)
{
  clearAll();

  int level;

  if(count <= 5)
  {
    level = count * 2;
  }
  else
  {
    level = (10 - count) * 2;
  }

  level = constrain(level,0,10);

  for(int i=0;i<level;i++)
  {
    digitalWrite(leds[i], HIGH);
  }
}

// ===============================
// PING PONG MODE
// ===============================

void pingPongMode(int count)
{
  clearAll();

  int pos;

  if(count <= 4)
  {
    pos = count * 2;
  }
  else
  {
    pos = (9 - count) * 2;
  }

  pos = constrain(pos,0,9);

  digitalWrite(leds[pos], HIGH);
}

// ===============================
// RANDOM MODE
// ===============================

void randomMode()
{
  clearAll();

  static int prev = -1;

  int r = random(0,10);

  while(r == prev)
  {
    r = random(0,10);
  }

  prev = r;

  digitalWrite(leds[r], HIGH);
}

// ===============================
// CLEAR LEDs
// ===============================

void clearAll()
{
  for(int i=0;i<10;i++)
  {
    digitalWrite(leds[i], LOW);
  }
}