
#include "windows.h"   
#include <GL/glut.h> 
#include <time.h> 
#include <random> 
#include <iostream> 

int N = 30, M = 20; 
int scale = 25; 

int w = scale*N; 
int h = scale*M;  

int dir, num = 4; // 4 направления и начальный размер змеи. 
struct { int x; int y; } s[100]; 

class fruct  
{
public:
	int x, y; 

	void New() // паблик с новыми фруктами. Он будет вызываться в начале игры и в тот момент, когда змея съест один из фруктов 
	{
		x = rand() % N; 
		y = rand() % M;  
	}

	void DrawFruct() // паблик, отрисовывающий фрукты 
	{
		glColor3f(1.0, 0.0, 0.0);  
		glRectf(x*scale, y*scale, (x + 1)*scale, (y + 1)*scale);  
	}
} m[1]; 

void Draw() // функция, которая отрисовывает линии 
{
	glColor3f(0.0, 0.0, 0.0); 
	glBegin(GL_LINES);  
	for (int i = 0; i < w; i += scale)  
	{
		glVertex2f(i, 0); glVertex2f(i, h);  
	}
	for (int j = 0; j < h; j += scale) 
	{
		glVertex2f(0, j); glVertex2f(w, j); 
	}

	glEnd(); 
}

void tick() 
{
	for (int i = num; i > 0; --i) 
	{
		s[i].x = s[i - 1].x; 
		s[i].y = s[i - 1].y; 
	}
	
	if (dir == 0) s[0].y += 1; 
	if (dir == 1) s[0].x -= 1; 
	if (dir == 2) s[0].x += 1; 
	if (dir == 3) s[0].y -= 1; 

	for (int i = 0; i < 10; i++) //цикл, в котором наша змея будет расти 
	{
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) 
		{
			num++; 
			m[i].New(); 
		}
	}
	
	if (s[0].x > N) dir = 1; 
	if (s[0].y > M) dir = 3; 
	if (s[0].x < 0) dir = 2;
	if (s[0].y < 0) dir = 0;

	for (int i = 1; i < num; i++) 
		if (s[0].x == s[i].x && s[0].y == s[i].y) 
			num = i; 
}

void Snake() // выводим змейку на экран 
{
	glColor3f(0.1, 1.0, 0.0); 
	for (int i = 0; i < num; i++) 
	{
		glRectf(s[i].x*scale, s[i].y*scale, (s[i].x + 0.9)*scale, (s[i].y + 0.9)*scale); 
	}
}

void Key(int key, int a, int b) // функция нажатия клавиш 
{
	switch (key) 
	{
	case 101: dir = 0; break; 
	case 102: dir = 2; break;
	case 100: dir = 1; break;
	case 103: dir = 3; break;
	}
}

void Display() //функция общий отрисовки 
{
	glClear(GL_COLOR_BUFFER_BIT);

	Draw(); 
	Snake();

	for (int i = 0; i < 1; i++) 
		m[i].DrawFruct();

	glFlush();
	glutSwapBuffers();
}

void timer(int = 0) // Таймер игры(промежуток времени, в котором будет производится все процессы) 
{
	Display();   
	tick();
	glutTimerFunc(100, timer, 0);  
}

int main(int argc, char **argv) // Главная функция 
{
	std::cout << "Loading...";  
	srand(time(0));
	for (int i = 0; i<10; i++)  
		m[i].New();

	s[0].x = 10; // начальное положение змейки по X 
	s[0].y = 10; // и Y координате 
				 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h); 
	glutCreateWindow("Snake");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(Display); 
	glutSpecialFunc(Key);
	glutTimerFunc(50, timer, 0);
	glutMainLoop();

	return 0;
}