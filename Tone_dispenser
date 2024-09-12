### 초음파 센서를 활용한 음 디스펜서

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소와 LCD의 행, 열 개수에 맞게 초기화

const int trigPins[] = {7, 9, 11, 13, 23, 25, 27};
const int echoPins[] = {6, 8, 10, 12, 22, 24, 26};
const int buzzerPin = 5;

// 계이름 주파수 정의 (도, 레, 미, 파, 솔, 라, 시)
const int noteFrequencies[] = {261, 294, 329, 349, 392, 440, 494};

// RGB LED 핀 (빨강, 초록, 파랑)
const int RLED = 2;
const int GLED = 3;
const int BLED = 4;

// 버튼 핀
const int buttonUpPin = 30;
const int buttonDownPin = 31;

// 거리 측정을 위한 변수
long durations[7];
int distances[7];

// 옥타브 조정 변수
int octave = 0; // 0 = 기본 옥타브, 1 = 한 옥타브 위, -1 = 한 옥타브 아래, 등.

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  pinMode(buzzerPin, OUTPUT); // 부저 핀 출력으로 설정
  pinMode(buttonUpPin, INPUT_PULLUP); // 버튼 핀 입력으로 설정 및 풀업 저항 사용
  pinMode(buttonDownPin, INPUT_PULLUP); // 두 번째 버튼 핀 입력으로 설정 및 풀업 저항 사용

  // 초음파 센서 핀 모드 설정
  for (int i = 0; i < 7; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  // RGB LED 핀 모드 설정
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  // I2C LCD 초기화
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Octave: ");
}

void loop() {
  // 버튼 처리 부분
  if (digitalRead(buttonUpPin) == LOW) {
    delay(50); // 디바운스 처리
    if (digitalRead(buttonUpPin) == LOW) {
      octave++; // 옥타브 증가
      if (octave > 3) { // 최대 4 옥타브로 제한
        octave = 3;
      }
      while (digitalRead(buttonUpPin) == LOW); // 버튼이 눌린 상태가 끝날 때까지 대기
    }
  }
  
  if (digitalRead(buttonDownPin) == LOW) {
    delay(50); // 디바운스 처리
    if (digitalRead(buttonDownPin) == LOW) {
      octave--; // 옥타브 감소
      if (octave < -3) { // 최소 1 옥타브로 제한
        octave = -3;
      }
      while (digitalRead(buttonDownPin) == LOW); // 버튼이 눌린 상태가 끝날 때까지 대기
    }
  }

  for (int i = 0; i < 7; i++) {
    // Trig 핀을 LOW로 설정
    digitalWrite(trigPins[i], LOW); 
    delayMicroseconds(2);
    
    // Trig 핀을 HIGH로 설정, 10 마이크로초 후에 다시 LOW로 설정
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    
    // Echo 핀의 HIGH 상태가 유지된 시간(마이크로초 단위) 측정
    durations[i] = pulseIn(echoPins[i], HIGH);
    
    // 거리를 계산 (소리의 속도는 340m/s)
    distances[i] = durations[i] * 0.034 / 2;
  }

  // 옥타브 상태를 출력
  lcd.setCursor(8, 0); // 옥타브 상태 출력 위치
  lcd.print("    "); // 이전 출력 지우기
  lcd.setCursor(8, 0); // 옥타브 상태 출력 위치 재설정

  if (octave > 0) {
    for (int i = 0; i < octave; i++) {
      lcd.print("+");
    }
  } else if (octave < 0) {
    for (int i = 0; i < -octave; i++) {
      lcd.print("-");
    }
  } else {
    lcd.print("0"); // 기본 옥타브는 0으로 표시
  }

  // 측정된 거리와 음 출력
  int noteIndex = -1;
  for (int i = 0; i < 7; i++) {
    Serial.print("Distance ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distances[i]);
    Serial.println(" cm");

    // 일정 거리 이내에 물체가 감지되면 음 출력 및 RGB LED 색상 변경
    if (distances[i] < 5) { // 5cm 이내에 물체가 있으면
      setColor(i);  // 해당 음에 맞는 색상 설정
      int frequency = noteFrequencies[i];
      frequency = frequency * pow(2, octave); // 옥타브 조정
      tone(buzzerPin, frequency);  // 부저 음 켜기
      delay(500); // 0.5초 동안 음을 출력
      noTone(buzzerPin);  // 부저 음 끄기 
      turnOffLED();  // RGB LED 끄기
      noteIndex = i;
    }
    delay(10);
  }

  // 출력된 음을 아래줄에 표시
  lcd.setCursor(0, 1); // 아래줄로 이동
  lcd.print("Note: ");
  lcd.print("     "); // 이전 출력 지우기
  // 출력된 음 표시
  if (noteIndex != -1) { // 유효한 음인 경우에만 출력
    lcd.setCursor(6, 1);
    switch (noteIndex) {
      case 0:
        lcd.print("C");
        break;
      case 1:
        lcd.print("D");
        break;
      case 2:
        lcd.print("E");
        break;
      case 3:
        lcd.print("F");
        break;
      case 4:
        lcd.print("G");
        break;
      case 5:
        lcd.print("A");
        break;
      case 6:
        lcd.print("B");
        break;
    }
    lcd.print(octave); // 옥타브 표시
  }
  delay(10); // 10ms 대기
}

void setColor(int index) {
  switch(index) {
    case 0: // 빨강 (도)
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, HIGH);
      break;
    case 1: // 주황 (레)
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, 210);
      digitalWrite(BLED, HIGH);
      break;
    case 2: // 노랑 (미)
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
      break;
    case 3: // 초록 (파)
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
      break;
    case 4: // 파랑 (솔)
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, 100);
      digitalWrite(BLED, LOW);
      break;
    case 5: // 남색 (라)
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, 128);
      break;
    case 6: // 보라 (시)
      digitalWrite(RLED, 128);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, 128);
      break;

   void turnOffLED() {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
    }

