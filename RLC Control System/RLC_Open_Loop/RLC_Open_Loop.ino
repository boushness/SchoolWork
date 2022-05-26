// Riley Ruckman
// TCES455, Au20
// Project - RLC circuit with unity feedback and PI controller

const int batteryPin = 1;
const int outputPin = 0;
const int inputPin = 8;

double battery, output;

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryPin, INPUT);
  pinMode(outputPin, INPUT);
  pinMode(inputPin, OUTPUT);
  Serial.begin(9600);
  
  battery = analogRead(batteryPin);
  output = analogRead(outputPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  battery = analogRead(batteryPin);

  //analogWrite(inputPin, battery*((double)255/1023));

  output = analogRead(outputPin);

  Serial.print(millis()); Serial.print("\t");
  Serial.print(battery * ((double)5/1023)); Serial.print("\t");
  Serial.print(output * ((double)5/1023));
  Serial.println();
}
