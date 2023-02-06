const int H_MODE = 8; //bits
int HAPTIC_BEATS[H_MODE] = {2,3,4,5,6,7,8,9};
int H_STATE[H_MODE] = {0,0,0,0,0,0,0,0};
int TICK_TIME = 1500;
int BEAT_TIME = 1000;
int CONNTROL_BIT = 0;
bool is_payloaded = false;

void setup () {
   Serial.begin(9600);
   for(int i = 0; i < H_MODE; ++i)
     pinMode(HAPTIC_BEATS[i], OUTPUT);
}

void set_random_bits() {
  randomSeed(millis());
  for(int i = 0; i < H_MODE; ++i)
    H_STATE[i] = random(0,2);
}

void set_control_bits() {
  for(int i = 0; i < H_MODE; ++i)
    H_STATE[i] = CONNTROL_BIT & (1 << i);
}

void clear_control_beats() {
  for(int i = 0; i < H_MODE; ++i)
    H_STATE[i] = 0; 
}

void read_control(){
  //if(Serial.available( ) > 0) {
    CONNTROL_BIT = Serial.readString().toInt();
  if(true) {
    //CONNTROL_BIT = Serial.read();
    //CONNTROL_BIT = Serial.parseInt();
    CONNTROL_BIT = 255;
    //CONNTROL_BIT = random(0,256);
    is_payloaded = true;
  } else {
    is_payloaded = false;
  }
}

void loop () { 
  read_control();
  if(is_payloaded) {
    //set_random_bits();
    set_control_bits();
    for(int i = 0; i < H_MODE; ++i){
      if(H_STATE[i] != 0)
        digitalWrite(HAPTIC_BEATS[i], HIGH);
    }
    delay(BEAT_TIME);
    for(int i = 0; i < H_MODE; ++i)
      digitalWrite(HAPTIC_BEATS[i], LOW);
    delay(TICK_TIME - BEAT_TIME);

    clear_control_beats();
  }
}
