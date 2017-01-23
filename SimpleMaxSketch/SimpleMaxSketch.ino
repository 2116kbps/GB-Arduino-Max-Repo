//
// Simple Max-Connection Sketch
//
// by Darwin Grosse for Cycling '74
//
// Note: This sketch uses simple coding - rather than efficient coding. No attempt is made to be clever - rather,
// the goal is to make a sketch that will be easy for people to modify regardless of experience level.
//
// --------------------------------------------------------------------------------------------------------------

// variable setup
byte incoming;          // this is where we will store incoming serial data
byte last_analog = -1;  // we start with a negative number so that the first reading will give us a new value!

// the setup part of the sketch
void setup() {
  
  // we need to set up the serial port for communication with the computer
  Serial.begin(57600);
  
  // we need to set up the four digital pins for output. We will also flash the lights to show we have
  // a good program. 
  for (int i=2; i<=5; i++) {    // scan through pins 2-5
    pinMode(i, OUTPUT);         // set the pin for OUTPUT
    digitalWrite(i, HIGH);      // turn the pin ON
    delay(500);                 // wait a half-second
    digitalWrite(i, LOW);       // turn the pin OFF
    delay(500);                 // wait another half-second
  }
  
}  // end of setup

// the loop part of the sketch
void loop() {
  
  // This is where we take data coming from the computer and use it to turn on the LEDs
  // ----------------------------------------------------------------------------------
  if (Serial.available() > 0) {  // if we have incoming data from the computer...
    incoming = Serial.read();    // get one byte from the serial port
    
    switch (incoming) {
      case 0:                    // if the byte is 0
        digitalWrite(2, LOW);    // turn off pin 2
        break;
      case 1:                    // if the byte is 1
        digitalWrite(2, HIGH);   // turn on pin 2
        break;
      case 2:                    // if the byte is 2
        digitalWrite(3, LOW);    // turn off pin 3
        break;
      case 3:                    // if the byte is 3
        digitalWrite(3, HIGH);   // turn on pin 3
        break;
      case 4:                    // if the byte is 4
        digitalWrite(4, LOW);    // turn off pin 4
        break;
      case 5:                    // if the byte is 5
        digitalWrite(4, HIGH);   // turn on pin 4
        break;
      case 6:                    // if the byte is 6
        digitalWrite(5, LOW);    // turn off pin 5
        break;
      case 7:                    // if the byte is 7
        digitalWrite(5, HIGH);   // turn on pin 5
        break;
    }
  }  // end of if for Serial.available()
  
  // This is where is check the current value of the potentiometer, and send the value if it has changed.
  // ----------------------------------------------------------------------------------------------------
  incoming = analogRead(0) >> 3;  // get the current value of the control
                                  // strip the 3 lowest bits - to prevent jitter, and to put the value
                                  // in the typical MIDI range of 0 - 127
  
  if (incoming != last_analog) { // make sure it has changed...
    Serial.write(incoming);      // send the byte to the computer
    last_analog = incoming;      // save the new data
  }  // end of if values have changed
  
} // end of loop()
