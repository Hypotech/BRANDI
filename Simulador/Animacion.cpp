/*
 * Definicion de las funciones de animacion del simulador BRANDI
 *
 * Elaborado por: Hipolito Morales Christian
 */

 /**
\def ACI_MOTOR1 
altura del cilindro que hace de motor 1.
@def ACI_BASE
 altura del cilindro que hace de base.
@def ACU_BASE2
altura del cubo que hace de base para el motor 2.
@def ACU_MOTOR2
altura del cubo que hace de motor 2
@def ACU_ESL1
altura del cubo que hace de eslabon 1
@def ACU_MOTOR3
altura del cubo que hace de motor 2
@def ACU_MOTOR4
altura del cubo que hace de motor 4
@def ACI_MOTOR5
altura del cilindro que hace de motor(o rotor) 1

*/

#include <GL/freeglut.h>
#include <math.h>
#include "Animacion.hpp"

/**
 *@var GLfloat ex 
 *@brief valor de la posición de la camara en el eje x 
 *@var GLfloat ey
 *@brief  valor de la posición de la camara en el eje y
 *@var GLfloat ez
 *@brief  valor de la posición de la camara en el eje z
 *@var GLfloat cx
 *@brief  valor de la componente x del punto al que observa la camara.
 *@var GLfloat cy
 *@brief  valor de la componente y del punto al que observa la camara.
 *@var GLfloat cz
 *@brief  valor de la componente z del punto al que observa la camara.
 */

/************* Variables para el control de la camara *************/
GLfloat ex=27.0f, ey=18.0f, ez=0.0f,cx=0.0f,  cy=13.5f, cz=0.0f;
/*****************************************************************/

/**
 *@var GLfloat RMotor1
 *@brief  variable global, su valor representa el ángulo (medido en grados) de rotación del motor 1 de BRANDI.
 *@var GLfloat RMotor2
 *@brief  variable global, su valor representa el ángulo (medido en grados) de rotación del motor 2 de BRANDI.
 *@var GLfloat RMotor3
 *@brief  variable global, su valor representa el ángulo (medido en grados) de rotación del motor 3 de BRANDI.
 *@var GLfloat RMotor4
 *@brief  variable global, su valor representa el ángulo (medido en grados) de rotación del motor 4 de BRANDI.
 *@var GLfloat RMotor5
 *@brief  variable global, su valor representa el ángulo (medido en grados) de rotación del motor 5 de BRANDI.
 */
/******* Variables para rotar los motores, medidas en angulos ******/
GLfloat RMotor1= 0, RMotor2 = 0, RMotor3 = 0, RMotor4=90, RMotor5= 0; // volores de home
/******************************************************************/

/**
 *@var int winSimulador
 *@brief  variable global, indica la dirección de la ventana donde se desplegará el simulador. Esta
 * variable es utilizada por la función escenario e inicializada por la función config_Simulador.
 */
/****** Direccion de la ventana en la que se ha de desplegar ******/
int winSimulador = 0;
/******************************************************************/

/**
 * \brief Lleva a cabo la creación y despligue del escenario.
 */

void Escenario ()
{
/**
 * \details 
Aqui se modelan y se despliegan todos los objetos que son parte del simulador: el BRADI y una rejilla que hace de piso, se invoca esta función cada vez que se necesita redibujar dado un cambio en los angulos de los motores o las variables de la camara, la invocación es llevada a cabo por las callbacks glutDisplayFunc y glutIdleFunc. Consulte la documentación de freeglut para más información.
 */

    GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

    limitar_Motores();

    glutSetWindow (winSimulador);

    glLoadIdentity();
    gluLookAt (ex, ey, ez, cx, cy, cz, 0.0, 1.0, 0.0);
    	
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);  	
    glDisable(GL_DEPTH_TEST);
    glDisable( GL_LIGHTING );
    //###### Dibujar piso #####
        glPushMatrix();
	glColor3f( 0.0, 0.7, 0.7 );
	glTranslatef(0,0,0);
	glBegin( GL_LINES );
	    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
	    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	    {
		xLocal = DEF_floorGridScale * loopX;
		glVertex3f( xLocal, 0.0, -zExtent );
		glVertex3f( xLocal, 0.0,  zExtent );
	    }
	    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
	    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	    {
		zLocal = DEF_floorGridScale * loopZ;
		glVertex3f( -xExtent, 0.0, zLocal );
		glVertex3f(  xExtent, 0.0, zLocal );
	    }
	glEnd();
	glPopMatrix();
    //####### creando brazo robotico #######
    //****Defino los colores para materiales*****
    GLfloat color_azul[] = {0.1,0.7,0.7 ,1.0f}; 
    GLfloat color_rojo[] = {1.0,0.2,0.1,1.0};
    GLfloat color_negro[] = {0.1,0.1,0.1};
    //*******************************************
    glEnable( GL_LIGHTING );
    glEnable(GL_DEPTH_TEST); //habilita el z buffe

#define ACI_BASE 11.0 /// altura del cilindro que hace de base.
    //Dibujando los elementos...	
    glPushMatrix(); //cilindro base	
	glMaterialfv (GL_FRONT, GL_DIFFUSE,color_rojo);// cara, luz,color
	glTranslatef(0,0,0); //se ejecuta al ultimo
	glRotatef(-90,1,0,0);
	glutSolidCylinder (5.8, ACI_BASE,20,1);//radio, altura, slices,stacks
    glPopMatrix();

#define ACI_MOTOR1 1.0
    glPushMatrix();
    glRotatef(RMotor1,0,1,0); //rota segun teclas F1 y F2
    glPushMatrix();//cilindro GLibertad1 o motor 1
        glMaterialfv(GL_FRONT, GL_DIFFUSE,color_azul);
	glTranslatef(0,ACI_BASE,0);//traslada arriba de la base
	glRotatef(-90,1,0,0);
	glutSolidCylinder (2.0,ACI_MOTOR1,20,1);//radio, altura, slices,stacks
    glPopMatrix();

    #define ACU_BASE2 0.9 //altura del cubo que hace de base para el motor 2
    glPushMatrix();//cubo base
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color_azul);
       	glTranslatef(0, ACI_BASE+ACI_MOTOR1+ACU_BASE2/2, -1.9); //traslada arriba del rotor 1
	glScalef(4, ACU_BASE2, 8.3); //ancho, alto, largo
	glutSolidCube(1);
    glPopMatrix();

#define ACU_MOTOR2 2.0 //altura del cubo que hace de motor 2
    glPushMatrix();//cubo Glibertad2 o  motor_2
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color_negro);
       	glTranslatef(0,ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2,-1.5);//arriba de su base
	glScalef(4,ACU_MOTOR2,7.5); //ancho, alto, largo
	glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();    //Rotor1 o articulacion1
	glTranslatef(0,ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2,1.125);
	DibujarRotor(2.01f,color_rojo,RMotor2);//separcaion,color,angulo
    glPopMatrix();

#define ACU_ESL1 2.0 //altura del cubo que hace de eslabon 1
    glPushMatrix();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color_rojo);
       	glTranslatef(0,ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_ESL1/2,0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,5);
	glScalef(4,ACU_ESL1,10); //ancho, alto, largo
	glutSolidCube(1);
    glPopMatrix(); 
	
    #define ACU_MOTOR3 2.0 //altura del cubo que hace de motor 2
    GLfloat Ancho_M3= 4, Alto_M3= ACU_MOTOR3, Largo_M3= 13;

    glPushMatrix();//cubo motor_3
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color_negro);
       	glTranslatef(0,ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2,0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,9);
	glRotatef(RMotor3,1,0,0);
	glTranslatef(0,-(Largo_M3/2-ACU_ESL1/2),0);
	glRotatef(90,1,0,0);
	glScalef(Ancho_M3,Alto_M3,Largo_M3); //ancho, alto, largo
	glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();    //Rotor1 o articulacion1
	glTranslatef(0,ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2,0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,9);
	DibujarRotor(2.01f,color_rojo,RMotor3);//separcaion,color,angulo
    glPopMatrix();


    #define ACU_MOTOR4 5.0 //altura del cubo que hace de motor 4
    const  GLfloat Ancho_M4= 3, Alto_M4= ACU_MOTOR3, Largo_M4= 5;

    glPushMatrix();//cubo motor_4
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color_rojo);
	glTranslatef(0,(ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2),0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,9);
	glRotatef(RMotor3,1,0,0);
	glTranslatef(0,-(Largo_M3-Alto_M4/2-ACU_ESL1/2),0);
	glRotatef(RMotor4,1,0,0);
	glTranslatef(0,0,Largo_M4/2-Alto_M3/2);
	glScalef(Ancho_M4,Alto_M4,Largo_M4); //ancho, alto, largo
	glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();    //Rotor3 o articulacion3
	glTranslatef(0,(ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2),0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,9);
	glRotatef(RMotor3,1,0,0);
	glTranslatef(0,-(Largo_M3-Alto_M4/2-ACU_ESL1/2),0);
	DibujarRotor(2.01f,color_rojo,RMotor4);//separcaion,color,angulo
    glPopMatrix();

    #define ACI_MOTOR5 0.5 //altura del cilindro que hace de motor(o rotor) 1
    const GLfloat radio_M5= 0.7;
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE,color_azul);
	glTranslatef(0,(ACI_BASE+ACI_MOTOR1+ACU_BASE2+ACU_MOTOR2/2),0);
	glRotatef(RMotor2,1,0,0);
	glTranslatef(0,0,9);
	glRotatef(RMotor3,1,0,0);
	glTranslatef(0,-(Largo_M3-Alto_M4/2-ACU_ESL1/2),0);
	glRotatef(RMotor4,1,0,0);
	glTranslatef(0,0,4);
	glRotatef(RMotor5,0,0,1);
	glutSolidCylinder (radio_M5,ACI_MOTOR5,10,1);//radio, altura, slices,stacks
    glPopMatrix();


    glPopMatrix();
    glutSwapBuffers();
}

/**\brief Función de utilidad, usada por la función Escenario
\details Dibuja un Rotor, más preciso dos circulos paralelos que simula ser un rotor.
\param [in] separacion Distancia entre los 2 circulos paralelos.
\param [in] ColorMater Especifica el color del material con el que se han de dibujar los 2 circulos.
\param [in] angulo Varaiable que hace rotar los circulos con eje en centro, un determinado ángulo.
@see Escenario
 */
void DibujarRotor(GLfloat separacion, const GLfloat *const ColorMater,GLfloat angulo)
{
	glMaterialfv(GL_FRONT,GL_DIFFUSE,ColorMater);

	glPushMatrix();
	    glTranslatef(0-separacion,0,0); 
	    glRotatef(angulo,1,0,0);
	    glRotatef(90,0,1,0);
	    circulo();
	    glPushMatrix();
		glTranslatef(0.5,0,-0.1);
		glScalef(0.2,0.2,0);
		circulo();
	    glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	    glTranslatef(separacion,0,0); 
	    glRotatef(angulo,1,0,0);
	    glRotatef(-90,0,1,0);
	    circulo();
	glPopMatrix();
}
/** \brief Funcion de utilidad, usada por la función DibujarRotor.
\details Crea un circulo (realmente un poligono de 100 lados, aparentemente un circulo).
@see DibujarRotor
 */
void circulo()
{
        glBegin(GL_POLYGON);
            for(int i=0; i<100; i++){
               float x = (float) cos(i*2*PI/100);
               float y = (float) sin(i*2*PI/100);
               glVertex2f(x, y);
            }
        glEnd();
}

/**
 * @brief Esta función indica el área de la ventana en la que se puede dibujar.
 * @details Además establece el tipo de proyección que se utilizará. Esta función se invoca cada vez se redimensiona la ventana
 * por la callback glutReshapeFunc.
 * @param [in] w ancho de la ventana.
 * @param [in] h largo de la ventana.
 */
void VentCambios(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //area de la ventana en la que se puede dibujar
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float) w / (float)h, 1.5, 150.0);  //angulo,RATIO,Dmin,Dmax
  //glOrtho(0,10,0,10,-10,10); //define la zona de proyeccion: una caja de 10anchox10largox2deprofundo
 
  glClearColor(0.0f,0.0f,0.6f,1.0f);
  glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Esta función permite cambiar los valores de los motores y de la camara, mediante el teclado.
 * @details Se invoca cada vez que detecta que se presionó una tecla por la callback glutSpecialFunc.
 */
void controlaTeclasEspec(int key,int x, int y)
{
    GLfloat dx, dy, dz, dx0, dy0, dz0;
    GLfloat delta= 0.01f, deltaR=0.01f;

	if(key == GLUT_KEY_DOWN)
	{//increase distance from camera to origin
		dx=cx-ex; dy=cy-ey; dz=cz-ez; 
		ex-=deltaR*dx; ey-=deltaR*dy; ez-=deltaR*dz; 		
	}
    if(key == GLUT_KEY_UP)
	{//reduce distance from camera to origin (close up)
		dx=cx-ex; dy=cy-ey; dz=cz-ez; 
		ex+=deltaR*dx; ey+=deltaR*dy; ez+=deltaR*dz; 
	}
    
    if(key == GLUT_KEY_RIGHT)
		//Rotate (+) camera around origin in Oxz plane
	{
	    dx0=cz-ez;  dz0= ex - cx; 
	    dx=cx-ex;  dz=cz-ez;
	    GLfloat s=sqrtf(dx*dx+dz*dz);
	    dx+=delta*dx0;       dz+=delta*dz0;
	    GLfloat s1=sqrtf(dx*dx+dz*dz)/s;
	    dx/=s1;		dz/=s1; 
	    ex=cx-dx; ez=cz-dz;	    
	}

    if(key == GLUT_KEY_LEFT)
	//Rotate (-) camera around origin in Oxz plane
	{
	    dx0=cz-ez;  dz0= ex - cx;  
	    dx=cx-ex;  dz=cz-ez;
	    GLfloat s=sqrtf(dx*dx+dz*dz);
	    dx-=delta*dx0;    dz-=delta*dz0;
	    GLfloat s1=sqrtf(dx*dx+dz*dz)/s;
	    dx/=s1;    dz/=s1; 
	    ex=cx-dx; ez=cz-dz;
	}

    if (key == GLUT_KEY_F1)
    {
	RMotor1--;
    }

    if (key == GLUT_KEY_F2)
    {
	RMotor1++;
    }

    if (key == GLUT_KEY_F3)
    {
	    RMotor2--;
    }

    if (key == GLUT_KEY_F4)
    {
	    RMotor2++;
    }

    if (key == GLUT_KEY_F5)
    {
	    RMotor3--;
    }

    if (key == GLUT_KEY_F6)
    {
	    RMotor3++;
    }

    if (key == GLUT_KEY_F7)
    {
	    RMotor4--;
    }

    if (key == GLUT_KEY_F8)
    {
	    RMotor4++;
    }

    if(key == GLUT_KEY_F9)
	{
	    RMotor5-=4;
	}

    if(key == GLUT_KEY_F10)
	{
	    RMotor5+=4;
	}

    if(key == GLUT_KEY_PAGE_UP)
	{
	    cz++;
	}
    if(key == GLUT_KEY_PAGE_DOWN)
	{
	    cz--;
	}

    // Refresca ventana
    glutPostRedisplay();
}

/**
 * @brief Esta función configura la iluminación del escenario. Asi como la posición del foco.
 * @details Esta función es utilizada por la función config_Simulador.
 @see config_Simulador
 */
void initLuz()
{
    GLfloat colorLDifusa[] = { 0.75, 0.75, 0.75, 1.0 };
    GLfloat light0Posicion[] =  {1.0,4.0,3.0};
 
    glLightfv (GL_LIGHT0, GL_DIFFUSE, colorLDifusa);
    glLightfv(GL_LIGHT0,GL_POSITION,light0Posicion);
    
    glEnable (GL_LIGHT0);//ahora se prende la luz0
}

/**
 * @brief Lleva a cabo la configuración inicial requerida por las demás funciones del modulo de Simulación.
 * @details Determina la ventana de despligue para la función Escenario, configura la iluminación, y las callbacks glutDisplayFunc, glutReshapeFunc,glutSpecialFunc.
 * @param [in] VentanaDespliegue Dirección de la ventana donde se desplegará el simulador.
@see initLuz
@see Escenario
 */
void config_Simulador(const int VentanaDespliegue)
{
    winSimulador = VentanaDespliegue;
    glutSetWindow(winSimulador);
    initLuz();
    glutDisplayFunc(Escenario);
    glutReshapeFunc(VentCambios);
    glutSpecialFunc (controlaTeclasEspec);
}
/**
 *@brief Esta función comprueba no se sobrepasen los limites en los ángulos de los motores, según las especificaciones de BRANDI.
 *@details Esta función es invocada por la función Escenario.
@see Escenario
 */

void limitar_Motores(void)
 {
	if (RMotor2 < -180)
		RMotor2 = -180;
	if (RMotor2 > 0)
		RMotor2 = 0;
	if (RMotor3 < -180)
		RMotor3 = -180;
	if(RMotor3 > 0)
	    RMotor3 = 0;
	if(RMotor4 < 0)
	    RMotor4 = 0;
	if(RMotor4 > 180)
	    RMotor4 = 180;

 }
