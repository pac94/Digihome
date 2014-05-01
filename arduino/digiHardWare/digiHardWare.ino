

#define red 6

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(red, OUTPUT); 
}

void loop() {
  // print the string when a newline arrives:
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if(inChar == 'a')
    {
      if(digitalRead(red) == LOW)
        digitalWrite(red,HIGH);
      else
        digitalWrite(red,LOW);
      inChar = 0;
    }
  }
}



