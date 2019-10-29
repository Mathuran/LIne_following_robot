#include <NewPing.h>

const int LED1 = 10;
const int LED2 = 11;
const int LED3 = 9;
const int TRIG = 12;
const int ECHO = 13;
const int MLforward = A1;
const int MLbackward = A2;
const int MRforward = A3;
const int MRbackward = A4;
const float distancecm = 20;
const float maxdistancecm = 500;
unsigned long echotime;
const float k = 9.5;
const float m =2.5;
float error = 1;
float leftpower;
float rightpower;
bool turn = false;

NewPing sonar(TRIG, ECHO, maxdistancecm);

void setup() {
  for (int x = 9; x < 13; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(ECHO, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
//  Serial.begin(9600);
}


void loop() {
  leftpower = 140;
  rightpower = 140;
  digitalWrite(LED3, LOW);
  echotime = sonar.ping_median(7);
  error = sonar.convert_cm(echotime) - distancecm;
  digitalWrite(LED3, HIGH);
  delay(50);
  leftpower = min(250, 140 + (k * error));
  rightpower = min(250, 140 + (-k * error));
/*
  Serial.print("error ;");
  Serial.println(error);
  Serial.print("left ;");
  Serial.println(leftpower);
  Serial.print("right  ;");
  Serial.println(rightpower);
*/
  if (error < -3) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
   // Serial.print("close");
    
  } else if (error > 3) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
   // Serial.print("Far");
    
  } else {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    leftpower = 140;
    rightpower = 140;
   // Serial.print("good");

  }
  analogWrite(MLforward, leftpower);
  analogWrite(MRforward, rightpower);
  delay(35+(m*abs(error)));
  analogWrite(MLforward, 130);
  analogWrite(MRforward, 130);
  

}
