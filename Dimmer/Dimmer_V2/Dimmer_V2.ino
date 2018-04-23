void setup() {
  Serial.begin(115200);
  //pinMode(2,INPUT);
   pinMode(2, INPUT_PULLUP);
  pinMode(3,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), zero_cross, LOW);
  // put your setup code here, to run once:

}

void zero_cross ()
{
  Serial.println(millis());
  delay(8);
  digitalWrite(3,HIGH);
  delay(1);
  digitalWrite(3,LOW);
}

void loop() {
// put your main code here, to run repeatedly:

}
