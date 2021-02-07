const double LOWER_LIMIT = 25.0; // temperature desired minimum, deg. C
const double UPPER_LIMIT = 30.0; // temperature desired maximum, deg. C

const double OFFSET_VOLTAGE = .5; // TMP36 offset voltage, V
const double OUTPUT_VOLTAGE_SCALING = .01; // TMP36 output voltage scaling, V/deg. C
const double SUPPLY_VOLTAGE = 5; // Supply voltage, V

const int ADC_RANGE = 1023; // TMP36 input max ADC value
const int SENSOR = 0; // TMP36 input number
const int RLED = 11; // Red led output
const int GLED = 10; // Green led output
const int BLED = 9; // Blue led output

double k, b;

void setup()
{
  k = SUPPLY_VOLTAGE / (ADC_RANGE * OUTPUT_VOLTAGE_SCALING);
  b = -OFFSET_VOLTAGE / OUTPUT_VOLTAGE_SCALING;
  
  Serial.begin(9600);
}

void loop()
{
  int x = analogRead(SENSOR);
  double t = k * x + b;
  
  Serial.println(t);
  delay(500);

  if (t > UPPER_LIMIT)
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
    return;
  }

  if (t <= LOWER_LIMIT)
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
    return;
  }

  digitalWrite(RLED, LOW);
  digitalWrite(GLED, HIGH);
  digitalWrite(BLED, LOW);
}
