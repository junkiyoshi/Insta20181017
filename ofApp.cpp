#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(239);

	ofImage image = ofImage("images/gecko.png");
	int span = 10;

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);

	image.draw(5, 5);

	this->fbo.end();

	ofPixels pixels;
	this->fbo.readToPixels(pixels);

	for (int x = 0; x < this->fbo.getWidth(); x += span) {

		for (int y = 0; y < this->fbo.getHeight(); y += span) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x, y));
			}
		}
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<int> next_index = vector<int>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j ){ continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance <= span) {

				next_index.push_back(j);
			}
		}

		this->next_indexes.push_back(next_index);
	}

	for (int i = 0; i < 800; i++) { this->particles.push_back(Particle(this->locations, this->next_indexes)); }
}
//--------------------------------------------------------------
void ofApp::update() {

	for (Particle& particle : particles) { particle.Upate(); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (Particle& particle : particles) { particle.Draw(); }
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}