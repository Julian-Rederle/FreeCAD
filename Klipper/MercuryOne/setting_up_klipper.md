See [official documentation](https://www.klipper3d.org/Config_checks.html) for more information

# Steppers

First, to check if all endfstops are working correctly, do a quick erndstop check by running `QUERY_ENDSTOPS` while pressing the stops one-by-one.

Next check all the steppers with:
```bash
STEPPER_BUZZ STEPPER=stepper_x
STEPPER_BUZZ STEPPER=stepper_y
STEPPER_BUZZ STEPPER=stepper_z
```
