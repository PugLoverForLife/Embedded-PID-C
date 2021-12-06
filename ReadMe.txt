Instructions for implementation from the PID Tester.cpp

1. Main is only used to simulate input into the system so main() can be omitted.
2. All of the other functions, constants, and arrays are needed so please ensure you copy them all.
3. As the array, deltas, is created on the heap, please ensure you call the closePID() function when you are done using the PID to ensure memory deallocation.
4. The KP, KI, and KD constants are what control the loop but they will need tuning to your specific use case.
5. The array deltas' size is set to 10 as default. That buffer may need tweaking depending on how responsive you need the control loop to be.
6. The constant SETPOINT will need to be adjusted for your needs, please be sure to change it as necessary.