//**************************************************************************
// Práctica 2
//
// Rafael Lachica Garrido
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "lampara.h"
#include "file_ply_stl.h"
#include <iostream>
using namespace std;

//variables globales y la clase OBJETO

Objeto * obj;
Lampara * lamp;
    
// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0); //Muestre de frente
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

 
/******************************************************
Sobrecarga de la funcion dibujar_tipo axiliares que llaman a la de la clase
*******************************************************/
void draw_puntos (){
    clear_window();
    change_observer();
    draw_axis();
    lamp->pintarPuntos();
    glutSwapBuffers();
}


void draw_lineas (){
    clear_window();
    change_observer();
    draw_axis();
   lamp->pintarLineas();
    glutSwapBuffers();
}


void draw_solido (){
    clear_window();
    change_observer();
   lamp->pintarSolido();
    glutSwapBuffers();
}


void draw_ajedrez (){
    clear_window();
    change_observer();
   draw_axis();
    lamp->pintarAjedrez();
    glutSwapBuffers();
}

void draw_normales (){
    clear_window();
    change_observer();
    draw_axis();
    lamp->pintarLineas();
    lamp->pintarNormalesVertices ();
    lamp->pintarNormalesCaras ();
    glutSwapBuffers();
}


void agitarLampara(){
    clear_window();
    change_observer();
    lamp->agitarLampara();
    glutSwapBuffers();
}

void girarLampara(){
    clear_window();
    change_observer();
    lamp->girarLampara();
    glutSwapBuffers();
}

//Funcion que rota la lampara
void moverLampara(){
clear_window();
change_observer();
lamp->moverLampara();
glutSwapBuffers();
}

void saltarCirculos(){
clear_window();
change_observer();
lamp->saltarCirculos();
glutSwapBuffers();
}
//**************************************************************************
//Funcion Dibujar Escena
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
lamp->pintarPuntos();
glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
//0 puntos 1 lineas 2 solido 3 ajedrez
if (toupper(Tecla1)=='Q') exit(0);

switch (toupper(Tecla1)){
        case '1':
            glutDisplayFunc(draw_ajedrez);
        break;
        case '2':
            glutDisplayFunc(draw_solido); 
        break;
        case '3':
            glutDisplayFunc(draw_lineas); 
        break;
        case '4':
            glutDisplayFunc(draw_puntos); 
            break;
        case '5':
            glutDisplayFunc(draw_normales);
            break;
            case 'A':
            glutDisplayFunc(moverLampara);
            break;
            case 'S':
            glutDisplayFunc(girarLampara);
            break;
            case 'D':
            glutDisplayFunc(agitarLampara);
            break;
            case 'F':
            glutDisplayFunc(saltarCirculos);
            break;
            case '+':
                lamp->velocidad*=2;
            break;
            case '-':
                lamp->velocidad/=2;
            break;
        clear_window();

    }
    glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
    case GLUT_KEY_LEFT:Observer_angle_y--;break;
    case GLUT_KEY_RIGHT:Observer_angle_y++;break;
    case GLUT_KEY_UP:Observer_angle_x--;break;
    case GLUT_KEY_DOWN:Observer_angle_x++;break;
    case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
    case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    }
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=50*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana (r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

glClearColor(0.2,0.5,0.9,1); 
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

    vector<float> vertices;
    vector<int> caras;
    float color[3];
    
    
         _file_ply * p = new _file_ply();
    p->open("lamp.ply");
    p->read(vertices,caras); 

    obj= new Objeto(vertices,caras); //Creamos objeto   
        obj->revolucion(360,10);
    
    lamp = new Lampara();
    lamp->Cuenco(vertices,caras);

     p->open("estructura.ply");
    p->read(vertices,caras); 
    lamp->Estructura(vertices,caras);

     p->open("base.ply");
    p->read(vertices,caras); 
    lamp->Base(vertices,caras);

    p->open("foco.ply");
    p->read(vertices,caras);
    lamp->Foco(vertices,caras);

    lamp->cuenco->normalesCaras();
    lamp->base->normalesCaras();
    lamp->estructura->normalesCaras();
    lamp->cuenco->normalesVertices();
    lamp->base->normalesVertices();
    lamp->estructura->normalesVertices();

   
    glutInit(&argc, argv);


    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-UI_window_width)*0.5,
                       (glutGet(GLUT_SCREEN_HEIGHT)-UI_window_height)*0.8);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 2 RLG");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
