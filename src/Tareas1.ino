/*
 * Programa básico para implementación de múltiples tareas en freeRTOS
 * utilizando un sistema embebido ESP32 Devkit V1 DOIT
 * Autor: Sangiovanni, Dante
 * Fecha: 09/09/2021
 * Modoficado por: -
 * Fecha: -
*/

///////////////////////////////////////////// VSCODE //////////////////////////////////////////////////////
#include "Arduino.h"

/////////////////////////////////////////// DEFINICIONES //////////////////////////////////////////////////////
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

#define POTE 26
#define LED  25

///////////////////////////////////// PROTOTIPOS DE LAS TAREAS ////////////////////////////////////////////////
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void Tarea1( void *pvParameters );
void Tarea2( void *pvParameters );
void TareaLedExterno( void *pvParameters );

/////////////////////////////////////////// CONFIGURACIONES //////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200);
  delay(2500); 
  
  Serial.println("Iniciando sistema operativo en tiempo real..");
  Serial.println("Creando tareas..");
  delay(5000); 
  
  xTaskCreatePinnedToCore(TaskBlink,"TaskBlink",1024,NULL,2,NULL,ARDUINO_RUNNING_CORE);
  
  xTaskCreatePinnedToCore(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  1024   // Stack size
    ,  NULL
    ,  1      // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);
  
  xTaskCreatePinnedToCore(
    Tarea1
    ,  "Tarea1"   // A name just for humans
    ,  1024       // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3          // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    Tarea2
    ,  "Tarea2"   // A name just for humans
    ,  1024       // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3          // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TareaLedExterno
    ,  "TareaLedExterno"    // A name just for humans
    ,  1024                 // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3                    // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

///////////////////////////////////// BUCLE (SIN USO EN RTOS) ///////////////////////////////////////////////////
void loop()
{
  // Empty. Things are done in Tasks.
  //Serial.println("---> Soy el loop !");
}

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

    Serial.print("---> Pote: ");
    Serial.println(sensorValue);
    vTaskDelay(100);
  }
}
///////////////////////////////////// FIN DEL PROGRAMA ///////////////////////////////////////////////////
