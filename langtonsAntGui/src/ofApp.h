#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void drawGrid();
		void drawAnt(int posX, int posY);
		void cycle();
		void drawWorld();
		void antDirection();
		int x, y, rows, columns, cellSize, antX, antY, timeBuffer, interval;
		int **cells = 0;
		int **cellsMemory = 0;
		char dir;
		int aliveCells, deadCells = 0;

		ofxToggle grid;
		ofxToggle isRunning;
		ofxColorSlider color;
		ofxLabel alive;
		ofxLabel dead;
		ofxFloatSlider speed;
		ofxLabel message;
		ofxButton reset;
		ofxPanel gui;
};
