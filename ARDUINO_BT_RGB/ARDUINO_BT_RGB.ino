// Controle de um LED RGB por um módulo Bluetooth Hc-05 + Arduino  usando o RoboRemo app
//BABUINO.TEC
//vagnerromario@hotmail.com

// Hardware setup:
// Conexão do  modulo bluetooth hc-05 no arduino 
// BT          Arduino 
// GND ------- GND
// VCC ------- 5V
// TX-O ------ pin0
// RX-I ------ pin1

// RGB led        Arduino
// VCC ---------- 5V
// red ----|__|-- pin8
// green --|__|-- pin9
// blue ---|__|-- pin10

//       3 resistores  x 330R

#include <Servo.h>
Servo myservo;  
int pos = 0;  
#define bluetooth Serial

int red = 8;       // LOW = acende, HIGH = apaga
int green = 9;    // LOW = acende, HIGH = apaga
int blue = 10;     // LOW = acende, HIGH = off

char cmd[100];
int cmdIndex;


void exeCmd() {
  
  if( (cmd[0]=='r' || cmd[0]=='g' || cmd[0]=='b') && cmd[1]==' ' ) { 
    // "r", "g", "b" São as referentes letras em ingles para  red, green and blue (vermelho,verde,azul )   
       int val = 0;
       for(int i=2; cmd[i]!=0; i++) {
         val = val*10 + (cmd[i]-'0');
       }
       // if cmd is "r 100", val will be 100        
       if(cmd[0]=='r') analogWrite(red, 255-val);
       if(cmd[0]=='g') analogWrite(green, 255-val);
       if(cmd[0]=='b') analogWrite(blue, 255-val);
       
  } 

  
}



void setup() {
  
  delay(500); 
  myservo.attach(11);
  bluetooth.begin(9600); 
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  digitalWrite(red, HIGH);  // luz desligada
  digitalWrite(green, HIGH);  // luz desligada
  digitalWrite(blue, HIGH);  // luz desligada
  
  cmdIndex = 0;
}


void loop() {
  
  if(bluetooth.available()) {
    
    char c = (char)bluetooth.read();
    
    if(c=='\n') {
      cmd[cmdIndex] = 0;
      exeCmd();  
      cmdIndex = 0; 
    } else {      
      cmd[cmdIndex] = c;
      if(cmdIndex<99) cmdIndex++;
    }
    
       
    
  }
  
  
}

