/*
  Arduino Engineering Kit Hall Sensor Test
  This sketch demonstrates some APIs exposed by the MKR Motor Shield library.
  For the complete list, visit the reference page on https://www.arduino.cc/en/Reference/MKRMotorShield
  This example code is in the public domain.
*/

#include <MKRMotorCarrier.h>

//#define INTERRUPT_PIN A6 // IN1
//#define INTERRUPT_PIN A5 // IN3
//#define INTERRUPT_PIN A1 // IN2
#define INTERRUPT_PIN A2 // IN4

int batteryVoltage;
int hallCount;

void setup() {

  Serial.begin(115200);
  while (!Serial);

  // Start communicationg with the motor shield
  if (controller.begin()) {
    Serial.print("MKR Motor Shield connected, firmware version ");
    Serial.println(controller.getFWVersion());
  } else {
    Serial.println("Couldn't connect! Is the red led blinking? You may need to update the firmware with FWUpdater sketch");
    while (1);
  }

  // Reboot the motor controller; brings every value back to default
  Serial.println("reboot");
  controller.reboot();

  delay(500);

  //Interrupts
  hallCount = 0;
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(INTERRUPT_PIN, Isr, RISING);

   Serial.println("System ready: Place the magnet close the the hall sensor...");
}

volatile bool irqFlag = false;

void Isr() {
  irqFlag = true;
}

void loop() {

  //Battery
  float batteryVoltage = (float)battery.getConverted();

  if (batteryVoltage < 10) {
    Serial.print("Battery voltage: ");
    Serial.print(batteryVoltage);
    Serial.println(" ");
    Serial.println("WARNING: LOW BATTERY");
    Serial.println("ALL SYSTEMS DOWN");
    M1.setDuty(0);
    M2.setDuty(0);
    M3.setDuty(0);
    M4.setDuty(0);    
    while (batteryVoltage < 11) {
      batteryVoltage = (float)battery.getConverted();
    }
  }

  if (irqFlag == true) {
    hallCount++;
    Serial.print("Hall count: ");
    Serial.println(hallCount);
    irqFlag = false;
  }
  //Ping the samd11
  controller.ping();
  delay(200);
}
