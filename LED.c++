### LED 1개의 ON / OFF 실험 

const int LED = 9;

void setup()  // LED 핀을 9번 핀으로 정의
{
  pinMode( LED, OUTPUT );  // LED 핀을 출력으로 설정
}

void loop()
{
  for(int i=100; i<=1000; i=i+100)
  {
     digitalWrite( LED, HIGH );  // LED 켜기
     delay(i)
     digitalWrite( LED, LOW );   // LED 끄기
     delay(i);
  }
}
