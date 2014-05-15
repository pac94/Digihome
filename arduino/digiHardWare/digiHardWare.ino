/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */
#define jaune 2
#define orange 3
#define vert 7

int z = 0;
int inputString[30];         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // print the string when a newline arrives:
  int size = 0;
  if (stringComplete) {
    if(inputString[0] == 0x7E)
    {
      size = inputString[1];
      if(inputString[size + 2] == 0xE7)
      {
        switch(inputString[2])
        {
          case 1 :
                    set_state();
                    break;
          case 2 :
                    get_state();        
                    break;
          case 3 : 
                    manage_temperature();
                    break;
          default :
                    get_state();
        }
      }      
    } 
    // clear the string:
    //Serial.write();
    stringComplete = false;
  }
  
  
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    int inChar = (int)Serial.read(); 
    // add it to the inputString:
    inputString [z++]= inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    //Serial.print((int)inChar);
    if (inChar == 231) {
      z = 0;
      Serial.println("ICI");
      stringComplete = true;
    } 
  }
}

void set_state()
{
  int i = 0;
  while(i < (inputString[1] - 1))
  {
     Serial.print(inputString[3 + i]);
     Serial.print(" : ");
     Serial.println(inputString[4 + i]);
    digitalWrite(inputString[3 + i], inputString[4 + i]);
    i += 2;
  }
}

void get_state()
{
  
}

void manage_temperature()
{
  
}
