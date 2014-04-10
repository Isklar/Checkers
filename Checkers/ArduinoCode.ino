#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
char incomingBytes[4];   // for incoming serial data
int incomingNumber;
int ldrCode = 0;
int ldrVal = 0;
// initialize the stepper library on pins 8 through 11:
Stepper stepperY(stepsPerRevolution, 2,3,4,5);  
Stepper stepperZ(stepsPerRevolution, 40,41,42,43);            
Stepper stepperX(stepsPerRevolution, 10,11,12,13);  

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println("Initialising Steppers...");
  // set the speed at 60 rpm:
  stepperX.setSpeed(60);
  stepperY.setSpeed(60);
  stepperZ.setSpeed(60);

  Serial.println("Initialising Pins...");
  // Magnet
  pinMode(A12, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  Serial.println("Ready!");
}

void loop() {

  while(Serial.available() < 0);
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    Serial.readBytesUntil('x', incomingBytes, 4);
    Serial.print("Received: ");
    for (int i = 0; i < 4; i++){
      Serial.print(incomingBytes[i]);
    }

    if(incomingBytes[0] == 'm'){
      Serial.print("\nMagnet: "); 
      if(incomingBytes[1] - '0' == 0){
        Serial.println("off"); 
        digitalWrite(A12, LOW);
      }
      if(incomingBytes[1] - '0' == 1){
        Serial.println("on"); 
        digitalWrite(A12, HIGH);
      }
    }

    incomingNumber = 0;
    ldrVal = 0;
    if(incomingBytes[0] == 'l'){           
      incomingNumber = incomingBytes[1]-'0';
      incomingNumber = (incomingNumber*10) + incomingBytes[2]-'0';
      //Serial.print("\nLDR: ");
     // Serial.print(incomingNumber); 
      int x = 0;
      for (x = 0; x <13;x++){
      ldrVal = analogRead(x);
      Serial.print(x);
      Serial.print(" - ");
      Serial.println(ldrVal);
    }

    }

    incomingNumber = 0;
    if(incomingBytes[0] == 's'){
      incomingNumber = incomingBytes[1]-'0';
      incomingNumber = (incomingNumber*10) + incomingBytes[2]-'0';
      incomingNumber = (incomingNumber*10) + incomingBytes[3]-'0';
      Serial.println("\nX - clockwise");
      stepperX.step(incomingNumber);
      delay(800);
      Serial.println("X - counterclockwise");
      stepperX.step(-incomingNumber);
      delay(800);

      Serial.println("Y - clockwise");
      stepperY.step(incomingNumber);
      delay(800);
      Serial.println("Y - counterclockwise");
      stepperY.step(-incomingNumber);
      delay(800); 

      Serial.println("Z - clockwise");
      stepperZ.step(incomingNumber);
      delay(800);
      Serial.println("Z - counterclockwise");
      stepperZ.step(-incomingNumber);
      delay(800);
    }

    incomingNumber = 0;
    if(incomingBytes[0] == 'q'){
      incomingNumber = incomingBytes[1]-'0';
      incomingNumber = (incomingNumber*10) + incomingBytes[2]-'0';
      incomingNumber = (incomingNumber*10) + incomingBytes[3]-'0';
      Serial.print(incomingNumber);
      switch (incomingNumber){
        
      case 999:
        stepperZ.step(-400);
        delay(100);
        break;
       case 888:
        stepperZ.step(400);
        delay(100);
        break;
      case 431:
        stepperX.step(-200);
        delay(500);
        stepperZ.step(-400);
        delay(100);
        break;
      case 430:
        stepperX.step(200);
        delay(500);
        stepperZ.step(400);
        delay(100);
        break;
      case 411:
        stepperX.step(200);
        delay(500);
        stepperZ.step(-400);
        delay(100);
        break;
      case 410:
        stepperX.step(-200);
        delay(500);
        stepperZ.step(400);
        delay(100);
        break;
      case 341:
        stepperX.step(-400);
        delay(500);
        stepperZ.step(-200);
        delay(100);
        break;
      case 340:
        stepperX.step(400);
        delay(500);
        stepperZ.step(200);
        delay(100);
        break;
      case 321:
        stepperZ.step(-200);
        delay(100);
        break;
      case 320:
        stepperZ.step(200);
        delay(100);
        break;
      case 301:
        stepperX.step(400);
        delay(500);
        stepperZ.step(-200);
        delay(100);
        break;
      case 300:
        stepperX.step(-400);
        delay(500);
        stepperZ.step(200);
        delay(100);
        break;
      case 231:
        stepperX.step(-200);
        delay(100);
        break;
      case 230:
         stepperX.step(200);
        delay(100);
        break;
      case 211:
        stepperX.step(200);
        delay(100);
        break;
      case 210:
        stepperX.step(-200);
        delay(100);
        break;
      case 141:
        stepperX.step(-400);
        delay(500);
        stepperZ.step(200);
        delay(100);
        break;
      case 140:
        stepperX.step(400);
        delay(500);
        stepperZ.step(-200);
        delay(100);
        break;
      case 121:
        stepperZ.step(200);
        delay(100);
        break;
      case 120:
        stepperZ.step(-200);
        delay(100);
        break;
      case 101:
        stepperX.step(400);
        delay(500);
        stepperZ.step(200);
        delay(100);
        break;
      case 100:
        stepperX.step(-400);
        delay(500);
        stepperZ.step(-200);
        delay(100);
        break;
      case 31:
        stepperX.step(-200);
        delay(500);
        stepperZ.step(400);
        delay(100);
        break;
      case 30:   
        stepperX.step(200);
        delay(500);
        stepperZ.step(-400);
        delay(100);
        break;
      case 11:   
        stepperX.step(200);
        delay(500);
        stepperZ.step(400);
        delay(100);
        break;
      case 10:   
        stepperX.step(-200);
        delay(500);
        stepperZ.step(-400);
        delay(100);
        break;
      }

    }
  }
}



