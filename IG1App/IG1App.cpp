#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mCamera2 = new Camera(mViewPort);
	mScene = new Scene;

	mCamera->set2D();
	mScene->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mCamera2; mCamera2 = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::update()
{
	if (updating) {

		if ((glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime) > 17) { //a 60 fps, hay 16.6666 ms entre frame y frame

			mScene->update();
			display();
			mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
		}
	}

}
//-------------------------------------------------------------------------


void IG1App::display() const
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (splitViewport) {

		splitDisplay();
	}
	else {

		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	}

	glutSwapBuffers();	// swaps the front and back buffer
}

//-------------------------------------------------------------------------

void IG1App::splitDisplay() const
{
	Viewport viewTemp = *mViewPort;
	mViewPort->setSize(mWinW / 2, mWinH);
	mViewPort->setPos(0, 0);
	mCamera->setSize(mWinW / 2, mWinH);
	mScene->render(*mCamera);  // uploads the viewport and camera to the GPU

	mViewPort->setPos(mWinW / 2, 0);
	mCamera2->setCenital();
	mCamera2->setSize(mWinW / 2, mWinH);
	mScene->render(*mCamera2);  // uploads the viewport and camera to the GPU

	mCamera->setSize(mWinW, mWinH);

	*mViewPort = viewTemp;
}


//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
	case 'U':
		updating = !updating;
		break;
	case 'P':
	case 'p':
		mCamera->changePrj();
		mCamera2->changePrj();
		break;
	case 'v':
		cout << "Foto guardada\n";
		mScene->saveCapture();
		break;
	case 'q':
		mScene->setActiveLight(0,true);
		break;
	case 'w':
		mScene->setActiveLight(0, false);
		break;
	case 'a':
		mScene->setActiveLight(1, true);
		break;
	case 's':
		mScene->setActiveLight(1, false);
		break;
	case 'z':
		mScene->setActiveLight(2, true);
		break;
	case 'x':
		mScene->setActiveLight(2, false);
		break;
	case 'd':
		mScene->setActiveLight(3, true);
		break;
	case 'f':
		mScene->setActiveLight(3, false);
		break;
	case 't':
		mScene->setActiveLight(4, true);
		break;
	case 'g':
		mScene->setActiveLight(4, false);
		break;
	case 'e':
		mScene->setLightOff();
		break;
	case 'k':
	case 'K':
		splitViewport = !splitViewport;
		break;
	case '0':
		delete mScene;
		mScene = new Scene;
		mScene->setState(0);
		mScene->init();
		break;
	case '1':
		delete mScene;
		mScene = new Scene;
		mScene->setState(1);
		mScene->init();
		break;
	case '2':
		delete mScene;
		mScene = new Scene;
		mScene->setState(2);
		mScene->init();
		break;
	case '3':
		delete mScene;
		mScene = new Scene;
		mScene->setState(3);
		mScene->init();

	break;	case '4':
		delete mScene;
		mScene = new Scene;
		mScene->setState(4);
		mScene->init();

	break;	case '5':
		delete mScene;
		mScene = new Scene;
		mScene->setState(5);
		mScene->init();
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		mCamera->moveLR(1);
		break;
	case GLUT_KEY_LEFT:
		mCamera->moveLR(-1);
		break;
	case GLUT_KEY_UP:
		mCamera->moveUD(1);
	case GLUT_KEY_DOWN:
		mCamera->moveUD(-1);
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseButt = button;
	mMouseCoord = glm::dvec2(x, winHeight() - y);
}
//-------------------------------------------------------------------------

void IG1App::motion(int x, int y)
{
	if (mCamera->isCenital()) mCamera->set2D();
	// guardamos la anterior posición en var. temp.
	glm::dvec2 mp = mMouseCoord;
	// Guardamos la posición actual
	mMouseCoord = glm::dvec2(x, winHeight() - y);
	mp = (mMouseCoord - mp); // calculamos el desplazamiento realizado

	if (mMouseButt == GLUT_LEFT_BUTTON) {
		mCamera->orbit(-mp.x * 0.05, -mp.y); // sensitivity = 0.05
	}
	else if (mMouseButt == GLUT_RIGHT_BUTTON) {
		mCamera->moveLR(-mp.x);
		mCamera->moveUD(-mp.y);
	}

	glutPostRedisplay();
}
//-------------------------------------------------------------------------

void IG1App::mouseWheel(int wheelNumber, int direction, int x, int y)
{
	glutPostRedisplay();

	//GLUT_ACTIVE_CTRL / _ALT / _SHIFT
	int m = glutGetModifiers();
	if (m == 0) // ninguna está presionada
	{
		mCamera->moveFB(direction * 10);
	}
	else if (m == GLUT_ACTIVE_CTRL)
	{
		if (direction == 1) mCamera->setScale(+0.01);
		else mCamera->setScale(-0.01);
	}

	glutPostRedisplay();
}
//-------------------------------------------------------------------------


