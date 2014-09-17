# Hacking a Parrot AR Drone

## Contributors
*   [Dylan Kret](https://github.com/kaptainkret)
*   [Austin Odell](https://github.com/austinodell)
*   [Matthew Thorp](https://github.com/Mthorp)
*   [Andrew Walters](https://github.com/andrewfwalters)

## Overall Task

Replace autopilot firmware with a Simulink-based Rapid Prototyping toolchain for open-source autopilot design and implementation on the AR Drone.  The toolchain will include a Simulink Blockset which allows users to access the Drone's sensors and actuators, and an automatic 'build' procedure for code generation, cross-compilation and deployment on the Drone target.  The toolchain will also enable data logging and system monitoring in real time using Simulink's External Mode capability.