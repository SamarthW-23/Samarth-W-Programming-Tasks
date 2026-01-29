const int IN1=3;
const int buttonPin=7;
const int delayBtnPin = 6;
bool isOn = false;
int prevButtonState = HIGH;
long prevChangeTime =0;
int StableButtonState = HIGH;
const long DebounceTime = 40;

int delayTime=200;
int delayIncrement = 200;



void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(delayBtnPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int raw = digitalRead(buttonPin);

  if(raw != prevButtonState){
    prevChangeTime = millis();
    prevButtonState = raw;
  }

  if((millis()-prevChangeTime) > DebounceTime && (raw != StableButtonState)){
    StableButtonState = raw;
    if(StableButtonState == LOW){
      isOn = !isOn;
    }
  }

  if(isOn){

    int read = digitalRead(delayBtnPin);
    if(read == LOW){
      delay(30);
      if(read == LOW){
        delayTime = delayTime + delayIncrement;
      
        if((delayTime =< 200) || (delayTime >= 1000)){
          delayIncrement = -delayIncrement;
        }

        while(digitalRead(delayBtnPin) == LOW){}
        delay(30);
      }
    }
   
    analogWrite(IN1, 80);
    delay(delayTime);
    analogWrite(IN1,0);
    delay(delayTime);
    

  }
  else{
    analogWrite(IN1, 0);
  }
}
