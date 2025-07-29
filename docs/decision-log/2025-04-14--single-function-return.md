# Single function return point

## Subject
A lot of coding standard sources, such as MISRA-C or Barr's, claims that the functions should or must have a single point of return at the end of the function.

## Pros
* Long functions' flow are more readible
* Before returning all resources can be released
* Long functions are easier to debug

## Cons
* Short functions become more robust and over-conditioned

## Decision
I'll follow the Barr's rule that a function should have a single return point at the end of its body, **unless** it affects its readability. However the function readability is very subjective, so there is a need to be careful here.

## Example

```c

// GO WITH THIS

int
// cppcheck-suppress staticFunction
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    int result = coords_validate(coords);

    if (result < 0)
    {
        return -EINVAL;
    }

    result = context_acquire(mode, coords, errsize, handle);

    if (result < 0)
    {
        return -ENOMEM;
    }

    return 0;
}

// INSTEAD OF THIS

int
// cppcheck-suppress staticFunction
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    int result = coords_validate(coords);

    if (result >= 0)
    {
        result = context_acquire(mode, coords, errsize, handle);

        if (result >= 0)
        {
            result = 0;
        }
        else
        {
            result = -ENOMEM;
        }
    }
    else
    {
        result = -EINVAL;
    }

    return result;
}
```

## Reasoning
* Barr's recommendation is less strinct than MISRA-C. Functions that handles resouces release may follow "single-return" principle, while those like in example above may not, since the only thing they do is som instantiations, creation, etc.