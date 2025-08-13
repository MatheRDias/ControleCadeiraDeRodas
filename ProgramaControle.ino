
#include "mpu6050.h"


int anguloy;
int angulox;
#define IN1 8
#define IN2 9



#define IN3 11
#define IN4 12
 



void setup() {



  pinMode(2,OUTPUT);
  Serial.begin(9600);

 

  mpu_begin();

  Serial.println("Calibrando, deixa parado!");
  delay(1000);
  mpu_calibrate(400);
  Serial.println("===== Calibrado! =====\n");

  delay(20);
  
}

void loop() {

   int direita = 3;
  int esquerda = 4;
  int frente = 5;
  int tras = 6;
  
  
  mpu_loop();
  
  anguloy = getAngleY();
  angulox = getAngleX();



if (anguloy  <= 3 || anguloy  >= -3 ){



digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
   digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);   
    
  }

  
  if (anguloy  >=  3 ){

    //direita 
    
   digitalWrite(IN1,  HIGH );
  digitalWrite(IN2, LOW);
  
   digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  
    
  }else if (anguloy <= -3){

  digitalWrite(IN1,LOW );
  digitalWrite(IN2, HIGH);
  
   digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
 

    
   }else{ 
    digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
   digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
   }


 if (angulox  >=  3 ){

  //tras

   digitalWrite(IN1,  HIGH );
  digitalWrite(IN2, LOW);
  
   digitalWrite(IN3,HIGH );
  digitalWrite(IN4, LOW);
   

    
    
  }else if (angulox <= -3){
    
  //frente
     digitalWrite(IN1,  LOW );
  digitalWrite(IN2, HIGH);
  
   digitalWrite(IN3, LOW );
  digitalWrite(IN4, HIGH); 
   }else{ 
    digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
   digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
   }









  Serial.println(anguloy);

 

  
}
