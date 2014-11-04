#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h>

Servo myMotor1;  //ping, (libreria servo sistema de frecuencia de pulso para ESC y servo) 
Servo myMotor2;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
int pito=3;  

int dato;    //variables
int data;
int canal;
int distanceRY=0;
int distanceRX=0;
int distanceLY=0;
int distanceLX=0;
int valboton;
int btestado;
int valx;
int valy;
int valz;
int valbatery;
int valspy;
int velocidad;
int sV1;
int sV2;
int sV3;
int sV4;
boolean pase1=false;
boolean pase2=false;
boolean pase3=false;
boolean pase4=false;
boolean confi=false;

void setup(){
  Serial.begin(57600);
  delay(500);
  Mirf.cePin = 8;        // pin radio esclavo 
  Mirf.csnPin = 7;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1"); 
  Mirf.payload = sizeof(valx);//salida
  Mirf.payload = sizeof(valy);//salida
  Mirf.payload = sizeof(valz);//salida
  Mirf.payload = sizeof(btestado);//salida
  Mirf.payload = sizeof(data);//entrada
  Mirf.payload = sizeof(dato);//entrada

  Mirf.channel = 10;
  Mirf.config();
  delay(500);
  pinMode(pito,OUTPUT);
  myMotor1.attach(2);
  myMotor2.attach(3);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(10);
  myMotor1.write(0);
  myMotor2.write(0);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void loop(){

  while(confi==false){
    Mirf.getData((byte *) &dato);
    Serial.println(dato);
    if(dato>0&&dato<30){
   canal=dato;
      Mirf.spi = &MirfHardwareSpi;
      Mirf.init();
      Mirf.setRADDR((byte *)"clie1"); 
      Mirf.payload = sizeof(valx);//salida
      Mirf.payload = sizeof(valy);//salida
      Mirf.payload = sizeof(valz);//salida
      Mirf.payload = sizeof(btestado);//salida
      Mirf.payload = sizeof(data);//entrada
      Mirf.payload = sizeof(dato);//entrada
      Mirf.payload = sizeof(dato);//entrada
      Mirf.channel = canal;
      Mirf.config();
      Serial.println(canal);
      delay(500);
      digitalWrite(pito,HIGH);
      delay(500);
      digitalWrite(pito,LOW);
      delay(500);
      digitalWrite(pito,HIGH);
      delay(1000);
      digitalWrite(pito,LOW);
      confi=true;  
    }
  }
  while(confi==true){
    Mirf.getData((byte *) &dato);
    Serial.println(dato);

    if(dato==510){
      dato=0;
      while(pase1==false){ 
        modoSimplevuelo(); 
      }  
    }
    if(dato==515){
      while(pase2==false){ 
        modoComplejovuelo();
      }
    }
    if(dato==525){
      while(pase3==false){ 
        modoSimplecoche();
      }
    }
    if(dato==520){
      while(pase4==false){ 
        modoComplejocoche();
      }
    }
    delay(10);
  }
}

//////////////////#################### nueva pestaña para las funciones #####################\\\\\\\\\\\\

void modoSimplevuelo(){ // MODO SIMPLER RECEPTOR AVION 2 SERVOS 1 MOTOR 
  Mirf.getData((byte *) &dato);
  Serial.println(dato);
  delay(10);
  if(dato==630){    //motor
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    velocidad=data;
     //Serial.println(velocidad);
    myMotor1.write(velocidad);
  }

  if(dato==615){  // timon
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    sV1=data;
     //Serial.println(sV1);
    if(sV1<=1){
      sV1=map(sV1, 1,180,90,180);
      servo1.write(sV1);    
    }
    if(sV1<=-1){
      sV1=map(sV1, -1,-180,90,0);
      servo1.write(sV1);     
    }
  }

  if(dato==600){   //cola
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);  
    }
    sV2=data;
    // Serial.println(sV2);
    if(sV2<=1){
      sV2=map(sV2, 1,180,90,180);
      servo2.write(sV2);    
    }
    if(sV2<=-1){
      sV1=map(sV2, -1,-180,90,0);
      servo2.write(sV2);
    }
  }
}

void modoComplejovuelo(){
  while(Mirf.dataReady()){  // MODO COMPLEJO RECEPTOR AVION 4 SERVOS 2 MOTORES
    Mirf.getData((byte *) &dato);
    //Serial.println(dato);
  }
  Mirf.setTADDR((byte *)"serv1");  
  Mirf.send((byte *) &valx);
  Mirf.send((byte *) &valy);
  Mirf.send((byte *) &valz);
  Mirf.send((byte *) &valboton);
  Mirf.send((byte *) &valspy);
  while(Mirf.isSending()){
    delay(50);
  }

  if(dato==12111){   //motor   
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }   
    velocidad=data;
    //Serial.println(velocidad);
    velocidad=min(velocidad, 255);
    velocidad=max(velocidad, 0);
    if(velocidad>=velocidad){
      myMotor1.write(velocidad);  
      myMotor2.write(velocidad); 
    }
  }

  if(dato==31565){  //timon  
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    sV1=data;
     //Serial.println(sV1);
    if(sV1<=1){
      sV1=map(sV1, 1,180,90,180);
      servo1.write(sV1);    
    }
    if(sV1<=-1){
      sV1=map(sV1, -1,-180,90,0);
      servo1.write(sV1);  
    }
  }

  if(dato==23796){   //flayer alas
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    sV2=data;
     //Serial.println(sV2);
    if(sV2<=1){
      sV2=map(sV2, 1,180,90,180);
      servo2.write(sV2);    
    }
    if(sV2<=-1){
      sV1=map(sV2, -1,-180,90,0);
      servo3.write(sV2);   
      Serial.println("denro mamon3");
    }
  }

  if(dato==-2628){  // COLA
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);  
    }
    sV4=data;
     //Serial.println(sV4);
    if(sV4<=1){
      sV4=map(sV4, 1,180,90,180);
      servo4.write(sV4);    
    }
    if(sV4<=-1){
      sV4=map(sV4, -1,-180,90,0);
      servo4.write(sV4);  
      Serial.println(data);
    } 
  }

  if(dato==505){
    //##### OTRAS OPERACIONES
  }
  if(dato==510){
    //##### OTRAS OPERACIONES  
  }
}


void modoSimplecoche(){
  while(Mirf.dataReady()){  // MODO SIMPLER RECEPTOR AVION 2 SERVOS 1 MOTOR 
    Mirf.getData((byte *) &dato);
    //Serial.println(dato);
  }
  Mirf.setTADDR((byte *)"serv1");  
  Mirf.send((byte *) &valx);
  Mirf.send((byte *) &valy);
  Mirf.send((byte *) &valz);
  Mirf.send((byte *) &valboton);
  Mirf.send((byte *) &btestado);
  Mirf.send((byte *) &valspy);
  while(Mirf.isSending()){
    delay(50);
  }
  myMotor1.write(velocidad);

  if(dato==12111){    //motor   ojo entra negativo marcha atras ESC preparado para ello 
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }   
    velocidad=data;
     //Serial.println(velocidad);
    if(velocidad>=velocidad){
      myMotor1.write(velocidad);  
    }
  }


  if(dato==23796){  // direccion
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    sV1=data;
     //Serial.println(sV1);
    if(sV1<=1){
      sV1=map(sV1, 1,180,90,180);
      servo1.write(sV1);    
    }
    if(sV1<=-1){
      sV1=map(sV1, -1,-180,90,0);
      servo1.write(sV1);     
    }
  }
}

void modoComplejocoche(){
  while(Mirf.dataReady()){  // MODO COMPLEJO RECEPTOR AVION 4 SERVOS 2 MOTORES
    Mirf.getData((byte *) &dato);
  //  Serial.println(dato);
  }
  Mirf.setTADDR((byte *)"serv1");  
  Mirf.send((byte *) &valx);
  Mirf.send((byte *) &valy);
  Mirf.send((byte *) &valz);
  Mirf.send((byte *) &valboton);
  Mirf.send((byte *) &btestado);
  Mirf.send((byte *) &valspy);
  while(Mirf.isSending()){
    delay(50);
  }

  if(dato==12111){   //motor
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }   
    velocidad=data;
     Serial.println(velocidad);
    if(velocidad>=velocidad){
      myMotor1.write(velocidad);  
      myMotor2.write(velocidad); 
    }
  }

  if(dato==31565){  //direccion  
    if(Mirf.dataReady()){
      Mirf.getData((byte *) &data);
    }
    sV1=data;
    // Serial.println(sV1);
    if(sV1<=1){
      sV1=map(sV1, 1,180,90,180);
      servo1.write(sV1);    
      servo2.write(sV1);  
    }
    if(sV1<=-1){
      sV1=map(sV1, -1,-180,90,0);
      servo1.write(sV1);  
      servo2.write(sV1);  
    }
  }

  if(dato==505){
    //##### OTRAS OPERACIONES
  }
  if(dato==510){
    //##### OTRAS OPERACIONES  
  }
}
