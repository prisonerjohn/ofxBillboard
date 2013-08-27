#include "testApp.h"
#include "ofxBillboard.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(ofColor::grey);
    
    eyeImage.loadImage("eyeball.png");
    
    keyPressed('1');
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{
    cam.begin();
    {
        static float objectRadius = 200;
        drawObject(ofVec3f(sinf(ofGetFrameNum() * 0.1) *  objectRadius,
                           cosf(ofGetFrameNum() * 0.1) *  objectRadius,
                           objectRadius),
                   ofVec3f(0, 0, 1));
        drawObject(ofVec3f(sinf(ofGetFrameNum() * 0.1) *  objectRadius,
                           objectRadius,
                           cosf(ofGetFrameNum() * 0.1) *  objectRadius),
                   ofVec3f(1, 0, 0));
        drawObject(ofVec3f(objectRadius,
                           sinf(ofGetFrameNum() * 0.1) *  objectRadius,
                           cosf(ofGetFrameNum() * 0.1) *  objectRadius),
                   ofVec3f(0, 1, 0));
        
        // draw axes
        static float axisLength = 200;
        ofSetColor(ofColor::red);
        ofLine(0, 0, 0, axisLength, 0, 0);
        ofSetColor(ofColor::green);
        ofLine(0, 0, 0, 0, axisLength, 0);
        ofSetColor(ofColor::blue);
        ofLine(0, 0, 0, 0, 0, axisLength);
    }
    cam.end();
        
    ofDrawBitmapStringHighlight("Billboard (1-5): " + modeName, 10, 20);
}

//--------------------------------------------------------------
void testApp::drawObject(const ofVec3f& pos, const ofVec3f& axis)
{
    if (mode == BILLBOARD_CYLINDRICAL) {
        ofxBillboardBeginCylindrical(cam.getGlobalPosition(), pos);
    }
    else if (mode == BILLBOARD_CYLINDRICAL_CHEAT) {
        ofxBillboardBeginCylindricalCheat();
    }
    else if (mode == BILLBOARD_SPHERICAL) {
        ofxBillboardBeginSpherical(cam.getGlobalPosition(), pos);
    }
    else if (mode == BILLBOARD_SPHERICAL_CHEAT) {
        ofxBillboardBeginSphericalCheat();
    }
    
    ofPushMatrix();
    ofTranslate(pos);
    {
        ofSetColor(ofColor::white);
        eyeImage.draw(-50, -50, 100, 100);
    }
    ofPopMatrix();
    
    if (mode != BILLBOARD_NONE) {
        ofxBillboardEnd();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) {
        case '1':
            mode = BILLBOARD_CYLINDRICAL;
            modeName = "CYLINDRICAL";
            break;
            
        case '2':
            mode = BILLBOARD_CYLINDRICAL_CHEAT;
            modeName = "CYLINDRICAL CHEAT";
            break;
            
        case '3':
            mode = BILLBOARD_SPHERICAL;
            modeName = "SPHERICAL";
            break;
            
        case '4':
            mode = BILLBOARD_SPHERICAL_CHEAT;
            modeName = "SPHERICAL CHEAT";
            break;
            
        case '5':
            mode = BILLBOARD_NONE;
            modeName = "NONE";
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
