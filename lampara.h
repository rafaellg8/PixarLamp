#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "user_code.h"
using namespace std;

class Lampara : public Objeto 
{
public:
	Objeto * cuenco;
	Objeto * estructura;
	Objeto * base;
	Objeto * lampara;
	Objeto * foco;
	int rotEstructura; //Grados rota estructura
	float gradosX;  //Grados de la lampara iniciales
	float gradosZ;
	float gradosM;
	bool var;		//Variable auxiliar
	bool var2;
	int numdiv; //Numero de divisiones
	float velocidad; //Variable controla velocidad animacion
	Lampara();
	void Cuenco(vector<float> &v, vector<int> &c);
	void Estructura(vector<float> &v, vector<int> &c);
	void Base (vector<float> &v, vector<int> &c);
	void Foco (vector<float> &v, vector<int> &c);
	void pintarPuntos();
	void pintarSolido();
	void pintarAjedrez();
	void pintarLineas();
	void pintarNormalesVertices();
	void pintarNormalesCaras();
	void moverLampara();
	void girarLampara();
	void agitarLampara();
	void saltar(); //Mueve estructura y el cuenco hacia delante y hacia atras
	/*Estas 4 funciones lo que hacen es ajustar la figura para que encaje perfectamente*/
	void setSolido();
	void setAjedrez();
	void setLineas();
	void setPuntos();

	void saltarCirculos();
};