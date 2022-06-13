#pragma once
#include "model_mesh_triangles.h"
#include "loader_obj.h"

class Boat : public ModelMeshTriangles {
    ModelMeshTriangles* enemigo;
    double width;
    double lenght;
public:
    //Constructor que inicializa una balsa con un modelo predeterminado
    Boat(double xPos, double yPos, double zPos) :ModelMeshTriangles() {

        LoaderOBJ lobj(0.1);
        enemigo = new ModelMeshTriangles();
        lobj.loadModel("Balsa.obj");
        *enemigo = lobj.getModelMeshTriangles();
        this->setSolids(enemigo->getTriangles());
        this->setColor(Vector3D(1, 0, 1));
        this->setPos(Vector3D(xPos, yPos, zPos));
        this->setRot(Vector3D(270, 0, 0));
        this->setWidth(2);
        this->setLenght(2);
    }


    void setWidth(double w) { width = w; }
    void setLenght(double l) { lenght = l; }
    double getWidth() { return width; }
    double getLenght() { return lenght; }

};