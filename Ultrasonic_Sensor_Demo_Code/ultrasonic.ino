
const int trigPin = 5;
const int echoPin = 18;
//const int trigPin = 2;
//const int echoPin = 5;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, trigPin, TXD2);
  
  
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
}

int digitalReadoutputPin(uint8_t pin){
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  if(port == NOT_A_PIN)
    return LOW;

  return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}

void loop() {
Serial2.begin(9600, SERIAL_8N1, trigPin, echoPin);
  Serial.println("Waiting: ");
     delay(900);
     
      
           while (Serial2.available()) {
        Serial.print(char(Serial2.read()));
        
      }
    
  

}
