#include <Wire.h>

const uint8_t Address = 0x48;
const uint8_t AccessTH = 0xA1;
const uint8_t AccessTL = 0xA2;
const uint8_t WriteDelay = 0xA;
const uint8_t AccessConf = 0xAC;

const uint8_t ReadTemp = 0xAA;
const uint8_t ReadDelay = 100;
const uint8_t StartConvert = 0xEE;
const uint8_t StopConvert = 0x22;

const uint8_t thFlag = 64;
const uint8_t tlFlag = 32;

const int serial = 9600;

uint8_t conf;

uint8_t newConf;

uint8_t temp[2];
int count = 0;

float convertTemp(){
  float result = 0;
  result += temp[0];
  temp[1] == 128? result+=0.5 : result+=0.0;
}

void setTout(uint8_t max1, uint8_t min1, uint8_t max2, uint8_t min2  ){
  /*char minTemp1 = min;
  char minTemp2 = min - (minTemp1 * 10);
  minTemp2 == 0 ? minTemp2 = 0: minTemp2 = 128;

  char maxTemp1 = max;
  char maxTemp2 = max - maxTemp1 * 10;
  maxTemp2 == 0 ? maxTemp2 = 0: maxTemp2 = 128;
  */
  Wire.beginTransmission(Address);
  Wire.write(AccessConf);
  delay(WriteDelay);
  Wire.write(0x2);
  Wire.endTransmission();
  //set TH value  Wire.write(accessTH);
  delay(WriteDelay);
  
  Wire.beginTransmission(Address);
  //set TH flag
  Wire.write(AccessTH);
  
  Wire.write(max1);
 
  
  Wire.write(min1);
  delay(WriteDelay);
  Wire.endTransmission();
  delay(WriteDelay);
  //set Tl value
  
  Wire.beginTransmission(Address);
  Wire.write(AccessTL);
  Wire.write(max2);
  Wire.write(min2);
  delay(WriteDelay);
  Wire.endTransmission();
  
}

void readTemp(){
  count = 0;
  Wire.beginTransmission(Address);
  Wire.write(StartConvert);
  Wire.endTransmission();  
  delay(100);
  
  Wire.beginTransmission(Address);
  Wire.write(ReadTemp);
  Wire.endTransmission();    
  Wire.requestFrom(Address, 2);
  while (Wire.available()&&count<2){
       temp[count]= Wire.read();
       delay(ReadDelay);
       if(temp[count] == 128 ){
        temp[count] = 5;
           Serial.print(",");
           Serial.print(temp[count]);
       }else if(temp[count] == 0){
          temp[count] = 0;
          Serial.print(",");
          Serial.print(temp[count]);
       }
        else{
           Serial.print(temp[count]);
       }
       count++;
  }
  //Serial.print(temp[count-1]);
  Serial.print("\n");
  
  Serial.print("\n");
}

void readConfig(){
  Wire.beginTransmission(Address);
  delay(100);
  Wire.write(AccessConf);
  Wire.endTransmission(false);
  Wire.requestFrom(Address,(uint8_t)1,(uint8_t) true);
  if (Wire.available())
  {
    conf = Wire.read();
  }
  Serial.print("readConfig fertig\n");
  Serial.print("\n\n");
  Serial.print(conf);
  Serial.print("\n\n");
  newConf = conf | thFlag;
}

void setup(){
  Wire.setModule(0);
  Wire.begin();
  Serial.begin(9600);
  Serial.print("start\n");
  readConfig();
  setTout(30, 0, 28, 0);
}

void loop(){
  readTemp();
  //Serial.print("\nTemperatur:");
  //Serial.print(convertTemp());
}
