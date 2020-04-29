int encoder_pin = 2; // pulse output from the module
unsigned int rpm=0; // rpm reading
volatile byte pulses=0; // number of pulses
unsigned long timeold=0; 
// number of pulses per revolution
// based on your encoder disc
unsigned int pulsesperturn = 12;
void counter()
{
   //Update count
   pulses++;
}

void setup() {
  // put your setup code here, to run once:
pinMode(9,OUTPUT);      //motor pin 100 ohm
pinMode(10,OUTPUT);      // variable speed 220 ohm
  Serial.begin(9600);
   pinMode(encoder_pin, INPUT);
   //Interrupt 0 is digital pin 2
   //Triggers on Falling Edge (change from HIGH to LOW)
   attachInterrupt(0, counter, FALLING);
   // Initialize
   
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - timeold >= 100) {
      //Don't process interrupts during calculations
      detachInterrupt(0);
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
      timeold = millis();
      pulses = 0;
      Serial.print("RPM = ");
      Serial.println(rpm,DEC);
      //Restart the interrupt processing
      attachInterrupt(0, counter, FALLING);
      // put your main code here, to run repeatedly:
   }
 digitalWrite(10,0); // variable speed resistance
digitalWrite(9,0);    // motor
}
