#pragma once

#include "ofMain.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
enum BillboardMode
{
    BILLBOARD_CYLINDRICAL,
    BILLBOARD_CYLINDRICAL_CHEAT,
    BILLBOARD_SPHERICAL,
    BILLBOARD_SPHERICAL_CHEAT,
    BILLBOARD_NONE
};

//--------------------------------------------------------------
//--------------------------------------------------------------
class testApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawObject(const ofVec3f& pos, const ofVec3f& axis);
    
    private:
        ofEasyCam cam;
        ofImage eyeImage;
    
        BillboardMode mode;
        string modeName;
};
