### LED 4개의 ON / OFF 실험

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;   //LED를 연결한 핀의 상태 지정

Void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}    //LED1번부터 2번, 3번 차례로 1초씩 점등

void loop()
{
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED3, HIGH);
  delay(1000);
  digitalWrite(LED4, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
  digitalWrite(LED2, LOW);
  delay(1000);
  digitalWrite(LED3, LOW);
  delay(1000);
  digitalWrite(LED4, LOW);
  delay(1000);
}
