
byte num1[10]={B01111110,
               B01001000,
               B00111101,
               B01101101,
               B01001011,
               B01100111,
               B01110111,
               B01001100,
               B01111111,
               B01101111};
               
byte num2[10]={B01111110,
               B01001000,
               B00111101,
               B01101101,
               B01001011,
               B01100111,
               B01110111,
               B01001100,
               B01111111,
               B01101111};
byte flicker[15]={B11011101,
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
                  B10111101 };
byte offLED[7]={B11101111,
                B11111011,
                B10111111,
                B11111110,
                B11011111,
                B11110111,
                B11111101};

int latchPin1 = 4;
int clockPin1 = 3;
int dataPin1 = 2;
int latchPin2 = 7;
int clockPin2 = 6;
int dataPin2 = 5;
int latchPin3 = 13;
int clockPin3 = 12;
int dataPin3 = 11;
int pin1=A1;
int pin2=A2;
int pin3=A0;
int temppin=A3;
int speakerPin=3; 
int n1=9, n2=9, m=0, k1=15, k2=0, p1=-1, p2=8, birthdayCount=1;
int value1, value2, value3, current_temp, previous_temp;
unsigned int current_time, previous_time=0;
int length = 28; 
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = {2,2,8,8,8,16,1,2,2,8,8,8,16,1,2,2,8,8,8,8,16,1,2,2,8,8,8,16};
int tempo = 200;

void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
   digitalWrite(speakerPin, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speakerPin, LOW);
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


void(* resetFunc) (void) = 0;
void setup() { 
Serial.begin(9600);
pinMode(pin1,INPUT);
pinMode(pin2,INPUT);
pinMode(pin3,INPUT);
pinMode(temppin,INPUT);
pinMode(latchPin1,OUTPUT);
pinMode(dataPin1,OUTPUT);  
pinMode(clockPin1,OUTPUT);
pinMode(latchPin2,OUTPUT);
pinMode(dataPin2,OUTPUT);  
pinMode(clockPin2,OUTPUT);
pinMode(speakerPin,OUTPUT);
analogReference(INTERNAL);

digitalWrite(latchPin1, LOW);
shiftOut(dataPin1, clockPin1, LSBFIRST, B00000000);
digitalWrite(latchPin1, HIGH);
digitalWrite(latchPin2, LOW);
shiftOut(dataPin2, clockPin2, LSBFIRST, B00000000);
digitalWrite(latchPin2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

current_time=millis()%1500;
current_temp=analogRead(temppin);
value1=digitalRead(pin1);
value2=digitalRead(pin2);
value3=digitalRead(pin3);

 Serial.print(current_temp); Serial.print(" ");
 Serial.println(previous_temp);

if(value1 && m==0)
{
  if(n1==9) n1=0;
  else n1++;
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, num1[n1]);
  digitalWrite(latchPin1, HIGH);
}
while(value1)
{
  delay(20);
  value1=digitalRead(pin1);
}


if(value2 && m==0)
{
  if(n2==9) n2=0;
  else n2++;
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, num2[n2]);
  digitalWrite(latchPin2, HIGH);
}
while(value2)
{
  delay(20);
  value2=digitalRead(pin2);
}

if(value3)
{
  if(m==0) m=1;
  else m=0;         
}
while(value3)
{
  delay(20);
  value3=digitalRead(pin3);
}

if(m>=1)
{ 
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
  delay(20);
  digitalWrite(latchPin1, LOW);
  shiftOut(dataPin1, clockPin1, LSBFIRST, num1[n1]);
  digitalWrite(latchPin1, HIGH);
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, num2[n2]);
  digitalWrite(latchPin2, HIGH);  
  delay(30);

 if(current_temp>=previous_temp+3)
 {  
    if(p1==7) m=3;
    else p1++;
    if(p2==0) m=3;
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

if(birthdayCount<=3 && m==3)
 {
  if(birthdayCount==0) delay(2000);
  if(birthdayCount==3) m=4;
  for (int i = 0; i < length; i++)
  {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); 
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   delay(tempo);
   }
   birthdayCount++;
 }
if(m==4)
{
  resetFunc();
}

if(current_time>=1400)
 {
   previous_temp = current_temp;
 }
}
