//**************************************************************************
// Práctica 2
//
// Rafael Lachica Garrido 2014/15
//
// IG
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include <cmath>
using namespace std;
struct puntos {
  	float x;
	float y;
	float z;
};

class Objeto {
public:
	vector<puntos> vertices; //Vertices del objeto
	vector<puntos> Normales; //Normales a las caras
	vector<puntos> NorVert; //Normales a los verties
	vector<puntos> centroCara; //Guarda el punto central de la cara
	/*Vector de caras del objeto cara (1,2,3) --> Cara 1 contiene vertices[1].xyz vertices[2].xyz vertices[3].xyz coordenadas caras*/
	vector<int> caras;		
	int ncaras;
	int nvertices;
	float color [3];

	Objeto(); 	//Constructor por defecto

	Objeto(vector<float> &Vertices,vector<int> & Caras);

	Objeto(vector<puntos> &Vertices,vector<int> & Caras);

	Objeto(vector<float> &Vertices);

	void draw_cube();

	void draw_vertices();

	void draw_lineas();

	void draw_solido();

	void draw_ajedrez();

	void revolucion(float grados,int nd); //numero grados y numero divisiones

	void generaCaras(int npuntos,int ndivid,float grados);

	float convRad(double angle);

	void puntosTapas(int npuntos);

	void generaTapas(int npuntos,int ndivid,float grados);

	void normalesCaras();

	void normalesVertices();

	void pintarNormalesCaras();	

	void pintarNormalesVertices();


};