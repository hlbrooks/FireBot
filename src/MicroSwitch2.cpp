/** @file MicroSwitch2.cpp
 *  This task is the first of two micro limit switch tasks in the program.
 *  This switch is pressed when the motor has fully translated back to the
 *  position it began before the fire was extinguished. This switch is 
 *  designed to change the value of the shared state variable to 3 for the
 *  FSM within task_Extinguish. This will halt the motor's rotation once 
 *  it is back to its reset position
 * 
 *  @author  Hunter Brooks & William Dorosk
 *  @date    20 Nov 2021 File Created
 *  @date    2  Dec 2021 Finalized file
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif

#include "taskshare.h"               // Header for inter-task shared data
#include "taskqueue.h"               // Header for inter-task data queues  
#include "shares.h"                  // Header for shares
#include "MicroSwitch2.h"            // Header for MicroSwitch2 task module

/// Define the input pin from the Nucleo that will integrate with the micro limit switch
//  This pin will be read whenever the extinguisher motor is rotating away from the extinguisher lever
#define IN1 PB6 // The input pin that reads as a digital zero when the switch is pressed

 /** @brief   This is the task function that controls the first micro limit switch
  *  @details This task is the first of two micro limit switch tasks in the program.
  *           This switch is pressed when the motor has fully translated back to the
  *           position it began before the fire was extinguished. This switch is 
  *           designed to change the value of the shared state variable to 3 for the
  *           FSM within task_Extinguish. This will halt the motor's rotation once 
  *           it is back to its reset position
  *  @param   p_params A pointer to function parameters which we don't use.
  */

void MicroSwitch2 (void* p_params)
{
    (void)p_params;                             // Shuts up a compiler warning

    /// The number of RTOS ticks between runs of the MicroSwitch2 task
    const TickType_t MICROSWITCH2_PERIOD = 100;

    // Initialise the xLastWakeTime variable with the current time.
    // It will be used to run the task at precise intervals
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // Set the pin to behave as an input pin tied to pullup resistor
    pinMode(IN1, INPUT_PULLUP);

    for (;;)
    {
        // If the extinguisher motor is rotating away from the extinguisher lever, 
        //     the input pin tied to the micro limit switch will be read every
        //     time this task is run, else the task exits
        // If the input pin is read and returns a digital zero, the task_extinguisher
        //     state variable share is set to three
 
        if (state_extinguish.get() == 2)  //share
        {
            uint8_t current_value = digitalRead (IN1);
            if (current_value == 0)
            {
                current_value = 1;
                state_extinguish.put(3);  //share
            }
            else
            {
            }
        }
        else
        {
        }

        // This type of delay waits until it has been the given number of RTOS
        // ticks since the task previously began running. This prevents timing
        // inaccuracy due to not accounting for how long the task took to run
        vTaskDelayUntil (&xLastWakeTime, MICROSWITCH2_PERIOD);
    }
}
