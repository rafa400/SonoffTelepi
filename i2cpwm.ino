Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define MIN_PULSE_WIDTH       750
#define MAX_PULSE_WIDTH       2250
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50
// our servo # counter
uint8_t servonum = 0;

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}

void initI2C() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  Wire.begin(D2,D1);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
}

void scanI2C() {
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan

}

void testI2Cpwm() {
  pwm.setPWM(0, 0, pulseWidth(0));
  Serial.println("0");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(45));
  Serial.println("45");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(90));
  Serial.println("90");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(135));
  Serial.println("135");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(180));
  Serial.println("180");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(135));
  Serial.println("135");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(90));
  Serial.println("90");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(45));
  Serial.println("45");
  delay(500);
  pwm.setPWM(0, 0, pulseWidth(0));
  Serial.println("0");
}

void putPWM(int motor,int angle) {
  pwm.setPWM(motor, 0, pulseWidth(angle));
  Serial.print("motor ");
  Serial.print(motor);
  Serial.print(" => ");
  Serial.println(angle);
}

//******************************************************************
// Distance
#define echoPin D6 // Echo Pin
#define trigPin D5 // Trigger Pin

long duration, distance; // Duration used to calculate distance

void initDistance() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  return distance;
}

const int n=8;
int mov[n*2]={60,60, 60,120, 120,120, 120,60,
              60,60, 60,120, 120,120, 120,60 };
int stp[n*2]={90,90, 90,90, 90,90, 90,90,
              90,90, 90,90, 90,90, 90,90 };

              
int forward[n*2];

void goahead() {
      for(int i=0;i<n*2;i++) forward[i]=mov[i];
}
void goback() {
      for(int i=0;i<n*2;i++) forward[i]=mov[n*2-i-1];
}
void gostop() {
      for(int i=0;i<n*2;i++) forward[i]=stp[i];
}

int n_loop=0;
int last_millis=millis();

void i2cpwmcheck() {
   int a=millis();
   if (a>=last_millis+300) 
   if (forward[2*n_loop%n]>0) {
     pinMode(GPIO13Led, OUTPUT);
     digitalWrite(GPIO13Led, HIGH);
     pinMode(D8, OUTPUT);
     digitalWrite(D8, HIGH);
     putPWM(0,forward[2*n_loop%n]);
     putPWM(1,forward[(2*n_loop%n)+1]);
     forward[2*n_loop%n]=0;
     forward[(2*n_loop%n)+1]=0;
     last_millis=a;
     n_loop++;
   } else {
     digitalWrite(GPIO13Led, LOW);
     digitalWrite(D8, LOW);
   }
}

