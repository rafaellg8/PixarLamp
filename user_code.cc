//**************************************************************************
// Práctica 2
//
// Rafael Lachica Garrido 2014/15
//
// IG
//**************************************************************************
#include "user_code.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

//*********************************************
//CONSTRUCTOR OBJETOS
//*********************************************
Objeto::Objeto()
{};

Objeto::Objeto(vector<float> &Vertices,vector<int> &Caras){
	ncaras = Caras.size();
	vertices.resize(Vertices.size()/3);
	int j=0;
	for (int i=0;i<Vertices.size();i+=3)
	{
		vertices[j].x=Vertices[i];
		vertices[j].y=Vertices[i+1];
		vertices[j].z=Vertices[i+2];
		j++;

	}

	caras.resize(Caras.size());
	for (int i=0;i<Caras.size();i++){
		caras[i]=Caras[i];
	}
	nvertices=Vertices.size()/3;

}


//*********************************************
//CONSTRUCTOR OBJETOS
//*********************************************
Objeto::Objeto(vector<float> &Vertices){
	ncaras = Vertices.size()*2;
	vertices.resize(Vertices.size()/3);
	int j=0;
	for (int i=0;i<Vertices.size();i+=3)
	{
		vertices[j].x=Vertices[i];
		vertices[j].y=Vertices[i+1];
		vertices[j].z=Vertices[i+2];
		j++;

	}
	nvertices=vertices.size()/3;
	caras.resize(0);
}

//***************************************************************************
// Funciones DIBUJOS
//***************************************************************************

void Objeto::draw_vertices()
{
	glColor3f(this->color[0],this->color[1],this->color[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPointSize(5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&(this->vertices[0]));
	glDrawArrays(GL_POINTS,0,this->nvertices);
		
}


void Objeto::draw_lineas()
{
	glColor3f(this->color[0],this->color[1],this->color[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPointSize(2);
	for (int i=0;i<this->caras.size();i+=3){
	glBegin(GL_LINE_LOOP);
		glVertex3f(this->vertices[this->caras[i]].x,this->vertices[this->caras[i]].y,this->vertices[this->caras[i]].z);
		glVertex3f(this->vertices[this->caras[i+1]].x,this->vertices[this->caras[i+1]].y,this->vertices[this->caras[i+1]].z);
		glVertex3f(this->vertices[this->caras[i+2]].x,this->vertices[this->caras[i+2]].y,this->vertices[this->caras[i+2]].z);	
        glEnd();
     }
}

void Objeto::draw_solido()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(this->color[0],this->color[1],this->color[2]);
	glBegin(GL_TRIANGLES);
	for (int i=0;i<this->caras.size();i++){
		glVertex3f(this->vertices[this->caras[i]].x,this->vertices[this->caras[i]].y,this->vertices[this->caras[i]].z);
	}	
	glEnd();
	
	
}

void Objeto::draw_ajedrez()
{
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_FLAT); //Pintar plano sin gradientes color
	glBegin(GL_TRIANGLES);
	for (int i=0;i<this->caras.size();i++){
		if (i%2==0)
				glColor3f(this->color[0],this->color[1],this->color[2]);
 		else 
 					glColor3f(2*this->color[3],this->color[0],this->color[1]);	
		glVertex3f(this->vertices[this->caras[i]].x,this->vertices[this->caras[i]].y,this->vertices[this->caras[i]].z); //Segundo color aleatorio
	}
	glEnd();
	
}
void Objeto::pintarNormalesCaras()
{
	glPointSize(5);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for(int i = 0; i<Normales.size(); i++){
        glVertex3f((centroCara[i].x+Normales[i].x), //Sumamos los vertices con las normales
                    (centroCara[i].y+Normales[i].y), 
                    (centroCara[i].z+Normales[i].z));
        glVertex3f(centroCara[i].x,centroCara[i].y,centroCara[i].z);
    }
    glEnd();
		
}

void Objeto::pintarNormalesVertices(){
	glPointSize(5);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	for(int i = 0; i<NorVert.size(); i++){
        glVertex3f( (vertices[i].x+NorVert[i].x), //Sumamos los vertices con las normales
                    (vertices[i].y+NorVert[i].y), 
                    (vertices[i].z+NorVert[i].z));
        glVertex3f( vertices[i].x, 
                    vertices[i].y, 
                    vertices[i].z);
    }
    glEnd();
}


/************************************
FUNCIONES MODELOR OBJETO REVOLUCION
************************************/

float Objeto::convRad(double angle){
	return (angle*(M_PI/180));
}

void Objeto::revolucion(float grados,int nd){
	int ndivid=nd;
	//grados = 100;
	float limgrados=grados/ndivid;
	

	float x,y,z=0.0;
	int npuntos = nvertices;

	for (int i=0;i<ndivid;i++){
		for (int j=0;j<npuntos;j++){
			x=(fabs(vertices[j].x)*cos(convRad(limgrados*i)));
			y=vertices[j].y;
			z=(fabs(vertices[j].x)*sin(convRad(limgrados*i)));
		
			if (z<0.0)
				z=z+(2*fabs(z));
			else if (z>0.0)
				z=z-(2*fabs(z));

			//guardamos el punto
			this->vertices.push_back({x,y,z});
		}

	}
	this->nvertices=vertices.size();

	caras.resize(0);


/**ALGORITMO CARAS**/
	
	generaCaras(npuntos,ndivid,grados); //llamamaos a generar las caras
	puntosTapas (npuntos); //obtenemos los puntos de las tapas
	generaTapas(npuntos,ndivid,360.0); //generamos las caras de las tapas
}

void Objeto::generaCaras(int npuntos,int ndivid,float grados){
	int n;
	if (grados==360){ //Controlamos que pueda pintar solo una parte de la figura ej: 3/4 bien pintados
		n=nvertices;
	}
	else{
	n = ndivid*npuntos;
	}

	for (int i=0;i<n;i++){
			if ((i+1)%npuntos!=0){ //Comprobamos que no se salga de las tapas de arriba
			//Asignar en triangulos las caras
			caras.push_back(i);caras.push_back(i+1);caras.push_back((i+npuntos)%nvertices); //Cara A del cuadrado AB
			caras.push_back(i+1);caras.push_back((i+1+npuntos)%nvertices);caras.push_back((i+npuntos)%nvertices);
		}
	}
			
}

void  Objeto::puntosTapas(int npuntos){
	puntos t; // Punto donde está la tapa abajo
	puntos T; //Punto donde está la tapa de arriba

	t = vertices[0]; //Almacenamos los puntos
	T = vertices[npuntos-1];

	//Dejamos solo los puntos sobre el eje Y	
	t.x = 0; t.z=0;
	T.x = 0; T.z=0;T.y=(vertices[npuntos-1].y+0.10); //Subimos un poco para redondear la punta

	vertices.push_back(t); //Penúltima posicion del vector, t
	vertices.push_back(T); //Ultima posicion del T

	this->nvertices=vertices.size(); //Actualizamos la cara
}

void Objeto::generaTapas(int npuntos,int ndivid,float grados) {
	/************************
	Tapa Abajo
	*************************/
	for (int i=0;i<ndivid;i++){
		caras.push_back(i*npuntos);
		caras.push_back(nvertices-2);
		caras.push_back(((i+1))*npuntos);
	}

	//Ultima cara
	if (grados==360){ caras.push_back(ndivid* npuntos);
	 caras.push_back(nvertices-2);
	 caras.push_back(0);}
	
	 /***********************
	 Tapa Arriba
	 ************************/

	 for (int i=npuntos-1;i<npuntos*(ndivid);i+=npuntos){
	 	caras.push_back(i);
	 	caras.push_back((i+npuntos));
	 	caras.push_back(nvertices-1);
	 }

	 //Ultima cara
	 if (grados==360){
	 caras.push_back(nvertices-3);
	 caras.push_back(npuntos-1);
	 caras.push_back(nvertices-1);
	}
}

/**++++++++++++++++++++++++
FUNCIONES NORMALES
+++++++++++++++++++++++++++*/
void Objeto::normalesCaras(){
	puntos vectorP;
	puntos vectorQ;
// producto Vector producto vectorial.
	puntos producto;
	float modulo;
	float X,Y,Z; //Variables auxiliares centro x, y z en una cara

	//P vector formado por las vertices A,B o 1,2
	for(int i=0; i<caras.size(); i+=3){
		vectorP.x=vertices[caras[i+1]].x - vertices[caras[i]].x;
    	vectorP.y=vertices[caras[i+1]].y - vertices[caras[i]].y;
   		vectorP.z=vertices[caras[i+1]].z - vertices[caras[i]].z;

   		vectorQ.x=vertices[caras[i+2]].x-vertices[caras[i]].x;
    	vectorQ.y=vertices[caras[i+2]].y-vertices[caras[i]].y;
    	vectorQ.z=vertices[caras[i+2]].z-vertices[caras[i]].z;

    	 //Una vez obtenidos ambos vectores realizamos el producto vectorial entre ellos.
    	producto.x=( (vectorP.y*vectorQ.z) - (vectorP.z*vectorQ.y) );
    	producto.y=( (vectorP.z*vectorQ.x) - (vectorP.x*vectorQ.z) );
    	producto.z=( (vectorP.x*vectorQ.y) - (vectorP.y*vectorQ.x) );
	
    	modulo=sqrtf( (producto.x*producto.x) + (producto.y*producto.y) + (producto.z*producto.z) );
	
    	 //Normalización de n
    producto.x=(producto.x/modulo); //Para que se aleje de la cara
    producto.y=(producto.y/modulo);
    producto.z=(producto.z/modulo);
    
    Normales.push_back({producto.x,producto.y,producto.z});

    //Punto central de la cara
    X = (vertices[caras[i]].x + vertices[caras[i+1]].x + vertices[caras[i+2]].x)/3;
    Y = (vertices[caras[i]].y + vertices[caras[i+1]].y + vertices[caras[i+2]].y)/3;
    Z = (vertices[caras[i]].z + vertices[caras[i+1]].z + vertices[caras[i+2]].z)/3; 

    //Metemos punto central en el vector
    centroCara.push_back({X,Y,Z});
	}
}

void Objeto::normalesVertices(){
	float mod;
	float Nx,Ny,Nz;
	
	for (int i=0;i<nvertices;i++){
		Nx=Ny=Nz=0;
		for (int j=0;j<ncaras;j++){
			if (caras[j] == i || caras[j+1] == i || caras[j+2] == i){
				Nx += Normales[j].x; //Calculamos las normales vertices cada cara
				Ny += Normales[j].y;
				Nz += Normales[j].z;
			}
		}
		mod = sqrtf(Nx*Nx + Ny*Ny + Nz*Nz);
		Nx /= mod;
		Ny /= mod;
		Nz /= mod;

		NorVert.push_back({Nx,Ny,Nz});
	}
}