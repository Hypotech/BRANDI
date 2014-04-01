/**
 * @mainpage Taller de Mecatrónica
 * @author Hipólito Morales Christian
 * 
 */

#include "Simulador/Animacion.hpp"
#include "Kinect/TrackingKinect.hpp"
//#include "USB/usbConexion.hpp"
#include <cstdlib>

extern GLfloat RMotor1; extern GLfloat RMotor2; extern GLfloat RMotor3; extern GLfloat RMotor4; extern GLfloat RMotor5;

//extern float AnguloManoIzq; extern float AnguloMunyecaIzq; extern float AnguloCodoIzq;
extern float AnguloManoDer; extern float AnguloMunyecaDer; extern float AnguloCodoDer;

/**
 * Indices que se utilizan para determinar de manera practica que buffer corresponde cada motor.
 */
enum motores {
    MOTOR1, /*!< 0 */
    MOTOR2, /*!< 1 */
    MOTOR3, /*!< 2 */
    MOTOR4, /*!< 3 */
    MOTOR5  /*!< 4 */
};

/**
 * @brief Lleva a cabo la interfaz entre el Kinect y el simulador.
 * @details Se pretendia que también mandará los valores al robot BRANDI, vía USB.
 * @warning La funcionalidad de comunicación USB con el robot BRANDI contiene errores y por lo tanto se deshabilitado.
 */
void Kinect_mandarValores_Simulador_y_BRANDI();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    int mainVentana = glutCreateWindow ("BRANDI");
    
    config_Simulador(mainVentana);
    ini_Kinect();

    inicializar_USB();
    glutIdleFunc(Kinect_mandarValores_Simulador_y_BRANDI);

    glutMainLoop();
    atexit(Libera_Kinect);
    return 0;
}

void Kinect_mandarValores_Simulador_y_BRANDI()
{
    if (GetKinectFrame() != FALSE)
    {

	 RMotor2 = AnguloCodoDer;
	 RMotor3 = AnguloMunyecaDer;
	 RMotor4 = AnguloManoDer;
     }

	// char DatosUSB[5];
	// DatosUSB[MOTOR1] = (char)0; 
	// DatosUSB[MOTOR2] = (char)(AnguloCodoDer * 255/180);   
	// DatosUSB[MOTOR3] = (char)(AnguloMunyecaDer * 255/280);
	// DatosUSB[MOTOR4] = (char)(AnguloManoDer * 255/280);
	// DatosUSB[MOTOR5] = (char)0;		      
	// enviar_Dato_USB(DatosUSB,5);

    glutPostRedisplay();
}

