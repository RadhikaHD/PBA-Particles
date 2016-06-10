#include "Generator.h"

#include <vector>

#define WINDOW_WIDTH    1080
#define WINDOW_HEIGHT   1080
#define STARTX 0.5
#define STARTY 1.0
#define STARTZ 0.5
#define TOTAL_PARTICLES 1000
#define TIME_STEP 0.08
#define RADIUS 0.05

static double WinWidth = WINDOW_WIDTH;
static double WinHeight = WINDOW_HEIGHT;
static Vector3d origin(STARTX, STARTY, STARTZ);
static Vector3d V0(0.1,0.1,0.1);
static int noOfParticles = TOTAL_PARTICLES;

static Generator generator(origin, noOfParticles, TIME_STEP);

void do_material()
{
    
    float mat_ambient[] = {0.0,0.0,0.0,1.0};
    float mat_diffuse[] = {1.0,0.549,0.0,1.0};;
    float mat_specular[] = {0.3,0.3,0.3,1.0};
    float mat_shininess[] = {2.0};
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    
}

void do_lights()
{
    
    float light0_ambient[] = {0.0, 0.0, 0.0, 0.0};
    float light0_diffuse[] = {2.0, 2.0, 2.0, 0.0};
    float light0_specular[] = {2.25, 2.25, 2.25, 0.0};
    float light0_position[] = {1.5, 2.0, 2.0, 1.0};
    float light0_direction[] = { -1.5, -2.0, -2.0, -2.0, 1.0};
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    
    glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
}

void setup_the_viewvolume()
{
    
    Vector3d eye, view, up;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(37.0, 1.0, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    eye.x = 0.5;
    eye.y = 1.3;
    eye.z = 3.0;
    view.x = 0.5;
    view.y = 0.2;
    view.z = 0.0;
    up.x = 0.0;
    up.y = 1.0;
    up.z = 0.0;
    
    gluLookAt(eye.x, eye.y, eye.z, view.x, view.y, view.z, up.x, up.y, up.z);
    
}

void doReshape(int w, int h)
{
    
    int vpw, vph;
    float aspect = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
    
    if(float(w) / float(h) > aspect)
    {
        vph = h;
        vpw = int(aspect * h + 0.5);
    }
    else
    {
        vpw = w;
        vph = int(w / aspect + 0.5);
    }
    
    glViewport(0, 0, vpw, vph);
    WinWidth = w;
    WinHeight = h;
    setup_the_viewvolume();
    
}

void DrawSphere(float x, float y, float z)
{
    
    float drawx = x;
    float drawy = y;
    float drawz = z;
    float drawrad = RADIUS;
    
   // GLfloat sphere_diffuse[] = { 1.0,0.549,0.0, 1.0 };
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
    
    glPushMatrix();
    glTranslatef (drawx,drawy-0.5,0.4);
    glutSolidSphere(drawrad,40,40);
    glPopMatrix ();
    
    glFlush();
    
}

void drawDisplay()
{
   
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    DrawSphere(STARTX,STARTY,STARTZ);
    
    generator.run();
    
    glutSwapBuffers();
    
    
}

void Timer(int unused)
{
    std::cout<<"postredisplay"<<std::endl;
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}


int main(int argc, char* argv[])
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100,50);
    glutCreateWindow("Particles Everywhere");
    glutReshapeFunc(doReshape);
    do_lights();
    do_material();
    generator.addParticles();
    glutDisplayFunc(drawDisplay);
    Timer(0);
    glutMainLoop();
    return 0;
    
}

