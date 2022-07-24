#include <Servo.h>
Servo myservoL;      //create object for left servo
Servo myservoR;      //create object for right servo
Servo myservoJ;      //create object for joint servo

#define dir1Left 3   //direction 1 of left motors
#define dir2Left 2   //direction 2 of left motors
#define dir1Right 4  //direction 1 of right motors
#define dir2Right 5  //direction 2 of right motors

#define servoLeft A0
#define servoRight A1
#define servoJoint A2

void setup() {
  
  Serial.begin(115200);
  while(!Serial) {
    ;
  }
  pinMode(dir1Left, OUTPUT);
  pinMode(dir2Left, OUTPUT);
  pinMode(dir1Right, OUTPUT);
  pinMode(dir2Right, OUTPUT);

  //attach servos
  myservoL.attach(servoLeft);
  myservoR.attach(servoRight);
  myservoJ.attach(servoJoint);

}

char uart_rec;  //uart receive from ESP32
int valJ = 60;    // rotation degree of servo
int pos = 0;
int num = 0;

void loop() {
  if (Serial.available()) {
    uart_rec = char(Serial.read());
   // Serial.println(uart_rec);
  }

  if (uart_rec == 'w') {        // Stands for WASD keyboards as controller
    moveForward();
  }
  else if (uart_rec == 's') {   // Stands for WASD keyboards as controller
    moveBackward();
  }
  else if (uart_rec == 'a') {   // Stands for WASD keyboards as controller
    moveLeft();
  }
  else if (uart_rec == 'd') {   // Stands for WASD keyboards as controller
    moveRight();
  }
  else if (uart_rec == 'q') {   // Stands for "quit" to stop
    stopMove();
  }
/*  else if (uart_rec == '0' || uart_rec == '1' || uart_rec == '2' || uart_rec == '3' || uart_rec == '4' || uart_rec == '5' || uart_rec == '6' ) {
    valR = int(uart_rec);
    valR = valR * 30;
    myservoR.write(valR);
    delay(20);
  }*/
//    valR = map(valR, 0, 6, 0, 180);
  
  else if (uart_rec == ';') {
    ;   // stop mode
  }
  else if (uart_rec == '0') {             // set right servo to initial position (0 degree)
    myservoR.write(0);
    delay(20);
    uart_rec = ';';
  }
  else if (uart_rec == '1') {
    for (pos = 0; pos <= 20; pos++) {       // increase degree from 0 - 20 slowly
      myservoR.write(pos);                 // tell servo to go to position in variable 'pos'
      delay(20);                           // waits 20 ms for the servo to reach the position
   }
   uart_rec = ';';
  }
  else if (uart_rec == '2') {
    for (pos = 20; pos <= 40; pos++) {    // increase degree from 20 - 40 slowly
      myservoR.write(pos);                // tell servo to go to position in variable 'pos'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
   uart_rec = ';';
  }
  else if (uart_rec == '3') {
    for (pos = 40; pos <= 150; pos++) {    // increase degree from 40 - 150 slowly
      myservoR.write(pos);                // tell servo to go to position in variable 'pos'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
   uart_rec = ';';
  }
  else if (uart_rec == '4') {               // pick parts lower
    for (valJ = 30; valJ >= 5; valJ--) {    // decrease degree from 30 - 5 slowly
      myservoJ.write(valJ);                // tell servo to go to position in variable 'valJ'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
    uart_rec = ';';
  }
  else if (uart_rec == '5') {               // pick parts higher
    for (valJ = 60; valJ >= 30; valJ--) {    // decrease degree from 60 - 30 slowly
      myservoJ.write(valJ);                // tell servo to go to position in variable 'valJ'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
    uart_rec = ';';
  }
  else if (uart_rec == '6') {
    myservoJ.write(60);                // tell servo to go to initial position (60 degree)
    delay(20);  
    uart_rec = ';';
  }
  else if (uart_rec == '7') {              // after picking lower parts, go back to initial position
    for (valJ = 5; valJ <= 30; valJ++) {    // increase degree from 5 - 30 slowly
      myservoJ.write(valJ);                // tell servo to go to position in variable 'valJ'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
    uart_rec = ';';
  }
  else if (uart_rec == '8') {               // after picking higher parts, go back to initial position
    for (valJ = 30; valJ <= 60; valJ++) {    // increase degree from 30 - 60 slowly
      myservoJ.write(valJ);                // tell servo to go to position in variable 'valJ'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
    uart_rec = ';';
  }
  else if (uart_rec == '9') {                // drop parts
    for (valJ = 60; valJ <= 175; valJ++) {    // increase degree from 60 - 175 slowly
      myservoJ.write(valJ);                // tell servo to go to position in variable 'valJ'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
    uart_rec = ';';
  }
  /*
  else if (uart_rec == '+') {
    for (pos = 0; pos <= 25; pos++) {    // increase degree from 40 - 150 slowly
      myservoJ.write(pos);                // tell servo to go to position in variable 'pos'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
   uart_rec = ';';
  }
  else if (uart_rec == '-') {
    for (pos = 0; pos <= 25; pos++) {    // increase degree from 40 - 150 slowly
      myservoJ.write(pos);                // tell servo to go to position in variable 'pos'
      delay(20);                          // waits 20 ms for the servo to reach the position
    }
   uart_rec = ';';
  }
  

 
  else if (uart_rec == '+') {
    int i = valR;
    while(i >= 0 && i <= valR + 5 && i <= 180) {
      i++;
      myservoR.write(i);
      delay(20);
    }
    
  }
  else if (uart_rec == '-') {
    int i = valR;
    while(i >= 0 && i >= valR - 5 && i <= 180) {
      i--;
      myservoR.write(i);
      delay(20);
    }
    valR = i;
  }*/
 // else if (uart_rec == '7' || uart_rec == '1' || uart_rec == '2' || uart_rec == '3'
  delay(20);
}

void moveForward() {
  
  digitalWrite(dir1Left,HIGH);
  digitalWrite(dir2Left,LOW);
  digitalWrite(dir1Right,HIGH);
  digitalWrite(dir2Right,LOW);

}

void moveBackward() {

  digitalWrite(dir1Left,LOW);
  digitalWrite(dir2Left,HIGH);
  digitalWrite(dir1Right,LOW);
  digitalWrite(dir2Right,HIGH);

}

void moveLeft() {
  
  digitalWrite(dir1Left,LOW);
  digitalWrite(dir2Left,HIGH);
  digitalWrite(dir1Right,HIGH);
  digitalWrite(dir2Right,LOW);

}

void moveRight() {

  digitalWrite(dir1Left,HIGH);
  digitalWrite(dir2Left,LOW);
  digitalWrite(dir1Right,LOW);
  digitalWrite(dir2Right,HIGH);

}

void stopMove() {
  
  digitalWrite(dir1Left,LOW);
  digitalWrite(dir2Left,LOW);
  digitalWrite(dir1Right,LOW);
  digitalWrite(dir2Right,LOW);

}
