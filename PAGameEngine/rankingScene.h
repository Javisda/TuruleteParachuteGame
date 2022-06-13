#pragma once
#include "sceneV2.h"
#include "ranking.h"

using namespace std;
class RankingScene :public SceneV2 {
	vector<Camera*> cameras;
	Camera* activeCamera;

	Light* light;

	Barco* barco;
	Canon* canon;

	Text* top1;
	Text* top2;
	Text* top3;

	double mx, my;

public:
	RankingScene() {
		setSize(Vector3D(100, 100, 100));
		generaCamaras();
		generaLuces();
		generaFondo();
		generaInterfaz();
		dibujaRanking();
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
		top1 = new Text();
		top1->setPos(Vector3D(-11, 10, 0));
		top1->setColor(Vector3D(0, 0, 0));
		this->add(top1);

		top2 = new Text();
		top2->setPos(Vector3D(-11, 9, 0));
		top2->setColor(Vector3D(0, 0, 0));
		this->add(top2);

		top3 = new Text();
		top3->setPos(Vector3D(-11, 8, 0));
		top3->setColor(Vector3D(0, 0, 0));
		this->add(top3);
	}

	void dibujaRanking() {
		//Escritura en pantalla del top puntos
		string line;
		ifstream fIn("ranking.txt");
		if (fIn.is_open()) {
			getline(fIn, line);
			top1->setText("Top 1: " + line + " puntos");
			getline(fIn, line);
			top2->setText("Top 2: " + line + " puntos");
			getline(fIn, line);
			top3->setText("Top 3: " + line + " puntos");
		}
		fIn.close();
	};

};
