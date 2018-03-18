#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//2 output ch, 1 input ch
	ofSoundStreamSetup(2, 1, 44100, 512, 3);
	micSamples.assign(512, 0.0f);
}

//--------------------------------------------------------------
void ofApp::update(){
unique_lock<mutex> lock(audioMutex);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Try as ofPolyline
    
    ofTranslate(0.0, 170);
    ofNoFill();
    ofSetLineWidth(3);
    ofSetColor(92, 107, 251);//blue
	
    ofBeginShape();
	float x = 0;
    float y = 0;
    for(auto &sample: micSamples){
        ofVertex(x*4, sample*100.0f);
        x++;
    }
    ofEndShape();
    
}

void ofApp::audioIn(ofSoundBuffer &inBuff){
	for(int i=0; i < inBuff.size(); i++){
		//assign our buffer samples to our
		//floating point vector.

		micSamples[i]		= inBuff[i]*0.5;
	}
}

void ofApp::audioOut(ofSoundBuffer &outBuff){
	
    
    unique_lock<mutex> lock(audioMutex);
    
    for(size_t i = 0; i < outBuff.size(); i++) {
    
        
    outBuff.getSample(i, 0) = micSamples[i];
    outBuff.getSample(i, 1) = micSamples[i+1];
        
    }
	
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
