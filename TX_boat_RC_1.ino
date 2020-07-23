//Передатчик (пульт)
#include <SPI.h>                                                       
#include <nRF24L01.h>                                                 
#include <RF24.h>                                                     
RF24 radio(9,10);                                                      
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"}; 
byte control[5];                                                      
byte POT_1 = A0;                                               
byte POT_2 = A1;                             
    
void setup() {
 radio.begin();                            
 radio.setAutoAck(1);                      
 radio.setRetries(0,15);                   
 radio.enableAckPayload();                 
 radio.setPayloadSize(32);                 
 radio.openWritingPipe(address[0]);        
 radio.stopListening();                    
 radio.setChannel(0x60);                   
 radio.setPALevel (RF24_PA_MAX);           
 radio.setDataRate (RF24_1MBPS);     
}

void loop() {
 radio.write(&control, sizeof(control));     
 control[0]=map(analogRead(POT_1),0,1023,0,255);    
 control[1]=map(analogRead(POT_2),0,1023,0,179);    
}

 

 



