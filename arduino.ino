#include <SoftwareSerial.h> 
#include <AFMotor.h>

//initial motors pin
AF_DCMotor rightMotor1(1);
AF_DCMotor rightMotor2(4);
AF_DCMotor leftMotor1(2);
AF_DCMotor leftMotor2(3);
SoftwareSerial BT(9,10);
//void forward();
//void backward();
//void left();
//void right();
//void Stop();
//char command; 
char val;
int response_time=5;


const char Stop =0;
const char direct_left=1;
const char direct_right=2;
const char direct_forward=3;
const char direct_backward=4;
const char leftforward=5;
const char rightforward=6;
const char leftbackward=7;
const char rightbackward=8;



void setup()
{
    BT.begin(9600);
    Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop(){
    if (BT.available()){
      val=BT.read();
      Serial.println(val);
    }
    if (val==Stop){
        stop();
        delay(response_time);
        return;
    }
    if (val==direct_forward){
        forward();
        delay(response_time);
        return;
    }
    if (val==direct_backward){
        backward();
        delay(response_time);
        return;
    }
    if (val==direct_left){
        parell_left();
        delay(response_time);
        return;
    }
    if (val==direct_right){
        parell_right();
        delay(response_time);
        return;
    }
    if (val==leftforward){
        left_forward();
        delay(response_time);
        return;
    }
    if (val==rightforward){
        right_forward();
        delay(response_time);
        return;
    }
    if (val==leftbackward){
        left_backward();
        delay(response_time);
        return;
    }
    if (val==rightbackward){
        right_backward();
        delay(response_time);
        return;
    }

//      forward();
//      delay(1000);
//      backward();
//      delay(1000);
//      parell_left();
//      delay(1000);
//      parell_right();
//      delay(1000);
//      right_forward();
//      delay(1000);
//      right_backward();
//      delay(1000);
//      left_forward();
//      delay(1000);
//      left_backward();
//      delay(1000);
}

void forward()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(FORWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(FORWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255);//Define maximum velocity
    leftMotor1.run(FORWARD); //rotate the motor clockwise
    leftMotor2.setSpeed(255);//Define maximum velocity
    leftMotor2.run(FORWARD); //rotate the motor clockwise
}

void backward()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(BACKWARD); //rotate the motor anti-clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(BACKWARD); //rotate the motor anti-clockwise
    leftMotor1.setSpeed(255); //Define maximum velocity
    leftMotor1.run(BACKWARD); //rotate the motor anti-clockwise
    leftMotor2.setSpeed(255); //Define maximum velocity
    leftMotor2.run(BACKWARD); //rotate the motor anti-clockwise
}

void stop()
{
    rightMotor1.setSpeed(0); //Define minimum velocity
    rightMotor1.run(RELEASE); //stop the motor when release the button
    rightMotor2.setSpeed(0); //Define minimum velocity
    rightMotor2.run(RELEASE); //rotate the motor clockwise
    leftMotor1.setSpeed(0); //Define minimum velocity
    leftMotor1.run(RELEASE); //stop the motor when release the button
    leftMotor2.setSpeed(0); //Define minimum velocity
    leftMotor2.run(RELEASE); //stop the motor when release the button
}                  

void clockwise()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(BACKWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(BACKWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255); //Define maximum velocity
    leftMotor1.run(FORWARD); //rotate the motor anti-clockwise
    leftMotor2.setSpeed(255); //Define maximum velocity
    leftMotor2.run(FORWARD); //rotate the motor anti-clockwise
}

void counterwise()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(FORWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(FORWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255); //Define maximum velocity
    leftMotor1.run(BACKWARD); //rotate the motor anti-clockwise
    leftMotor2.setSpeed(255); //Define maximum velocity
    leftMotor2.run(BACKWARD); //rotate the motor anti-clockwise
}

void parell_left()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(FORWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(BACKWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255);//Define maximum velocity
    leftMotor1.run(BACKWARD); //rotate the motor clockwise
    leftMotor2.setSpeed(255);//Define maximum velocity
    leftMotor2.run(FORWARD); //rotate the motor clockwise
}

void parell_right()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(BACKWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(FORWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255);//Define maximum velocity
    leftMotor1.run(FORWARD); //rotate the motor clockwise
    leftMotor2.setSpeed(255);//Define maximum velocity
    leftMotor2.run(BACKWARD); //rotate the motor clockwise
}

void left_forward()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(FORWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(0); //Define maximum velocity
    rightMotor2.run(RELEASE); //rotate the motor clockwise
    leftMotor1.setSpeed(0);//Define maximum velocity
    leftMotor1.run(RELEASE); //rotate the motor clockwise
    leftMotor2.setSpeed(255);//Define maximum velocity
    leftMotor2.run(FORWARD); //rotate the motor clockwise
}

void right_forward()
{
    rightMotor1.setSpeed(0); //Define maximum velocity
    rightMotor1.run(RELEASE); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(FORWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255);//Define maximum velocity
    leftMotor1.run(FORWARD); //rotate the motor clockwise
    leftMotor2.setSpeed(0);//Define maximum velocity
    leftMotor2.run(RELEASE); //rotate the motor clockwise
}

void left_backward()
{
    rightMotor1.setSpeed(0); //Define maximum velocity
    rightMotor1.run(RELEASE); //rotate the motor clockwise
    rightMotor2.setSpeed(255); //Define maximum velocity
    rightMotor2.run(BACKWARD); //rotate the motor clockwise
    leftMotor1.setSpeed(255);//Define maximum velocity
    leftMotor1.run(BACKWARD); //rotate the motor clockwise
    leftMotor2.setSpeed(0);//Define maximum velocity
    leftMotor2.run(RELEASE); //rotate the motor clockwise
}

void right_backward()
{
    rightMotor1.setSpeed(255); //Define maximum velocity
    rightMotor1.run(BACKWARD); //rotate the motor clockwise
    rightMotor2.setSpeed(0); //Define maximum velocity
    rightMotor2.run(RELEASE); //rotate the motor clockwise
    leftMotor1.setSpeed(0);//Define maximum velocity
    leftMotor1.run(RELEASE); //rotate the motor clockwise
    leftMotor2.setSpeed(255);//Define maximum velocity
    leftMotor2.run(BACKWARD); //rotate the motor clockwise
}
