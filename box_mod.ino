#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int sensorPin = A0;  // Analog input pin that senses Vout
const int buttonup = 2;
const int buttondown = 3;
const int fire = 5;
const int firebutton = 4;

int sensorValue = 0;       // sensorPin default value

int button1 = 0;
int button2 = 0;
int fire1 = 0;

float Vin = 5;             // Input voltage
float Vout = 0;            // Vout default value
float Rref = 880;          // Reference resistor's value in ohms (you can give this value in kiloohms or megaohms - the resistance of the tested resistor will be given in the same units)
float R = 0;               // Tested resistors default value

float voltmax = 42;
float voltmin = 0;

float volt = 0;
float watt = 0;
float ohm = 0.1;

void setup()   
{ 
  Serial.begin(9600);
  
  pinMode(buttonup, INPUT);
  pinMode(buttondown ,INPUT);
  pinMode(firebutton, INPUT);
  pinMode(fire, OUTPUT);
  digitalWrite(buttonup, HIGH);
  digitalWrite(buttondown, HIGH);
  
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  display.clearDisplay();
}

void loop() 
{
  sensorValue = analogRead(sensorPin);  // Read Vout on analog input pin A0 (Arduino can sense from 0-1023, 1023 is 5V)
  Vout = (Vin * sensorValue) / 1023;    // Convert Vout to volts
  R = Rref * (1 / ((Vin / Vout) - 1));  // Formula to calculate tested resistor's value
  delay(1000);                          // Delay in milliseconds between reeds
  
    float volt1 = volt/10;
    watt = volt1*volt1/ohm;
    
    if (volt >= 42)
      {
        volt = 42;
      }
    if (volt <= 32)
      {
        volt = 32;      
      } 
  
    float pwm = volt/0.1960784313;// i moved the decimal place over one for greater accuracy
    //variable voltage setup
    if(fire1 == HIGH)
      {
        analogWrite(fire, pwm);
      }
    fire1 = digitalRead(firebutton);
    button1 = digitalRead(buttonup);
    button2 = digitalRead(buttondown);
     
      if (button1 == HIGH)
        {
          volt++;
          delay(50);
        }
      if (button2 == HIGH)
        {
          volt--;
          delay(50);
        }
     
    //titles
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("arduino box mod");
  display.setCursor(10, 20);
  display.println("watts =");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 30);
  display.println("volts =");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 40);
  display.println("ohms  =");
  display.setTextSize(1);
  display.setTextColor(WHITE);
//variables
  display.setCursor(60, 30);
  display.println(volt/10);
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.setCursor(60, 40);
  display.println(R);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(60, 20);
  display.println(watt); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display(); 
  display.clearDisplay();
}



