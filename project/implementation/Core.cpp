#include "Core.h"
#include "SceneManager.h"
#include "TheRenderer.h"
#include "TheTime.h"
#include "Logic.h"
#include "Physics.h"
#include "PostProcessing.h"

#include "TestScene.cpp"

SceneManager sceneManager;
TheRenderer renderer;
TheTime theTime;
Logic logic;
Physics physics;
PostProcessing postProcessing;
ObjectManager o;

double accumulatedTime = 0;
double const FIXED_TIME_INTERVAL = 0.014;
int asteroidAmount = 30;

float acceleration = 0.f;
float turning = 0.f;
float pi = 3.1414f;
float frequency = 2.0f;
float _cameraSpeed = 2.0f;
float translationSpeed = 0.2f;
float translationOffset = 0.4f;
float turningFactor = 1.5f;
float accelerationFactor = 1.0f;
float brakeFactor = -1.0f;
vmml::Vector3f position = vmml::Vector3f(0,0,0);
vmml::Vector3f velocity = vmml::Vector3f(0,0,0);

bool isDebug = false;
bool doPostProcessing = true;
bool isTouched;

const vmml::Vector3f greenLight = vmml::Vector3f(0.0f, 1.0f, 0.0f);
const vmml::Vector3f lightBlueLight = vmml::Vector3f(0.5f, 0.5f, 1.0f);
const vmml::Vector3f whiteLight = vmml::Vector3f(1.0f, 1.0f, 1.0f);

vmml::Vector3f cameraPosition;

/* Cache things */
GLint lastSPACE, lastO, lastP, last1, last2;
float logicUpdate, physicsUpdate, logicFixedUpdate, preProcessing, postProcessingTime, render, logicLateUpdate, uiDraw;

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Initialize the Project */
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Core::init()
{
	bRenderer::loadConfigFile("config.json");	// load custom configurations replacing the default values in Configuration.cpp

												// let the renderer create an OpenGL context and the main window
	if (Input::isTouchDevice())
		bRenderer().initRenderer(true);										// full screen on iOS
	else
		bRenderer().initRenderer(1600, 900, false, "ASTEROIDS 3D");		// windowed mode on desktop
																			//bRenderer().initRenderer(View::getScreenWidth(), View::getScreenHeight(), true);		// full screen using full width and height of the screen

	// start main loop 
	bRenderer().runRenderer();
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* This function is executed when initializing the renderer */
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Core::initFunction()
{
	// get OpenGL and shading language version
	bRenderer::log("OpenGL Version: ", glGetString(GL_VERSION));
	bRenderer::log("Shading Language Version: ", glGetString(GL_SHADING_LANGUAGE_VERSION));

	acceleration = 0.0f;
	turning = 0.0f;
	pi = 3.14f;
	frequency = 0.2f;
	GLfloat dayNightPulse = 0.0f;
	_offset = 0.0f;
	_randomOffset = 0.0f;
	_cameraSpeed = 2.0f;
	_running = true;
	 _lastStateSpaceKey = bRenderer::INPUT_UNDEFINED;

	// set shader versions (optional)
	bRenderer().getObjects()->setShaderVersionDesktop("#version 120");
	bRenderer().getObjects()->setShaderVersionES("#version 100");
	_viewMatrixHUD = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);

    // Create camera before loading the space since its position is needed for the skybox
    bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.f, -35.5f, 4.0f), vmml::Vector3f(-1.3f, 0.f, 0.f));
    bRenderer().getObjects()->loadTexture("colorLUT.png");
    //bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.0f, 0.0f, 10.0f), vmml::Vector3f(0.f, 0.0f, 0.f));
    
    // Create scenes
	SceneManager::addScene("Test", new TestScene);

	renderer.setRenderer(&bRenderer(), &_running);
	SceneManager::loadScene("Test");

	//PostProcessing::init();
    
    // Set starting postion
    //bRenderer().getObjects()->getCamera("camera")->setPosition(vmml::Vector3f(-50, 480, -580));
    

    // *******************************************************************************************************************************************************************************************
    // Lights
    // *******************************************************************************************************************************************************************************************
    
    //bRenderer().getObjects()->setAmbientColor(vmml::Vector3f(20 / 255.0, 20 / 255.0, 20 / 255.0));
    
    //bRenderer().getObjects()->createLight("firstLight", vmml::Vector3f(-800.0f, 0.0f, 0.0f), vmml::Vector3f(0.5f, 0.5f, 1.0f), vmml::Vector3f(1.0f, 1.0f, 1.0f), 10000.0f, 0.4f, 9000.0f);
    
    //bRenderer().getObjects()->createLight("shipLight", vmml::Vector3f(800.0f, 0.0f, 0.0f), vmml::Vector3f(1.0f, 1.0f, 1.0f), vmml::Vector3f(1.0f, 1.0f, 1.0f), 10000.0f, 0.4f, 9000.0f);

    

}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Draw your scene here */
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Core::loopFunction(const double &deltaTime, const double &elapsedTime)
{

	theTime.setTime(deltaTime, elapsedTime);

	Logic::update();
	renderer.render();
}

/* This function is executed when terminating the renderer */
void Core::terminateFunction()
{
	Logic::destroy();
	renderer.destroy();
	Physics::destroy();
	SceneManager::destroy();

	bRenderer::log("I fucked shit up");
}


/* For iOS only: Handle device rotation */
void Core::deviceRotated()
{
	if (bRenderer().isInitialized()) {
		// set view to full screen after device rotation
		bRenderer().getView()->setFullscreen(true);
		bRenderer::log("Device rotated");
	}
}

/* For iOS only: Handle app going into background */
void Core::appWillResignActive()
{
	if (bRenderer().isInitialized()) {
		// stop the renderer when the app isn't active
		bRenderer().stopRenderer();
	}
}

/* For iOS only: Handle app coming back from background */
void Core::appDidBecomeActive()
{
	if (bRenderer().isInitialized()) {
		// run the renderer as soon as the app is active
		bRenderer().runRenderer();
	}
}

/* For iOS only: Handle app being terminated */
void Core::appWillTerminate()
{
	if (bRenderer().isInitialized()) {
		// terminate renderer before the app is closed
		bRenderer().terminateRenderer();
	}
}

/* Helper functions */
GLfloat Core::randomNumber(GLfloat min, GLfloat max) {
	return min + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (max - min)));
}