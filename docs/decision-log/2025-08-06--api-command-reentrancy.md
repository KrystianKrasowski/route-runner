# API Query/Command dispatcher reentrancy

## Subject
After splitting tasks into dispatcher and commands via event groups, the reentrancy problem occured.
API does not prevent itself from multiple calls of action methods, i. e. `apply_maneuver_by_remote`, `switch_mode_by_remotq`, etc.

Should I implement some locking mechanism?

## Big picture
* Expose only those methods from API: `query(remote_control)`, `query(line_position)`, `dispatch(action)`.
* The `query(...)` methods set action bits internally
* The `dispatch(...)` methods check bits and if set, clear and deletgate flow to private API method

### Pros
* API client uses only the product of the query outcome

### Cons
* Too much verbosity
* Overcomplication
* Reentrancy is not achived anyway - there still might be the case where two tasks race in the bit check condition.
Both might receive `true` from checking, therefore both might perform same action.

## Decision
Keep `query` method, keep action methods public as well.

## Reasoning
* **Overengineering**. This project is overengineered already :D (for learning purposes, of course).
* No profit, more stack call.
* `apply_maneuver_by_remote` isn't pure function - it depends on the `store_` state, yet it provides the same maneuver for the same store's state.
Reentrace of this method may only cause unnecesarry hardware updates, which should be delt anyway on the STM32 side
* `switch_mode_by_remote` method isn't pure function as well, yet it is idempotent, therefore it is safe to call mutliple times as well
* `tune_pid` method is the one to be careful about. Here it will be the caller responsibility not to call it more than once per query.
* If I ever wanted to synchronize, lock, wrap this in critical section, I'd prefer it to be the application layer responsibility,
as it provides FreeRTOS API that is well design for that cases: mutexes, semaphores, critical sections, etc.
* The last, but not least, as always - **YAGNI**
