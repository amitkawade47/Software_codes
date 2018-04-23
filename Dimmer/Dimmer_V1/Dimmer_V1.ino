int AC_LOAD = 3;  // Output to Opto Triac pin
int dimming = 128;  // Dimming level (0-128)  0 = ON, 128 = OFF

void setup()
{
  Serial.begin(9600);
  pinMode(AC_LOAD, OUTPUT);// Set AC Load pin as output
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  attachInterrupt(digitalPinToInterrupt(2), zero_crosss_int, LOW);  // Choose the zero cross interrupt # from the table above
}

//the interrupt function must take no parameters and return nothing
void zero_crosss_int()  //function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation : 1 full 50Hz wave =1/50=20ms 
  // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) 
  // For 60Hz => 8.33ms (10.000/120)
  // 10ms=10000us
  // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65
  //digitalWrite(13,HIGH);
  //delay(200);
  //digitalWrite(13,LOW);
 // Serial.print("Time : ");
  //Serial.println(millis());
  int pulsTime = 200;
  int dimtime = 7000;//(75*dimming); // For 60Hz =>65    
  
  delayMicroseconds(dimtime); // Wait till firing the TRIAC
  
  digitalWrite(AC_LOAD, HIGH);   // Fire the TRIAC
  delayMicroseconds(pulsTime);      // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(AC_LOAD, LOW); // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
  
  //int delayTime = 10-(dimtime+pulsTime);
  
 /* delay(dimtime); // Wait till firing the TRIAC
  
  digitalWrite(AC_LOAD, HIGH);   // Fire the TRIAC
  delay(pulsTime);      // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(AC_LOAD, LOW); // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
  */
}

void zero_int()
{
  digitalWrite(AC_LOAD,HIGH);
  delay(100);
  digitalWrite(AC_LOAD,LOW);
  delay(500);
}


void loop()  {
  digitalWrite(AC_LOAD,HIGH);
  //delay(1);
  delayMicroseconds(100);
  digitalWrite(AC_LOAD,LOW);
  //delay(2);
  delayMicroseconds(900);
  //dimming= 64;
  //for (int i=5; i <= 128; i++){
  //dimming=i;
  //delay(10);
  // }
}

