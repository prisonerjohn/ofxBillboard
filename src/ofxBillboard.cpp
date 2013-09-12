//
//  ofxBillboard.cpp
//  ofxBillboard
//
//  Created by Elie Zananiri on 2013-08-26.
//  Adapted from the Lighthouse 3D Billboarding Tutorial by António Ramires Fernandes.
//  http://www.lighthouse3d.com/opengl/billboarding/
//

#include "ofxBillboard.h"

//--------------------------------------------------------------
void ofxBillboardBeginCylindrical(const ofVec3f& camPos, const ofVec3f& objPos)
{
	// Save the current modelView matrix.
    ofPushMatrix();
    
    // Translate the object to its position.
    ofTranslate(objPos);
    
    // The original lookAt vector for the object in world coordinates.
    ofVec3f lookAt(0, 0, 1);
        
    // The vector in world coordinates from the local origin to the camera projected in the XZ plane.
	ofVec3f objToCamProj(camPos.x - objPos.x, 0, camPos.z - objPos.z);
    objToCamProj.normalize();
    
    // Easy fix to determine wether the angle is negative or positive:
    //  For positive angles, upAux will be a vector pointing in the positive y direction.
    //  Otherwise, upAux will point downwards effectively reversing the rotation.
    ofVec3f upAux = lookAt.getCrossed(objToCamProj);
    
    // Compute the angle.
    float angleCosine = lookAt.dot(objToCamProj);
    
    // Perform the rotation.
    // The if statement is used for stability reasons:
    //  If the lookAt and objToCamProj vectors are too close together then angleCosine could be bigger than 1 due to lack of precision.
    if ((angleCosine < 0.99990) && (angleCosine > -0.9999)) {
        ofRotate(RAD_TO_DEG * acos(angleCosine), upAux.x, upAux.y, upAux.z);
    }
}

//--------------------------------------------------------------
void ofxBillboardBeginSpherical(const ofVec3f& camPos, const ofVec3f& objPos)
{
	ofxBillboardBeginCylindrical(camPos, objPos);

    // So far it is just like the cylindrical billboard.
    // The second part tilts the object so that it faces the camera.
    
    // objToCam is the vector in world coordinates from the local origin to the camera.
    ofVec3f objToCam = camPos - objPos;
    
    // Normalize to get the cosine afterwards.
    objToCam.normalize();
    
    // The vector in world coordinates from the local origin to the camera projected in the XZ plane.
	ofVec3f objToCamProj(camPos.x - objPos.x, 0, camPos.z - objPos.z);
    objToCamProj.normalize();
    
    // Compute the angle between objToCamProj and objToCam, i.e. the required angle for the lookup vector.
	float angleCosine = objToCamProj.dot(objToCam);
    
    // Tilt the object.
    // The test is done to prevent instability when objToCam and objToCamProj have a very small angle between them.
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999)) {
		if (objToCam.y < 0) {
			ofRotate(RAD_TO_DEG * acos(angleCosine),  1, 0, 0);
        }
		else {
			ofRotate(RAD_TO_DEG * acos(angleCosine), -1, 0, 0);
        }
    }
}

//--------------------------------------------------------------
void ofxBillboardBeginCylindricalCheat(const ofVec3f& objPos)
{
    // Save the current modelView matrix.
	ofPushMatrix();
    
    // Translate the object to its position.
    ofTranslate(objPos);
    
	// Get the current modelView matrix.
	float modelView[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
    
	// Note that a row in the C convention is a column.
	// In OpenGL convention (see the red book, pg.106 in version 1.2):
	//  right vector is [1,0,0]  (1st column)
	//  lookAt vector is [0,0,1] (3d column)
	// Leave the up vector unchanged (2nd column)
	// Notice the increment in i in the first cycle (i+=2)
	for (int i = 0; i < 3; i += 2) {
		for (int j = 0; j < 3; j++) {
            modelView[i * 4 + j] = (i == j)? 1.0 : 0.0;
		}
    }
    
    // Set the modelView matrix.
	glLoadMatrixf(modelView);
}

//--------------------------------------------------------------
void ofxBillboardBeginSphericalCheat(const ofVec3f& objPos)
{	
    // Save the current modelView matrix.
	ofPushMatrix();
    
    // Translate the object to its position.
    ofTranslate(objPos);
    
	// Get the current modelView matrix.
	float modelView[16];
    glGetFloatv(GL_MODELVIEW_MATRIX , modelView);
    
	// Undo all rotations.
	// Beware all scaling is lost as well.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
            modelView[i * 4 + j] = (i == j)? 1.0 : 0.0;
		}
    }
    
    // Set the modelView matrix with no rotations.
	glLoadMatrixf(modelView);
}

//--------------------------------------------------------------
void ofxBillboardEnd()
{
    // Restore the modelView matrix.
    ofPopMatrix();
}
