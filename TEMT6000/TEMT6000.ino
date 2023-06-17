int temtPin = A0;
int light_value;
void setup() {
  Serial.begin(9600);
  pinMode(temtPin, INPUT); //data pin for ambientlight sensor
  pinMode(13, OUTPUT);
}

void loop() {
  int light_value = analogRead(temtPin);
  float volts = analogRead(A0) * 5.0 / 1024.0;   // 將5V電壓分成 1024等分
  float amps = volts / 10000.0;      // 電流=電壓/電阻(10K歐姆)
  float microamps = amps * 1000000;  //得到毫安培
  float lux = microamps * 2.0;       // 乘以2，得到流明

  Serial.print ("Raw ADC data: ");
  Serial.print (light_value);
  Serial.print ("  Volts: ");
  Serial.print (volts);
  Serial.print ("  Lux: ");
  Serial.println (lux);  
  delay(500);
  if (light_value > 1000) {  //感測值超過1000時，亮Arduino板上的LED燈
    digitalWrite(13, HIGH);
  }
  else {digitalWrite(13,LOW);}
}