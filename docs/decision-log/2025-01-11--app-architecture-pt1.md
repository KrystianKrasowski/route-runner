# Application architecture

What application architecture to choose from:
* RTOS
* Superloop

## Superloop

Pros:
* Simple, verbose and easy to start with
* Can introduce some of the architecture patterns like sequencer, finite state machine or serial task execution
* No/limited concurrency

Cons:
* No real time execution - for example when PID controller starts its computarion and the stop command appears, the PID algorithm will end its work first before stop command would execute
* Probably not industry way to go

## RTOS

Pros:
* Professional approach
* Industry standard
* Real time behaviour - for example stop command could suspend PID task execution

Cons:
* Steep learning curve
* Complex integration with non-HAL approach (or maybe not?)
* Concurrency

## Decision
To kickstart the project the **superloop** with **task sequencer** approach would be applied, along with custom, simple **messaging queue**

* It will allow smooth transition to RTOS
* The complexity at the start of the project will be decreased and the work can focus on PID control, accuracy of the device, etc
* Device functionality will not be as complex at first, that late response to STOP command would not be an issue.