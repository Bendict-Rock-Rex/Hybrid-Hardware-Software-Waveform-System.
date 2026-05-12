// ===============================
// FINAL ESP8266 CODE
// ===============================

#include <ESP8266WiFi.h>

const char* ssid = "IMMASHAJI-2.4G";
const char* password = "2236535@";

WiFiServer server(80);

// TOUCH SENSOR PINS

#define T1 D1
#define T2 D5
#define T3 D6
#define T4 D7

void setup()
{
  Serial.begin(9600);

  pinMode(T1, INPUT);
  pinMode(T2, INPUT);
  pinMode(T3, INPUT);
  pinMode(T4, INPUT);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  server.begin();
}

void loop()
{
  // ===============================
  // TOUCH CONTROL
  // ===============================

  checkTouch();

  // ===============================
  // WEB SERVER
  // ===============================

  WiFiClient client = server.available();

  if(client)
  {
    String request = client.readStringUntil('\r');

    client.flush();

    // MODES

    if(request.indexOf("/STAIR") != -1)
      Serial.write('S');

    if(request.indexOf("/RUN") != -1)
      Serial.write('R');

    if(request.indexOf("/BINARY") != -1)
      Serial.write('B');

    if(request.indexOf("/TRIANGLE") != -1)
      Serial.write('T');

    if(request.indexOf("/PING") != -1)
      Serial.write('P');

    if(request.indexOf("/RANDOM") != -1)
      Serial.write('X');

    // SPEED

    if(request.indexOf("/FAST") != -1)
      Serial.write('F');

    if(request.indexOf("/SLOW") != -1)
      Serial.write('L');

    // STOP

    if(request.indexOf("/STOP") != -1)
      Serial.write('Z');

    // ===============================
    // WEBPAGE
    // ===============================

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<html>");
    client.println("<head>");
    client.println("<title>Waveform Engine</title>");
    client.println("</head>");

    client.println("<body>");

    client.println("<h1>WiFi Waveform Engine</h1>");

    client.println("<h2>Modes</h2>");

    client.println("<a href=\"/STAIR\"><button>STAIRCASE</button></a><br><br>");

    client.println("<a href=\"/RUN\"><button>RUNNING</button></a><br><br>");

    client.println("<a href=\"/BINARY\"><button>BINARY</button></a><br><br>");

    client.println("<a href=\"/TRIANGLE\"><button>TRIANGLE</button></a><br><br>");

    client.println("<a href=\"/PING\"><button>PING PONG</button></a><br><br>");

    client.println("<a href=\"/RANDOM\"><button>RANDOM</button></a><br><br>");

    client.println("<h2>Speed</h2>");

    client.println("<a href=\"/FAST\"><button>FASTER</button></a><br><br>");

    client.println("<a href=\"/SLOW\"><button>SLOWER</button></a><br><br>");

    client.println("<h2>Control</h2>");

    client.println("<a href=\"/STOP\"><button>STOP</button></a><br><br>");

    client.println("</body>");
    client.println("</html>");

    delay(1);

    client.stop();
  }
}

// ===============================
// TOUCH SENSOR FUNCTIONS
// ===============================

void checkTouch()
{
  static int modeIndex = 0;

  // ======================
  // MODE CHANGE
  // ======================

  if(digitalRead(T1))
  {
    modeIndex++;

    if(modeIndex > 5)
    {
      modeIndex = 0;
    }

    switch(modeIndex)
    {
      case 0:
        Serial.write('S');
        break;

      case 1:
        Serial.write('R');
        break;

      case 2:
        Serial.write('B');
        break;

      case 3:
        Serial.write('T');
        break;

      case 4:
        Serial.write('P');
        break;

      case 5:
        Serial.write('X');
        break;
    }

    delay(400);
  }

  // ======================
  // SPEED UP
  // ======================

  if(digitalRead(T2))
  {
    Serial.write('F');

    delay(300);
  }

  // ======================
  // SPEED DOWN
  // ======================

  if(digitalRead(T3))
  {
    Serial.write('L');

    delay(300);
  }

  // ======================
  // STOP
  // ======================

  if(digitalRead(T4))
  {
    Serial.write('Z');

    delay(300);
  }
}
