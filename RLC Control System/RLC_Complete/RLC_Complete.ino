// Riley Ruckman
// TCES455, Au20
// Project - RLC circuit with unity feedback and PI controller

const int batteryPin = A1;
const int outputPin = A0;
const int inputPin = 8;

double battery, Controller2Input;

//PID constants
double kp = 2.4;
double ki = 24;
double kd = 0;

unsigned long currentTime, previousTime;
double elapsedTime;
double error = 0;
double lastError = 0;
double input, output, Setpoint;
double cumError = 0, rateError = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryPin, INPUT);
  pinMode(outputPin, INPUT);
  pinMode(inputPin, OUTPUT);
  Serial.begin(9600);
  
  battery = analogRead(batteryPin) * ((double)5/1023);
  output = analogRead(outputPin) * ((double)5/1023);

  Setpoint = battery;
}

void loop() {
  // put your main code here, to run repeatedly:

  // Reads voltage of battery in Volts
  battery = analogRead(batteryPin) * ((double)5/1023);

  // Sets Setpoint to the current voltage of the battery
  Setpoint = battery;

  // Reads output of RLC circuit in Volts
  output = analogRead(outputPin) * ((double)5/1023);

  // Calculates controller output given the current output of the RLC circuit
  // and the current voltage of the battery
  Controller2Input = computePID(output) * ((double)255/5);
  delay(10); // Give time for computePID() to calculate

  // Saturation Block
  if (Controller2Input < 0) {
    Controller2Input = 0;
  } else if (Controller2Input > battery*((double)255/5)) {
    Controller2Input = battery*((double)255/5);
  }

  // Sends Controller2Input to RLC circuit
  analogWrite(inputPin, Controller2Input);

  // Prints the current execution time in milliseconds
  Serial.print(millis()); Serial.print("\t");
  // Prints voltage of battery in Volts
  Serial.print(battery); Serial.print("\t");
  // Prints output of RLC circuit in Volts
  Serial.print(output); Serial.print("\t");
  // Prints Controller2Input value in Volts
  Serial.print(Controller2Input * ((double)5/255)); Serial.println();
}

// Computes PID output based off input, Setpoint, and the set gain values Kp, Ki, and Kd
double computePID(double inp){
       
  currentTime = millis();                               // get current time
  elapsedTime = (double)(currentTime - previousTime);   // compute time elapsed from previous computation
  
  error = Setpoint - inp;                               // determine error
  cumError += error * elapsedTime;                      // compute integral
  rateError = (error - lastError)/elapsedTime;          // compute derivative
  
  double out = kp*error + ki*cumError + kd*rateError;   // PID output               
  
  lastError = error;                                    // remember current error
  previousTime = currentTime;                           // remember current time
  
  return out;                                           // have function return the PID output
}
