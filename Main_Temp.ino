#include <EEPROM.h>

const int NUMERO_TEMPERATURAS = 40; // constante con el numero de temperaturas que guardamos, asi cambiando este valor se cambia en todo el programa.

  
  //--------------------------ESCRIBIR------------------------------------------
  // Funcion : Nos escribe los valores de temperatura que va leyendo.
  // Frequencia: Cada 10 minutos
  //----------------------------------------------------------------------------
  int escribir(){
   int PIN_temperatura = 0;//PIN A0
   int memfull = 12;
   int direccion_escritura = 0;
   float temperatura_escritaC = 0.0;
   
   temperatura_escritaC = analogRead(PIN_temperatura);
   temperatura_escritaC = (5.0 * temperatura_escritaC *100.0)/1024.0;
   temperatura_escritaC -= 400;
   EEPROM.write(direccion_escritura, temperatura_escritaC);
    direccion_escritura+=1;
  
      if(direccion_escritura == NUMERO_TEMPERATURAS)
        direccion_escritura = 0;
        digitalWrite(memfull, HIGH);

   //delay(36000000);
   delay(5000);
   return direccion_escritura;
  }
  
  //-------------------------------LEER-----------------------------------------
  //Funcion: Nos lee de golpe los valores guardados en EEPROM
  //----------------------------------------------------------------------------
  
  void leer(){
     int direccion_lectura = 0; 
     float Temperatura_leidaC = 0.0;
     
     for(int i = 0; i<NUMERO_TEMPERATURAS; i++){
  	Temperatura_leidaC = EEPROM.read(Temperatura_leidaC); 
        direccion_lectura+=1;
        Serial.print(Temperatura_leidaC);
     }
  }
  
  //-----------------------------LIMPIAR-----------------------------------------
  //Funcion: Nos pone toda la memoria EEPROM a 0
  //-----------------------------------------------------------------------------
  
  void limpiar(){
  for(int i=0;i<NUMERO_TEMPERATURAS;i++)
    EEPROM.write(i,0);
  
  digitalWrite(13,HIGH);
  
}

 //--------------------------------------------------------------------------------
  

void setup(){
  Serial.begin(9600);
}
void loop(){
  while(Serial.available() == 0);
  int valor = Serial.read() - '0';
  
  if(valor ==1){
    Serial.print("Escribiendo...");
    while(escribir() != NUMERO_TEMPERATURAS && valor != 0){ // mientras que no llegue al maximo de temperaturas y que el numero que entra por el serial sea diferente de 0, sigue escribiendo
        if(Serial.available()!=0){ 
        valor = Serial.read() - '0';//leemos el valor que entra por el serial monitor
        }
    }
    Serial.print("Leyendo...");
    leer();
    Serial.print("Limpiando...");
    limpiar();
  }
}

