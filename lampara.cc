#include "lampara.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
using namespace std;

	
Lampara::Lampara(){
	this->cuenco = new Objeto();
	this->estructura = new Objeto();
	this->base = new Objeto();
	this->foco = new Objeto();
	rotEstructura = 0;
	gradosX = 0.0;
	gradosZ = 0.0;
	gradosM = -100.0; 
	var=false;
	numdiv = 60; //numero divisiones
	velocidad = 1;
}

void Lampara::Cuenco(vector<float> &v, vector<int> &c){
	float xp;
	float yp;
	this->cuenco = new Objeto(v,c);
	this->cuenco->revolucion(360.0,numdiv);
	this->cuenco->color[0]=this->cuenco->color[1]=this->cuenco->color[2]=0.8;

	/**Ponemos a punto las coordenadas de los vertices para que esté inclinada*/
	for (int i=0;i<this->cuenco->nvertices;i++){
		xp	= cos(-90)*this->cuenco->vertices[i].x - sin(-90)*this->cuenco->vertices[i].y; 
		yp =  cos(-90)*this->cuenco->vertices[i].y + sin(-90)*this->cuenco->vertices[i].x;
		this->cuenco->vertices[i].x = xp;
		this->cuenco->vertices[i].y = yp;
	}

	for (int i=0;i<this->cuenco->nvertices;i++)
		this->cuenco->vertices[i].y+=4.0; //Subimos hacia arriba para que encaje
}
void Lampara::Estructura(vector<float> &v, vector<int> &c){
	float xp,yp; //x', y' variables auxliares
	this->estructura = new Objeto(v,c);
	estructura->revolucion(360.0,numdiv);
	this->estructura->color[0]=this->estructura->color[1]=this->estructura->color[2]=0.8;

	for (int i=0;i<this->estructura->nvertices;i++){
		xp	= cos(-35.0)*this->estructura->vertices[i].x - sin(-35.0)*this->estructura->vertices[i].y; 
		yp =  cos(-35.0)*this->estructura->vertices[i].y + sin(-35.0)*this->estructura->vertices[i].x;
		this->estructura->vertices[i].x = xp;
		this->estructura->vertices[i].y = yp;
	}

	for (int i=0;i<this->estructura->nvertices;i++)
		this->estructura->vertices[i].x+=0.3;
	
}
void Lampara::Base (vector<float> &v, vector<int> &c){
	this->base = new Objeto(v,c);
	base->revolucion(360.0,numdiv);
	this->base->color[0]=this->base->color[1]=this->base->color[2]=0.8;

	for (int i=0;i<this->base->nvertices;i++){
		this->base->vertices[i].x-=1.2;
		this->base->vertices[i].y-=0.5;
	}
}
void Lampara::Foco(vector<float> &v, vector<int> &c){
	float xp,yp; //x', y' variables auxliares
	this->foco = new Objeto(v,c);
	foco->revolucion(360.0,numdiv);
	foco->color[0]=foco->color[1]=1;
	foco->color[2]=0.8;


	//Aplicamos la misma rotacion que al cuenco
	for (int i=0;i<this->foco->nvertices;i++){
		xp	= cos(-90)*this->foco->vertices[i].x - sin(-90)*this->foco->vertices[i].y; 
		yp =  cos(-90)*this->foco->vertices[i].y + sin(-90)*this->foco->vertices[i].x;
		this->foco->vertices[i].x = xp;
		this->foco->vertices[i].y = yp;
	}

	for (int i=0;i<this->foco->nvertices;i++)
		this->foco->vertices[i].y+=4.0;
}
void Lampara::pintarPuntos(){
	this->cuenco->draw_vertices();
	this->estructura->draw_vertices();
	this->base->draw_vertices();
	this->foco->draw_vertices();
}

void Lampara::pintarSolido(){
	this->cuenco->draw_solido();
	this->estructura->draw_solido();
	this->base->draw_solido();
	this->foco->draw_solido();
}

void Lampara::pintarAjedrez(){
	this->cuenco->draw_ajedrez();
	this->estructura->draw_ajedrez();
	this->base->draw_ajedrez();
	this->foco->draw_ajedrez();
}

void Lampara::pintarLineas(){
	this->cuenco->draw_lineas();
	this->estructura->draw_lineas();
	this->base->draw_lineas();
	this->foco->draw_lineas();
}

void Lampara::pintarNormalesCaras(){
	pintarLineas();
	this->cuenco->pintarNormalesCaras();
	this->estructura->pintarNormalesCaras();
	this->base->pintarNormalesCaras();
}

void Lampara::pintarNormalesVertices(){
	pintarLineas();
	this->cuenco->pintarNormalesVertices();
	this->estructura->pintarNormalesVertices();
	this->base->pintarNormalesVertices();
}


void Lampara::agitarLampara(){
	//Mesa
	glBegin(GL_QUADS);
	glColor3f(0.5,0.2,0);
    glVertex3f( 8,-10,8);
    glVertex3f(8,-10,-8 );
    glVertex3f( -8,-10,-8 );
    glVertex3f(-8,-10,8);
    glEnd();
	/*Hacemos tope de grados para que giren
	dcha a izquierda y un pequeño semaforo*/
	if (gradosX < 40 && var==false){
		gradosX+=velocidad;
	}
	else if (gradosX > -40){
		var=true;
		gradosX-=velocidad;
	}
	else var = false;
	if (gradosZ < 20 && var2==false)
		gradosZ+=velocidad;
	else if (gradosZ > 0){
		var2=true;
		gradosZ-=velocidad;
	}
	else
		var2=false;
	base->draw_solido();
	estructura->draw_solido();
	glRotatef(gradosX,0,1,0);
	glRotatef(gradosZ,0,0,1);
	cuenco->draw_solido();
	foco->draw_solido();
	glutPostRedisplay();
	
}

void Lampara::moverLampara(){
	//Mesa
	glBegin(GL_QUADS);
	glColor3f(0.5,0.2,0);
    glVertex3f( 8,-10,8);
    glVertex3f(8,-10,-8 );
    glVertex3f( -8,-10,-8 );
    glVertex3f(-8,-10,8);
    glEnd();
	if (gradosX < 45 && var==false){
		gradosX+=velocidad;
	}
	else if (gradosX > -45){
		var=true;
		gradosX-=velocidad;
	}
	else var = false;
	
	base->draw_solido();
	estructura->draw_solido();
	glRotatef(gradosX,0,1,0);
	cuenco->draw_solido();
	foco->draw_solido();
	glutPostRedisplay();
	
}

void Lampara::girarLampara(){ //Misma funcion anterior, solo que giramos sobre y 180 grados
	//Mesa
	glBegin(GL_QUADS);
	glColor3f(0.5,0.2,0);
    glVertex3f( 8,-10,8);
    glVertex3f(8,-10,-8 );
    glVertex3f( -8,-10,-8 );
    glVertex3f(-8,-10,8);
    glEnd();
	/*Rotaremos de -30 a 30 grados*/
	if (gradosZ < 20 && var==false)
		gradosZ+=velocidad;
	else if (gradosZ > 0) {
		var=true;
		gradosZ-=velocidad;
	}
	else //Cuando complete el giro volver al principio
		var=false;

	/*Preparamos el objeto a pintar*/
	
	base->draw_solido();
	estructura->draw_solido();
	
	/*Modificamos la rotacion de la lampara*/
	glRotatef(gradosZ,0,0,1);
	foco->draw_solido();
	cuenco->draw_solido();

	glutPostRedisplay();
}

void Lampara::saltar(){
	//Mesa
	if (gradosZ < 20 && var==false)
		gradosZ+=velocidad;
	else if (gradosZ > 0) {
		var=true;
		gradosZ-=velocidad;
	}
	else //Cuando complete el giro volver al principio
		var=false;

	/*Preparamos el objeto a pintar*/
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0,gradosZ/2,0);
	/*Modificamos la rotacion de la lampara*/
	glRotatef(gradosZ,0,0,1);
	base->draw_solido();
	glPopMatrix();
	glTranslatef(0,gradosZ/2,0);
	glRotatef(-gradosZ,0,0,1);	
	glTranslatef(-0.8,0,0); //Arreglamos para que no se vean huecos
	foco->draw_solido();
	cuenco->draw_solido();
	glPopMatrix();
	glTranslatef(0,gradosZ/2,0);
	glRotatef(gradosZ,0,0,1);
	estructura->draw_solido();
	//glutPostRedisplay();
}

void Lampara::saltarCirculos(){
	glBegin(GL_QUADS);
	glColor3f(0.5,0.2,0);
    glVertex3f( 100,-10,100);
    glVertex3f(100,-10,-100 );
    glVertex3f( -100,-10,-100 );
    glVertex3f(-100,-10,100);
    glEnd();
	if (gradosM < 100){
		gradosM+=velocidad;
		glTranslatef(gradosM,0,0);
	saltar();
	}
	else{
		gradosM=-100;
	}
	glutPostRedisplay();
}
