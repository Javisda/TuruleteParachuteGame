#pragma once
#include "model_mesh_triangles.h"
#include "loader_obj.h"

class Barco : public ModelMeshTriangles {
	ModelMeshTriangles* barco;
public:
	//Constructor que inicializa un barco con un modelo predeterminado
	Barco() {
		LoaderOBJ lobj(0.5);
		this->barco = new ModelMeshTriangles();
		lobj.loadModel("Barco.obj");
		*barco = lobj.getModelMeshTriangles();
		this->setSolids(this->barco->getTriangles());

		this->barco->setColor(Vector3D(0.5, 0.25, 0));
		this->barco->setPos(Vector3D(0, 5, 0));
		this->barco->setVel(Vector3D(0, 0, 0));
		this->barco->setRot(Vector3D(-90, 0, 0));
	}

};
