#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include "kdtree.h"
#include "kdtree.cpp"
#include <fstream>
#include <string>
#include <vector>
#define KEY_ESC 27

using namespace std;

int mx = 0;
int my = 0;

float ax = 0.0;
float ay = 0.0;
float speed = 0.1;

KDTree<double, 3> *tree;

void t1()
{
	ifstream fe("cc.txt");
	ofstream fs("cc1.txt");
	string cadena;
	int cont = 0,ini,mid,fin;
	bool i1, i2, i3;
	while (!fe.eof())
	{
		getline(fe,cadena);
		i1 = i2 = i3 = true;
		for (unsigned i = 0; i<cadena.size(); i++)
		{
			if (cadena[i] == ',')
				cont++;
			if (cont == 2 and i1)
			{
				ini = i;
				i1 = false;
			}
			if (cont == 3 and i2)
			{
				mid = i;
				i2 = false;
			}
			if (cont == 4 and i3)
			{
				fin = i;
				i3 = false;
			}
		}
		string gg;
		cout << ini << " " << mid << " " << fin << endl; 
		gg = cadena.substr(ini + 1, mid-ini-1) + " " + cadena.substr(mid + 1, fin - mid - 1);
		cout << gg << endl;
		cont=0;
		fs << gg << endl;

	}
	fe.close();
	fs.close();
}

vector<Point<double>> points;
vector<Point<double>> limits;

void t2()
{
	ifstream fe("cc1.txt");
	double cx,cy;

	while (!fe.eof())
	{
		fe >> cx >> cy;
		Point<double> temp(cx, cy);
		points.push_back(temp);
	}
	fe.close();
}
void t3()
{
	ifstream fe("bunnyCoords.txt");
	double cx, cy, cz;

	while (!fe.eof())
	{
		fe >> cx >> cy >> cz;
		cx *= 80; cy *= 80; cz *= 80;
		Point<double> temp(cx, cy, cz);
		points.push_back(temp);
		//tree->insert(temp);
	}
	fe.close();
}

void t4()
{
	ifstream fe("tyraCoords2.txt");
	double cx, cy, cz;

	while (!fe.eof())
	{
		fe >> cx >> cy >> cz;
		cx *= 80; cy *= 80; cz *= 80;
		Point<double> temp(cx, cy, cz);
		points.push_back(temp);
		//tree->insert(temp);
	}
	fe.close();
}

void t5()
{
	ifstream fe("dragon.txt");
	double cx, cy, cz;

	while (!fe.eof())
	{
		fe >> cx >> cy >> cz;
		cx *= 500; cy *= 500; cz *= 500;
		Point<double> temp(cx, cy, cz);
		points.push_back(temp);
		//tree->insert(temp);
	}
	fe.close();
}



//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex3d(-30, 0, 0);
	glVertex3d(30, 0, 0);
	glColor3d(0, 255, 0);
	glVertex3d(0, -30, 0);
	glVertex3d(0, 30, 0);
	glColor3d(0, 0, 255);
	glVertex3d(0, 0, -30);
	glVertex3d(0, 0, 30);
	glEnd();
}

bool r = false;

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x;
		my = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		r = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		r = false;
	}
}

void OnMouseMotion(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;

	mx = x;
	my = y;

	ax += dx * speed;
	ay += dy * speed;
}



void idle() { // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 500.0);

	glTranslatef(0, 0, -100.0);
	glRotatef(ax, 0, 1, 0);
	glRotatef(ay, 1, 0, 0);
	glScaled(0.3, 0.3, 0.3);

	//displayGizmo();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glutSolidTeapot(7);

	glTranslatef(20, 20, 0);
	//glutSolidCube(10);
	//dibujar quadTree (qt->draw())
	tree->draw3d(tree->kdt_root, limits, 0);
	/*glBegin(GL_POINTS);
	for()
		glVertex2f(v.at(i)[0],v.at(i)[1])
	glEnd();*/
	//dibuja el gizmo

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glEnable(GL_DEPTH_TEST);
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}

//
//el programa principal
//

int main(int argc, char** argv) {
	
	t5();

	limits.push_back(Point<double>(100, -100));
	limits.push_back(Point<double>(100, -100));
	limits.push_back(Point<double>(-100, 100));

	int n_points;
	cout << "ingrese cantidad de puntos: ";
	cin >> n_points;
	tree = new KDTree<double, 3>(points, limits, n_points);


	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("KDTree"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);


	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	

	return 0;
}