from openframeworks import *
from protopixel import Content
from random import randint
import math

print "CircleAnimation"


#a global variable
size = 1000

content = Content("CircleAnimation")
content.FBO_SIZE = (size,size) #optional: define size of FBO, default=(100,100)


videoFiles = []
videoFiles.append(content.add_asset('baldosa1.mp4'))
videoFiles.append(content.add_asset('baldosa2.mp4'))
videoFiles.append(content.add_asset('baldosa3.mp4'))


videoPlayers = []



@content.OSC('/amazon/arduino/norm/baldosa1') 
def tile1(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa1", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa1"
    videoPlayers[0].play()



@content.OSC('/amazon/arduino/norm/baldosa2')
def tile2(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa2", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """
    print "baldosa2"
    videoPlayers[1].play()



@content.OSC('/amazon/arduino/norm/baldosa3')
def tile3(i):
    """
    This function handles OSC user input in address "/amazon/arduino/norm/baldosa3", with 1 arguments: i.
    Use pl.OSC decorator to define handles like this. Multiple scripts can listen to
    the same address simultaneously.
    """

    print "baldosa3"
    videoPlayers[2].play()



def setupPlayers():

    for x in xrange(len(videoFiles)):
        videoPlayers.append(ofVideoPlayer())

    for i in xrange(len(videoFiles)):
        result = videoPlayers[i].load(videoFiles[i])
        if result:
            print "SetupPlayers: Successfully loaded ->  ", videoFiles[i]
            videoPlayers[i].setLoopState(OF_LOOP_NONE)
        else:
            print "SetupPlayers: unable to load -> ", videoFiles[i]

        
        


def setup():
    """
    This will be called at the beggining, you set your stuff here
    """
    
    #ofEnableAlphaBlending()
    setupPlayers()
   
   



def update():
    """
    For every frame, before drawing, we update stuff
    """

    for videoPlayer in videoPlayers:    
        if videoPlayer.isLoaded():
            videoPlayer.update()

def draw():
    """
    For every frame draw stuff. Do not forget to clear the frmebuffer!
    """
    ofClear(0, 0, 0)
    ofSetColor(255, 255, 255)

    ofEnableBlendMode(OF_BLENDMODE_ADD)

    for videoPlayer in videoPlayers:    
        if videoPlayer.isLoaded():
            videoPlayer.draw(0, 0, size, size)

    

def exit():
    """
    Before removing the script, in case you have pending business.
    """
    for videoPlayer in videoPlayers:    
        if videoPlayer.isLoaded():
            videoPlayer.stop()
            

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
