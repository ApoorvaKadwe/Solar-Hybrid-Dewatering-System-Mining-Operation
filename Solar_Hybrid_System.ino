INITIAL UPLOAD OF SYSTEM LOGIC
#define BLYNK_TEMPLATE_ID "Your_Blynk_Template_id"
#define BLYNK_TEMPLATE_NAME "solar power dewatering"
#define BLYNK_AUTH_TOKEN "You_Blynk_Token"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define TRIG_PIN 5
#define ECHO_PIN 18
#define RELAY_PIN 2
#define LED_PIN 4
#define BUZZER_PIN 15
#define LDR_PIN 34

BlynkTimer timer;

void sendData() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  int lightValue = analogRead(LDR_PIN);

  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V4, lightValue);

  Serial.println("-----------------------"); 
  
  if (distance >= 250) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    
    Serial.print("STATUS: SAFE | DISTANCE: "); Serial.print(distance); Serial.println(" cm");
    Blynk.virtualWrite(V2, "IDLE");
    Blynk.virtualWrite(V5, "✅ LEVEL SAFE");
  } 
  else if (distance < 250 && distance >= 50) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);

    Serial.print("STATUS: PUMPING | DIST: "); Serial.print(distance); Serial.println(" cm");
    if (lightValue > 2000) {
       Blynk.virtualWrite(V2, "☀️ SOLAR POWER");
    } else {
       Blynk.virtualWrite(V2, "⛽ DIESEL BACKUP");
    }
    Blynk.virtualWrite(V5, "💧 PUMPING...");
  }
  else if (distance < 50 && distance > 0) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH); 
    tone(BUZZER_PIN, 1000); 

    Serial.println("!!! ALERT: EMERGENCY WATER LEVEL !!!");
    Serial.print("CURRENT DISTANCE: "); Serial.println(distance);
    
    Blynk.virtualWrite(V2, "⚡ MAX POWER");
    Blynk.virtualWrite(V5, "⚠️ EMERGENCY: FLOOD");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
