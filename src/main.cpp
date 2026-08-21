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

float camAngleY = 0.0f;
float zoom = 60.0f;

float moveX = 0.0f;
float moveY = 0.0f;

bool showText = true;


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
// 3. 3D TEXT
// =====================================================

void drawText(
    const char* text,
    float x,
    float y,
    float z
)
{
    if (!showText)
        return;

    glDisable(GL_LIGHTING);

    glColor3f(
        1.0f,
        1.0f,
        1.0f
    );

    glRasterPos3f(
        x,
        y,
        z
    );

    for (int i = 0;
         text[i] != '\0';
         i++)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_12,
            text[i]
        );
    }

    glEnable(GL_LIGHTING);
}


// =====================================================
// 4. CUSTOM SATURN RING
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
// 5. PLANET
// Rotation + Translation + Text
// =====================================================

void drawPlanetManual(
    float distance,
    float size,
    float red,
    float green,
    float blue,
    float speed,
    const char* name,
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


    // Planet name
    drawText(
        name,
        -size,
        size + 0.7f,
        0.0f
    );


    // Saturn ring
    if (hasRing)
    {
        glPushMatrix();

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
// 6. SUN
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
// 7. CAMERA
// =====================================================

void setupCamera()
{
    glLoadIdentity();

    // Camera backward
    glTranslatef(
        0.0f,
        -moveY,
        -zoom
    );

    // Horizontal movement
    glTranslatef(
        -moveX,
        0.0f,
        0.0f
    );

    // Camera rotation
    glRotatef(
        camAngleY,
        0.0f,
        1.0f,
        0.0f
    );

    // Slight vertical adjustment
    glTranslatef(
        0.0f,
        -2.0f,
        0.0f
    );
}


// =====================================================
// 8. MANUAL PERSPECTIVE
// =====================================================

void setupPerspective(
    float fov,
    float aspect,
    float nearPlane,
    float farPlane
)
{
    float f =
        1.0f /
        tan(
            (fov * PI / 180.0f)
            / 2.0f
        );

    float matrix[16] = {0};

    matrix[0] =
        f / aspect;

    matrix[5] =
        f;

    matrix[10] =
        (farPlane + nearPlane) /
        (nearPlane - farPlane);

    matrix[11] =
        -1.0f;

    matrix[14] =
        (2.0f *
         farPlane *
         nearPlane) /
        (nearPlane - farPlane);

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    glMultMatrixf(matrix);

    glMatrixMode(
        GL_MODELVIEW
    );
}


// =====================================================
// 9. DISPLAY
// =====================================================

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    // 3D Camera
    setupCamera();

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
        4.0f,
        "Mercury"
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
        3.0f,
        "Venus"
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
        2.0f,
        "Earth"
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
        1.5f,
        "Mars"
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
        1.0f,
        "Jupiter"
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
        "Saturn",
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
        0.5f,
        "Uranus"
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
        0.3f,
        "Neptune"
    );


    glutSwapBuffers();
}


// =====================================================
// 10. CONTINUOUS ANIMATION
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
// 11. RESHAPE
// =====================================================

void reshape(
    int width,
    int height
)
{
    if (height == 0)
        height = 1;

    float aspect =
        (float)width /
        (float)height;

    glViewport(
        0,
        0,
        width,
        height
    );

    setupPerspective(
        45.0f,
        aspect,
        1.0f,
        350.0f
    );
}


// =====================================================
// 12. INITIALIZATION
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

    setupPerspective(
        45.0f,
        1200.0f / 750.0f,
        1.0f,
        350.0f
    );
}


// =====================================================
// 13. MAIN
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

    glutReshapeFunc(
        reshape
    );

    glutTimerFunc(
        0,
        update,
        0
    );

    glutMainLoop();

    return 0;
}