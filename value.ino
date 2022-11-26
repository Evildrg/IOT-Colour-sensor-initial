#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12
#define led 13
 
// Calibration Values
// Get these from Calibration Sketch

 
// Variables for Color Pulse Width Measurements
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
// Variables for final Color values
 
int redValue;
int greenValue;
int blueValue;
int rmax=0;
int rmin=5000;
int gmax=0;
int gmin=5000;
int bmax=0;
int bmin=5000;
int b,g,r;
void setup() {
 
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  
  // Setup Serial Monitor
  Serial.begin(9600);

  Serial.println("put black colour, checking in: "); 
  for(int i=10;i>0;i--){  

  Serial.println(i +" ");
  delay(1000);
  }
  for(int i=0;i<100;i++){  
  // Read Red value
  redPW = getRedPW();
  Serial.println(redPW);
  // Map to value from 0-255
  if (redPW>rmax){
    rmax=redPW;
  }
  // Delay to stabilize sensor
  delay(20);}
  
  for(int i=0;i<100;i++){  
  // Read Green value
  greenPW = getGreenPW();
  if (greenPW>gmax){
    gmax=greenPW;
  }

  delay(20);}

  for(int i=0;i<100;i++){
  // Read Blue value
  bluePW = getBluePW();
  if (bluePW>bmax){
    bmax=bluePW;
  }
  delay(20);}
  
  Serial.println("Put a white paper. Checking in:");
  for(int i=10;i>0;i--){  

  Serial.print(i +" ");
  delay(1000);
  }             
  for(int i=0;i<100;i++){  
  // Read Red value
  redPW = getRedPW();
  Serial.println(redPW);
  if (redPW<rmin){
    rmin=redPW;
  }
  // Delay to stabilize sensor
  delay(20);}
  
  for(int i=0;i<100;i++){  
  // Read Green value
  greenPW = getGreenPW();
  Serial.println(greenPW);

  if (greenPW<gmin){
    gmin=greenPW;
  }
  delay(20);}

  for(int i=0;i<100;i++){
  // Read Blue value
  bluePW = getBluePW();
  Serial.println(bluePW);
  if (bluePW<bmin){
    bmin=bluePW;
  }
  delay(20);}

  Serial.println(rmin);
  Serial.println(rmax);
  
}
 
void loop() {
redValue=0;
blueValue=0;
greenValue=0;
  
  for(int i=0;i<100;i++){  
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue =redValue+ map(redPW, rmin,rmax,255,0);
  // Delay to stabilize sensor
  delay(20);}
  
  for(int i=0;i<100;i++){  
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = greenValue+ map(greenPW, gmin,gmax,255,0);
  // Delay to stabilize sensor
  delay(20);}

  for(int i=0;i<100;i++){
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = blueValue+map(bluePW, bmin,bmax,255,0);
  // Delay to stabilize sensor
  delay(20);}
  b=blueValue/100;
  r=redValue/100;
  g=greenValue/100;
  
  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue/100);
  Serial.print(" - Green = ");
  Serial.print(greenValue/100);
  Serial.print(" - Blue = ");
  Serial.println(blueValue/100);

  if(g-r <=30 && r-g<=30){
    if (g-b <=50){
      if(g<50){
        Serial.print("black colour");
      }
      else{
      Serial.print("white colour");
      }
    }
    else{
      Serial.print("Yellow colour");
    }
  }
   else{
    if (r>b ){
      if (r>g){
      Serial.print("Red colour");
    }
    else{
      Serial.print("Green colour");
    }
    }
    else{
      if (b>g){
        Serial.print("blue colour");
      }
      else{
      Serial.print("Green colour");
      }
      
     
    }
   }
  
}
 
 
// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
