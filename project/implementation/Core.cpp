#include "Core.h"
#include "SceneManager.h"
#include "TheRenderer.h"
#include "TheTime.h"
#include "Logic.h"
#include "Physics.h"

#include "TestScene.cpp"
#include "StartScene.cpp"
#include "CrashScene.cpp"

//Needed to have Visual Studio recompile core.cpp in all incremental builds. Does not do anything, but can be changed to code is updated and recompile triggered
//bool justAnotherBoolInTheWall = false;

SceneManager sceneManager;
TheRenderer renderer;
TheTime theTime;
Logic logic;
Physics physics;
ObjectManager o;

//Variables for physics/collision detection
double accumulatedTime = 0;
double const FIXED_TIME_INTERVAL = 0.014;

//Driving variables
float acceleration = 0.f;
float turning = 0.f;
float _cameraSpeed = 2.0f;
float translationSpeed = 0.2f;
float translationOffset = 0.4f;
float turningFactor = 1.5f;
float accelerationFactor = 1.0f;
float brakeFactor = -1.0f;
vmml::Vector3f position = vmml::Vector3f(0,0,0);
vmml::Vector3f velocity = vmml::Vector3f(0,0,0);

//Day and night cycle variables
float pi = 3.1414f;
float frequency = 3.0f;
GLfloat dayNightPulse = 0.0f;
vmml::Vector3f lightDirection = vmml::Vector3f(1.f, 1.f, 1.f);
GLfloat directionFloat = 0.0f;
GLfloat treeAnimation = 0.0f;

bool isDebug = false;
bool isTouched;
DepthMapPtr dpr;


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

		bRenderer().initRenderer(1600, 900, false, "Needless speed");		// windowed mode on desktop
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

				 		std::cout<< "-----------------------------------------------\n";	


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



	//ShaderPtr uiShader = bRenderer().getObjects()->loadShaderFile("uishader", 0, false, false, false, false, false);
	//MaterialPtr blurMaterial = bRenderer().getObjects()->createMaterial("blurMaterial", uiShader);								// create an empty material to assign either texture1 or texture2 to

	//std::cout<< "-----------------------------------------------\n";	


    // Create camera
    bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.f, -4.5f, -3.0f), vmml::Vector3f(-0.5f, 0.f, 0.f));
    //bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.f, -34.5f, -3.0f), vmml::Vector3f(-1.57f, 0.f, 0.f));

	bRenderer().getObjects()->createCamera("shadowCamera", vmml::Vector3f(0.f, -100.5f, .0f), vmml::Vector3f(-1.57f, 0.f, 0.f));
	//bRenderer().getObjects()->createCamera("shadowCamera", vmml::Vector3f(0.f, -4.5f, -3.0f), vmml::Vector3f(-0.5f, 0.f, 0.f));


	bRenderer().getObjects()->createFramebuffer("fbo");	
	dpr = bRenderer().getObjects()->createDepthMap("depthMap", 1024, 1024);	// create texture to bind to the fbo

	//bRenderer().getObjects()->createSprite("sprite",blurMaterial);															// create a sprite using the material created above

	bRenderer().getObjects()->loadTexture("colorLUT.png");
    //bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.0f, 0.0f, 10.0f), vmml::Vector3f(0.f, 0.0f, 0.f));
    
    // Create scenes
	SceneManager::addScene("Start", new StartScene); //Start Menu Scene
	SceneManager::addScene("Test", new TestScene); //Game Scene
	SceneManager::addScene("Crash", new CrashScene); //Crash Scene

	renderer.setRenderer(&bRenderer(), &_running);
	SceneManager::loadScene("Start");
    
    // Set starting postion
    //bRenderer().getObjects()->getCamera("camera")->setPosition(vmml::Vector3f(-50, 480, -580));

}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Draw your scene here */
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Core::loopFunction(const double &deltaTime, const double &elapsedTime)
{



	theTime.setTime(deltaTime, elapsedTime);
	// Update Physics for collisions
	accumulatedTime += deltaTime;
	if (accumulatedTime > FIXED_TIME_INTERVAL) {
		Physics::update();
		accumulatedTime = 0;
	}



	//Inputs for Scenes WINDOWS
	GLint current1 = TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_1);

	if (current1 != last1) {
		last1 = current1;
		if (current1 == bRenderer::INPUT_PRESS) {
			SceneManager::loadScene("Test");
		}
	}


	//Inputs for Scenes IOS
	TouchMap touchMap = TheRenderer::Instance()->renderer->getInput()->getTouches();

	//Start Scene, so any touch should start the game
	if (SceneManager::getCurrentName().compare("Start") == 0) {
		for (auto t = touchMap.begin(); t != touchMap.end(); ++t)
		{
			SceneManager::loadScene("Test");
		}
	}

	//If the game is running
	if (SceneManager::getCurrentName().compare("Test") == 0) {

		std::vector<GameObject*> livingObjects = SceneManager::getCurrentScene()->gameObjectList;

		bool carAlive = false;
		for (std::vector<GameObject*>::iterator it = livingObjects.begin(); it != livingObjects.end(); ++it) {
			if ((*it)->name.find("Car") != std::string::npos) {
				carAlive = true;
			}
		}

		//Go to end screen if player crashed the spaceship (LOST)
		if (!carAlive) {
			SceneManager::loadScene("Crash");
		}

		//If crash menu then restart the game by tapping
		isTouched = false;
		if (SceneManager::getCurrentName().compare("Crash") == 0) {

			touchMap.clear();
			touchMap = TheRenderer::Instance()->renderer->getInput()->getTouches();
			for (auto t = touchMap.begin(); t != touchMap.end(); ++t)
			{
				SceneManager::loadScene("Test");
			}
		}

	}


	Logic::update();
	Logic::lateUpdate();
	renderer.renderShadows();
	renderer.render();
	//vmml::Matrix4f modelMatrix = vmml::create_translation(vmml::Vector3f(0.0f, 0.0f, -0.5));
	//bRenderer().getObjects()->getFramebuffer("fbo")->bindDepthMap(bRenderer().getObjects()->getTexture("depthMap"));
	//bRenderer().getObjects()->getMaterial("blurMaterial")->setTexture("fbo_texture", dpr);

	//bRenderer().getModelRenderer()->drawModel(bRenderer().getObjects()->getModel("sprite"), modelMatrix, _viewMatrixHUD, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false);
	//std::cout<<"--------------------------------------------------3\n"<<std::endl;



}


/* This function is executed when terminatingthe renderer */
void Core::terminateFunction()
{
	Logic::destroy();
	renderer.destroy();
	Physics::destroy();
	SceneManager::destroy();

	bRenderer::log("(EX)TERMINATE");
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