/* Battery Management System
   uses 24 volt Li-Po Battery */

// ---------------------------------------------------------------------------

// Inputs
#define VOLT_PIN 36
#define CURR_PIN 39
#define POT_PIN 34
#define TEMP_PIN 35

// Driver control pins
#define VREF_PIN 16
#define DIR_PIN 23
#define BRK_PIN 22

// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------

int getSpeed() {
  int speed = analogRead(POT_PIN);
  int speed_changed = map(speed, 0, 4095, 0, 255);
  ledcWrite(0, speed_changed);
  return speed_changed;
}

void motorInit() {
  digitalWrite(BRK_PIN, HIGH);
  digitalWrite(DIR_PIN, HIGH);
  getSpeed();
}

void stopMotor() {
  int speed_pot = analogRead(POT_PIN);
  int speedinkms = map(speed_pot, 0, 4095, 0, 72);
  if (speedinkms > 20) {
    for (int i = speed_pot; i >= 20; i--) {
      ledcWrite(0, i);
      delay(10);
    }
  } else {
    ledcWrite(0, 0);
  }
  delay(1000);
}

float getVoltage() {
  int volt_at_pin = analogRead(VOLT_PIN);
  float voltage_in = (volt_at_pin * 3.3) / resolution;
  float ans = voltage_in / R;
  return ans;
}

float getCurrent() {
  float Vout = 0;
  for (int i = 0; i < 100; i++) {
    Vout = (Vout + (resADC * analogRead(CURR_PIN)));
    delay(1);
  }

  Vout = Vout / 100;
  float actualCurrent = (Vout - zeroPoint) / scale_factor + curr_error;

  return actualCurrent;
}

float getTemperature() {
  int temp_at_pin = analogRead(TEMP_PIN);
  float mv = (temp_at_pin / 4096.0) * 5000;
  float cel = mv / 10;

  return cel;
}

// ---------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("Battery Management System");

  ledcAttachPin(VREF_PIN, 0);
  ledcSetup(0, 5000, 8);

  pinMode(BRK_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  pinMode(VOLT_PIN, INPUT);
  pinMode(CURR_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);

  motorInit();
}

float voltage, current, temperature, motor_speed;

void loop() {
  motor_speed = getSpeed();

  voltage = getVoltage();
  if (voltage < volt_threshold)
    stopMotor();

  current = getCurrent();
  if (current > curr_threshold)
    stopMotor();

  temperature = getTemperature();
  if (temperature > temp_threshold)
    stopMotor();

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
