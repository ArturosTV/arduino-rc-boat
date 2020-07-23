//Приёмник (катер)
#include <Servo2.h>                                            
#include <SPI.h>                                                        
#include <nRF24L01.h>                                                   
#include <RF24.h>                                                       
RF24 radio(9,10);                                                       
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  
byte recieved_control[5];                                              
Servo2 servo1;                                                          
byte IN1 = 2;                                                             
byte IN2 = 4;                                                  
byte ENA = 3;                 
int fspeed;           
int bspeed;           
int data; 
    
void setup(){
 radio.begin();                            
 radio.setAutoAck(1);                      
 radio.setRetries(0,15);                   
 radio.enableAckPayload();                 
 radio.setPayloadSize(32);                 
 radio.openReadingPipe(1,address[0]);      
 radio.setChannel(0x60);                   
 radio.setPALevel (RF24_PA_MAX);           
 radio.setDataRate (RF24_1MBPS);           
 radio.startListening();                   
 radio.powerUp();                          
 pinMode (IN1, OUTPUT);                    
 pinMode (IN2, OUTPUT);                    
 pinMode (ENA, OUTPUT);  
 servo1.attach(5);
}

void stop()    {                                   
 analogWrite(ENA, 0);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
}

void forward(int fspeed){                                     
 analogWrite(ENA, fspeed);
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
}

void backward(int bspeed){                                     
 analogWrite(ENA, bspeed);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
}

void loop() {
 byte pipeNo;                          
 while( radio.available(&pipeNo)){                            
  radio.read(&recieved_control, sizeof(recieved_control) );   
}
 servo1.write(recieved_control[1]);                        
 if (recieved_control[0]>=0&&recieved_control[0]<=115)data = recieved_control[0], bspeed = map(data, 0, 115, 255, 0), backward(bspeed);
 if (recieved_control[0]>=140&&recieved_control[0]<=255)data = recieved_control[0], fspeed = map(data, 140, 255, 0,255), forward(fspeed);
 if (recieved_control[0] >115 && recieved_control[0] <140)data = recieved_control[0], stop();
}
