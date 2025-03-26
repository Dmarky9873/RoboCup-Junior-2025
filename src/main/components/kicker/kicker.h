//Kyle Andersen 2025
class Kicker {
public:
  bool kickTriggered = false;
  int kickPin = 3;
  float kickDelay = 100;
  Kicker(int pin, float delay)
    : kickPin(pin), kickDelay(delay) {}
  void init() {
    pinMode(kickPin, OUTPUT);
  }
  void performKick() {
    digitalWrite(kickPin, HIGH);
    delay(100);
    digitalWrite(kickPin, LOW);
    delay(100);
  }
  void triggerKick() {
    kickTriggered = true;
  }
}