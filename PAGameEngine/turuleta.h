#pragma once
#include "model_mesh_triangles.h"
#include "loader_obj.h"

class Turuleta : public ModelMeshTriangles {
	ModelMeshTriangles* turuleta;
	double width;
	double lenght;
public:
	Turuleta(double xPos, double yPos, double zPos) :ModelMeshTriangles() {

		LoaderOBJ lobj2(0.05);
		turuleta = new ModelMeshTriangles();
		lobj2.loadModel("TuruletaParachute.obj");
		*turuleta = lobj2.getModelMeshTriangles();
		this->setSolids(turuleta->getTriangles());

		this->setColor(Vector3D(1, 1, 0));
		this->setRot(Vector3D(-90, 0, 180));

		this->setWidth(3);
		this->setLenght(3);
	}

	void setWidth(double w) { width = w; }
	void setLenght(double l) { lenght = l; }
	double getWidth() { return width; }
	double getLenght() { return lenght; }
};