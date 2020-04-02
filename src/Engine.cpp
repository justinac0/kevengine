#include "Engine.h"

Shader shader;
Shader sunShader;
Camera camera;
Model model;
Model sun;

Engine::Engine() {

}

Engine::~Engine() {

}

void Engine::start() {
	this->rendererThread = new std::thread(Engine::update, this);
	this->rendererThread->join();
}


void Engine::update(Engine* engine) {
	engine->window.create(800, 600, "kevengine");
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "OPENGL EXT ERROR" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);

	model.load("./bin/models/cube.obj");
	model.setScale(10, 10, 10);
	sun.load("./bin/models/sphere.obj");

    shader.load("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    sunShader.load("./bin/shaders/sun_vertex.glsl", "./bin/shaders/sun_fragment.glsl");

    sun.move(400, 6500, -400);
    sun.setScale(500, 500, 500);

	camera.init(0.5f, 4.0f);

	while (!glfwWindowShouldClose(engine->window.getHandle())) {
		glfwPollEvents();
		glfwSwapBuffers(engine->window.getHandle());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.update(engine->window.getHandle());

		// draw sun
		sunShader.use();
		sunShader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
		sunShader.sendUniformMat4("view", camera.getViewMatrix());
		sunShader.sendUniformMat4("model", sun.getMatrix());
		sun.render();

		// draw terrain
		shader.use();
		shader.sendUniformVec3("lightPosition", sun.getPosition());
		shader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
		shader.sendUniformMat4("view", camera.getViewMatrix());
		shader.sendUniformMat4("model", model.getMatrix());
		model.render();
	}
}

void Engine::stop() {

}
