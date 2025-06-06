### 모터 회전 속도에 따른 LED 색상 변화 확인하기

const int EN = 9;  // 모터 제어를 위한 PWM 핀
const int MC1 = 3;  // 모터 회전 방향 제어 핀 1
const int MC2 = 2;  // 모터 회전 방향 제어 핀 2
const int POT = A0;  // 가변 저항 입력 핀
const int SWITCH = 4;  // 방향 전환을 위한 스위치 핀

// LED 핀 정의
const int GREEN_LED = 5;  // 초록색 LED 핀
const int YELLOW_LED = 6;  // 노란색 LED 핀
const int RED_LED = 7;  // 빨간색 LED 핀

int val = 0;  // 가변 저항 값 저장 변수
int velocity = 0;  // 모터 속도 저장 변수
bool direction = true;  // 모터 회전 방향 (true: 전진, false: 후진)
bool lastSwitchState = LOW; // 이전 스위치 상태 저장 변수

void setup() 
{
  pinMode(EN, OUTPUT);  // PWM 핀을 출력으로 설정
  pinMode(MC1, OUTPUT);  // 모터 방향 제어 핀 1을 출력으로 설정
  pinMode(MC2, OUTPUT);  // 모터 방향 제어 핀 2를 출력으로 설정
  pinMode(SWITCH, INPUT_PULLUP);  // 스위치 핀을 입력으로 설정, 풀업 저항 사용

  // LED 핀을 출력으로 설정
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  // 시리얼 통신 시작
  Serial.begin(9600);

  brake();  // 초기에는 모터를 정지 상태로 설정
}

void loop(){
  // 가변 저항 읽기
  val = analogRead(POT);

  // 시리얼 모니터에 가변 저항 값 출력
  Serial.print("Potentiometer Value: ");
  Serial.println(val);

  // LED 상태 제어 (속도에 따라 LED 색상 변화)
  if (velocity <= 100) {
    digitalWrite(GREEN_LED, HIGH);   // 속도가 낮으면 초록색 LED 켜기
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (velocity > 100 && velocity <= 200) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);  // 중간 속도에서는 노란색 LED 켜기
    digitalWrite(RED_LED, LOW);
  }
  else if (velocity > 200) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);     // 속도가 높으면 빨간색 LED 켜기
  }

  // 스위치 상태 읽기
  bool currentSwitchState = digitalRead(SWITCH);

  // 스위치가 눌릴 때마다 모터 회전 방향 변경
  if (currentSwitchState == LOW && lastSwitchState == HIGH) {
    direction = !direction;  // 방향 반전
  }

  lastSwitchState = currentSwitchState;  // 스위치 상태 업데이트

  // 가변 저항 값에 따라 모터 속도 설정
  velocity = map(val, 0, 1023, 0, 255);

  if (velocity > 10) {  // 속도가 충분히 크면 모터 동작
    if (direction) {
      forward(velocity);  // 전진
    }
    else {
      reverse(velocity);  // 후진
    }
  }
  else {
    brake();  // 속도가 낮으면 모터를 정지 상태로 설정
  }
}

void forward(int rate){ 
  digitalWrite(MC1, HIGH);  // 전진 방향 설정
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);  // PWM 신호를 통해 속도 제어
}

void reverse (int rate){ 
  digitalWrite(MC1, LOW);  // 후진 방향 설정
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);  // PWM 신호를 통해 속도 제어
}

void brake(){
  digitalWrite(MC1, LOW);  // 모터 정지
  digitalWrite(MC2, LOW);
  analogWrite(EN, 0);  // PWM 신호를 0으로 설정하여 모터 정지
}
