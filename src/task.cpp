#include "Arduino.h"
#include "task.h"

///////////////////////////////////// DEFINICIÓN DE LAS TAREAS ///////////////////////////////////////////////////
void Tarea1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  Serial.println("Iniciando la tarea 1");

  for (;;) 
  {
    Serial.println("--->                            Soy la tarea 1");
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}

void Tarea2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  Serial.println("Iniciando la tarea 2");

  for (;;) 
  {
    Serial.println("--->                                                    Soy la tarea 2");
    vTaskDelay(1500);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}

void TareaLedExterno(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(LED, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(250);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(250);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {

    int sensorValue = analogRead(POTE);

    Serial.print("---> Potenciometro: ");
    Serial.println(sensorValue);
    vTaskDelay(100);
  }
}