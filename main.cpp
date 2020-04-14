#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include "game.h"

#define COLUMNS 40 
#define ROWS 40
#define FPS 8

extern short sDirection;
extern bool gameOver;
extern int score;

void timer(int);
void display();
void init();
void reshape(int,int);
void key_c(int,int,int);

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("Snake Game");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutSpecialFunc(key_c);
	init();
	glutMainLoop();
	return 0;
}

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	initGrid(COLUMNS,ROWS);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();
	if(gameOver){
		char _score[10];
		sprintf(_score,"%d",score); 
		char s1[70] = "echo \"Game Over.....!\nYour Score : ";
		char s2[30] = "  \" | xmessage -file -";
		strcat(s1,_score);
		strcat(s1,s2);
		system(s1);
		exit(0);
	}
}

void reshape(int w,int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer,0);
}

void key_c(int key,int,int){
	switch(key){
		case GLUT_KEY_UP:
			if(sDirection != DOWN)
				sDirection = UP;
			break;
		case GLUT_KEY_DOWN:
			if(sDirection != UP)
				sDirection = DOWN;
			break;
		case GLUT_KEY_RIGHT:
			if(sDirection != LEFT)
				sDirection = RIGHT;
			break;
		case GLUT_KEY_LEFT:
			if(sDirection != RIGHT)
				sDirection = LEFT;
			break;
	}
}


