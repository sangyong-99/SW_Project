#include <bits/stdc++.h>
#include <iostream>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


//const int GRID_SIZE = 1; // 그리드 크기
const float VOXEL_SIZE = 1.0f; // 복셀 크기

float cameraDistance = 10.0f;
float cameraAngleX = 45.0f;
float cameraAngleY = 45.0f;
int lastMouseX = -1;
int lastMouseY = -1;

void drawVoxel(float x, float y, float z) {
    // 복셀 면을 그립니다
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // 면의 색상 설정
    // 각 면의 꼭지점을 정의합니다
    glVertex3f(x, y, z);
    glVertex3f(x + VOXEL_SIZE, y, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    glVertex3f(x, y + VOXEL_SIZE, z);
    
    glVertex3f(x, y, z + VOXEL_SIZE);
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    
    glVertex3f(x, y, z);
    glVertex3f(x, y + VOXEL_SIZE, z);
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x, y, z + VOXEL_SIZE);
    
    glVertex3f(x + VOXEL_SIZE, y, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    
    glVertex3f(x, y, z);
    glVertex3f(x + VOXEL_SIZE, y, z);
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    glVertex3f(x, y, z + VOXEL_SIZE);
    
    glVertex3f(x, y + VOXEL_SIZE, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glEnd();

    // 복셀 면의 선을 그립니다
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // 검은색으로 선의 색상 설정
    // 각 면의 선을 정의합니다
    glVertex3f(x, y, z);
    glVertex3f(x + VOXEL_SIZE, y, z);
    
    glVertex3f(x + VOXEL_SIZE, y, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    glVertex3f(x, y + VOXEL_SIZE, z);
    
    glVertex3f(x, y + VOXEL_SIZE, z);
    glVertex3f(x, y, z);
    
    glVertex3f(x, y, z + VOXEL_SIZE);
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glVertex3f(x, y, z + VOXEL_SIZE);
    
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + VOXEL_SIZE);
    
    glVertex3f(x + VOXEL_SIZE, y, z);
    glVertex3f(x + VOXEL_SIZE, y, z + VOXEL_SIZE);
    
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z);
    glVertex3f(x + VOXEL_SIZE, y + VOXEL_SIZE, z + VOXEL_SIZE);
    
    glVertex3f(x, y + VOXEL_SIZE, z);
    glVertex3f(x, y + VOXEL_SIZE, z + VOXEL_SIZE);
    glEnd();
}


void drawGrid() {
//    for (int x = 0; x < 1; ++x) {
//        for (int y = 0; y < 1; ++y) {
//            for (int z = 0; z < 1; ++z) {
//                drawVoxel(x * VOXEL_SIZE, y * VOXEL_SIZE, z * VOXEL_SIZE);
//            }
//        }
//    }
    drawVoxel(3, 1, 0);
    drawVoxel(1, 1, 0);
    drawVoxel(3, -1, 0);
    drawVoxel(1, -1, 0);
    drawVoxel(2, 0, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance * cos(cameraAngleY * 3.14159265 / 180) * sin(cameraAngleX * 3.14159265 / 180),
              cameraDistance * sin(cameraAngleY * 3.14159265 / 180),
              cameraDistance * cos(cameraAngleY * 3.14159265 / 180) * cos(cameraAngleX * 3.14159265 / 180),
              0, 0, 0,
              0, 1, 0);

    drawGrid();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

void motion(int x, int y) {
    if (lastMouseX == -1 || lastMouseY == -1) {
        return;
    }

    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    cameraAngleX += dx * 0.1f;
    cameraAngleY += dy * 0.1f;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Voxel System");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}

