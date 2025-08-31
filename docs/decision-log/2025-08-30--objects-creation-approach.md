# How to create objects in embedded C++

## Subject
Should objects be created by Meyers' singleton or exposed by extern global?

## Big picture
* From the beginning of C++ refactor I took Meyers' singleton appraoch:
    * None of the objects in the application is created dynamically
    * All of the objects live as long as application itself
    * Almost all of the objects are single instance.

### Pros
* The same contract for all object creation, while at the same time the creation logic may differ. 
For example, the `L293` object that represents motor driver channel is on of the cases, when there are more than one instance.
The ETL object pool is used for such cases, but this solution isn't constrained to it. 
It can perform creation by local `static`, object pool, memory arena, freerfos heap, etc. At the same time only the static `of` method is exposed.

### Cons
* Constructor duplication - not as much a problem, but some inconveniance
* Threadsafe static - adds 4 bytes for each object despite the `-fno-threadsafe-statics` compiler flag
* Instatiation in main function prolongs initialization time - not noticable

## Alternative - extern global
* Objects can be statically created as their number and dependencies are known up-front

### Pros
* Less indirection
* Less memory usage

### Cons
* More boilerplate for initialization
* All application module would need to be refactored
* Extern mutable global is exposed - not huge issue - in the matter of fact the same applies with Meyers' singleton approach. 
It is visible only for modules that need this.
* Opens the door to manipulate the peripherals before initialization (for example logic in constructor - yes, bad practice, but nothing prevents from that besides common sense)

## Decision
Device tree is refactored to exposed global `g_device_tree`. Application sticks to Meyers' singleton

## Reasoning
* Refactoring devices layer is easy, saves noticable amount of memory usage, makes code much cleaner.
About peripherals manipulation in constructor - I believe in my common sense. And seriously - this is one person project for learning. Even if this is a mistake - good.
* Changing the whole application module would take quite amount of effort and time.
Since this is a place where freeRTOS API is called it is safer to call it at runtime.
Meyers' singleton forces lazy initialization which fits this requirement perfectly.
On top of that, with freeRTOS tasks, event groups, mutexes wrappers there is a bit of creation logic which currently used factory object is natural place to handle it.
