// Name: Xander Fernald
// Quarter, Year: Winter 2020
// Lab: 7
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>
#include <cmath>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

vector<vec2> P;

float factorial(int n) {
    float fact = 1;
    for (unsigned i = n; i > 0; i--) {
        fact *= i;
    }
    return fact;
}

float combination(int n, int k) {
    float fact_n, fact_k, fact_nk, comb;
    fact_n = factorial(n);
    fact_k = factorial(k);
    fact_nk = factorial(n - k);
    comb = fact_n / (fact_k * fact_nk);
    return comb;
}

float binomial(int n, int k, float t) {
    float comb = combination(n, k);
    float bin = comb * pow(t, k) * pow(1 - t, n - k);
    return bin;
}

void GL_render()
{
    float x, y, point;
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
    // glVertex2f(-.5f,-.5f);
    // glVertex2f(.5f,-.5f);
    // glVertex2f(.5f,.5f);
    // glVertex2f(-.5f,.5f);
    for (float t = 0.0; t < 1.0; t += 0.01) {
        for (int i = 0; i < P.size(); i++) {
            x = binomial(P.size(), i, t) * P.at(i)[0];
            y = binomial(P.size(), i, t) * P.at(i)[1];
            point = vec2(x, y);
        }
    }
    glEnd();
    glFlush();


}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        P.push_back(vec2(px, py));
        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - xfern001");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
