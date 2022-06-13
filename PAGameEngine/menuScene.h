#pragma once
#include "sceneV2.h"

using namespace std;
class MenuScene :public SceneV2 {
	vector<Camera*> cameras;
	Camera* activeCamera;

	Light* light;

	Barco* barco;
	Canon* canon;

	Text* informacion1;
	Text* informacion4;

	double mx, my;

public:
	MenuScene() {
		setSize(Vector3D(100, 100, 100));
		generaCamaras();
		generaLuces();
		generaFondo();
		generaInterfaz();
		
	}

	Camera* getCamera() { return activeCamera; }
	Camera* getCamera(int i) { return cameras[i]; }
	void setCamera(Camera* c) { activeCamera = c; }

	vector<Camera*> getCameras() { return cameras; }
	void setCameras(vector<Camera*> vc) { cameras = vc; }

	void update(const double& dt) {
		for (Solid* ps : getSolids()) {
			ps->update(dt);
		}
	}

	void render() {
		this->activeCamera->render();
		Composite::render();
	}

	void processKeyPressed(unsigned char key, int x, int y) {
		
	}

	void generaCamaras() {
		Camera* camera1 = new Camera(Vector3D(0, 0, 20));
		camera1->setRot(Vector3D(17, 25, 0));
		camera1->setPos(camera1->getPos() + Vector3D(-5, 5, -5));
		cameras.push_back(camera1);

		activeCamera = camera1;
	}

	void generaLuces() {
		light = new Light(Vector3D(0, -0.7, 0.5));
		this->add(light);
	}

	void generaFondo() {
		barco = new Barco();
		barco->setColor(Vector3D(0.5, 0.25, 0));
		barco->setPos(Vector3D(0, 5, 0));
		barco->setVel(Vector3D(0, 0, 0));
		barco->setRot(Vector3D(-90, 0, 0));
		this->add(barco);

		canon = new Canon();
		canon->setPos(barco->getPos() + canon->getDesfase());
		canon->setScene(this);
		this->add(canon);

		Cuboid* mar;
		mar = new Cuboid();
		mar->setColor(Vector3D(0, 1, 1));
		mar->setLength(300);
		mar->setWidth(300);
		mar->setHeight(1);
		mar->setPos(Vector3D(0, 0, 0));
		this->add(mar);
	}

	void generaInterfaz() {
		informacion1 = new Text();
		informacion1->setText("Pulse 1 para empezar a jugar.");
		informacion1->setPos(Vector3D(-11, 10, 0));
		informacion1->setColor(Vector3D(0, 0, 0));
		this->add(informacion1);

		Text* informacion4 = new Text();
		informacion4->setText("Pulse 4 para ver el top 3");
		informacion4->setPos(Vector3D(-11, 9, 0));
		informacion4->setColor(Vector3D(0, 0, 0));
		this->add(informacion4);
	}
	
};
