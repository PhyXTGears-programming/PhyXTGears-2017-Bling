# PhyXTGears 2017 Robot Bling
## Basic Information
This is the code for the Bling on our 2017 robot.  
Our setup uses a arduino mega to run an LED panel.
Our LED panel (40 pixles wide by 16 pixels high) is composed of two 32x8 panels and two 8x8 panels, chained together and connected to one pin on the Arduino.
The LEDs in the use 24-bit color, and are wired like one long string (the data for the last pixel must travel through all of the other pixels).  
* Using the NeoPixel library we can control the panel like a string of pixels.  
* The NeoMatrix library lets us control the panel's individual pixels by using (x, y) coordinates.  
* Using the Adafruit GFX library we can draw lines and shapes.  

## Libraries
We use the Adafruit NeoPixel, Adafruit NeoMatrix, and Adafruit GFX libraries.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Note: You must use Adafruit GFX version 1.4.4 or triangles won't draw correctly.

## Get your code on our robot!
To get you code of the robot, all you have to do us fork our code, make some simple changes to it, and create a pull request.
If we accept your pull request, your code will be on the robot soon.  
If you need help with Git or GitHub see our wiki.  
We have information on how our code works in our wiki.


## PhyXTGears Robotics Team
We are FRC team 1720.
www.phyxtgears.org
