void setPhase(unsigned char ph);
void advancePhase(char dir);

const unsigned char AHPin = 12;
const unsigned char ALPin = 6;
const unsigned char BHPin = 11;
const unsigned char BLPin = 5;
const unsigned char CHPin = 10;
const unsigned char CLPin = 4;
const unsigned char delayPin = A0;

char currentPhase = 0;
char motorDirection = 1;
unsigned long previousDelay = 0;

const unsigned char phaseStates[6]{
  B011000,
  B010010,
  B000110,
  B100100,
  B100001,
  B001001
};

void setPhase(unsigned char ph){
  Serial.begin(115200);
  unsigned char phase = phaseStates[ph];
  digitalWrite(AHPin, (phase & B100000) >> 5);
  digitalWrite(ALPin, (phase & B010000) >> 4);
  digitalWrite(BHPin, (phase & B001000) >> 3);
  digitalWrite(BLPin, (phase & B000100) >> 2);
  digitalWrite(CHPin, (phase & B000010) >> 1);
  digitalWrite(CLPin, phase & B000001);
}

void advancePhase(char dir){
  currentPhase += dir;
  if(currentPhase > 5){
    currentPhase = 0;
  }else if(currentPhase < 0){
    currentPhase = 5;
  }
}

void setup(){
  pinMode(AHPin, OUTPUT);
  pinMode(ALPin, OUTPUT);
  pinMode(BHPin, OUTPUT);
  pinMode(BLPin, OUTPUT);
  pinMode(CHPin, OUTPUT);
  pinMode(CLPin, OUTPUT);
  pinMode(delayPin, INPUT);
}

void loop(){
  long delay = map(analogRead(delayPin), 0, 1024, 0, 100000);
    if(micros() - previousDelay <= delay) { return; }
    previousDelay += delay;

    advancePhase(motorDirection);
    setPhase(currentPhase);
}
