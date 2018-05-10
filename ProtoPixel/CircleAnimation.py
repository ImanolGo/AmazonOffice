from openframeworks import *
from protopixel import Content
from random import randint
import math

print "CircleAnimation"


#a global variable
color = ofColor(255)
elapsedTime = 0.0
scaleFactor = 10
size = 1000

content = Content("CircleAnimation")
content.FBO_SIZE = (size,size) #optional: define size of FBO, default=(100,100)

content.add_parameter("color1", type="color", value=ofColor(255, 10, 10))
content.add_parameter("color2", type="color", value=ofColor(10, 255, 10))
content.add_parameter("color3", type="color", value=ofColor(10, 10, 255))
content.add_parameter("animationTime", min=0.01, max=20.0, value=5.0)




class Circle:
    size = 10
    xPos = 0
    yPos = 0
    clr = ofColor(255)
    animationTime = 5.0
    elapsedTime = 0.0
    r = 0
    g = 0
    b = 0
    a = 0

    def __init__(self, x, y):
        self.xPos = x
        self.yPos = y

    def update(self):

        self.elapsedTime+=ofGetLastFrameTime()
        if(self.elapsedTime<self.animationTime):
            amount = self.elapsedTime/self.animationTime
            self.size = 4*size*(amount) 
            amount = amount*amount
            self.a = 255 - int(255*amount) 

    def draw(self):
        #ofPushStyle()
        ofFill()
        ofSetColor(ofColor(self.r,self.g,self.b,self.a))
        ofDrawEllipse(self.xPos, self.yPos, self.size, self.size)
        #ofPopStyle()

    def setAnimationTime(self, value):
        self.animationTime = value

    def setColor(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b
        
    def start(self):
        self.a = 255
        self.size = 0
        self.elapsedTime = 0.0



circles = []



@content.parameter_changed('color1')
def parameter_changed(value):
    """
    This function is called every time a a_integer is changed.
    We get the new value as an argument
    """

    #print value
    if len(circles) >= 3:
        circles[0].setColor(content['color1'].r,content['color1'].g,content['color1'].b)
 
@content.parameter_changed('color2')
def parameter_changed(value):
    """
    This function is called every time a a_integer is changed.
    We get the new value as an argument
    """

    #print value
    if len(circles) >= 3:
        circles[1].setColor(content['color2'].r,content['color2'].g,content['color2'].b)
 
 
@content.parameter_changed('color3')
def parameter_changed(value):
    """
    This function is called every time a a_integer is changed.
    We get the new value as an argument
    """

    #print value
    if len(circles) >= 3:
        circles[2].setColor(content['color3'].r,content['color3'].g,content['color3'].b)
 
           
           

@content.parameter_changed('animationTime')
def parameter_changed(value):
    """
    This function is called every time a a_integer is changed.
    We get the new value as an argument
    """
    global circles

    for circle in circles:
        circle.setAnimationTime(content['animationTime'])


@content.OSC('/amazon/arduino/norm/baldosa1') 
def tile1(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa1", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa1"

    if len(circles) >= 3:
        circles[0].start()


@content.OSC('/amazon/arduino/norm/baldosa2')
def tile2(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa2", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """
    print "baldosa2"

    if len(circles) >= 3:
        circles[1].start()

@content.OSC('/amazon/arduino/norm/baldosa3')
def tile3(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa3", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa3"

    if len(circles) >= 3:
        circles[2].start()


def setup():
    """
    This will be called at the beggining, you set your stuff here
    """
    ofSetBackgroundAuto(False)
    ofEnableAlphaBlending()

    global size, circles

    x = size*0.78
    y = size*0.42
    circles.append(Circle(x,y))
    circles[0].setAnimationTime(content['animationTime'])
    circles[0].setColor(content['color1'].r,content['color1'].g,content['color1'].b)
   
    x = size*0.777
    y = size*0.32
    circles.append(Circle(x,y))
    circles[1].setAnimationTime(content['animationTime'])
    circles[1].setColor(content['color2'].r,content['color2'].g,content['color2'].b)

    x = size*0.025
    y = size*0.25
    circles.append(Circle(x,y))
    circles[2].setAnimationTime(content['animationTime'])
    circles[2].setColor(content['color3'].r,content['color3'].g,content['color3'].b)



def update():
    """
    For every frame, before drawing, we update stuff
    """

    for circle in circles:
        circle.update()


def draw():
    """
    For every frame draw stuff. Do not forget to clear the frmebuffer!
    """
    global circles, size

    ofSetColor(0,0,0,10)
    ofFill()
    ofDrawRectangle(0,0,size,size)

    #ofSetColor(color)
    for circle in circles:
        circle.draw()
        
    #ofSetColor(content['color1'].r,content['color1'].g,content['color1'].b);
    circles[0].draw()
  

def exit():
    """
    Before removing the script, in case you have pending business.
    """
    pass


def on_enable():
    """
    This function is called when this content just got enabled.
    """
    pass


def on_disable():
    """
    This function is called when this content just got disabled.
    `update` and `draw` functions are not called while this content is disabled.
    """
    pass
