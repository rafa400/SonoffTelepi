Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
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
}

