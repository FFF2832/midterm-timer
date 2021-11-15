#include <Stepper.h> //引入步進馬達函示庫
#include "pitches.h"

const int stepsPerRevolution = 2048;  //此馬達轉一圈為2048步
const int RPM = 5; //馬達旋轉速度
int freq = 2000;
int channel = 0;
int resolution = 8;
int tonePin = 26;
bool btn1_Pressed = false, btn2_Pressed = false, btn3_Pressed = false;
const int btn1_pin = 34, btn2_pin = 32;
//宣告Stepper物件，的步數和引腳
//引角依序對應驅動版的1N1、1N3、1N2、1N4
Stepper myStepper(stepsPerRevolution, 13, 14, 12, 27);  

 int melody[] = {  
    NOTE_G4 , NOTE_C5,NOTE_D5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_B4,
  NOTE_B4, NOTE_G4 , NOTE_C5,NOTE_D5, NOTE_E5, NOTE_G5, NOTE_C5,
  NOTE_D5,NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, 
  NOTE_B4,NOTE_B4,
  };

  int noteDurations[] = {  
 8, 8, 8, 2, 2, 2, 8,
  2, 4, 4, 4, 4, 2, 8,
  8,  8, 8, 8, 2, 2, 2, 8,
  2, 4, 4, 4, 4, 2, 8,
  8
  };   

  unsigned long currentTime = 0, tonePreviousTime = 0, PreviousTime = 0;

  int pauseBetweenNotes = 0;
int noteDuration = 0;
int thisNote = 0;
boolean nextTone = true;
boolean nextoo = true;

void setup() {  
  Serial.begin(115200);
  myStepper.setSpeed(RPM);  //設定馬達轉速
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(tonePin, channel);
   pinMode(btn1_pin,INPUT);
  pinMode(btn2_pin,INPUT);
 
}
void init(){
  myStepper.step(stepsPerRevolution);
}
void loop() {
 int now=1;
//  Serial.println(digitalRead(btn1_pin));
// Serial.println(digitalRead(btn2_pin));
  if(digitalRead(btn1_pin) == 1 && btn1_Pressed == false){
    if(now==1)
    {
     btn1_Pressed = true;
     myStepper.step(1024);
   
      for (int thisNote = 0; thisNote < 30; thisNote++) 
      {
         if(digitalRead(btn2_pin) == 1 && btn2_Pressed == false)
         {
          btn2_Pressed = true;
           now=0;
           nextTone = false;
            nextoo = false;
             myStepper.step(2048);
         }
          else if(digitalRead(btn2_pin) == 0 && btn2_Pressed == true)
          {
          btn2_Pressed = false;
    
           }
        Serial.println(now);
        if(nextTone)
        {
          int noteDuration = 1000 / noteDurations[thisNote];
          ledcWriteTone(channel,melody[thisNote]);
          pauseBetweenNotes = noteDuration * 1.30;
          nextTone = false;
         }
   
        if(nextoo)
        {
        myStepper.step(50);
        nextoo = false;
        }
 
        currentTime = millis(); //記錄現在時間
     
        if((currentTime - PreviousTime) > 10 )
        {
   
          nextoo = true;
          PreviousTime = currentTime;
       } 
        if((currentTime - tonePreviousTime) > noteDuration){
          ledcWriteTone(channel, 0);
          } //buzzer停止播放
        if((currentTime - tonePreviousTime) > 100)
        {
          nextTone = true;
//      thisNote++;
          if(thisNote == 30) thisNote = 0;
          tonePreviousTime = currentTime; 
        } //buzzer播放下一個音
        
    }
     
 
      
      
  }
   
   

  }
   else if(digitalRead(btn1_pin) == 0 && btn1_Pressed == true)
    {
    btn1_Pressed = false;
    }
  

  
   
}
