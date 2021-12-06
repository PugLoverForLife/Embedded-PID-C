/*
Author: Devin Himmelheber
Date Created: 12/1/2021
Description: 
This program creates a PID control system and allows the user to test it via the main function.

KP, KI, and KD are the different control values for the PID controller and can be changed in the define section.

The PID process value buffer is called deltas and its size is controlled via the DELTA_SIZE constant.

VERBOSE is used for console print outs to debug if needed. Turning the VERBOSE constant to 'true' will allow for 
additional information to be printed to the screen.

The ClosePID function needs to be called whenever the PID is no longer needed or the program finishes to deallocate
the deltas array since it is created on the heap.
*/


#include <iostream>
#include <stdio.h>
#include <cmath>
#include <numeric>

#define VERBOSE false

// Define section
#define KP 500.0
#define KI 80.0
#define KD 200.0
#define DELTA_SIZE 10
#define SETPOINT 100

// Creates the delta buffer for the PID controller
double* deltas = new double[DELTA_SIZE];

// Prototypes
double PID_Calculation(double value);
void deltas_Update(double delta);
double calculate_p(double delta);
double calculate_i(double control_value);
double calculate_d(double control_value);

void closePID();

// Main is a tester for the PID function
int main()
{
    double input = 0;
    for (int i = 0; i < DELTA_SIZE; i++)
    {
        deltas[i] = 0;
    }

    while (input != -1.0)
    {
        printf("Please enter the value for the PID: ");
        std::cin >> input;

        if (input > -1)
        {
            if (VERBOSE == true)
            {
                for (int i = 0; i < 10; i++)
                {
                    printf("%f\n", deltas[i]);
                }
            }
            printf("%.3f\n", PID_Calculation(input));
        }
    }
    closePID();

    return 0;
}



double PID_Calculation(double value) {
    double delta = SETPOINT - value;

    deltas_Update(delta);

    return calculate_p(delta);
}

void deltas_Update(double delta) // Performs a pop and queue on the deltas array
{
    // Pop the highest indexed value out of the front of the queue and shift the rest of the queue forward
    for (int i = DELTA_SIZE - 2; i >= 0; i--)
    {
        if(VERBOSE == true)
            printf("Index %d -> index %d\n", i, i+1);
        deltas[i + 1] = deltas[i];
    }

    // Push the most recent value to the back of the queue
    deltas[0] = delta;
}

// Calculate proportional gain
double calculate_p(double delta)
{
    return calculate_i(delta * KP); // Calulates proportional gain and then passes on the control value
}

// Calculate integral gain
double calculate_i(double control_value)
{
    double sum = 0;

    for (int i = 0; i < DELTA_SIZE; i++)
    {
        sum += deltas[i];
    }
    control_value += sum * KI; // Calulates integral gain and then passes on the control value

    return calculate_d(control_value);
}

// Calculate derivative gain
double calculate_d(double control_value)
{
    control_value += (deltas[0] - deltas[1]) * KD; // Calulates derivative gain and then passes on the control value

    return control_value;
}

void closePID() // Memory clean-up to be done when the PID is no longer needed.
{
    delete[] deltas;
}