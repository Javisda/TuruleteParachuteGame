#pragma once
#include "sphere.h"
#include "Math.h"
#include "balsa.h"
#include "turuleta.h"

class Bullet : public Sphere {
	double bulletSize = 0.08;
	Vector3D desfase = Vector3D(0.018, 0.12, 0.4);

	Vector3D aimsToBullet;
	double v0;
	double v0x;
	double v0z;
	double v0y;
	double g;

	double x = 0, y = 0, z = 0;
	double t;

	Vector3D posi;

	double width, lenght;
public:
	//Constructor que inicializa las fisicas y la posicion y direccion que tomará la bala al ser instanciada
	Bullet(Vector3D a, Vector3D p) {
		this->setSize(bulletSize);
		this->setPos(p + this->getDesfase());
		aimsToBullet = a;
		posi = this->getPos();
		v0 = 20.0;
		v0x = v0 * sin(aimsToBullet.getX());
		v0z = v0 * cos(aimsToBullet.getY());
		v0y = v0 * sin(aimsToBullet.getY());
		g = 9.8;
		t = 0;
	}

	double getBulletSize() { return bulletSize; }
	void setBulletSize(double b) { bulletSize = b; }

	Vector3D getDesfase() { return desfase; }
	void setDesfase(Vector3D v) { desfase = v; }

	void setWidth(double w) { width = w; }
	void setLenght(double l) { lenght = l; }
	double getWidth() { return width; }
	double getLenght() { return lenght; }

	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }

	//Actualiza el movimiento de la bala con las ecuaciones del movimiento parabólico
	void update(double time) {
		t += 0.02;
		x = (v0x * t);
		z = (v0z * t);
		y = ((v0y * t) - (g / 2) * pow(t, 2));
		this->setPos(Vector3D(x + posi.getX(), y + posi.getY(), z + posi.getZ()));
	}

	//Deteccion de colision con balsas
	bool checkColisionWithEnemy(Boat* enemy) {
		if (this->getPos().distance(enemy->getPos()) < (this->getWidth() + enemy->getWidth()) / 2 || this->getPos().distance(enemy->getPos()) < (this->getLenght() + enemy->getLenght()) / 2) {
			return true;
		}
		return false;
	}

	//Deteccion de colision con turuletas
	bool checkColisionWithTuruleta(Turuleta* turuleta) {
		if (this->getPos().distance(turuleta->getPos()) < (this->getWidth() + turuleta->getWidth()) / 2 || this->getPos().distance(turuleta->getPos()) < (this->getLenght() + turuleta->getLenght()) / 2) {
			return true;
		}
		return false;
	}

};