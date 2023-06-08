#define sync_pin D3 //power button repurposed for sync button (pin 5 on the module)
#define data_pin D2 //data line (pin 6 on the module)
#define clock_pin D1 //clock line (pin 7 on module) 

int start_cmd[10] = {0,0,0,0,0,1,0,0,1,0}; //Start Module (Needed for the sync led animation)
int power_cmd[10] = {0,0,1,0,0,0,0,1,0,1}; //Makes the startup animation on the ring of light.

int sync_cmd[11] = {0,0,0,0,0,0,0,1,0,0,1}; //Initiates the sync process.
volatile boolean sync_enable = 0;

void sendData11(int cmd_do[]) {

  pinMode(data_pin, OUTPUT);
  digitalWrite(data_pin, LOW);    //start sending data.
  int prev = 1;
  for(int i = 0; i < 11; i++){

    while (prev == digitalRead(clock_pin)){} //detects change in clock
    prev = digitalRead(clock_pin);
      // should be after downward edge of clock, so send bit of data now
    delayMicroseconds(1000);
    digitalWrite(data_pin, cmd_do[i]);

    while (prev == digitalRead(clock_pin)){} //detects upward edge of clock
    prev = digitalRead(clock_pin);
  }
  digitalWrite(data_pin, HIGH);
  pinMode(data_pin, INPUT);
}

void sendData10(int cmd_do[]) {
  pinMode(data_pin, OUTPUT);
  digitalWrite(data_pin, LOW);    //start sending data.
  int prev = 1;
  for(int i = 0; i < 10; i++){

    while (prev == digitalRead(clock_pin)){} //detects change in clock
    prev = digitalRead(clock_pin);
      // should be after downward edge of clock, so send bit of data now
    delayMicroseconds(1000);
    digitalWrite(data_pin, cmd_do[i]);

    while (prev == digitalRead(clock_pin)){} //detects upward edge of clock
    prev = digitalRead(clock_pin);
  }
  digitalWrite(data_pin, HIGH);
  pinMode(data_pin, INPUT);
}

void initLEDs(){
  sendData10(start_cmd);
  delay(50);
  sendData10(power_cmd);
  delay(50);
}

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing...");
  pinMode(sync_pin, INPUT);
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, INPUT);
  delay(1000);
  initLEDs();
  Serial.println("OK");
}

void loop() {
  delay(100);
  sync_enable = digitalRead(sync_pin);
  if(sync_enable==0) {
    sync_enable = 1;
    Serial.println("Synchronizing...");
    sendData11(sync_cmd);
    delay(3000);
  }
}
