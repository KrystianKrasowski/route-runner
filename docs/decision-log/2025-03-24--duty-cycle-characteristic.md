# Duty cycle characteristic

What characteristic to choose for duty cycle per error relation:
* linear
* polynumeral
* linear with quadratic mix

# Description
The linear characteristic - `dc(e) = abs(-2 * abs(e) + 100)` - acts proportionally to the error, but there are areas on the track where vehicle reacts to very small curves.

The polynumeral characteristic whould give smooth transitions around 100 and 0 duty cycle values meaning, that the vehicle
would correct less near small errors. However finding the polynumeral (by Lagrange's interpolation) for given points is quite hard and results very small fractions making it difficult for processor to compute - or making the implementation more complex by using fixed point arithemtic.

The linear and quadratic mix smoothens ride only around of 100 duty cycle value. There is actually no need to smooth values around 0 because DC motor would stop spin around 10, thus it would smoothen itself. This is great compromise between two options above with the function result: 

```
dc(e) = abs(-2 * abs(e) + 100), for e < -50 and e > 50
dc(e) = -1/25 * e^2 + 100, for e >= 50 and e <= 50
```

# Decision
The duty cycle - error characteristic would be linear

# Explanation
There is literally no differance in vehicle performence between linear and mixed approach, so there is no need to make the implementation more complex. 

#Conclusion

Actually there should be no surprise. The PID regulator is applied, thus the real relation is between duty cycle and regulated error.