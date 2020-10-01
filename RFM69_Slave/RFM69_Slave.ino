#include <Wire.h>

#define RFM69_REG_MSG_AVAIL        0x01
#define RFM69_REG_TX_FREE          0x02
#define RFM69_REG_GET_MSG          0x08


uint8_t  reg_addr;
byte     rd_msg[64];


void setup()
{
  Wire.begin(0x08);                 // join i2c bus with address 
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent);  // register event    HAL_UART_Transmit(&huart3, (uint8_t*)linefeed, strlen(linefeed),HAL_MAX_DELAY);

  Serial.begin(9600);            // start serial for output
  delay(2000);
  Serial.println("RFM69 Slave");
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available())  // loop through all but the last
  {
    reg_addr = Wire.read();   // receive byte as a character
    Serial.print("receive event");           // print the character
    Serial.println(reg_addr,HEX);           // print the character
  }
}


void requestEvent()
{
 static char c = '0';
 Serial.println("request event");
 switch (reg_addr)
 {
    case RFM69_REG_MSG_AVAIL:
        Wire.write('4');
        break;
    case RFM69_REG_TX_FREE:
        Wire.write('1');
        break;
    case RFM69_REG_GET_MSG:    
        strcpy(rd_msg,"ABCDEFGHIK_123456789");
        Wire.write(rd_msg,60);    
        break;
 }
 if (c > 'z')
   c = '0';
}
