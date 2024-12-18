void setup() {
  pinMode(A0,INPUT); 
  pinMode(A3,INPUT); 
  pinMode(A1,INPUT);
  pinMode(A4,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  pinMode(A5,OUTPUT);
  pinMode(8,INPUT);
  analogWrite(A5,128);
}

void loop() {
  
  int dayNightLDR=analogRead(A3);
  
  Serial.print("Day LDR=");
  Serial.println(dayNightLDR);
  Serial.print("Laser LDR=");
  Serial.println(analogRead(A0));
  if(digitalRead(8)==0){
    digitalWrite(3,LOW);
    if(dayNightLDR<500){
      analogWrite(A5,128);
      analogWrite(A4,128);
      if(analogRead(A0)<850 || analogRead(A1)<850){
        a:
        digitalWrite(3,HIGH);
        analogWrite(A5,0);
        analogWrite(A4,0);
        delay(5000);
        analogWrite(A5,128);
        analogWrite(A4,128);
        delay(1);
        if((analogRead(A0)<850 || analogRead(A1)<850) && analogRead(A3)<500){
          goto a;
        }
        digitalWrite(3,LOW);
      }
    }
    else{
      analogWrite(A5,0);
      analogWrite(A4,0);
    }
  }
  else{
    analogWrite(A5,0);
    analogWrite(A4,0);
    digitalWrite(3,HIGH);
  }
}
