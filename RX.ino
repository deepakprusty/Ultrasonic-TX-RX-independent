/* 
  Developed by:  Eduardo Zola - Zola Lab 2018 - www.zolalab.com.br - egzola@gmail.com
*/

int pos = 0;
unsigned char CH = 0;
unsigned int bits1 = 0;
boolean capture = false;

void setup() 
{
   Serial.begin(115200);
   pinMode(5,INPUT_PULLUP);
}

void loop() 
{
   if(digitalRead(5))
   {
      bits1 = 0;
      unsigned long deltaT = millis();
      while(millis()-deltaT <= 10) if(digitalRead(5)) bits1 ++;
      //Serial.println(bits1); 
      if(capture)
      {
         boolean b = 0;
         if(bits1 > 290 && bits1 < 600) b = 0;
         if(bits1 > 20 && bits1 < 290) b = 1;
         if(b) bitSet(CH,7-pos); else bitClear(CH,7-pos);
         //Serial.print(b);
         pos++;
         if(pos == 8)
         {
            Serial.print((char)CH);
            pos = 0;
            capture = false;
         }
      }
      if(bits1 > 600) 
      {
         capture = true;
         pos = 0;
      }
   }
}
