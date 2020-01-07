#include "Engine.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void run(Engine* engine) {
	engine->window.create(800, 600, "kevengine");

	engine->model.load("./bin/models/terrain.obj");
	engine->skybox.load("./bin/models/sphere.obj");
	engine->sun.load("./bin/models/sphere.obj");

    engine->shader.load("./bin/shaders/vertex.glsl", "./bin/shaders/fragment.glsl");
    engine->skyBoxShader.load("./bin/shaders/sb_vertex.glsl", "./bin/shaders/sb_fragment.glsl");
    engine->sunShader.load("./bin/shaders/sun_vertex.glsl", "./bin/shaders/sun_fragment.glsl");

    engine->sun.move(400, 6500, -400);
    engine->sun.setScale(500, 500, 500);

	engine->camera.init(0.5f, 4.0f);

	while (!glfwWindowShouldClose(engine->window.getHandle())) {
        glfwPollEvents();
        glfwSwapBuffers(engine->window.getHandle());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        engine->camera.update(engine->window.getHandle());

        // draw gradient skybox
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        engine->skyBoxShader.use();
        engine->skyBoxShader.sendUniformMat4("perspective", engine->camera.getPerspectiveMatrix());
        engine->skyBoxShader.sendUniformMat4("view", glm::mat4(glm::mat3(engine->camera.getViewMatrix())));
        engine->skybox.render();

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        // draw sun
        engine->sunShader.use();
        engine->sunShader.sendUniformMat4("perspective", engine->camera.getPerspectiveMatrix());
        engine->sunShader.sendUniformMat4("view", engine->camera.getViewMatrix());
        engine->sunShader.sendUniformMat4("model", engine->sun.getMatrix());
        engine->sun.render();

        // draw terrain
        engine->shader.use();
        engine->shader.sendUniformVec3("lightPosition", engine->sun.getPosition());
        engine->shader.sendUniformMat4("perspective", engine->camera.getPerspectiveMatrix());
        engine->shader.sendUniformMat4("view", engine->camera.getViewMatrix());
        engine->shader.sendUniformMat4("model", engine->model.getMatrix());
        engine->model.render();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

Engine::Engine() {

}

Engine::~Engine() {

}

void Engine::start() {
	std::thread mainThread(run, this);
	mainThread.join();
}

void Engine::stop() {

}
