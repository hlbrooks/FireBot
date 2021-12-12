/** @file task_Thermal_Sensor.h
 *  This task continuously uses the thermal camera to scan for temperatures
 *  within the view of the lense when a fire is not being extinguished. 
 *  If a temperature above 140 degrees Fahrenheit is measured, an interrupt 
 *  is generated which raises the value of a share from 0 to 1, thus allowing
 *  the other tasks to take the appropriate actions.
 * 
 *  @author Hunter Brooks & William Dorosk
 *  @date   20 Nov 2021 Created file
 */

void task_Thermal_Sensor (void* p_params);