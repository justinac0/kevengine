#include "Engine.h"

Shader shader;
Shader skyBoxShader;
Shader sunShader;
Camera camera;
Model model;
Model skybox;
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

	model.load("./bin/models/terrain.obj");
	skybox.load("./bin/models/sphere.obj");
	sun.load("./bin/models/sphere.obj");

    shader.load("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    skyBoxShader.load("./bin/shaders/sb_vertex.glsl", "./bin/shaders/sb_fragment.glsl");
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
		
		// draw gradient skybox
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		skyBoxShader.use();
		skyBoxShader.sendUniformMat4("perspective", camera.getPerspectiveMatrix());
		skyBoxShader.sendUniformMat4("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
		skybox.render();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);

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
