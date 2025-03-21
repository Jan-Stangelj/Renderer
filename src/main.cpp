#include "window.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "model.hpp"
#include "gbuffer.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

int main(){ 
    Renderer::Window Window(1280, 720, "Renderer", true);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Dosent work on wayland -> dosent work for me
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window.getGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();

    Renderer::Shader buffer("../src/shaders/buffer.vert", "../src/shaders/buffer.frag");
    Renderer::Shader lighting("../src/shaders/basicquad.vert", "../src/shaders/lighting.frag");
    lighting.use();
    lighting.setVec3("skybox", glm::vec3(0.2f, 0.2f, 0.3f));

    Renderer::Model sponza("../assets/models/sponza/Sponza.gltf");
    sponza.size = glm::vec3(0.005f);

    Renderer::Model helmet("../assets/models/helmet/DamagedHelmet.gltf");
    helmet.size = glm::vec3(0.25f);
    helmet.position = glm::vec3(0.0f, 1.0f, 0.0f);
    helmet.rotation = glm::vec3(90.0f, 0.0f, 0.0f);

    Renderer::PointLight light(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), 32.0f);
    light.Bind(lighting, 0);
    Renderer::PointLight light2(glm::vec3(3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 32.0f);
    light2.Bind(lighting, 1);
    Renderer::PointLight light3(glm::vec3(-3.0f, 2.0f, 0.0f), glm::vec3(1.0f), 32.0f);
    light3.Bind(lighting, 2);

    Renderer::SpotLight light4(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(1.0f), 16.0f, glm::vec3(0.0f, 0.0f, -1.0f), 15.0f, 60.0f);
    light4.Bind(lighting, 0);

    lighting.use();
    lighting.setInt("numPointLights", 3);
    lighting.setInt("numSpotLights", 1);
    lighting.setInt("numDirLights", 0);

    // Camera
    Renderer::Camera cam(60.0f, Window.resolution().x/Window.resolution().y, 0.1f, 1000.0f);
    cam.setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

    Renderer::gBuffer deferredBuffer(Window.resolution());


    float exposure = 1.0f;


    // Main loop
    while (!Window.shouldWindowClose()){
        Window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        cam.cameraMovement(Window, Window.deltaTime(), 1.5f);
        cam.cameraRotation(0.075f);
        lighting.use();
        cam.applyToShader(lighting);
        buffer.use();
        cam.applyToShader(buffer);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        lighting.use();
        lighting.setFloat("exposure", exposure);

        deferredBuffer.bindFramebuffer();
        glClearColor(pow(0.2f, 2.2), pow(0.3f, 2.2), pow(0.3f, 2.2), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sponza.draw(buffer);
        helmet.draw(buffer);
        deferredBuffer.unbindFramebuffer();

        lighting.use();
        deferredBuffer.bindTextures(lighting);
        deferredBuffer.renderQuad();

        ImGui::Begin("Settings");
        std::string frametime = "Frametime: " + std::to_string(Window.deltaTime()) + "ms";
        std::string fps = "FPS: " + std::to_string((int)floor(1.0f / Window.deltaTime()));
        ImGui::Text(frametime.c_str());
        ImGui::Text(fps.c_str());
        ImGui::DragFloat("Exposure", &exposure, 0.01f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        Window.swapBuffers();

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(Window.getGlfwWindow());
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}