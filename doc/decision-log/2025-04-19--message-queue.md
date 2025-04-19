# Message queue

## Subject
Is message queue for communication between the application layer and infrastructure layer good solution?

### Pros
* Good decoupling. Drivers does not know anything about applications and vice versa
* Backlog - from the mq perspective this is good and expected

### Cons
* May be huge memory requirement
* Backlog - from the line follower perspective we actually want to get rid of stale data
* Additional layer in application architecture

## Decision
No message queue is needed. The application task will read the data from drivers by adapters.

## Reasoning
* **YAGNI.** Although it gives good decoupling mechanism between the application and drivers layers, actually we do not need that. Application is an orchiestrator thus it should see every layer (or interface to it)
* **Huge memory usage.** Current implementation of mq has nice generic messages with byte-array payload. But this comes with a cost. Since we operate in embedded environment we want to use static arrays. And the payload needs to use as little memory as the biggest possible payload. Let's take a line sensor data. Now, the sensor itself averages the data in ISR which is not a good idea (ISR should be small and quick). That means that after refactor the sensor would put and array of **40 16bit integers**, meaning 80 bytes of memory. Plus `memcpy` to message payload, plus `memcpy` from message payload, plus conversion to `linebot_coords_t`. Morover, we have 3 mq topisc with 5 messages capacity. That gives us 3 * 5 * 80 **1,2kB just for message queue**. And thats insane, due to the fact that this solves a problems that we don't actually have. See below.
* **Backlog.** Line following robot should not handle the backlog for applying the motion. It should use only fresh data. As for now the ADC conversion is taking place once/1ms, thus the main loop has 1ms to perform: message conversion, mode update, PID computation, drive DC motors. 1ms is more than enough for this operations (**NEED BENCHMARK!**). It will never come to put more than one message on the queue topic. And if for some reason it did, the robot should not handle previous line coordinates as it is in constant motion and line position is changing dynamically. We actually want to drop stale data.
* **KISS.** The drivers will provide a function to get the newes data (some double buffering with bool flag). The function would return by out argument the value and return code to indicate that data is fresh or stale. The function's clinet - by proxy the application - will then decide to perform its task or not. The adapter proxy would perform averaging (line sensor case), etc and return the domain type directly. No `memcpy`s, no messages, not mq topics.