### 가변저항 읽기

const int POT = 0;  // POT 핀을 아날로그 핀 0으로 정의

int val = 0;  // 변수 val을 선언하고 0으로 초기화

void setup() {
  Serial.begin(9600);  // 시리얼 통신을 9600 보율로 시작
}

void loop() {
  val = analogRead(POT);  // POT 핀으로부터 아날로그 입력을 읽고 val 변수에 저장
  Serial.println(val);  // val 값을 시리얼 모니터에 출력
  delay(500);  // 500ms 지연
}
