#include <PS2X_lib.h>  //for v1.6
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define PS2_DAT        4      
#define PS2_CMD        3  
#define PS2_SEL        2  
#define PS2_CLK        5  
#define pressures   false
#define rumble      false

PS2X ps2x; 
int Rbateria=A1;
boolean pad=false;                 //variables
boolean infoLCD=false;
boolean confi=false;
byte val = 0;
byte vibrate=0; 
int RX=0;
int RY=0;
int LX=0;
int LY=0;
int range1 = 178;               
int threshold1 = range1/4;     
int center1 = range1/2;
int range2 = 178;               
int threshold2 = range2/4;     
int center2 = range2/2;
int range3 = 510;               
int threshold3 = range3/4;     
int center3 = range3/2;
int range4 = 510;               
int threshold4 = range4/4;     
int center4 = range4/2;

int distanceRY=0;
int distanceRX=0;
int distanceLY=0;
int distanceLX=0;
int canal=0;
int valboton;
int btestado;
int valx;
int valy;
int valz;
int dato;
int data;
long valbatery;
int valspy;
int a;
int b;
int c;
int d;

void setup(){

  Serial.begin(57600);
  delay(500); 
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  delay(500);           
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload = sizeof(valx);//entrada
  Mirf.payload = sizeof(valy);//entrada
  Mirf.payload = sizeof(valz);//entrda
  Mirf.payload = sizeof(btestado);//entrada
  Mirf.payload = sizeof(data); //salida
  Mirf.payload = sizeof(dato);//salida
  Mirf.payload = sizeof(canal);//salida
  Mirf.channel = 10;
  Mirf.config();
  delay(500);
pinMode(Rbateria,INPUT);
}

void loop(){    

  while(confi==false){

    ps2x.read_gamepad(false,vibrate);

    if(ps2x.Button(PSB_PAD_RIGHT)){ 
      canal++;
      canal=min(canal,31);
      valboton=6;                             
      Serial.write(valboton);
      delay(150);  
    }

    if(ps2x.Button(PSB_PAD_LEFT)){
      canal--;
      canal=max(canal,0);
      valboton=7;                             
      Serial.write(valboton);
      delay(150); 
    }
   
    if(ps2x.Button(PSB_START)) {        
      valboton=9;                             
      Serial.write(valboton);
      dato=canal; 
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *) &dato);
      while(Mirf.isSending()){                           
      }
      Mirf.spi = &MirfHardwareSpi;
      Mirf.init();
      Mirf.setTADDR((byte *)"serv1");
      Mirf.payload = sizeof(valx);
      Mirf.payload = sizeof(valy);
      Mirf.payload = sizeof(valz);
      Mirf.payload = sizeof(btestado);
      Mirf.payload = sizeof(data); 
      Mirf.payload = sizeof(dato);
      Mirf.channel = canal;
      Mirf.config();
      delay(1000);
      confi=true; 
    }  
  }
  while(confi==true){
    
    ps2x.read_gamepad(false,vibrate);

    if(ps2x.Button(PSB_TRIANGLE)){           
      valboton=1;      
      Serial.write(valboton);
      dato=510;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte*) &dato);
      while(Mirf.isSending()){
      }    
      padpsx();
    }

    if(ps2x.Button(PSB_CIRCLE)){              
      valboton=2;                             
      Serial.write(valboton);    
      dato=515;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *) &dato);
      while(Mirf.isSending()){
      }          
      padpsx();  
    }

    if(ps2x.Button(PSB_CROSS)){             
      valboton=3;                             
      Serial.write(valboton);    
      Serial.println(dato);
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *) &dato);
      while(Mirf.isSending()){                       
      }
      padpsx();  
    }

    if(ps2x.Button(PSB_SQUARE)){             
      valboton=4;                             
      Serial.write(valboton);    
      dato=520;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *) &dato);
      while(Mirf.isSending()){
      }
      padpsx();  
    }
  }
}


///////////////############################ abrir pestaña ###########################\\\\\\\\\\\\\\\\\\\\

int calculo(){
  RY = map(ps2x.Analog(PSS_RY),  0, 255, 0, range1);    
  distanceRY = RY-center1;
  if (abs(distanceRY)<threshold1) {
    distanceRY=0;
  }  
  RX = map(ps2x.Analog(PSS_RX),  0, 255, 0, range2);    
  distanceRX = RX-center2;
  if (abs(distanceRX)<threshold2) {
    distanceRX=0;
  }
  LY = map(ps2x.Analog(PSS_LY),  0, 255, 0, range3);    
  distanceLY = LY-center3;
  if (abs(distanceLY)<threshold3) {
    distanceLY=0;
  }
  LX = map(ps2x.Analog(PSS_LX),  0, 255, 0, range4);    
  distanceLX = LX-center4;
  if (abs(distanceLX)<threshold4) {
    distanceLX=0;
  }
  a=distanceRY;
  b=distanceRX;
  c=distanceLY;
  d=distanceLX;
}

void padpsx (){                                  //################################# control pad ##################################

  while(pad==false){

    ps2x.read_gamepad(false,vibrate);
    RY = ps2x.Analog(PSS_RY);
    RX = ps2x.Analog(PSS_RX);          
    LY = ps2x.Analog(PSS_LY); 
    LX = ps2x.Analog(PSS_LX); 
    calculo();

    if(a>0||a<0){ 
      dato=600; 
      Mirf.setTADDR((byte *)"clie1");    
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){

      }
      ps2x.read_gamepad();
      RY = map(ps2x.Analog(PSS_RY),  0, 255, 0, range1);    
      distanceRY = RY-center1;
      if (abs(distanceRY)<threshold1) {
        distanceRY=0;
      }       
      data=distanceRY;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&data);
      while(Mirf.isSending()){                       
      }
    }

    if(b>0||b<0){
      dato=615; 
      Mirf.setTADDR((byte *)"clie1");    
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){
      }
      ps2x.read_gamepad();
      RX = map(ps2x.Analog(PSS_RX),  0, 255, 0, range2);    
      distanceRX = RX-center2; 
      if (abs(distanceRX)<threshold2) {
        distanceRX=0;
      } 
      data=distanceRX;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&data);
      while(Mirf.isSending()){                     
      }
    }

    if(c>0||c<0){
      dato=630; 
      Mirf.setTADDR((byte *)"clie1");    
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){
      }
      ps2x.read_gamepad();
      LY = map(ps2x.Analog(PSS_LY),  0, 255, 0, range3);    
      distanceLY = LY-center3;
      if (abs(distanceLY)<threshold3) {
        distanceLY=0;
      }
      data=distanceLY;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&data);
      while(Mirf.isSending()){                   
      }
    }

    if(d>0||d<0){
      dato=645; 
      Mirf.setTADDR((byte *)"clie1");    
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){
      }
      ps2x.read_gamepad();
      LX = map(ps2x.Analog(PSS_LX),  0, 255, 0, range4);    
      distanceLX = LX-center4;
      if (abs(distanceLX)<threshold4) {
        distanceLX=0;
      }
      data=distanceLX;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&data);
      while(Mirf.isSending()){                       
      }
    }

    if(ps2x.Button(PSB_L1)){
      dato=490;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                       
      }
    }

    if(ps2x.Button(PSB_R1)){
      dato=495;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                      
      }
    }

    if(ps2x.Button(PSB_L2)){
      dato=500;
      Mirf.setTADDR((byte *)"serv1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                       
      }
    }

    if(ps2x.Button(PSB_R2)){
      dato=505;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                        
      }
    }

    if(ps2x.Button(PSB_TRIANGLE)){
      dato=510;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                      
      }
    }

    if(ps2x.Button(PSB_CIRCLE)){              
      dato=515;
      Mirf.setTADDR((byte *)"serv1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                       
      }
    }

    if(ps2x.Button(PSB_CROSS)){             
      dato=525;
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                     
      }
    }

    if(ps2x.Button(PSB_SQUARE)){             
      dato=520;  
      Mirf.setTADDR((byte *)"serv1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                     
      }
    }

    if(ps2x.Button(PSB_START)) {        
      dato=530; 
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                           
      }
    }

    if(ps2x.Button(PSB_SELECT)){
      dato=535; 
      Mirf.setTADDR((byte *)"clie1");  
      Mirf.send((byte *)&dato);
      while(Mirf.isSending()){                       
      }
    }                                                   //funciones de indicaciones pantalla

    if(ps2x.Button(PSB_PAD_UP)) {     
      valboton=5; 
      Serial.write(valboton);
      delay(150); 
    }

    if(ps2x.Button(PSB_PAD_RIGHT)){ 
      valboton=6;                             
      Serial.write(valboton);
      delay(150); 
    }

    if(ps2x.Button(PSB_PAD_LEFT)){
      valboton=7;                             
      Serial.write(valboton);
      delay(150); 
    }

    if(ps2x.Button(PSB_PAD_DOWN)){ // bateria  btestado
      valboton=8;                             
      valbatery = analogRead(Rbateria);
      btestado=((valbatery*(9600/1023))/100);
      Serial.write(valboton);
      Serial.write(btestado);  
      delay(150); 
    }

    if(!Mirf.isSending() && Mirf.dataReady()){  
      Mirf.getData((byte *) &valx);
      Mirf.getData((byte *) &valy);
      Mirf.getData((byte *) &valz);
      Mirf.getData((byte *) &valspy);
      delay(50);                                   
      Serial.write(valx);
      Serial.write(valy);
      Serial.write(valz);
      Serial.write(valspy);           
      delay(50);
    }  
  }
}
