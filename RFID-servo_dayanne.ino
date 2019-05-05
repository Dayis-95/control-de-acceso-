#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


#define RST_PIN  9
#define SS_PIN   10

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo; 

byte LecturaUID[4];
byte Usuario1[4]= {0xF9, 0x85, 0x46, 0xBA} ; //tarjeta 
byte Usuario2[4]= {0x50, 0xE1, 0xB98B, 0x2F} ;   // llave


void setup() {
  
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  myServo.write (180);
  Serial.println("Listo");
}

void loop(){

  
  if (! mfrc522.PICC_IsNewCardPresent())
  return;

  if (! mfrc522.PICC_ReadCardSerial())
  return;

  //VER EN LA LAP
  Serial.print("UID:");
  for (byte i = 0; i <mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print ( " 0");
      }
      else{
        Serial.print (" ");
      }
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      LecturaUID[i]=mfrc522.uid.uidByte[i];
      }

      Serial.print("\t");

       if(comparaUID(LecturaUID, Usuario1))
          Serial.println("Bienvenido Usuario 1");
       else if(comparaUID(LecturaUID, Usuario2))
           Serial.println("Bienvenido Usuario 2");
        else
           Serial.println("No te conozco");
     
                mfrc522.PICC_HaltA();
                Serial.println("Authorized access");
    Serial.println();
    delay(500);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
}

boolean comparaUID(byte lecturaUID[],byte usuario[])
{
  for (byte i=0; i <mfrc522.uid.size; i++){
    if(lecturaUID[i] != usuario[i])
       return(false);
  }
       return(true);
}

      
  
