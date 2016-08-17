#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    glEnable(GL_DEPTH_TEST); //enable depth comparisons and update the depth buffer
    ofDisableArbTex(); //needed for textures to work with gluSphere
    tex.loadImage("panorama.jpg");
    
    //prepare quadric for sphere
    quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    // 裏面のみ描画
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    sphereSize = 200;
    theta = 0;
    phi = 0;
    cam.setPosition(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
    eye.x = ((float)sphereSize * cos(ofDegToRad(phi))) * sin(ofDegToRad(theta));
    eye.y = (float)sphereSize * sin(ofDegToRad(phi));
    eye.z = (-(float)sphereSize * cos(ofDegToRad(phi))) * cos(ofDegToRad(theta));
    cam.lookAt(ofVec3f(eye.x, eye.y, eye.z));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    {
        //change origin to center
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
        cam.begin();
        {
            ofRotateX(90); //north pole facing up
            
            //bind and draw texture
            tex.getTextureReference().bind();
            gluSphere(quadric, sphereSize, 100, 100);
        }
        cam.end();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
    // camera control
    if (key == OF_KEY_RIGHT) {
        theta += 5.0;
        if (theta >= 360) {
            theta -= 360;
        }
    } else if (key == OF_KEY_LEFT) {
        theta -= 5.0;
        if (theta < 0) {
            theta += 360;
        }
    } else if (key == OF_KEY_UP) {
        phi += 5.0;
        if (phi > 90) {
            phi = 90;
        }
    } else if (key == OF_KEY_DOWN) {
        phi -= 5.0;
        if (phi < -90) {
            phi = -90;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (tmpX > 0 && tmpY > 0) {
        int dx = x - tmpX;
        float param = 90.0;
        theta = tmp_theta + (float)dx * param / ofGetWidth();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    tmpX = x;
    tmpY = y;
    tmp_theta = theta;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    tmpX = -1;
    tmpY = -1;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
