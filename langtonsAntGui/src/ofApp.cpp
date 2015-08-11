#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	timeBuffer = 0;
	interval = 0;
	dir = 'r';
	x = ofGetWindowWidth();
	y = ofGetWindowHeight();
	ofColor on(255,0,0);
	cellSize = 10;
	rows = x/cellSize;
	columns = y/cellSize;
	antX = x/2;
	antY = y/2;
	cells = new int *[rows];
	cellsMemory = new int *[rows];
	
	gui.setup();
	gui.add(grid.setup("grid on/off", true));
	gui.add(isRunning.setup("pause/play", true));
	gui.add(reset.setup("RESET"));
	gui.add(color.setup("color",ofColor(100,192,140),ofColor(0,0,0),ofColor(255,255,255)));
	gui.add(speed.setup( "speed", 210, 10, 300 ));
	gui.add(message.setup("click mouse", "cells on/off"));
	gui.add(alive.setup("living cells: ", ""));
	gui.add(dead.setup("dead cells: ", ""));

	for( int i = 0 ; i < rows ; i++ ){
		cells[i] = new int[columns];
		cellsMemory[i] = new int[columns];
	}

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			cells[i][j] = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawGrid(){
	ofFill(); 
	glLineWidth(0.3);
	ofSetColor(100);
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			ofNoFill(); 
			glLineWidth(0.3);
			ofSetColor(100);
			ofRect(i*cellSize, j*cellSize ,cellSize, cellSize);
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawAnt(int posX, int posY){
	ofFill();
	ofSetColor(255);
	ofRect(posX, posY, cellSize, cellSize);
}

//--------------------------------------------------------------
void ofApp::drawWorld(){
	aliveCells = 0;
	deadCells = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(cells[i][j] == 0){
				if(grid){
					ofNoFill();
					glLineWidth(0.3);
					ofSetColor(50);
				}else{
					ofFill();
					ofSetColor(0); 
				}
				deadCells+=1;
			}else{
				ofFill();
				glLineWidth(0.3);
				ofSetColor(color);
				aliveCells+=1;
			}
			ofRect(i*cellSize, j*cellSize ,cellSize, cellSize);
		}		
	}
	alive = ofToString(aliveCells);
	dead = ofToString(deadCells);
}
//--------------------------------------------------------------
void ofApp::cycle(){
	if(ofGetElapsedTimeMillis()-timeBuffer >= interval){
		for(int i=0; i<rows; i++){
			for(int j=0; j<columns; j++){
				if (i*cellSize == antX && j*cellSize == antY){
					if (cells[i][j] == 1){
						cells[i][j] = 0;
						if(dir == 'r'){
							dir = 'd';
						}
						else if(dir == 'd'){
							dir = 'l';
						}
						else if(dir == 'l'){
							dir = 'u';
						}
						else if(dir == 'u'){
							dir = 'r';
						}
					}else{
						cells[i][j] = 1;
						if(dir == 'r'){
							dir = 'u';
						}
						else if(dir == 'u'){
							dir = 'l';
						}
						else if(dir == 'l'){
							dir = 'd';
						}
						else if(dir == 'd'){
							dir = 'r';
						}
					}
				}
			}		
		}
		timeBuffer = ofGetElapsedTimeMillis();
		antDirection();
	}
}

//-------------------------------------------------------------
void ofApp::antDirection(){
	if(dir == 'r'){
		antX+=cellSize;
	}
	if(dir == 'l'){
		antX-=cellSize;
	}
	if(dir == 'u'){
		antY-=cellSize;
	}
	if(dir == 'd'){
		antY+=cellSize;
	}
}

//-------------------------------------------------------------
void ofApp::update(){
	if(isRunning){
		cycle();
	}

	interval = int(ofMap(speed, 10, 300, 200, 0));
	if (reset){
		dir = 'r';
		antX = x/2;
		antY = y/2;
		for(int i=0; i<rows; i++){
			for(int j=0; j<columns; j++){
				cells[i][j] = 0;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawWorld();
	drawAnt(antX, antY);
	ofSetColor(255);
	gui.draw();
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
	int xPosM = ofMap(mouseX, 0, ofGetWindowWidth(), 0, rows);
	int yPosM = ofMap(mouseY, 0, ofGetWindowHeight(), 0, columns);
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if (xPosM == i && yPosM == j){
				if (cells[i][j] == 1){
					cells[i][j] = 0;
				}else{
					cells[i][j] = 1;
				}
			}
		}
	}
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
