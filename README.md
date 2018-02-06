
# Raytracer 42

![GitHub Logo](/saves/save42.png)

## Usage

`./rt [scene]`

## Scene

Must be written in this order:
1. window
2. camera
3. light(s)
4. geo(s)

## Features

### Events
* **Translate cam (X and Y)** <kbd>&darr;</kbd><kbd>&uarr;</kbd><kbd>&larr;</kbd><kbd>&rarr;</kbd><br>
* **Translate cam (Z)** <kbd>PAGEUP</kbd><kbd>PAGEDOWN</kbd><br>
* **Rotate cam** <kbd>E</kbd><kbd>R</kbd> <kbd>D</kbd><kbd>F</kbd> <kbd>C</kbd><kbd>V</kbd><br>
* **Drag Geometry**<br>
* **Drag Geometry + mouse scroll to translate geomtry along Z axis**<br>
* **Screen** <kdb>P</kdb>

### Antialiasing
Modify samp_rate in `init_environment`

### Filters
Modify filter in `init_environment`
