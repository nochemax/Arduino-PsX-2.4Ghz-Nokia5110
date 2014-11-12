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
int pito=9;  

int menu;
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
  Mirf.cePin = 8;
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
  delay(1000);
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
      delay(500);
      digitalWrite(pito,HIGH);
      delay(500);
      digitalWrite(pito,LOW);
      confi=true;  
    }
  }
  while(confi==true){

    Mirf.getData((byte *) &dato);

    if(dato==510){
     
        modoSimplevuelo();       
      
    }
    if(dato==515){
      
        modoComplejovuelo();
      
    }
    if(dato==525){
     
       modoSimplecoche();
      
    }
    if(menu==520){
      
        modoComplejocoche();
      
    }
  }
}



//////////////////#################### nueva pestaña para las funciones #####################\\\\\\\\\\\\

void modoSimplevuelo(){ // MODO SIMPLER RECEPTOR AVION 2 SERVOS 1 MOTOR 
  while(pase1==false){ 
    Mirf.getData((byte *) &dato);
    menu=(int)dato;  
    Serial.println("botonpulsado");
    Serial.println(menu);

    if(menu==630){    //motor
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      velocidad=data;
      if(velocidad>=1){
        velocidad=map(velocidad,0,255,0,2000);
        myMotor1.write(velocidad);
        Serial.println("velocidad");
        Serial.println(velocidad);
        delay(250);  
      } 
      if(velocidad<=-1){
        velocidad=map(velocidad,0,-255,0,+2000);
        myMotor1.write(velocidad);
        Serial.println("velocidad");
        Serial.println(velocidad);
        delay(250);  
      }  
    }
    if(menu==615){  // timon
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      sV1=data;
      Serial.println("grados del servo timon");
      Serial.println(sV1);
      if(sV1>=1){
        sV1=map(sV1,0,89,123,178);
        servo1.write(sV1);    
        Serial.println("grados del servo timon");
        Serial.println(sV1);
        delay(250);
      }
      if(sV1<=-1){
        sV1=map(sV1,0,-89,123,+50);
        servo1.write(sV1);     
        Serial.println("grados del servo timon");
        Serial.println(sV1);
        delay(250);
      }
    }

    if(menu==600){   //cola
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);  
      }
      sV2=data;
      Serial.println("grados del servo cola");
      Serial.println(sV2);
      if(sV2>=1){
        sV2=map(sV2,0,-89,90,30);     
        servo2.write(sV2);    
        Serial.println("grados del servo cola");
        Serial.println(sV2);
        delay(250);
      }
      if(sV2<=-1){
        sV2=map(sV2,0,89,90,+120);
        servo2.write(sV2);     
        Serial.println("grados del servo cola");
        Serial.println(sV2);
        delay(250);
      }
    }
    if(menu==525){
      servo1.write(123);
      servo2.write(90); 
      delay(250);
    }
    myMotor1.write(velocidad);
  data=0;
  }
}

void modoComplejovuelo(){
  while(pase2==false){ 
    while(Mirf.dataReady()){ 
      Mirf.getData((byte *) &dato);
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
    if(dato==630){ //motor
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      velocidad=data;
      if(velocidad>=1){
        velocidad=map(velocidad,0,255,0,2000);
        myMotor1.write(velocidad);
        myMotor2.write(velocidad);
        delay(250);
      }
      if(velocidad<=-1){
        velocidad=map(velocidad,0,-255,0,+2000);
        myMotor1.write(velocidad);
        myMotor2.write(velocidad);
        delay(250);
      }
    }
    if(dato==615){ 
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      sV1=data;
      Serial.println(sV1);
      if(sV1>=1){
        servo1.write(sV1+89);
        delay(80);
      }
      if(sV1<=-1){
        servo1.write(sV1-89);
        delay(80);
      }
    }
    if(dato==23796){ //flayer alas queda por costruir
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
      }
    }
    if(dato==600){ 
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      sV2=data;
      if(sV2>=1){
        servo2.write(sV2+89);
        delay(250);
      }
      if(sV2<=-1){
        servo2.write(sV2-89);
        delay(250);
      }
    }
    if(dato==505){

    }
    if(dato==510){

    }
  }
}
void modoSimplecoche(){
  while(pase3==false){ 
    while(Mirf.dataReady()){ 
      Mirf.getData((byte *) &dato);
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
    if(dato==12111){ 
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      velocidad=data;
      if(velocidad>=1){
        velocidad=map(velocidad,0,255,0,2000);
        myMotor1.write(velocidad);
        myMotor2.write(velocidad);
        delay(250);
      }
      if(velocidad<=-1){
        velocidad=map(velocidad,0,-255,0,+2000);
        myMotor1.write(velocidad);
        myMotor2.write(velocidad);
        delay(250);
      }
    }
    if(dato==615){ 
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      sV1=data;
      if(sV1>=1){
        servo1.write(sV1+90);
        delay(250);
      }
      if(sV1<=-1){
        servo1.write(sV1-89);
        delay(250);
      }
    }
  }
}
void modoComplejocoche(){
  while(pase4==false){ 
    while(Mirf.dataReady()){ 
      Mirf.getData((byte *) &dato);
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
    velocidad=data;
    if(velocidad>=1){
      velocidad=map(velocidad,0,255,0,2000);
      myMotor1.write(velocidad);
      myMotor2.write(velocidad);
      delay(250);
    }
    if(velocidad<=-1){
      velocidad=map(velocidad,0,-255,0,+2000);
      myMotor1.write(velocidad);
      myMotor2.write(velocidad);
      delay(250);
    }
    if(dato==615){ // Direccion
      if(Mirf.dataReady()){
        Mirf.getData((byte *) &data);
      }
      sV1=data;

      if(sV1>=1){
        servo1.write(sV1+90);
        delay(250);
      }
      if(sV1<=-1){
        servo1.write(sV1-89);
        delay(250);
      }
    }
    if(dato==505){

    }
    if(dato==510){

    }
  }
}
