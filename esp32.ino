#include "BluetoothSerial.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Adafruit_MPU6050 mpu;

BluetoothSerial SerialBT;
char *pin = "1234"; //建立连接时的密码，不设置与hc05连接不上
//uint8_t address[3]={98d3,11,fc3662}; 
void setup() {
  Serial.begin(9600);     
  SerialBT.begin(9600);
  SerialBT.setPin(pin);    
  SerialBT.connect("98d3:11:fc3662");
  SerialBT.begin("HC-05"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);
}


int situation = 1;
float accel_x = 0;
float accel_y = 0;
float accel_z = 0;

const char Stop=0;
const char direct_left=1;
const char direct_right=2;
const char direct_forward=3;
const char direct_backward=4;
const char left_forward=5;
const char right_forward=6;
const char left_backward=7;
const char right_backward=8;





void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if (situation != 3) {
    accel_x += a.acceleration.x;
    accel_y += a.acceleration.y;
    accel_z += a.acceleration.z;
    situation++;
    return;
  }
  situation = 1;
  accel_x /= 3;
  accel_y /= 3;
  accel_z /= 3;

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(accel_x);
  Serial.print(", Y: ");
  Serial.print(accel_y);
  Serial.print(", Z: ");
  Serial.print(accel_z);
  Serial.println(" m/s^2");

  //  Serial.print("Rotation X: ");
  //  Serial.print(g.gyro.x);
  //  Serial.print(", Y: ");
  //  Serial.print(g.gyro.y);
  //  Serial.print(", Z: ");
  //  Serial.print(g.gyro.z);
  //  Serial.println(" rad/s");
  //
  //  Serial.print("Temperature: ");
  //  Serial.print(temp.temperature);
  //  Serial.println(" degC");
  if ((accel_x<-3)&&(accel_y>3)&&(accel_z>6)){
    SerialBT.println(left_forward);
    Serial.println("left_forward");
    Serial.println("left_forward");
    Serial.println("left_forward");
    Serial.println("left_forward");
    Serial.println("left_forward");
    return;
  }
  if ((accel_x>3)&&(accel_y>3)&&(accel_z>6)){
    SerialBT.println(right_forward);
    Serial.println("right_forward");
    Serial.println("right_forward");
    Serial.println("right_forward");
    Serial.println("right_forward");
    Serial.println("right_forward");
    return;
  }
  if ((accel_x<-3)&&(accel_y<-3)&&(accel_z>6)){
    SerialBT.println(left_backward);
    Serial.println("left_backward");
    Serial.println("left_backward");
    Serial.println("left_backward");
    Serial.println("left_backward");
    Serial.println("left_backward");
    return;
  }
  if ((accel_x>3)&&(accel_y<-3)&&(accel_z>6)){
    SerialBT.println(right_backward);
    Serial.println("right_backward");
    Serial.println("right_backward");
    Serial.println("right_backward");
    Serial.println("right_backward");
    Serial.println("right_backward");
    return;
  }
  //&&(abs(accel_y)<3)&&(abs(accel_x<3))
  if ((accel_z>5)){//(accel_x<1)&&(accel_y<1)&&
    SerialBT.println(Stop);
    Serial.println("Stop");
    Serial.println("Stop");
    Serial.println("Stop");
    Serial.println("Stop");
    Serial.println("Stop");
    return;
  }
  if ((accel_x<-5)&&(accel_z<6)){//&&(accel_z>1)
    SerialBT.println(direct_left);
    Serial.println("direct_left");
    Serial.println("direct_left");
    Serial.println("direct_left");
    Serial.println("direct_left");
    Serial.println("direct_left");
    return;
  }
  if ((accel_x>5)&&(accel_z<6)){//&&(accel_z>1)
    SerialBT.println(direct_right);
    Serial.println("direct_right");
    Serial.println("direct_right");
    Serial.println("direct_right");
    Serial.println("direct_right");
    Serial.println("direct_right");
    return;
  }
  if ((accel_y>5)&&(accel_z<6)){//&&(accel_z<-1)
    SerialBT.println(direct_forward);
    Serial.println("direct_forward");
    Serial.println("direct_forward");
    Serial.println("direct_forward");
    Serial.println("direct_forward");
    Serial.println("direct_forward");
    return;
  }
  if ((accel_y<-5)&&(accel_z<6)){//&&(accel_z>1)&&(accel_x<10)
    SerialBT.println(direct_backward);
    Serial.println("direct_back");
    Serial.println("direct_back");
    Serial.println("direct_back");
    Serial.println("direct_back");
    Serial.println("direct_back");
    return;
  }
  accel_x = 0;
  accel_y = 0;
  accel_z = 0;

  Serial.println("");
  delay(5);
}  







////testcode
//void loop() {
//    
////  if (Serial.available()) {
////    
////    SerialBT.write(Serial.read());
////  }
////  if (SerialBT.available()) {
////    
////    Serial.write(SerialBT.read());
////  }
//  int temp=100;
//  SerialBT.println(temp);
//  delay(1);
//}
