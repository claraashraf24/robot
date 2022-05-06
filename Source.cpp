#include <iostream>
#include <GL/glut.h>
using namespace std;
static int shoulder = 0, elbow = 0, fingerBase = 0, fingerUp = 0,RightKnee=0,RightHip=0, LeftKnee = 0, LeftHip = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

double eye[] = { 0.0 , 0.0, 1.0 }, center[] = { 0.0 , 0.0 , 0.0 }, up[] = { 0.0 , 1.0 , 0.0 };

double cp[3];

bool armUp = false;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawArm(float direction)
{
    glPushMatrix();
    //Mouse movements
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(direction*1.5, 1.5, 0.0);

    //Shoulder
    glScalef(direction, 1.0, 1.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    glTranslatef(1.0, 0.0, 0.0);

    //Elbow
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Fingers 
    for (float i = 0.4; i > -0.4; i -= 0.2)
    {
        //Finger phalange 1 
        glPushMatrix();
        glTranslatef(1.0, 0.25, 0.0);
        glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
        glTranslatef(0.15, 0.0, i);
        glPushMatrix();
        glScalef(0.3, 0.1, 0.1);
        glutWireCube(1);
        glPopMatrix();

        //Finger phalange 2 
        glTranslatef(0.15, 0.0, 0.0);
        glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
        glTranslatef(0.15, 0.0, 0.0);
        glPushMatrix();
        glScalef(0.3, 0.1, 0.1);
        glutWireCube(1);
        glPopMatrix();
        glPopMatrix();

    }

    //Thumb phalange 1 
    glPushMatrix();
    glTranslatef(1.0, -0.25, 0.0);
    glRotatef((GLfloat)-1 * fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Thumb phalange 2 
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-1 * fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
}

void drawBody(void)
{
    glPushMatrix();
        //Mouse movements
        glRotatef(angle2, 1.0, 0.0, 0.0);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glutWireCube(1);
    glPopMatrix();
}

void drawLeg(float direction)
{
    glPushMatrix();
    //Mouse movements
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    //Hip
    glScalef(direction, 1.0, 1.0);
    glTranslatef(0.0, -2.5, 0.0);
    glRotatef((GLfloat)direction == 1.0 ? RightHip : LeftHip, 1.0, 0.0, 0.0);
    glTranslatef(0.75, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 3.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Knee
    glTranslatef(0.0, -1.5, 0.0);
    glRotatef((GLfloat)direction == 1.0 ? RightKnee : LeftKnee, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.5, 0.0);
    glPushMatrix();
    glScalef(0.5, 3.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Foot
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.0, 2.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

}

void drawHead(void)
{
    glPushMatrix();
        glRotatef(angle2, 1.0, 0.0, 0.0);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 2.5, 0.0);
        glutWireSphere(0.5,10,10);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();   
        gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]); //look at function
        drawArm(1.0);   //Draw Right Arm
        drawArm(-1.0);  //Draw Left Arm
        drawBody();     //Draw Body
        drawLeg(1.0);   //Draw Right Leg
        drawLeg(-1.0);  //Draw Left Leg
        drawHead();     //Draw Right Leg
    glPopMatrix();
    glutSwapBuffers();
}

void startAnimation(int value)
{
    if (value == 1)
    {
        armUp = (shoulder == 90);
    }
    if (value == 0)
    {
        if (armUp)
        {
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            glutTimerFunc(30, startAnimation, shoulder == -90 ? 1 : 0);
        }
        else 
        {
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            glutTimerFunc(30, startAnimation, shoulder == 90 ? 1 :0);
        }
    }
}

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];

}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void hRotation(double a[], double b[], double c[], double theta) {
    crossProduct(a, b, c);
    normalize(c);
    rotatePoint(c, theta, a);
    rotatePoint(c, theta, b);
}

void moveFront(double center[], double eye[]) {
    double direction[3];
    double speed = 0.1;
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;

}

void moveBack(double center[], double eye[]) {
    double direction[3];
    double speed = 0.1;
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;
    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;

}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        rotatePoint(up, -0.1, eye);
        break;
    case GLUT_KEY_RIGHT:
        rotatePoint(up, 0.1, eye);
        break;
    case GLUT_KEY_UP:
        hRotation(up, eye, cp, -0.1);
        break;
    case GLUT_KEY_DOWN:
        hRotation(up, eye, cp, 0.1);
        break;
    }
    glutPostRedisplay();
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        moveFront(center, eye);
        glutPostRedisplay();

        break;
    case 'b':
        moveBack(center, eye);
        glutPostRedisplay();

        break;
    case 's':
        cout << (shoulder + 5) % 360 << endl;
        if ((shoulder + 5) % 360 <= 90)
        {
            shoulder = (shoulder + 5) % 360;
            armUp = (shoulder == 90);
            glutPostRedisplay();
        }
        break;
    case 'S':
        cout << (shoulder - 5) % 360 << endl;
        if ((shoulder - 5) % 360 >= -90)
        {
            shoulder = (shoulder - 5) % 360;
            armUp = !(shoulder == -90);
            glutPostRedisplay();
        }
        break;
    case 'e':
        cout << (elbow + 5) % 360 << endl;
        if ((elbow + 5) % 360 < 180)
        {
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'E':
        cout << (elbow - 5) % 360 << endl;
        if ((elbow - 5) % 360 > -180)
        {
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'k':
        cout << (RightKnee + 5) % 360 << endl;
        if ((RightKnee + 5) % 360 < 180)
        {
            RightKnee = (RightKnee + 5) % 360;
            glutPostRedisplay();

        }
        break;
    case 'K':
        cout << ((RightKnee - 5) % 360) << endl;
        if ((RightKnee - 5) % 360 >= 0)
        {
            RightKnee = (RightKnee - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'n':
        cout << (LeftKnee + 5) % 360 << endl;
        if ((LeftKnee + 5) % 360 < 180)
        {
            LeftKnee = (LeftKnee + 5) % 360;
            glutPostRedisplay();

        }
        break;
    case 'N':
        cout << ((LeftKnee - 5) % 360) << endl;
        if ((LeftKnee - 5) % 360 >= 0)
        {
            LeftKnee = (LeftKnee - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'h':
        cout << (RightHip + 5) % 360 << endl;
        if ((RightHip + 5) % 360 <= 180)
        {
            RightHip = (RightHip + 5) % 360;
            glutPostRedisplay();

        }
        break;
    case 'H':
        cout << ((RightHip - 5) % 360) << endl;
        if ((RightHip - 5) % 360 >= -180)
        {
            RightHip = (RightHip - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'i':
        cout << (LeftHip + 5) % 360 << endl;
        if ((LeftHip + 5) % 360 <= 180)
        {
            LeftHip = (LeftHip + 5) % 360;
            glutPostRedisplay();

        }
        break;
    case 'I':
        cout << ((LeftHip - 5) % 360) << endl;
        if ((LeftHip - 5) % 360 >= -180)
        {
            LeftHip = (LeftHip - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'f':
        cout << (fingerBase + 5) % 360 << endl;
        if ((fingerBase + 5) % 360 < 180)
        {
            fingerBase = (fingerBase + 5) % 360;
            glutPostRedisplay();

        }
        break;
    case 'F':
        cout << ((fingerBase - 5) % 360) << endl;
        if ((fingerBase - 5) % 360 > -90)
        {
            fingerBase = (fingerBase - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'p':
        cout << (fingerUp + 5) % 360 << endl;
        if ((fingerUp + 5) % 360 < 0)
        {
            fingerUp = (fingerUp + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'P':
        cout << ((fingerUp - 5) % 360) << endl;
        if ((fingerUp - 5) % 360 > -180)
        {
            fingerUp = (fingerUp - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case ' ':
        glutTimerFunc(0, startAnimation, 0);
        break;
    default:
        break;
    }
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
