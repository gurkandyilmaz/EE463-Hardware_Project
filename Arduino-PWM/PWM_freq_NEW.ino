
float D=0; //value read by analogRead(), from pot, 0 and 1023
float duty=0; // Duty cycle written to the PWM_pin.


int pot = A0;   // analog input to arduino from middle leg of the potentiometer to A0.
int pwm_pin=6;  // pwm output pin
int divider=8;  /*needed to divide the base frequency.
                  *The base frequency for pins 3,11(timer2)and 9,10(timer1) is 31250 Hz.
                  *The base frequency for pins 5 and 6(timer0) is 62500 Hz.
                  *can be 1,8,64,256,1024 for the pins 5,6,9,10
                  *can be 1,8,32,64,128,256,1024 for the pins 3 and 11
                  *divided frequencies for the pins 5,6 ; 62500,7812,976,244,61 Hz
                  *divided freq for the pins 9,10; 31250,3906,488,122,30 Hz
                  *divided freq for the pins 3,11; 31250,3906,980,490,245,122,30 Hz
                  */
/*   Notes on the usage of analog pins
 *   Changes on pins 5, 6 may cause the delay() and millis() functions to stop working.
 *   Changes on pins 9 or 10 will cause the Servo library to function incorrectly.
 *  PWM frequency divisors.
 *  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4 
 */
void setup() {
  Serial.begin(9600); 
  pinMode(pwm_pin,OUTPUT);
  pinMode(pot,INPUT);
  digitalWrite(pwm_pin,LOW);
   // Pwm frequency change
  setPwmFrequency(pwm_pin, divider); //Divides a given PWM pin frequency by a divisor.
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode; //set timer0 freq (in this case 7812 Hz)
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode; //set timer1 freq (in this case 3906 Hz)
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;  //set timer2 freq (in this case 3906 Hz)
  }
}

void loop() {                
                D=analogRead(pot);
                duty = map(D, 0, 1023, 0, 255);      
                analogWrite(pwm_pin,duty);
                //delay(10);
                Serial.print("The duty cycle: ");
                Serial.println(D) ;  
              
}
