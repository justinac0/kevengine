#ifndef ENGINE_H
#define ENGINE_H

#include "BufferUtil.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"

#include <thread>

class Engine {
private:

public:
	/////////////////// temporary vars -- will be automatitacally gathered from a scene file

	Shader shader;
	Shader skyBoxShader;
	Shader sunShader;
	Camera camera;
	Model model;
	Model skybox;
	Model sun;

	///////////////////

	Window window;

	Engine();
	~Engine();

	void start();
	void stop();
};

#endif // ENGINE_H
