#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358979323846


// =====================================================
// 1. CUSTOM SPHERE
// =====================================================

void drawCustomSphere(float radius, int stacks, int slices)
{
    for (int i = 0; i < stacks; i++)
    {
        float lat1 =
            -PI / 2.0f +
            PI * i / stacks;

        float lat2 =
            -PI / 2.0f +
            PI * (i + 1) / stacks;

        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j <= slices; j++)
        {
            float lon =
                2.0f * PI * j / slices;

            // First point
            float x1 =
                cos(lat1) * cos(lon);

            float y1 =
                cos(lat1) * sin(lon);

            float z1 =
                sin(lat1);

            glNormal3f(x1, y1, z1);

            glVertex3f(
                radius * x1,
                radius * y1,
                radius * z1
            );

            // Second point
            float x2 =
                cos(lat2) * cos(lon);

            float y2 =
                cos(lat2) * sin(lon);

            float z2 =
                sin(lat2);

            glNormal3f(x2, y2, z2);

            glVertex3f(
                radius * x2,
                radius * y2,
                radius * z2
            );
        }

        glEnd();
    }
}


// =====================================================
// 2. CUSTOM ORBIT
// x = r cos(theta)
// z = r sin(theta)
// =====================================================

void drawManualOrbit(float radius)
{
    glDisable(GL_LIGHTING);

    glColor3f(
        0.25f,
        0.27f,
        0.32f
    );

    glLineWidth(1.0f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++)
    {
        float theta =
            i * PI / 180.0f;

        float x =
            radius * cos(theta);

        float z =
            radius * sin(theta);

        glVertex3f(
            x,
            0.0f,
            z
        );
    }

    glEnd();

    glEnable(GL_LIGHTING);
}


// =====================================================
// 3. DISPLAY
// =====================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Center sphere
    glColor3f(
        1.0f,
        0.55f,
        0.0f
    );

    drawCustomSphere(
        4.5f,
        30,
        30
    );


    // Orbital paths
    drawManualOrbit(8.0f);
    drawManualOrbit(12.0f);
    drawManualOrbit(16.0f);
    drawManualOrbit(20.0f);


    glFlush();
}


// =====================================================
// 4. INITIALIZATION
// =====================================================

void init()
{
    glClearColor(
        0.0f,
        0.0f,
        0.05f,
        1.0f
    );
}


// =====================================================
// 5. MAIN
// =====================================================

int main(
    int argc,
    char** argv
)
{
    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_SINGLE |
        GLUT_RGB
    );

    glutInitWindowSize(
        1200,
        750
    );

    glutCreateWindow(
        "CG Lab Project - Manual 3D Solar System"
    );

    init();

    glutDisplayFunc(
        display
    );

    glutMainLoop();

    return 0;
}