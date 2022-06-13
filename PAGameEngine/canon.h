#pragma once
#include "model_mesh_triangles.h"
#include "loader_obj.h"
#include "bullet.h"
#include "sceneV2.h"

class Canon : public ModelMeshTriangles {
	ModelMeshTriangles* canon;
	Vector3D desfase = Vector3D(-0.85, -2.55, 1.2); //Vector que almacena el ajuste de posicion cañon/barco.
	Vector3D aimsTo;
	vector<Bullet*> balas;

	SceneV2* scene;

	int puntos;
	int vidas;
	bool estado;
public:
	//El cañon se comporta como un jugador, por ello tiene las variables de vidas, puntos y el estado vivo/muerto
	//Contructor cañon/jugador
	Canon() {
		LoaderOBJ lobj(0.5);
		canon = new ModelMeshTriangles();
		lobj.loadModel("Canon.obj");
		*canon = lobj.getModelMeshTriangles();
		this->setSolids(canon->getTriangles());

		this->setColor(Vector3D(0, 1, 0));
		this->setVel(Vector3D(0, 0, 0));
		this->setRot(Vector3D(-90, 0, 0));
		aimsTo = Vector3D(0, 0.2, 1);

		//Inicializa las variables principales de juego
		setVidas(3);
		setPuntos(0);
		setEstado(true); //Vivo
	}

	Vector3D getDesfase() { return desfase; }
	void setDesfase(Vector3D v) { desfase = v; }

	Vector3D getAimsTo() { return aimsTo; }
	void setAimsTo(Vector3D v) { aimsTo = v; }

	vector<Bullet*> getBalas() { return balas; }
	void setBalas(vector<Bullet*> b) {balas = b;}

	SceneV2* getScene() { return scene; }
	void setScene(SceneV2* s) { scene = s; }

	void setPuntos(int p) { puntos = p; }
	void setVidas(int v) { vidas = v; }
	void setEstado(bool e) { estado = e; }

	int getPuntos() { return puntos; }
	int getVidas() { return vidas; }
	bool getEstado() { return estado; }

	//Crea una instancia de bala y esta es disparada del cañon
	Bullet* disparaBala() {
		Bullet* bala;
		bala = new Bullet(aimsTo, this->getPos());
		bala->setWidth(0.5);
		bala->setLenght(0.5);
		bala->setColor(Vector3D(0, 0, 0));
		bala->setVel(Vector3D(sin(aimsTo.getX()), aimsTo.getY(), cos(aimsTo.getZ())));
		balas.push_back(bala);//Añade la bala a las demás que se vayan creando
		return bala;
	}

	//Metodos de control de juego
	void disminuyeVida() {
		if (vidas == 1) {
			estado = false;
		}
		vidas--;
	}
	void aumentaVida() {
		if (vidas < 5) { //Habrá un maximo de 5 vidas
			vidas++;
		}
	}
	void sumaPuntos(int p) {
		puntos += p;
	}


	void processKeyPressed(unsigned char key, int x, int y) {

		if (key == 'w' || key == 'W') { //Control de giro de cañon respecto al eje z
			if (this->getRot().getX() + 90 >= (-6 * 5)) {
				this->setRot(getRot() + Vector3D(-5, 0, 0));
				this->setAimsTo(this->getAimsTo() + Vector3D(0, 0.0872665, 0));
			}
		}
			
		if (key == 's' || key == 'S') { //Control de giro de cañon respecto al eje z
			if (this->getRot().getX() + 90 <= (6 * 5)) {
				this->setRot(this->getRot() + Vector3D(5, 0, 0));
				this->setAimsTo(this->getAimsTo() + Vector3D(0, -0.0872665, 0));
			}
		}
			
		if (key == 'a' || key == 'A') { //Control de giro de cañon respecto al eje y
			if (this->getRot().getZ() <= (15 * 5)) {
				this->setRot(this->getRot() + Vector3D(0, 0, 5));
				this->setAimsTo(this->getAimsTo() + Vector3D(0.0872665, 0, 0.0872665));
			}
		}
			
		if (key == 'd' || key == 'D') { //Control de giro de cañon respecto al eje y
			if (this->getRot().getZ() >= (-15 * 5)) {
				this->setRot(this->getRot() + Vector3D(0, 0, -5));
				this->setAimsTo(this->getAimsTo() + Vector3D(-0.0872665, 0, -0.0872665));
			}
		}
		
		//Disparo del cañon
		if(key == ' '){
			this->scene->add(disparaBala());
		}
	}

	//Pone el cañon a su posicion de inicio (apuntando al frente).
	void resetCanon() {
		this->setRot(Vector3D(-90, 0, 0));
		aimsTo = Vector3D(0, 0.2, 1);
	}

	//Borrado de bala
	void remove(Bullet* b) {

		try {
			balas.erase(std::remove(balas.begin(), balas.end(), b), balas.end());
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}
		
	}
};