#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//2 output ch, 1 input ch
	ofSoundStreamSetup(2, 1, 44100, 512, 3);
	micSamples.assign(512, 0.0f);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofScopedLock lockIt(audioMutex);

	//loop through our modulation buffer
	// and ring modulate it against a sin wave.
	//this is known as ring modulation.
	//BEWARE:  you must make sure you multiply
	//yout buffer sample by a float like 0.5 so you don't get a feedback loop
	for(int i=0; i < mModulationBuffer.size(); i+=2){
		mModulationBuffer[i] *= (sin(mPhase * TWO_PI) *0.5f);
		mModulationBuffer[i+1] *= (sin(mPhase * TWO_PI) *0.5f);
		// we offset our phase by the frequency / sampling rate
		mPhase += (400.0f / 44100.0f);
	}
	
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
	for(int i=0; i < mModulationBuffer.size();i+=2){
		float sample = mModulationBuffer[i];
		ofVertex(x*4, sample*100.0f);
        x++;
    }
    ofEndShape();
    
}

void ofApp::audioIn(ofSoundBuffer &inBuff){
	ofScopedLock lockIt(audioMutex);
	//copy our inbuffer over to our modulation buffer
	
	mModulationBuffer = inBuff;
	
}

void ofApp::audioOut(ofSoundBuffer &outBuff){
	ofScopedLock lockIt(audioMutex);
    //copy our modulation buffer to our output
	//so we can hear it.
	mModulationBuffer.copyTo(outBuff);
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
