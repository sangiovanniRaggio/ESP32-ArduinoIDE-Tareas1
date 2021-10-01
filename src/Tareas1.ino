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

#include "config.h"
#include "task.h"

/////////////////////////////////////////// CONFIGURACIONES //////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  delay(2500);

  Serial.println("Iniciando sistema operativo en tiempo real..");
  Serial.println("Creando tareas..");
  delay(5000);

  xTaskCreatePinnedToCore(TaskBlink, "TaskBlink", 1024, NULL, 2, NULL, ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
      TaskAnalogRead, "AnalogRead", 1024 // Stack size
      ,
      NULL, 1 // Priority
      ,
      NULL, ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
      Tarea1, "Tarea1" // A name just for humans
      ,
      1024 // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL, ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
      Tarea2, "Tarea2" // A name just for humans
      ,
      1024 // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL, ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
      TareaLedExterno, "TareaLedExterno" // A name just for humans
      ,
      1024 // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL, ARDUINO_RUNNING_CORE);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

///////////////////////////////////// BUCLE (SIN USO EN RTOS) ///////////////////////////////////////////////////
void loop()
{
  // Empty. Things are done in Tasks.
  Serial.println("---> Soy el loop !");
}

///////////////////////////////////// FIN DEL PROGRAMA ///////////////////////////////////////////////////
