#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(128);
	ofSetLineWidth(1.25);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(360 - 60);

	float R = 200;
	float r = 50;
	float u_span = 10;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int r = 50; r > 0; r -= 5) {

		int v_start = ofMap(ofNoise(r * 0.03 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);
		int v_end = v_start + 60;
		int v_span = 2;

		for (int v = v_start; v <= v_end; v += v_span) {

			for (int u = 0; u < 360; u += u_span) {

				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5));
				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v + v_span * 0.5));

				line.addVertex(this->make_point(R, r, u - u_span * 0.5, v - v_span * 0.5));
				line.addVertex(this->make_point(R, r, u + u_span * 0.5, v - v_span * 0.5));
				line.addVertex(this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5));
				line.addVertex(this->make_point(R, r, u - u_span * 0.5, v + v_span * 0.5));

				for (int i = 0; i < 4; i++) {

					if (r % 10 == 0) {

						face.addColor(ofColor(0));
						line.addColor(ofColor(255));
					}
					else {

						face.addColor(ofColor(255));
						line.addColor(ofColor(0));
					}
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				if (v == v_start) {

					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (v == v_end) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}
			}
		}
	}

	face.draw();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}