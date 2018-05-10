from openframeworks import *
from protopixel import Content
from random import randint
import math

print "CircleAnimation"


#a global variable
size = 1000

content = Content("CircleAnimation")
content.FBO_SIZE = (size,size) #optional: define size of FBO, default=(100,100)


videoFile1 = content.add_asset('baldosa1.mp4')
print videoFile1

videoFile2 = content.add_asset('baldosa2.mp4')
print videoFile2

videoFile3 = content.add_asset('baldosa3.mp4')
print videoFile3

# Video player from OF
vid1 = ofVideoPlayer()
vid2 = ofVideoPlayer()
vid3 = ofVideoPlayer()

@content.OSC('/amazon/arduino/norm/baldosa1') 
def tile1(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa1", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa1"
    vid1.play()



@content.OSC('/amazon/arduino/norm/baldosa2')
def tile2(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa2", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """
    print "baldosa2"
    vid2.play()



@content.OSC('/amazon/arduino/norm/baldosa3')
def tile3(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa3", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa3"
    vid3.play()



def setup():
    """
    This will be called at the beggining, you set your stuff here
    """
    
    ofEnableAlphaBlending()

    result = vid1.load(videoFile1)
    if result:
        print "loaded: ", videoFile1
        vid1.setLoopState(OF_LOOP_NONE)
        #vid1.play()
    else:
        print "unable to load: ", videoFile1

    result = vid2.load(videoFile2)
    if result:
        print "loaded: ", videoFile2
        vid2.setLoopState(OF_LOOP_NONE)
        #vid2.play()
    else:
        print "unable to load: ", videoFile2

    result = vid3.load(videoFile3)
    if result:
        print "loaded: ", videoFile3
        vid3.setLoopState(OF_LOOP_NONE)
        #vid3.play()
    else:
        print "unable to load: ", videoFile3
   
   



def update():
    """
    For every frame, before drawing, we update stuff
    """
    if vid1.isLoaded():
        vid1.update()

    if vid2.isLoaded():
        vid2.update()

    if vid3.isLoaded():
        vid3.update()
   


def draw():
    """
    For every frame draw stuff. Do not forget to clear the frmebuffer!
    """
    ofClear(0, 0, 0)
    ofSetColor(255, 255, 255)

    ofEnableBlendMode(OF_BLENDMODE_ADD)
    
    if vid1.isLoaded():
        vid1.draw(0, 0, size, size)

    if vid2.isLoaded():
        vid2.draw(0, 0, size, size)

    if vid3.isLoaded():
        vid3.draw(0, 0, size, size)

    

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
