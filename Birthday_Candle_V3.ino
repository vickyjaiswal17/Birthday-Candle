//******************BIRTHDAY CANDLE**************************//
//Developed by Vicky Jaiswal
//Date:- Nov,2021 - Dec,2021

//*******************BIRTHDAY CANDLE CODE*********************/



//**********MULTIPLEXED LED CONTROL********/
byte multiplexedLED1[17] = {  // Multiplexed individual LED control
  B00000000,
  B01111000,
  B10111000,
  B11011000,
  B11101000,
  B01110100,
  B10110100,
  B11010100,
  B11100100,
  B01110010,
  B10110010,
  B11010010,
  B11100010,
  B01110001,
  B10110001,
  B11010001,
  B11100001
};
byte multiplexedLED2[5] ={  // 0-1-2-3-4 CW pattern 
  B00000000,
  B01111111,
  B00111111,
  B00011111,
  B00001111,
};

byte multiplexedLED3[5] ={  // 0-1-2-3-4 CCW pattern
  B00000000,
  B01111111,
  B01101111,
  B01001111,
  B00001111,
};

byte multiplexedLED4[4] ={  // 1-1-1-1 CW Pattern
  B01111111,
  B10111111,
  B11011111,
  B11101111,
};
byte multiplexedLED5[4]={  // 2-2-2-2 CW Pattern
  
  B00111111,
  B10011111,
  B11001111,
  B01101111,
};

//************SEVEN SEGMENT LED CONTROL**************//

byte num1[10]={  // 0-9 digit control for 1st Seven Segment Digit
  B01111110,
  B01001000,
  B00111101,
  B01101101,
  B01001011,
  B01100111,
  B01110111,
  B01001100,
  B01111111,
  B01101111};

byte num2[10]={  // 0-9 digit control for 2nd Seven Segment Digit
  B01111110,
  B01001000,
  B00111101,
  B01101101,
  B01001011,
  B01100111,
  B01110111,
  B01001100,
  B01111111,
  B01101111};

//****************LED FLICKERING ARRAY****************//
byte flicker[15]={ 
  B11011101,
  B10110101,
  B11010011,
  B11011110,
  B11110110,
  B10101101,
  B11011011,
  B11110111,
  B10101010,
  B11001011,
  B10010110,
  B11110101,
  B10110111,
  B11101111,
  B10111101};


//****************PATTERN FOR OFF THR LEDs*****************//
byte offLED[7]={
  B11101111,
  B11111011,
  B10111111,
  B11111110,
  B11011111,
  B11110111,
  B11111101};

//*******************INCLUDING LYBRARIES*****************//
//#include<TimerOne.h>

  
//*******************ARDUINO PIN INITIALIZATION*****************//
int latchPin1 = 4;
int clockPin1 = 3;
int dataPin1 = 2;
int latchPin2 = 7;
int clockPin2 = 6;
int dataPin2 = 5;
int latchPin3 = 13;
int clockPin3 = 12;
int dataPin3 = 11;
int PBdigit1 = A0;
int PBsetOK = A1;
int PBdigit2 = A2;
int sensor = A3;
int speaker = 9;
int PWM = 10;


//*****************CODE VARIABLES****************************//
int value1, value2, value3, current_temp, previous_temp;
int n1=0, n2=0, STATE=0, k1=15, k2=0, p1=-1, p2=8, birthdayCount=0;
int DELAY1=50, DELAY2 = 150;
unsigned int current_time, previous_time=0;
unsigned int INDEX1=0;

//******************BIRTHDAY TUNE*****************//
int length = 28; 
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int tempo = 200;

void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
   digitalWrite(speaker, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speaker, LOW);
   delayMicroseconds(tone);
}
}

void playNote(char note, int duration) {
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int SPEE = 5;

for (int i = 0; i < 17; i++) 
 {
   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);
   }
 }
}


//**********************VOID SETUP()*************************//
void setup() {
  //Set the pinMode of AtMega328P pins
Serial.begin(9600);
pinMode(PBdigit1,INPUT);
pinMode(PBsetOK,INPUT);
pinMode(PBdigit2,INPUT);
pinMode(sensor,INPUT);
pinMode(latchPin1,OUTPUT);
pinMode(dataPin1,OUTPUT);  
pinMode(clockPin1,OUTPUT);
pinMode(latchPin2,OUTPUT);
pinMode(dataPin2,OUTPUT);  
pinMode(clockPin2,OUTPUT);
pinMode(latchPin3,OUTPUT);
pinMode(dataPin3,OUTPUT);  
pinMode(clockPin3,OUTPUT);
pinMode(speaker,OUTPUT);
pinMode(PWM,OUTPUT);


//Set PWM PIN to 50% duty cycle for getting -ve 5V on -ve power input of LM358
analogWrite(PWM, 128);

//Set digit1 off
digitalWrite(latchPin1, LOW);
shiftOut(dataPin1, clockPin1, LSBFIRST, B00000000);
digitalWrite(latchPin1, HIGH);

//Set digit2 off
digitalWrite(latchPin2, LOW);
shiftOut(dataPin2, clockPin2, LSBFIRST, B00000000);
digitalWrite(latchPin2, HIGH);

//Initially Set Multiplexed LEDs OFF
digitalWrite(latchPin3, LOW);
shiftOut(dataPin3, clockPin3, LSBFIRST, B00000000);
digitalWrite(latchPin3, HIGH);

// First LED pattern after Power on
  for(int i=0;i<5;i++)
  {
   for(int j=0;j<4;j++)
   {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED4[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY2);
   }
  }
  for(int i=0;i<5;i++)
  {
   for(int j=3;j>=0;j--)
   {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED4[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY2);
   }
  }

// Second LED pattern after Power on
for(int i=0;i<10;i++)
{
  for(int j=0;j<4;j++)
  {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED5[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY1);
  }
}

for(int i=0;i<10;i++)
{
  for(int j=3;j>=0;j--)
  {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED5[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY1);
  }
}

//Set All Multiplexed LEDs ON
digitalWrite(latchPin3, LOW);
shiftOut(dataPin3, clockPin3, LSBFIRST, B00001111);
digitalWrite(latchPin3, HIGH);
delay(2000);

//Set Digit1 to Zero
digitalWrite(latchPin1, LOW);
shiftOut(dataPin1, clockPin1, LSBFIRST, num1[0]);
digitalWrite(latchPin1, HIGH);

//Set digit2 to Zero
digitalWrite(latchPin2, LOW);
shiftOut(dataPin2, clockPin2, LSBFIRST, num2[0]);
digitalWrite(latchPin2, HIGH);

}



//********************VOID LOOP()**********************

void loop() {
  // put your main code here, to run repeatedly:

//Take the NTC sensor data in every 750-850ms of interval of time
  if(millis()%900>=750 && millis()%900<=850)
  {
    Serial.println(current_temp);
    previous_temp = current_temp;  //store the previous data
    current_temp=analogRead(sensor); //store the present data
    delay(50); 
  }
//Take Push Buttons datas
  value1 = digitalRead(PBdigit1); //Push button -->Set the first digit 
  value2 = digitalRead(PBdigit2); //Push button -->Set the second digit 
  value3 = digitalRead(PBsetOK);  //Push button -->Chage the STATE 0 to STATE 1


//STATE 0 :- Set the Digit of the birthday year
// Multiplexed LED in 2-2-2-2 pattern during STATE 0
if(STATE==0)
{
  INDEX1 = INDEX1%4;
  digitalWrite(latchPin3, LOW);
  shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED5[INDEX1]);
  digitalWrite(latchPin3, HIGH);
  delay(200);
  INDEX1++;
}


//Push button to change the value of first digit
if(value1 && STATE==0)
{
  analogWrite(speaker,128);
  delay(50);
  if(n1==9) n1=0;
  else n1++;
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, num1[n1]);
  digitalWrite(latchPin1, HIGH);
  delay(50);
  analogWrite(speaker,0);
}
while(value1)
{
  delay(20);
  value1=digitalRead(PBdigit1);
}

//Push button to change the value of second digit
if(value2 && STATE==0)
{
  analogWrite(speaker,128);
  delay(50);
  if(n2==9) n2=0;
  else n2++;
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, num2[n2]);
  digitalWrite(latchPin2, HIGH);
  delay(50);
  analogWrite(speaker,0);
}
while(value2)
{
  delay(20);
  value2=digitalRead(PBdigit2);
}


//this push button will toggle the STATE 0 to STATE 1 and vise versa
if(value3)
{
  analogWrite(speaker,128);
  delay(50);
  if(STATE==0) STATE=1;
  else STATE=0;
  delay(50);
  analogWrite(speaker,0);         
}
while(value3)
{
  delay(20);
  value3=digitalRead(PBsetOK);
}


//STATE 1 :- Candle LEDs will fliker like candles
//STATE 2 :- Sensor will detect the mouth blow and if reading will change +-6 in 750ms then Candle LEDs will start to turn OFF
if(STATE==1 || STATE==2)
{ digitalWrite(latchPin3, LOW);
  shiftOut(dataPin3, clockPin3, LSBFIRST, B00001111);
  digitalWrite(latchPin3, HIGH);
  if(k1==15) k1=0;
  else k1++;
  if(k2==0) k2=15;
  else k2--;
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, (num1[n1] & flicker[k1]));
  digitalWrite(latchPin1, HIGH);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, (num2[n2] & flicker[k2]));
  digitalWrite(latchPin2, HIGH);   
  delay(25);
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, num1[n1]);
  digitalWrite(latchPin1, HIGH);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, num2[n2]);
  digitalWrite(latchPin2, HIGH);  
  delay(30);

if((current_temp>=previous_temp+5) || (current_temp<=previous_temp-5))
{
  STATE = 2;  
}

if(STATE==2)
 {
   if(p1==7) STATE = 3;
   else p1++;
   if(p2==0) STATE = 3;
   else p2--;
   num1[n1]= num1[n1] & offLED[p1];
   num2[n2]= num2[n2] & offLED[p2];
   digitalWrite(latchPin1, LOW);
   shiftOut(dataPin1, clockPin1, LSBFIRST,num1[n1]);
   digitalWrite(latchPin1, HIGH);
   digitalWrite(latchPin2, LOW);
   shiftOut(dataPin2, clockPin2, LSBFIRST,num2[n2]);
   digitalWrite(latchPin2, HIGH);
   delay(250);
 }
}


// STATE 3:- HAPPY BIRTHDAY SONG after all candle LEDs are off
if(STATE==3)
{
  //Set digit1 off
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, B00000000);
  digitalWrite(latchPin1, HIGH);

  //Set digit2 off
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, B00000000);
  digitalWrite(latchPin2, HIGH);
  
 for(int birthdayCount=0;birthdayCount<3;birthdayCount++)
 {
  for (int i = 0; i < length; i++)
  {
    //Multiplexed LED in Pattern
    INDEX1 = INDEX1%5;
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED3[INDEX1]);
    digitalWrite(latchPin3, HIGH);
    delay(20);
    INDEX1++;
    
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); 
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   delay(tempo);
   }
 }
 STATE=4;
}

// LED in pattern in ending
if(STATE==4)
{
  for(int i=0;i<5;i++)
  {
   for(int j=0;j<4;j++)
   {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED4[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY2);
   }
  }
  for(int i=0;i<5;i++)
  {
   for(int j=3;j>=0;j--)
   {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, multiplexedLED4[j]);
    digitalWrite(latchPin3, HIGH);
    delay(DELAY2);
   }
  }
}
 
 
}
//*********************PROGRAM ENDS************************//


//function to check the data of Inputs
void dataCheck()
{
int a1 = analogRead(sensor);
int a2 = digitalRead(PBdigit1);
int a3 = digitalRead(PBsetOK);
int a4 = digitalRead(PBdigit2);
Serial.print(a1);
Serial.print("  ");
Serial.print(a2);
Serial.print("  ");
Serial.print(a3);
Serial.print("  ");
Serial.print(a4);
Serial.println("  ");
delay(250);
}
