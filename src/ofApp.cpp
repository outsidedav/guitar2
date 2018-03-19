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
    
    //draw polyline
    waveform.clear();
    for(size_t i = 0; i < mModulationBuffer.getNumFrames(); i++) {
        float sample = mModulationBuffer.getSample(i, 0);
        float x = ofMap(i, 0, mModulationBuffer.getNumFrames(), 0, ofGetWidth());
        float y = ofMap(sample, -1, 1, 0, ofGetHeight());
        waveform.addVertex(x, y);
    }
    
    rms = mModulationBuffer.getRMSAmplitude();
    
	
}

//--------------------------------------------------------------
void ofApp::draw(){

  //Draw waveform
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(1 + (rms * 30.));
    waveform.draw();
    
    
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

    

    if(currWaveForm==4){
        mModulationBuffer.copyTo(outBuff);
    }
    
    else{
    for(int i=0; i < mModulationBuffer.size(); i+=2){
        mPhase += (400.0f / 44100.0f);
        float sample = distortion(mPhase, currWaveForm);
        sample *= mModulationBuffer[i];
        outBuff[i]= sample;
        outBuff[i+1]= sample;
        }
   
    }
    
	
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            currWaveForm = 1;
            break;
        case '2':
            currWaveForm = 2;
            
            break;
        case '3':
            currWaveForm = 3;
            
            break;
            
        case '4':
            currWaveForm = 4;
            
            break;
     
        default:
            break;
    }
}

//--------------------------------------------------------------
float ofApp::distortion(float phase, int waveType){
    switch (waveType) {
        case 1://tri
            return abs(sin(phase*TWO_PI));
            ofLogNotice("tri");
            break;
        case 2://square
            return sin(phase*TWO_PI)>0?1:-1;
            ofLogNotice("square");
        case 3://sine
             return fmod(phase,TWO_PI);
        default:
            break;
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
