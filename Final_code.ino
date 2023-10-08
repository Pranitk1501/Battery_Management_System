  /* Battery Management System
uses 24 volt Li-Po Battery */

// ----------------------------------------------------------------------------------------------------------------------------------------------

// inputs
#define volt_pin 36
#define curr_pin 39
#define pot_pin 34
#define temp_pin 35

// driver control pins
#define vref 16
#define dir 23
#define brk 22

// ----------------------------------------------------------------------------------------------------------------------------------------------

// Global variables
float resolution = 4096.0;
float R1 = 1000.0, R2 = 150.0; 
float R = (R2 / (R1 + R2));

// Current calculation variables
float resADC = 3.3 / resolution;
float zeroPoint = 2.5, scale_factor = 0.1;
float curr_error = 0.0;

// Global Thresholds
float volt_threshold = 22;
float curr_threshold = 3;
float temp_threshold = 45;

// ----------------------------------------------------------------------------------------------------------------------------------------------

int get_speed()
{
  int Speed = analogRead(pot_pin);
  int speed_changed = map(Speed, 0, 4095, 0, 255);
  ledcWrite(0, speed_changed);
  return speed_changed;
}

void motor_init()
{
  digitalWrite(brk, HIGH) ;
  digitalWrite(dir, HIGH) ;
  get_speed();
}

void stop_motor()
{
  int speed_pot = analogRead(pot_pin);
  int speedinkms = map(speed_pot, 0, 4095, 0, 72);
  if(speedinkms > 20) {
    for(int i = speed_pot; i >= 20; i--){
      ledcWrite(0, i);
      delay(10);
    }
  }
  else
      ledcWrite(0, 0);
  delay(1000);
}

float get_voltage()
{
  int volt_at_pin = analogRead(volt_pin);
  float voltage_in = (volt_at_pin * 3.3) / resolution;
  float ans = voltage_in / R;
  return ans;
}

float get_current()
{
  float Vout = 0;
  for (int i = 0; i < 100; i++) {
    Vout = (Vout + (resADC * analogRead(curr_pin)));
    delay(1);
  }

  Vout = Vout / 100;
  float ActualCurrent = (Vout - zeroPoint) / scale_factor + curr_error;

  return ActualCurrent;
}

float get_temperature()
{
  int temp_at_pin = analogRead(temp_pin);
  float mv = ( temp_at_pin/4096.0)*5000;
  float cel = mv/10;

  return cel;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("Battery Management System");

  ledcAttachPin(vref, 0);
  ledcSetup(0, 5000, 8);

  pinMode(brk, OUTPUT) ;
  pinMode(dir, OUTPUT) ;

  pinMode(volt_pin, INPUT) ;
  pinMode(curr_pin, INPUT) ;
  pinMode(pot_pin, INPUT) ;
  pinMode(temp_pin, INPUT) ;
  
  motor_init();
  
}

float voltage, current, temperature, motor_speed;

void loop() {
  motor_speed = get_speed();
  
  voltage = get_voltage();
  if(voltage < volt_threshold)
    stop_motor();

  current = get_current();
  if(current > curr_threshold)
    stop_motor();

  temperature = get_temperature();
  if(temperature > temp_threshold)
    stop_motor();

  Serial.print("Speed: ");
  Serial.print(motor_speed);
  Serial.print(" Km/h");
  Serial.println();
  
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" Volts");
  Serial.println();

  Serial.print("Current: ");
  Serial.print(current);
  Serial.print(" Amps");
  Serial.println();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C");
  Serial.println();
}
