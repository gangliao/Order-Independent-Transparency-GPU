#include "cookbookogl.h"
#include <GLFW/glfw3.h>

#include "glutils.h"
#include "sceneoit.h"

#include <cstdio>
#include <cstdlib>

#include <sstream>
using std::stringstream;

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Scene *scene;
GLFWwindow * window;
string title;



string parseCLArgs(int argc, char ** argv);


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		if (scene)
			scene->animate(!(scene->animating()));
	}
	
}

void initializeGL() {
  glClearColor(0.5f,0.5f,0.5f,1.0f);

  glDebugMessageCallback(GLUtils::debugCallback, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
  glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0,
      GL_DEBUG_SEVERITY_NOTIFICATION, -1 , "Start debugging");

  scene->initScene();
}

void mainLoop() {
  const int samples = 50;
  float time[samples];
  int index = 0;

  while( ! glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) {
    GLUtils::checkForOpenGLError(__FILE__,__LINE__);
    scene->update(glfwGetTime());
    scene->render();
    glfwSwapBuffers(window);
    glfwPollEvents();

    // Update FPS
    time[index] = glfwGetTime();
    index = (index + 1) % samples;

    if( index == 0 ) {
      float sum = 0.0f;
      for( int i = 0; i < samples-1 ; i++ )
        sum += time[i + 1] - time[i];
      float fps = samples / sum;

      stringstream strm;
      strm << title;
      strm.precision(4);
      strm << " (fps: " << fps << ")";
      glfwSetWindowTitle(window, strm.str().c_str());
    }
  }
}

void resizeGL(int w, int h ) {
  scene->resize(w,h);
}

int main(int argc, char *argv[])
{
  string recipe = parseCLArgs(argc, argv);

  // Initialize GLFW
  if( !glfwInit() ) exit( EXIT_FAILURE );

  // Select OpenGL 4.3 with a forward compatible core profile.
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  //	glfwWindowHint(GLFW_SAMPLES, 8);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  // Open the window
  title = "KAUST -- " + recipe;
  window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL );
  if( ! window ) {
    glfwTerminate();
    exit( EXIT_FAILURE );
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);


  // Load the OpenGL functions.
  if( ogl_LoadFunctions() == ogl_LOAD_FAILED ) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  GLUtils::dumpGLInfo();

  // Initialization
  initializeGL();
  resizeGL(WIN_WIDTH,WIN_HEIGHT);

  // Enter the main loop
  mainLoop();

  // Close window and terminate GLFW
  glfwTerminate();
  // Exit program
  exit( EXIT_SUCCESS );
}

string parseCLArgs(int argc, char ** argv) {



  string recipe = "OIT";

  
    scene = new SceneOit();
 

  return recipe;
}


