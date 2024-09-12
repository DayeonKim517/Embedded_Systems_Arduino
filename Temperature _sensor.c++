### 온도센서를 사용하여 온도 경보 만들기 

const int BLED = 9; // 파란 LED의 핀 번호
const int GLED = 10; // 녹색 LED의 핀 번호
const int RLED = 11; // 빨간 LED의 핀 번호
const int TEMP = 0; // 아날로그 온도 센서 연결 핀 번호
const int LOWER_BOUND = 139; // 온도 범위의 하한 값
const int UPPER_BOUND = 147; // 온도 범위의 상한 값
int val = 0; // 아날로그 입력 값을 저장
void setup()
{
Serial.begin(9600); // 시리얼 통신 시작 (9600 bps)
pinMode(BLED, OUTPUT); // 파란 LED 핀을 출력 모드로 설정
pinMode(GLED, OUTPUT); // 녹색 LED 핀을 출력 모드로 설정
pinMode(RLED, OUTPUT); // 빨간 LED 핀을 출력 모드로 설정
}

void loop() {
  
  val = analogRead(TEMP); // 아날로그 온도 센서 값을 읽어옵니다.

  float voltage = val * (5.0 / 1023.0);   // 섭씨 온도 계산
  float temperatureC = (voltage - 0.5) * 100.0; // 10mV/°C, 500mV offset
 
  Serial.print("sen: ");
  Serial.print(val);
  Serial.print(" Temperature (C): ");
  Serial.println(temperatureC);
  delay(500);
  
if(val < LOWER_BOUND){
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
  else if(val > UPPER_BOUND){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  }
  else {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
}
