#pragma once
#include "sceneV2.h"
#include "ranking.h"

using namespace std;
class GameScene :public SceneV2 {
	vector<Camera*> cameras;
	Camera* activeCamera;

	int currentSecond = 0;

	Ranking* rank;

	Light* light;

	Barco* barco;
	Canon* canon;

	Text* puntos;
	Text* vidas;

	vector<Boat*> balsas;
	vector<Turuleta*> turuletas;

	vector<Boat*> removableBoats;
	vector<Turuleta*> removableTuruletas;
	vector<Bullet*> removableBullets;

	double mx, my;

public:
	GameScene() {
		setSize(Vector3D(100, 100, 100));

		generaCamaras();
		generaLuces();
		generaFondo();
		generaInterfaz();
		rank = new Ranking();

	}

	Camera* getCamera() { return activeCamera; }
	Camera* getCamera(int i) { return cameras[i]; }
	void setCamera(Camera* c) { activeCamera = c; }

	vector<Camera*> getCameras() { return cameras; }
	void setCameras(vector<Camera*> vc) { cameras = vc; }

	Barco* getBarco() { return barco; }
	void setBarco(Barco* b) { barco = b; }

	Canon* getCanon() { return canon; }
	void setCanon(Canon* c) { canon = c; }

	void update(const double& dt) {

		try {

			for (Solid* ps : getSolids()) {
				ps->update(dt);
			}

			for (Boat* balsa : balsas) {
				//Condicion pierde vidas en caso de que los enemigos lleguen a la posicion del barco
				if (balsa->getPos().getZ() <= (barco->getPos().getZ() + 5)) {

					removableBoats.push_back(balsa);

					this->canon->disminuyeVida();
					//continue;
				}
			}
			
			for (Turuleta* turuleta : turuletas) {
				//borrado de las turuletas que se pierden en el abismo del oceano
				if (turuleta->getPos().getY() < -5) {
					removableTuruletas.push_back(turuleta);
				}
			}

			//Recorre cada instancia de bala y de enemigo
			for (Bullet* bala : canon->getBalas()) {

				bool balaBorrada = false;

				//Comprobacion de si la bala se va
				if (bala->getPos().getY() < -5) {
					removableBullets.push_back(bala);
					balaBorrada = true;
				}

				//Gestion choque bala-balsa
				for (Boat* balsa : balsas) {
					//Si hay colision retira la bala a una posicion que le decimos y ponemos a 0 la velocidad
					if (bala->checkColisionWithEnemy(balsa)) {

						removableBoats.push_back(balsa);
						if (!balaBorrada)
						removableBullets.push_back(bala);

						this->canon->sumaPuntos(1);
						continue;
					}
					
				}

				//Gestion choque bala-gallina
				for (Turuleta* turuleta : turuletas) {
					if (bala->checkColisionWithTuruleta(turuleta)) {

						removableTuruletas.push_back(turuleta);
						if (!balaBorrada)
						removableBullets.push_back(bala);

						this->canon->aumentaVida();
						continue;
					}
				}
				
			}

			//Actualizacion de datos
			actualizaInterfaz();

			try
			{
				eliminaBarcas();
				eliminaTuruletas();
				eliminaBalas();
				
			}
			catch (const std::exception& e)
			{
				cerr << e.what() << endl;
			}

			currentSecond++;

			if (currentSecond % 100 == 0) {
				generaBalsa(getRand(-13, 13));
			}
			if (currentSecond % 500 == 0) {
				generaGallina(getRand(-10, 10));
			}
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}
	}

	void render() {
		this->activeCamera->render();
		Composite::render();
	}

	void processKeyPressed(unsigned char key, int x, int y) {

		//Camara de juego 1
		if(key== '1')
			this->activeCamera = cameras[0];
			//break;
		//Camara de juego 2
		if (key == '2')
			this->activeCamera = cameras[1];
		//Camara de juego 3
		if ((key == '3') && (canon->getBalas().size()>0))
			this->activeCamera = cameras[2];
		//Acercar camara
		if (key == 'r')
			this->activeCamera->setPos(this->activeCamera->getPos() + Vector3D(0, 0, -0.5));
		//Alejar camara
		if (key == 'f')
			this->activeCamera->setPos(this->activeCamera->getPos() + Vector3D(0, 0, 0.5));

		canon->processKeyPressed(key, x, y);
	}

	void generaCamaras() {
		Camera* camera1 = new Camera(Vector3D(0.9, 3, 0.65));
		camera1->setRot(Vector3D(10, 180, 0));
		cameras.push_back(camera1);

		Camera* camera2 = new Camera(Vector3D(0, 0, 20));
		camera2->setRot(Vector3D(90, 180, 0));
		camera2->setPos(camera2->getPos() + Vector3D(0, 15, 25));
		cameras.push_back(camera2);

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
		puntos = new Text();
		puntos->setText("Puntos: ");
		puntos->setPos(Vector3D(-10, 15, 50));
		puntos->setColor(Vector3D(0, 0, 0));
		this->add(puntos);
		puntos->setText("Puntos: " + to_string(canon->getPuntos()));

		vidas = new Text();
		vidas->setText("Vidas: ");
		vidas->setPos(Vector3D(25, 15, 50));
		vidas->setColor(Vector3D(0, 0, 0));
		this->add(vidas);
		vidas->setText("Vidas: " + to_string(canon->getVidas()));
	}

	void generaBalsa(double xPos) {
		Boat* balsa;
		balsa = new Boat(4, 3, 7);
		balsa->setPos(Vector3D(xPos, 1, 50));
		balsa->setVel(Vector3D(0, 0, -1));
		this->add(balsa);
		balsas.push_back(balsa);//Añada el nuevo enemigo al array de enemigos totales en la escena
	}

	void generaGallina(double xPos) {
		Turuleta* turuleta;
		turuleta = new Turuleta(4, 3, 7);
		turuleta->setPos(Vector3D(xPos, 10, 15));
		turuleta->setVel(Vector3D(0, -0.1, 0));
		this->add(turuleta);
		turuletas.push_back(turuleta);//Añada el nuevo enemigo al array de enemigos totales en la escena
	}

	void actualizaInterfaz() {
		puntos->setText("Puntos: " + to_string(canon->getPuntos()));
		vidas->setText("Vidas: " + to_string(canon->getVidas()));
	}

	bool detectaDerrota() {
		if (this->canon->getVidas() < 1) {
			rank->leeFichero();
			rank->escribeFichero(canon->getPuntos());
			
			return true;
		}
		else {
			return false;
		}
	}

	void resetScene() {
		cameras[0]->setPos(Vector3D(0.9, 3, 0.65));
		cameras[1]->setPos(Vector3D(0, 15, 45));
		currentSecond = 0;
		canon->setPuntos(0);
		canon->setVidas(3);
		canon->resetCanon();

		for (Boat* balsa : balsas) {//se prepara el borrado de todas las balsas
			removableBoats.push_back(balsa);
		}
		eliminaBarcas();

		for (Turuleta* turuleta : turuletas) {//se prepara el borrado de todas las turuletas
			removableTuruletas.push_back(turuleta);
		}
		eliminaTuruletas();

		for (Bullet* bala : canon->getBalas()) {//se prepara el borrado de todas las balas
			removableBullets.push_back(bala);
		}
		eliminaBalas();
		
	}
	
	void eliminaBarcas() {
		for (Boat* balsa : removableBoats) {
			balsas.erase(std::remove(balsas.begin(), balsas.end(), balsa), balsas.end());
			this->remove(balsa);
		}
		removableBoats.clear();
	}

	void eliminaTuruletas() {
		for (Turuleta* turuleta : removableTuruletas) {
			turuletas.erase(std::remove(turuletas.begin(), turuletas.end(), turuleta), turuletas.end());
			this->remove(turuleta);
		}
		removableTuruletas.clear();
	}

	void eliminaBalas() {
		for (Bullet* bala : removableBullets) {
			canon->remove(bala);
			this->remove(bala);
		}
		removableBullets.clear();
	}

	inline double getRand(double min, double max) {
		static const int PRECISION = 10000;
		double n = max - min;
		int ir = rand() % PRECISION;
		double r = min + (double)ir / PRECISION * n;
		return r;
	}

	inline double getRand(double max = 1) { return getRand(0, max); }
};