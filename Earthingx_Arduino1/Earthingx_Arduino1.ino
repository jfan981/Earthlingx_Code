#include <Servo.h>
#include <LiquidCrystal.h>

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

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int count;

// Happy Face elements
byte eyelid[8] = {B11111,B11111,B10101,B10001,B11011,B11111,B01110,B00100};
byte tooth_1[8] = {B00000,B00000,B11111,B01110,B01110,B01110,B00000,B11111};
byte smile_1[8] = {B00000,B00000,B11111,B00000,B00000,B00000,B00000,B11111};
byte smile_right[8] = {B00000,B00011,B11100,B00000,B00000,B00001,B00010,B11100};
byte smile_right2[8]= {B11111,B00010,B00100,B01000,B10000,B00000,B00000,B00000};
byte smile_left[8]{B00000,B11000,B00111,B00000,B00000,B10000,B01000,B00111};
byte smile_left2[8] = {B11111,B01000,B00100,B00010,B00001,B00000,B00000,B00000};

// Sad Face elements
byte sad_eye[8] = {B11111,B11111,B11111,B01110,B10101,B11011,B11111,B11111};
byte sad_mouth[8] = {B00000,B00000,B11111,B11111,B11111,B11111,B11111,B11111};
byte sad_mouth2[8] = {B11110,B11000,B00000,B00111,B11111,B11111,B11111,B11111};
byte sad_mouth3[8] = {B11111,B11111,B11111,B11100,B11000,B10011,B10111,B01111};
byte sad_mouth_right[8] = {B11111,B00011,B00000,B11100,B11111,B11111,B11111,B11111};
byte sad_mouth_right2[8] = {B11111,B11111,B11111,B00111,B00011,B11001,B11101,B11110};
byte block[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111};

// Surprise face for turn elements
byte surprise_eye_1[8] = {B11111,B11111,B11111,B11111,B11111,B10001,B10101,B10101};
byte sur_mouth1[8] = {B00000,B00000,B00001,B00010,B00100,B01000,B10000,B00000};
byte sur_mouth2[8] = {B00000,B10000,B01000,B00100,B00010,B00001,B00000,B00000};
byte dimple_right[8] = {B00111,B00111,B00111,B00000,B00000,B00000,B00000,B00000};
byte dimple_left[8] = {B11100,B11100,B11100,B00000,B00000,B00000,B00000,B00000};

// Stop Face bytes elements
byte stop_eye[8] = {B00000,B00100,B01110,B11011,B10001,B10001,B10001,B00000};
byte oval_mouth[8] = {B11111,B00000,B00000,B00000,B00000,B00000,B00000,B11111};
byte oval_mouth_right[8] = {B00000,B10000,B01000,B00100,B00100,B01000,B10000,B00000};
byte oval_mouth_left[8] = {B00000,B00001,B00010,B00100,B00100,B00010,B00001,B00000};

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

  lcd.begin(16, 2);
  lcd.home();

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
    happyFace();
    uart_rec = ';';
  }
  else if (uart_rec == 's') {   // Stands for WASD keyboards as controller
    moveBackward();
    sadFace();
    uart_rec = ';';
  }
  else if (uart_rec == 'a') {   // Stands for WASD keyboards as controller
    moveLeft();
    surpriseFace();
    uart_rec = ';';
  }
  else if (uart_rec == 'd') {   // Stands for WASD keyboards as controller
    moveRight();
    surpriseFace();
    uart_rec = ';';
  }
  else if (uart_rec == 'q') {   // Stands for "quit" to stop
    stopMove();
    stopFace();
    uart_rec = ';';
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

void happyFace() {
  lcd.clear();
  
  lcd.createChar(6, eyelid);
  lcd.setCursor(6,0);
  lcd.write(6);
  
  lcd.createChar(6, eyelid);
  lcd.setCursor(9,0);
  lcd.write(6);
  
  lcd.createChar(7, tooth_1);
  lcd.setCursor(7,1);
  lcd.write(7);
  
  lcd.createChar(7, tooth_1);
  lcd.setCursor(8,1);
  lcd.write(7);
  
  lcd.createChar(1, smile_1);
  lcd.setCursor(9,1);
  lcd.write(1);
  
  lcd.createChar(1, smile_1);
  lcd.setCursor(6,1);
  lcd.write(1);
  
  lcd.createChar(2, smile_right);
  lcd.setCursor(10,1);
  lcd.write(2);
  
  lcd.createChar(3, smile_right2);
  lcd.setCursor(11,1);
  lcd.write(3);
  
  lcd.createChar(4, smile_left);
  lcd.setCursor(5,1);
  lcd.write(4);
  
  lcd.createChar(5, smile_left2);
  lcd.setCursor(4,1);
  lcd.write(5);
}

void sadFace() {
  lcd.clear();
  
  lcd.createChar(6, sad_eye);
  lcd.setCursor(6,0);
  lcd.write(6);
  
  lcd.createChar(6, sad_eye);
  lcd.setCursor(9,0);
  lcd.write(6);
  
  lcd.createChar(8, sad_mouth);
  lcd.setCursor(7,1);
  lcd.write(8);
  
  lcd.createChar(8, sad_mouth);
  lcd.setCursor(8,1);
  lcd.write(8);
  
  lcd.createChar(1, sad_mouth2);
  lcd.setCursor(6,1);
  lcd.write(1);
  
  lcd.createChar(2, sad_mouth3);
  lcd.setCursor(5,1);
  lcd.write(2);
  
  lcd.createChar(3, sad_mouth_right);
  lcd.setCursor(9,1);
  lcd.write(3);
  
  lcd.createChar(4, sad_mouth_right2);
  lcd.setCursor(10,1);
  lcd.write(4);
  
  lcd.createChar(5, block);
  lcd.setCursor(0,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(1,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(2,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(3,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(4,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(11,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(12,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(13,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(14,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(15,1);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(0,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(1,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(2,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(3,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(4,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(5,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(7,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(8,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(10,0);
  lcd.write(5);
  
   lcd.createChar(5, block);
  lcd.setCursor(11,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(12,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(13,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(14,0);
  lcd.write(5);
  
  lcd.createChar(5, block);
  lcd.setCursor(15,0);
  lcd.write(5);
}

void surpriseFace() {
  lcd.clear();
  
  lcd.createChar(6, surprise_eye_1);
  lcd.setCursor(6,0);
  lcd.write(6);
  
  lcd.createChar(6, surprise_eye_1);
  lcd.setCursor(9,0);
  lcd.write(6);
  
  lcd.createChar(5, sur_mouth1);
  lcd.setCursor(9,1);
  lcd.write(5);
  
  lcd.createChar(4, sur_mouth2);
  lcd.setCursor(8,1);
  lcd.write(4);
  
  lcd.createChar(5, sur_mouth1);
  lcd.setCursor(7,1);
  lcd.write(5);
  
  lcd.createChar(4, sur_mouth2);
  lcd.setCursor(6,1);
  lcd.write(4);
  
  lcd.createChar(5, sur_mouth1);
  lcd.setCursor(5,1);
  lcd.write(5);
  
  lcd.createChar(4, sur_mouth2);
  lcd.setCursor(10,1);
  lcd.write(4);
  
  lcd.createChar(3, dimple_right);
  lcd.setCursor(11,1);
  lcd.write(3);
  
  lcd.createChar(2, dimple_left);
  lcd.setCursor(4,1);
  lcd.write(2);
}

void stopFace() {    // ^o^
  lcd.clear();
  
  lcd.createChar(6, stop_eye);
  lcd.setCursor(6,0);
  lcd.write(6);
  
  lcd.createChar(6, stop_eye);
  lcd.setCursor(8,0);
  lcd.write(6);
  
  lcd.createChar(4, oval_mouth);
  lcd.setCursor(7,1);
  lcd.write(4);
  
  lcd.createChar(5, oval_mouth_right);
  lcd.setCursor(8,1);
  lcd.write(5);
  
  lcd.createChar(2, oval_mouth_left);
  lcd.setCursor(6,1);
  lcd.write(2);
}
