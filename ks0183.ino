#include <IRremote.h>
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

//buzzer pin
int buzzer = 5;

//button pins
int KEY2 = 2;
int KEY3 = 3;

//pin definition of flowing light
int led5 = 13;
int led4 = 12;
int led3 = 11;
int led2 = 10;
int led1 = 9;

int RECV_PIN = 6; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;

char i=0,flag=2; 
void setup ()
{
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  attachInterrupt(0, falling0, FALLING);
  attachInterrupt(1, falling1, FALLING);

  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT); 
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  for(char i=9;i<14;i++)
   digitalWrite(i,LOW);    
}

void loop()
{
  if(flag==0)
  {
  buzzer_();                //testing buzzer
  led_display();            //testing LED
  }
  if(flag==1)
  { 
  //Serial.println("status,  Hum(%),  Tem(C)      analog_val      light_val     lm35_val");
  DHT11();
  Serial.print(" analog: ");
  analog();                //testing analog input
  Serial.print(" light: ");
  Light();
  Serial.print(" lm35: ");
  LM35();
  Serial.println("");
  delay(800);
  }
  if(flag!=0 & flag!=1)
  {
    if (irrecv.decode(&results))
     {
       Serial.println(results.value, HEX);
       irrecv.resume(); // Receive the next value
     }  
  }
}

//Humidity Range: 20-90% RH
//Humidity Accuracy: ±5% RH
//Temperature Range: 0-50 °C
//Temperature Accuracy: ±2% °C
//Operating Voltage: 3V to 5.5V
void DHT11()
{
int chk;
chk = DHT.read(DHT11_PIN);    // READ DATA
switch (chk)
  {
    case DHTLIB_OK:  
                Serial.print("DHT11: OK humidity: "); 
                Serial.print(DHT.humidity,1);
                Serial.print(" temperature: ");
                Serial.print(DHT.temperature,1);
                Serial.print("");
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("DHT11: Checksum error        "); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("DHT11: Time out error        "); 
                break;
    default: 
                Serial.print("DHT11: Unknown error         "); 
                break;
  }
}

void buzzer_(void)
{
 char i;  
 for(i=0;i<80;i++)// output a frequency sound
 { 
  digitalWrite(buzzer,LOW);// sound
  delay(1);//delay1ms 
  digitalWrite(buzzer,HIGH);//not sound
  delay(1);//ms delay 
 } 
 for(i=0;i<100;i++)// output a frequency sound
 { 
  digitalWrite(buzzer,LOW);// sound
  digitalWrite(buzzer,HIGH);//not sound
  delay(2);//2ms delay 
 }
}

void led_display()
{
 digitalWrite(led1,HIGH);
 delay(500);
 digitalWrite(led1,LOW);
 digitalWrite(led2,HIGH);
 delay(500);
 digitalWrite(led2,LOW);
 digitalWrite(led3,HIGH);
 delay(500);
 digitalWrite(led3,LOW);
 digitalWrite(led4,HIGH);
 delay(500);
 digitalWrite(led4,LOW);
 digitalWrite(led5,HIGH);
 delay(500);
 digitalWrite(led5,LOW);
}

void analog()
{
int val;
val=analogRead(A0);
Serial.print(val);
}

void Light()
{
int val;
val=analogRead(A1);
Serial.print(val);
}

// The LM35 is a temperature sensor. It provides a linear output proportional to the temperature,
// with 0 V corresponding to 0 degrees C and an output voltage change of 10 mV for each degree C change.
// Arduino analog-to-digital converter (ADC) has a resolution of 1024 bits, and the reference voltage is 5 V.
void LM35()
{
int val;
val = analogRead(A2);          // read value from A2
float mv = ( val/1024.0)*5000; // conversion to volts
float cel = mv/10;             // conversion to celsius
float farh = (cel*9)/5 + 32;   // conversion to fahrenheit
Serial.print(cel);
}

void falling0()
{
flag=0;
}
void falling1()
{
flag=1;
}
