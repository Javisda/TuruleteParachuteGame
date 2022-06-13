#pragma once
#include "scene.h"

using namespace std;
class SceneV2 :public Scene {
	vector<Camera*> cameras;
	Camera* activeCamera;

	double mx, my;

public:
	SceneV2() {
		setSize(Vector3D(100, 100, 100));
		
	}

	virtual Camera* getCamera() { return activeCamera; }
	virtual Camera* getCamera(int i) { return cameras[i]; }
	virtual void setCamera(Camera* c) { activeCamera = c; }

	virtual void update(const double& dt) {
		for (Solid* ps : getSolids()) {
				ps->update(dt);
		}
	}
	
	virtual void render() = 0;

	virtual void generaFondo() = 0;

	virtual bool detectaDerrota() {
		return false;
	}

	virtual void resetScene() {};

	virtual void dibujaRanking() {};

	virtual void processKeyPressed(unsigned char key, int x, int y) = 0;
};

