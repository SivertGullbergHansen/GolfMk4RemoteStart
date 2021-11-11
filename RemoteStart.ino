// ====================================================================================
// Authors: Sigurd Myhre & Sivert Gullberg Hansen
// Version: 4.0
// Required Modules: SIM800L
// ====================================================================================

#include <SoftwareSerial.h>

SoftwareSerial sim800l(3, 2); //SIM800L TX and RX pins

// User variables (You have to change these)
// ====================================================================================
String userPhone = "95756768";                                              // Whitelisted phone number (country code not required)
String statusString = "The engine is X,\nThe running time is set to Y min"; // The string we return to the userPhone when asking for a status. X is engineStatus, Y is RunTime
String engineStopped = "stopped";                                           // Used in status-string
String engineStarted = "started";                                           // Used in status-string
// ====================================================================================

// Arduino to car pins (Change if you're not using the same digital pins on the arduino as me)
// ====================================================================================
int ignPin = 4;         // Gives power to the ignition
int startPin = 5;       //Activates the starter solenoid
int lightFanPin = 6;    //Turns lights and blower motor on
int NeutSwitchPin = 11; // Tells us if the car is in neutral
int IgnHotPin = 12;     //Telles us if sommebody has insterted the key into the ignition
int voltagePin = 5;
// ====================================================================================

// Commands (These will be looked for as trigger words in the SMS you send to the car, change these to your own language)
// ====================================================================================
String cmdStatus = "status";     //Sends an status reply to the userPhone, when an SMS with the word "status" is recived
String cmdChangeTime = "change"; //Changes the runTime when an SMS with the word "endre" is recieved with an number between 1 - 40 min.
String cmdStart = "start";       //Trigger word for the engine to start
String cmdStop = "stop";         //Trigger word for the engine to stop, this will also send and reply to the userPhone that the engine is stopped
// ====================================================================================

// Timers (You don't have to change these)
// ====================================================================================
long startTime = 0;    // Which time our engine started running
long RunTime = 900000; // ms to have engine running before shutting off after starting
int maxTime = 40;      // max minutes RunTime is allowed to be set to by the user via SMS
// ====================================================================================

//Timers for the engine start procedure(Change these if necesarry)
// ====================================================================================
int primeDuration = 2000;   //This is the time the engine is primed for, on petrol cars this doesnt need to be long. But on diesel cars this may be set to longer for the glowplug to warm up
int starterDuration = 2000; //This is the timer that controlls how long the starter should be engaged, change accordingly
// ====================================================================================

//Resisotrs for voltage devider(Change these if necesarry)
// ====================================================================================
float R1 = 9730;
float R2 = 4580;
// ====================================================================================

//Sivert har liten tiss

void pinSetup() // Initialize arduino pins
{
  pinMode(ignPin, OUTPUT);
  pinMode(startPin, OUTPUT);
  pinMode(lightFanPin, OUTPUT);
  pinMode(NeutSwitchPin, INPUT_PULLUP);
  pinMode(IgnHotPin, INPUT);
  pinMode(voltagePin, INPUT);

  digitalWrite(ignPin, LOW);
  digitalWrite(startPin, LOW);
  digitalWrite(lightFanPin, LOW);
  digitalWrite(NeutSwitchPin, LOW);
}

void sim800Setup() // Initialize sim-reader
{
  sim800l.begin(9600); //Start softwareserial for the sim800l module

  Serial.println("SIM800L Initializing...");
  delay(1000);
  sim800l.println("AT"); //Configure text mode
  delay(1000);
  sim800l.println("AT+CMGF=1"); //Start handshake with SIM800L and return OK once complete
  delay(1000);
  sim800l.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
}

void changePin(int Pin, int PinMode, int DelayTime)
{
  digitalWrite(Pin, PinMode);
  delay(DelayTime);
}

void sendStatus() // Sends a reply to the userPhone including vehicle-status
{
  String Running = "";
  String returnString = statusString;
  if (digitalRead(ignPin) == LOW)
  {
    Running = engineStopped;
  }
  else if (digitalRead(ignPin) == HIGH)
  {
    Running = engineStarted;
  }
  returnString.replace("X", Running);
  returnString.replace("Y", String(RunTime / 60000));
  Reply(returnString);
}

void changeRunTime() // Changes how long the engine stays powered on before powering down
{
}

void startEngine() // Starts our engine
{
  changePin(ignPin, 1, primeDuration);
  changePin(startPin, 1, starterDuration);
  changePin(startPin, 0, starterDuration);
  digitalWrite(lightFanPin, HIGH);
  startTime = millis();
  delay(2000);

  if (batteryVoltage() < 13)
    Reply("Engine has failed starting, please retry");
}

void stopEngine() // Stops our engine
{
  digitalWrite(ignPin, LOW);
  digitalWrite(startPin, LOW);
  digitalWrite(lightFanPin, LOW);
  Reply("Engine is stopped");
}

void readCommand(String messageString) // Read commands from messageStrings
{
  Serial.println("Message Received: \n" + messageString);

  if (messageString.indexOf(cmdStatus) >= 0)
  {
    Serial.println("Command: Status Confirmed");
    sendStatus();
  }
  else if (messageString.indexOf(cmdChangeTime) >= 0)
  {
    Serial.println("Command: Change Time Confirmed");
    changeRunTime();
  }
  else if (messageString.indexOf(cmdStart) >= 0)
  {
    Serial.println("Command: Start Confirmed");
    startEngine();
  }
  else if (messageString.indexOf(cmdStop) >= 0)
  {
    Serial.println("Command: Stop Confirmed");
    stopEngine();
  }
  else
  {
    Serial.println("No command found!");
  }
}

String returnMessage() // Return Message Received, can only be run once sim800 is available.
{
  String incomingData = sim800l.readString(); // Get the data from the serial port.
  incomingData.toLowerCase();
  return incomingData;
}

void CheckPhone(String messageString) // Compares userPhone-value to message's phone number
{
  String stringToCheck = messageString;
  stringToCheck.trim(); // Remove whitespace
  stringToCheck = stringToCheck.substring(0, userPhone.length() + 12);

  if (stringToCheck.indexOf(userPhone) >= 0)
  {
    readCommand(messageString);
  }
  else if (messageString.length() > 18)
  {
    Serial.println("Phone number invalid! Has to be: " + userPhone);
  }
}

int batteryVoltage()
{
  return 0;
}

void engineLoop() // Checks our engine's status and applies measures
{
  if (digitalRead(IgnHotPin) == HIGH) // If key is turned while remote start active, disable remote start-script
  {
    digitalWrite(startPin, LOW);
    digitalWrite(ignPin, LOW);
    digitalWrite(lightFanPin, LOW);
  }

  if ((digitalRead(ignPin) == HIGH) && (millis() - startTime >= RunTime)) // Shut off engine when RunTime reached
  {
    digitalWrite(ignPin, LOW);
    digitalWrite(lightFanPin, LOW);
  }
}

void setup() // Setup arduino
{
  Serial.begin(115200); //Start serial over USB at speed 115200
  sim800Setup();
  pinSetup();
}

void loop() // Arduino loop
{
  updateSerial();
  engineLoop();
}

void updateSerial() // Our update loop, updating sim-reader and arduino serial-port when available
{
  delay(500);
  while (Serial.available())
  {
    sim800l.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while (sim800l.available())
  {
    Serial.write(sim800l.read()); //Forward what Software Serial received to Serial Port;
    CheckPhone(returnMessage());
  }
}

void Reply(String text) // Sends a reply to our phone
{
  sim800l.print("AT+CMGF=1\r");
  delay(1000);
  sim800l.print("AT+CMGS=\"" + userPhone + "\"\r");
  delay(1000);
  sim800l.print(text);
  delay(100);
  sim800l.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1000);
  Serial.println("SMS Sent Successfully.");
}
