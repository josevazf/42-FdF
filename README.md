# 42-FdF
FDF is short for ’fil de fer’ in French which means ’wireframe model’.
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_6.png)

This is the first graphical project from the 42 curriculum and requires the use of the <a href="https://github.com/42Paris/minilibx-linux">MiniLibx</a> library. This library was developed by 42 School and includes the necessary tools to open a window, create images and deal with keyboard and mouse events.

The main goal of this project is to create a wireframe model representation of a 3D landscape given by a .fdf file. 

Extra features that are triggered by the keyboard:
- Translation of the model.
- Rotations.
- Zoom in and out.
- Top view.
- Scale height representation.
- Change between diferent color gradients.

## Rendering

The program first represents the model in isometric projection and with a color gradient associated to the height variation.\
The coordinates of the landscape are stored in a .fdf file passed as a parameter to
your program.\
Each number represents a point in space:
- The horizontal position corresponds to its axis.
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.
- Some points can have a color defined in hex notation , ex.: `3,0xFF0000` represents a point with height `3` and the color `white`.

## Requirements (Linux)

<a href="https://github.com/42Paris/minilibx-linux">MiniLibx</a>
- MinilibX only supports TrueColor visual type (8,15,16,24 or 32 bits depth)
- gcc
- make
- X11 include files (package xorg)
- XShm extension must be present (package libxext-dev)
- Utility functions from BSD systems - development files (package libbsd-dev)

## How to use

```Bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

git clone

make

(choose a map)
./fdf maps/(map).fdf
```
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_1.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_2.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_3.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_4.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_5.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_7.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_8.png)
![image](https://github.com/josevazf/42-FdF/blob/main/docs/img/img_9.png)

## Norminette
This project was written in accordance with the Norm, which is the coding standard of the 42 school.

The Norm includes:
- Forbidden: for, do...while, switch, case, goto, ternary operators and variable-length arrays 
- Maximum of 25 lines per function
- Maximum line length: 80 columns
- Maximum 4 parameters per function 
- Variable assignments and declarations must be on separate lines
- etc...
