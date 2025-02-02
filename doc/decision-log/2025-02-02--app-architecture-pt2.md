# Application architecture

What application architecture to choose from:
* Layer
* Hexagonal

## Layer

Pros:
* Simple, strightforward
* Lighter binary

Cons:
* Not modular
* Component change implicates logic code refactor

## Hexagonal

Pros:
* Modular, extensible
* Scalable
* Unit test friendly

Cons:
* More complex
* Larger binary, maybe more RAM required

## Decision
Hexagonal. 

### Explanation
Unit tests are important to me as well as application to be extensible and scalable without a need to refactor logic. 

Examlpe 1. 
I can replace a motion adapter to the one that only displays some output to the serial console, just by editing a CMakeLists file in adapters package, without **any need to modify the code**.

Example 2.
I can develop an infrared pilot driver to remote control the device and switch between the controllers between IR and dualshock2, again, without any current code modification.