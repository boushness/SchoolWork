// Riley Ruckman
// TCES455, Au20
// Project - RLC circuit with unity feedback and PI controller

const int batteryPin = 1;
const int outputPin = 0;
const int inputPin = 8;

double battery, output, error;

PID myPID(&output, &afterController, &battery, 2.4, 24, 0, REVERSE);

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryPin, INPUT);
  pinMode(outputPin, INPUT);
  pinMode(inputPin, OUTPUT);
  Serial.begin(9600);
  
  battery = analogRead(batteryPin);
  output = analogRead(outputPin);

  error = battery - output;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  battery = analogRead(batteryPin);

  output = analogRead(outputPin);

  error = battery - output;

  if (error < 0) {
    error = 0;
  }
  analogWrite(inputPin, error*((double)255/1023));

  Serial.print(millis()); Serial.print("\t");
  Serial.print(battery * ((double)5/1023)); Serial.print("\t");
  Serial.print(output * ((double)5/1023));
  Serial.println();
}
