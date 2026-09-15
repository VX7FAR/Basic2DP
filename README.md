# BASIC2DP

Basic2DP is a 2D physics engine that can simulate collision, movement and force acting on a body.
This engine is made as an intro towards physics and making graphics in computer programs. It is made in C++17 and for graphics I used SFML(Simple and Fast Multimedia Library).
This project only features translation of now but I might implement rotation with additional shapes in the future.

### What you can do as of now:
- Add shapes
- Change velocity by incrementing or replacing the current vleocity
- Change themes (who doesnt love good themes)
- Make new themes
- Change gravity

### Themes
The project comes with inbuilt 10 themes to customize your experience.

## How to use
To run the software you simply have to extract the release folder and run the executable. You will see two windows open one will be an immovable window and other will be a terminal.
The immovable window will show the physics and since this project is CLI based you will have to use the terminals to interact with the application.

### There are somethings you should consider before reading the guide.
- Text in `<>` refer to elements that you will have to enter
- Text in `{}` refer to optional elements, in some cases the options may be seperated by `|`
- In some places where normally comma is given you do not have to give them, for example when giving location u dont have to do `41, 21` you can simply do `41 21`.
- In places where you may have to give integer values if you give something like `54ae` it will be recognized as `54`.

Now you should be ready to use.

**Getting help:**
```
help
```

**Getting Info about project:**
```
getinfo
```

**Adding bodies to display:**
```
addbody {radius} {x_position} {y_position}
```
Simply using `addbody` without anything else will add a shape of raidus 5 at position 0,0.

**Updating Velocity:**
```
updatevelocity <x_velocity> <y_velocity> {increment|change}
```
X and Y velocity are important to give but third option is set to increment by default.

**Update gravity:**
```
setgravity <x_pull> <y_pull>
```
In this program instead of having a making a point as gravity center you define how much pull there should be in x and y direction.

