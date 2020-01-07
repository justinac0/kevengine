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
	std::thread* rendererThread;

public:
	Window window;

	Engine();
	~Engine();

	void start();
	static void update(Engine* engine);
	void stop();
};

#endif // ENGINE_H
