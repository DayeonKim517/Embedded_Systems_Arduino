### 가변저항으로 모터 속도 조절
 
const int EN = 9;
const int MC1 = 3;
const int MC2 = 2;
const int POT = 0;

int val = 0;
int velocity = 0;

void setup() 
{
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake();
}

void loop(){
  val = analogRead(POT);

  if (val>562){
    velocity = map(val, 563, 1023, 0, 255);
    forward(velocity);
  }
  else if (val < 462){
    velocity = map(val, 461, 0, 0, 255);
    reverse(velocity);
  }
  else{
    brake();
  }
}

void forward(int rate){ 
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, rate);
}

void reverse (int rate){ 
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  digitalWrite(EN, rate);
}

void brake(){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, HIGH);
}
