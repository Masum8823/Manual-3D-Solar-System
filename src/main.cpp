#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358979323846

// =====================================================
// GLOBAL VARIABLES
// =====================================================

float orbitAngle = 0.0f;
float orbitSpeed = 0.5f;


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
// 3. CUSTOM SATURN RING
// =====================================================

void drawCustomRing(float planetSize)
{
    float R =
        planetSize + 1.2f;

    float r =
        0.18f;

    int majorSegments = 40;
    int minorSegments = 12;

    for (int i = 0;
         i < majorSegments;
         i++)
    {
        float theta1 =
            2.0f * PI * i /
            majorSegments;

        float theta2 =
            2.0f * PI * (i + 1) /
            majorSegments;

        glBegin(GL_QUAD_STRIP);

        for (int j = 0;
             j <= minorSegments;
             j++)
        {
            float phi =
                2.0f * PI * j /
                minorSegments;

            // First point
            float x1 =
                (R + r * cos(phi)) *
                cos(theta1);

            float y1 =
                r * sin(phi);

            float z1 =
                (R + r * cos(phi)) *
                sin(theta1);

            // Second point
            float x2 =
                (R + r * cos(phi)) *
                cos(theta2);

            float y2 =
                r * sin(phi);

            float z2 =
                (R + r * cos(phi)) *
                sin(theta2);

            glVertex3f(
                x1,
                y1,
                z1
            );

            glVertex3f(
                x2,
                y2,
                z2
            );
        }

        glEnd();
    }
}


// =====================================================
// 4. PLANET
// Rotation + Translation
// =====================================================

void drawPlanetManual(
    float distance,
    float size,
    float red,
    float green,
    float blue,
    float speed,
    bool hasRing = false
)
{
    // Orbit path
    drawManualOrbit(distance);

    glPushMatrix();

    // ROTATION
    glRotatef(
        orbitAngle * speed,
        0.0f,
        1.0f,
        0.0f
    );

    // TRANSLATION
    glTranslatef(
        distance,
        0.0f,
        0.0f
    );

    // Planet color
    glColor3f(
        red,
        green,
        blue
    );

    // Planet sphere
    drawCustomSphere(
        size,
        20,
        20
    );


    // =================================================
    // SATURN RING
    // =================================================

    if (hasRing)
    {
        glPushMatrix();

        // Ring tilt
        glRotatef(
            70.0f,
            1.0f,
            0.0f,
            0.0f
        );

        glColor3f(
            0.8f,
            0.65f,
            0.35f
        );

        drawCustomRing(size);

        glPopMatrix();
    }

    glPopMatrix();
}


// =====================================================
// 5. SUN
// =====================================================

void drawSun()
{
    glDisable(GL_LIGHTING);

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

    glEnable(GL_LIGHTING);
}


// =====================================================
// 6. DISPLAY
// =====================================================

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    // Sun
    drawSun();


    // =================================================
    // MERCURY
    // =================================================

    drawPlanetManual(
        8.0f,
        0.5f,
        0.7f,
        0.7f,
        0.7f,
        4.0f
    );


    // =================================================
    // VENUS
    // =================================================

    drawPlanetManual(
        12.0f,
        0.9f,
        0.9f,
        0.5f,
        0.2f,
        3.0f
    );


    // =================================================
    // EARTH
    // =================================================

    drawPlanetManual(
        16.0f,
        1.0f,
        0.2f,
        0.4f,
        1.0f,
        2.0f
    );


    // =================================================
    // MARS
    // =================================================

    drawPlanetManual(
        20.0f,
        0.8f,
        1.0f,
        0.2f,
        0.0f,
        1.5f
    );


    // =================================================
    // JUPITER
    // =================================================

    drawPlanetManual(
        28.0f,
        2.3f,
        0.8f,
        0.6f,
        0.4f,
        1.0f
    );


    // =================================================
    // SATURN
    // =================================================

    drawPlanetManual(
        36.0f,
        1.9f,
        0.7f,
        0.7f,
        0.5f,
        0.7f,
        true
    );


    // =================================================
    // URANUS
    // =================================================

    drawPlanetManual(
        44.0f,
        1.4f,
        0.4f,
        0.7f,
        1.0f,
        0.5f
    );


    // =================================================
    // NEPTUNE
    // =================================================

    drawPlanetManual(
        52.0f,
        1.4f,
        0.2f,
        0.2f,
        1.0f,
        0.3f
    );


    glutSwapBuffers();
}


// =====================================================
// 7. CONTINUOUS ANIMATION
// =====================================================

void update(int value)
{
    orbitAngle += orbitSpeed;

    if (orbitAngle > 100000.0f)
    {
        orbitAngle -= 100000.0f;
    }

    glutPostRedisplay();

    glutTimerFunc(
        20,
        update,
        0
    );
}


// =====================================================
// 8. INITIALIZATION
// =====================================================

void init()
{
    glEnable(
        GL_DEPTH_TEST
    );

    glClearColor(
        0.0f,
        0.0f,
        0.05f,
        1.0f
    );
}


// =====================================================
// 9. MAIN
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
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
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

    glutTimerFunc(
        0,
        update,
        0
    );

    glutMainLoop();

    return 0;
}