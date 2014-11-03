#include <LCD5110_Basic.h>
LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t MediumNumbers[];
extern uint8_t SmallFont[];
extern uint8_t BT1[];
extern uint8_t BT2[];
extern uint8_t BT3[];
extern uint8_t BT4[];
extern uint8_t psbn[];
char* myStrings[]={
  "CANAL1", "CANAL2", "CANAL3",
  "CANAL4", "CANAL5","CANAL6","CANAL7","CANAL8","CANAL9","CANAL10","CANAL11","CANAL12","CANAL13","CANAL14","CANAL15","CANAL16","CANAL17","CANAL18","CANAL19","CANAL20","CANAL21","CANAL22","CANAL23","CANAL23","CANAL24","CANAL25","CANAL26","CANAL27","CANAL28","CANAL29","CANAL30"};
String x;
boolean pase=false;
boolean pase1=false;
boolean pase2=false;
boolean pase3=false;
boolean pase4=false;
boolean infoLCD=false;
boolean confi=false;
int valboton;
int btestado;
int valx;
int valy;
int valz;
int valbatery;
int valspy; 
int estadomenu;
int boton;
int chanel;
void setup(){
  Serial.begin(57600);
  delay(1000);
  myGLCD.InitLCD();
  myGLCD.setFont(MediumNumbers);
  myGLCD.setFont(SmallFont);
  myGLCD.print("NEW", CENTER, 16);
  myGLCD.print("LINE", CENTER, 24);
  myGLCD.print("ROBOTIC", CENTER, 32);
  delay(1000);
  myGLCD.clrScr();
}

void loop(){

  while(confi==false){

    myGLCD.setFont(SmallFont);
    myGLCD.print("CONFIGURACION", CENTER, 0);
    myGLCD.setFont(SmallFont);
    myGLCD.print("SELEC", LEFT, 16);

    while(Serial.available()){
      valboton=Serial.read();
      boton=(int)valboton;  
    }

    if(boton==6){
      chanel++;
      chanel=min(chanel,31);
      for (int i = 0; i < chanel; i++){
        x=(myStrings[i]);
        delay (50);  
      }
      myGLCD.clrScr();
      myGLCD.print(x, RIGHT, 16);
      boton=0;  
    }

    if(boton==7){
      chanel--;
      chanel=max(chanel,0);
      for (int i = 0; i > chanel; i--){
        x=(myStrings[i]);
        delay (50);
      }
      myGLCD.clrScr();
      myGLCD.print(x, RIGHT, 16);
      boton=0;  
    }

    if(boton==9){
      confi=true;
      myGLCD.clrScr();
    }
  }


  while(confi==true){ 

    if(pase==false){
      valboton=0;
      myGLCD.drawBitmap(0, 0, psbn, 84, 48);
      pase=true;
    }

    while(Serial.available()){
      valboton=Serial.read();
      estadomenu=(int) valboton;  
    }

    if(estadomenu==1){
      if(pase1==false){
        myGLCD.clrScr();
        myGLCD.print("MODO 1", LEFT, 0);
        myGLCD.print("VUELO SPV", LEFT, 16);
        myGLCD.print("1 MOTOR 2 SERVOS", CENTER, 24);
        myGLCD.print("go0o0!!! go0o0!!", CENTER, 32);
        delay (4000);
        myGLCD.clrScr();
        pase1=true;  
      }
      while(pase1==true){
        if(Serial.available()){
          valboton=Serial.read();    
          btestado=Serial.read();  
        }
        myGLCD.print("INDICADORES", LEFT, 0);
        myGLCD.print("EJE X", LEFT, 16);
        myGLCD.printNumF(int(valx)/3, 2, RIGHT, 16);
        myGLCD.print("EJE Y", LEFT, 24);
        myGLCD.printNumF(int(valy)/3, 2, RIGHT, 24);
        myGLCD.print("EJE Z", LEFT, 32);
        myGLCD.printNumF(int(valz)/3, 2, RIGHT, 32); 
        if(valboton==8&&btestado>0){//######################### añadir elementos segun se integren valboton 5 a 8 cruceta control 5=muestra estado bateria 
          bateria(); 
        }   
      }    
    }

    if(estadomenu==2){
      if(pase2==false){
        myGLCD.clrScr();
        myGLCD.print("MODO 2", LEFT, 0);
        myGLCD.print("VUELO MXV", LEFT, 16);
        myGLCD.print("2 MOTOR 4 SERVOS", CENTER, 24);
        myGLCD.print("go0o0!!! go0o0!!", CENTER, 32);
        delay (4000);
        pase2=true;  
      }
      while(pase2==true){
        if(Serial.available()>0){      
          valx= Serial.read();    
          valy= Serial.read();
          valz= Serial.read();
          valboton= Serial.read();
          btestado= Serial.read();
          valspy= Serial.read();
        }   
      }   
      myGLCD.clrScr();
      myGLCD.print("INDICADORES", LEFT, 0);
      myGLCD.print("EJE X", LEFT, 16);
      myGLCD.printNumF(int(valx)/3, 2, RIGHT, 16);
      myGLCD.print("EJE Y", LEFT, 24);
      myGLCD.printNumF(int(valy)/3, 2, RIGHT, 24);
      myGLCD.print("EJE Z", LEFT, 32);
      myGLCD.printNumF(int(valz)/3, 2, RIGHT, 32);
      myGLCD.print("SPEED", LEFT, 48);
      myGLCD.printNumF(int(valspy)/3, 2, RIGHT, 48);
      delay (500);
      if(valboton==5){
        bateria();
      }  
    }

    if(estadomenu==3){
      if(pase3==false){
        myGLCD.clrScr();
        myGLCD.print("MODO 3", LEFT, 0);
        myGLCD.print("CAR SP", LEFT, 16);
        myGLCD.print("1 MOTOR 2 SERVOS", CENTER, 24);
        myGLCD.print("go0o0!!! go0o0!!", CENTER, 32);
        delay (4000);
        pase3=true;  
      }
      while(pase3==true){
        if(Serial.available()>0){      
          valboton= Serial.read();
          btestado= Serial.read();
          valspy= Serial.read();
        }   
        myGLCD.clrScr();
        myGLCD.print("INDICADORES", LEFT, 0);
        if(valboton==5){
          bateria();
        }  
      }
    }

    if(estadomenu==4){
      if(pase4==false){
        myGLCD.clrScr();
        myGLCD.print("MODO 1", LEFT, 0);
        myGLCD.print("CAR MX", LEFT, 16);
        myGLCD.print("2 MOTOR 2 SERVOS", CENTER, 24);
        myGLCD.print("go0o0!!! go0o0!!", CENTER, 32);
        delay (4000);
        pase4=true;  
      }
      while(pase4==true){
        if(Serial.available()>0){      
          valx= Serial.read();    
          valy= Serial.read();
          valz= Serial.read();
          valboton= Serial.read();
          btestado= Serial.read();
          valspy= Serial.read();
        }   
        myGLCD.clrScr();
        myGLCD.print("INDICADORES", LEFT, 0);
        myGLCD.print("EJE X", LEFT, 16);
        myGLCD.printNumF(int(valx)/3, 2, RIGHT, 16);
        myGLCD.print("EJE Y", LEFT, 24);
        myGLCD.printNumF(int(valy)/3, 2, RIGHT, 24);
        myGLCD.print("EJE Z", LEFT, 32);
        myGLCD.printNumF(int(valz)/3, 2, RIGHT, 32);
        myGLCD.print("SPEED", LEFT, 48);
        myGLCD.printNumF(int(valspy)/3, 2, RIGHT, 48);
        delay (500);
        if(valboton==5){
          bateria();
        }  
      }
    }
  }
}
