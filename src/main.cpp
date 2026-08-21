#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358979323846

// =====================================================
// FUNCTION PROTOTYPES
// =====================================================

void drawControls();

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
// BACKGROUND STARS
// =====================================================

void drawStars()
{
    glDisable(GL_LIGHTING);

    glPointSize(1.5f);

    glBegin(GL_POINTS);

    for (int i = 0;
         i < 450;
         i++)
    {
        float x =
            ((i * 37) % 220) - 110;

        float y =
            ((i * 71) % 170) - 85;

        float z =
            ((i * 53) % 220) - 110;

        float brightness =
            0.65f +
            (i % 4) * 0.1f;

        glColor3f(
            brightness,
            brightness,
            brightness
        );

        glVertex3f(
            x,
            y,
            z
        );
    }

    glEnd();

    glEnable(GL_LIGHTING);
}


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

// =====================================================
// SUN
// Scaling Transformation + Glow
// =====================================================

void drawSun()
{
    glDisable(GL_LIGHTING);

    // =================================================
    // MAIN SUN
    // =================================================

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


    // =================================================
    // SUN GLOW
    // =================================================

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glColor4f(
        1.0f,
        0.55f,
        0.0f,
        0.08f
    );

    glPushMatrix();

    // SCALING
    glScalef(
        1.35f,
        1.35f,
        1.35f
    );

    drawCustomSphere(
        4.5f,
        20,
        20
    );

    glPopMatrix();

    glDisable(GL_BLEND);

    glEnable(GL_LIGHTING);
}


// =====================================================
// MIRRORING
// Scaling -1 on Y-axis
// =====================================================

void drawReflection()
{
    glPushMatrix();

    // MIRRORING
    glScalef(
        1.0f,
        -1.0f,
        1.0f
    );

    glTranslatef(
        0.0f,
        20.0f,
        0.0f
    );

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glDisable(GL_LIGHTING);

    glColor4f(
        1.0f,
        0.7f,
        0.1f,
        0.10f
    );

    drawCustomSphere(
        4.5f,
        20,
        20
    );

    glEnable(GL_LIGHTING);

    glDisable(GL_BLEND);

    glPopMatrix();
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

    // Stars
    drawStars();

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


    // =================================================
    // MIRRORING
    // =================================================

    drawReflection();


    // =================================================
    // CONTROL PANEL
    // =================================================

    drawControls();

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
// SPECIAL KEYS
// =====================================================

void specialKeys(
    int key,
    int x,
    int y
)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:

            moveX -= 1.0f;

            break;


        case GLUT_KEY_RIGHT:

            moveX += 1.0f;

            break;


        case GLUT_KEY_UP:

            moveY += 1.0f;

            break;


        case GLUT_KEY_DOWN:

            moveY -= 1.0f;

            break;
    }

    glutPostRedisplay();
}


// =====================================================
// NORMAL KEYBOARD
// =====================================================

void keyboard(
    unsigned char key,
    int x,
    int y
)
{
    // =================================================
    // CAMERA ROTATE LEFT
    // =================================================

    if (key == 'a' ||
        key == 'A')
    {
        camAngleY += 5.0f;
    }


    // =================================================
    // CAMERA ROTATE RIGHT
    // =================================================

    else if (key == 'd' ||
             key == 'D')
    {
        camAngleY -= 5.0f;
    }


    // =================================================
    // ZOOM IN
    // =================================================

    else if (key == 'w' ||
             key == 'W')
    {
        zoom -= 2.0f;

        if (zoom < 20.0f)
            zoom = 20.0f;
    }


    // =================================================
    // ZOOM OUT
    // =================================================

    else if (key == 's' ||
             key == 'S')
    {
        zoom += 2.0f;

        if (zoom > 120.0f)
            zoom = 120.0f;
    }


    // =================================================
    // SPEED UP
    // =================================================

    else if (key == '+')
    {
        orbitSpeed += 0.1f;

        if (orbitSpeed > 5.0f)
            orbitSpeed = 5.0f;
    }


    // =================================================
    // SPEED DOWN
    // =================================================

    else if (key == '-')
    {
        orbitSpeed -= 0.1f;

        if (orbitSpeed < 0.0f)
            orbitSpeed = 0.0f;
    }


    // =================================================
    // PLANET NAME ON/OFF
    // =================================================

    else if (key == 't' ||
             key == 'T')
    {
        showText = !showText;
    }


    // =================================================
    // RESET
    // =================================================

    else if (key == 'r' ||
             key == 'R')
    {
        orbitAngle = 0.0f;

        orbitSpeed = 0.5f;

        camAngleY = 0.0f;

        zoom = 60.0f;

        moveX = 0.0f;

        moveY = 0.0f;
    }


    // =================================================
    // EXIT
    // =================================================

    else if (key == 27)
    {
        exit(0);
    }


    glutPostRedisplay();
}


// =====================================================
// SCREEN TEXT
// =====================================================

void drawScreenText(
    const char* text,
    float x,
    float y
)
{
    glRasterPos2f(
        x,
        y
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
}


// =====================================================
// CONTROL PANEL
// =====================================================

void drawControls()
{
    // Switch to 2D projection
    glMatrixMode(
        GL_PROJECTION
    );

    glPushMatrix();

    glLoadIdentity();

    glOrtho(
        0,
        1200,
        0,
        750,
        -1,
        1
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glPushMatrix();

    glLoadIdentity();

    // Disable 3D features
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);


    // =================================================
    // PANEL BACKGROUND
    // =================================================

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glColor4f(
        0.02f,
        0.02f,
        0.06f,
        0.88f
    );

    glBegin(GL_QUADS);

    glVertex2f(
        1010,
        60
    );

    glVertex2f(
        1190,
        60
    );

    glVertex2f(
        1190,
        650
    );

    glVertex2f(
        1010,
        650
    );

    glEnd();


    // =================================================
    // PANEL BORDER
    // =================================================

    glColor3f(
        0.4f,
        0.6f,
        1.0f
    );

    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(
        1010,
        60
    );

    glVertex2f(
        1190,
        60
    );

    glVertex2f(
        1190,
        650
    );

    glVertex2f(
        1010,
        650
    );

    glEnd();


    // =================================================
    // TITLE
    // =================================================

    glColor3f(
        1.0f,
        0.8f,
        0.2f
    );

    glRasterPos2f(
        1030,
        615
    );

    const char* title =
        "CONTROLS";

    for (int i = 0;
         title[i] != '\0';
         i++)
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            title[i]
        );
    }


    // =================================================
    // CONTROL INFORMATION
    // =================================================

    glColor3f(
        0.9f,
        0.9f,
        0.9f
    );

    drawScreenText(
        "W / S  : Zoom",
        1030,
        570
    );

    drawScreenText(
        "A / D  : Rotate",
        1030,
        535
    );

    drawScreenText(
        "Arrows : Move",
        1030,
        500
    );

    drawScreenText(
        "+      : Speed Up",
        1030,
        465
    );

    drawScreenText(
        "-      : Speed Down",
        1030,
        430
    );

    drawScreenText(
        "T      : Names ON/OFF",
        1030,
        395
    );

    drawScreenText(
        "R      : Reset",
        1030,
        360
    );

    drawScreenText(
        "ESC    : Exit",
        1030,
        325
    );


    // =================================================
    // CURRENT SPEED
    // =================================================

    char speedText[50];

    sprintf(
        speedText,
        "Speed: %.1f",
        orbitSpeed
    );

    glColor3f(
        0.3f,
        1.0f,
        0.5f
    );

    drawScreenText(
        speedText,
        1030,
        280
    );


    // =================================================
    // PROJECT INFORMATION
    // =================================================

    glColor3f(
        0.5f,
        0.8f,
        1.0f
    );

    drawScreenText(
        "3D SOLAR SYSTEM",
        1030,
        240
    );

    drawScreenText(
        "Rotation + Scaling",
        1030,
        210
    );

    drawScreenText(
        "Translation + Mirror",
        1030,
        185
    );


    // =================================================
    // STUDENT IDs
    // =================================================

    glColor3f(
        1.0f,
        0.8f,
        0.2f
    );

    drawScreenText(
        "STUDENT ID",
        1030,
        135
    );


    glColor3f(
        0.9f,
        0.9f,
        0.9f
    );

    drawScreenText(
        "41230301349",
        1030,
        105
    );

    drawScreenText(
        "41230301350",
        1030,
        80
    );


    // =================================================
    // RESTORE 3D SETTINGS
    // =================================================

    glDisable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glPopMatrix();

    glMatrixMode(
        GL_PROJECTION
    );

    glPopMatrix();

    glMatrixMode(
        GL_MODELVIEW
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
// LIGHTING
// =====================================================

void initLighting()
{
    glEnable(
        GL_LIGHTING
    );

    glEnable(
        GL_LIGHT0
    );

    glEnable(
        GL_COLOR_MATERIAL
    );

    glColorMaterial(
        GL_FRONT,
        GL_AMBIENT_AND_DIFFUSE
    );


    // =================================================
    // LIGHT POSITION
    // =================================================

    GLfloat lightPosition[] =
    {
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_POSITION,
        lightPosition
    );


    // =================================================
    // AMBIENT LIGHT
    // =================================================

    GLfloat ambient[] =
    {
        0.16f,
        0.16f,
        0.16f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_AMBIENT,
        ambient
    );


    // =================================================
    // DIFFUSE LIGHT
    // =================================================

    GLfloat diffuse[] =
    {
        1.0f,
        0.85f,
        0.55f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_DIFFUSE,
        diffuse
    );


    // =================================================
    // SPECULAR LIGHT
    // =================================================

    GLfloat specular[] =
    {
        1.0f,
        0.95f,
        0.80f,
        1.0f
    };

    glLightfv(
        GL_LIGHT0,
        GL_SPECULAR,
        specular
    );


    // =================================================
    // MATERIAL
    // =================================================

    GLfloat materialSpecular[] =
    {
        0.75f,
        0.75f,
        0.75f,
        1.0f
    };

    glMaterialfv(
        GL_FRONT,
        GL_SPECULAR,
        materialSpecular
    );


    GLfloat shininess[] =
    {
        40.0f
    };

    glMaterialfv(
        GL_FRONT,
        GL_SHININESS,
        shininess
    );


    glEnable(
        GL_NORMALIZE
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

    initLighting();

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

    glutKeyboardFunc(
        keyboard
    );

    glutSpecialFunc(
        specialKeys
    );

    glutMainLoop();

    return 0;
}
