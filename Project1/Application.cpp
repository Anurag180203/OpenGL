//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h" 

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        (glfwTerminate());
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        //float positions[] = {
        //    -50.0f, -50.0f, 0.0f, 0.0f, //0
        //     50.0f, -50.0f, 1.0f, 0.0f, //1
        //     50.0f,  50.0f, 1.0f, 1.0f, //2
        //    -50.0f,  50.0f, 0.0f, 1.0f  //3
        //};

        //unsigned int indices[] = {
        //    0, 1, 2,
        //    2, 3, 0
        //};

        //unsigned int vao;   //vertex array object
        //GLCall(glGenVertexArrays(1, &vao));
        //GLCall(glBindVertexArray(vao));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

       /* VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb,layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f,-1.0f ,1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        Shader shader("Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


        Texture texture("1.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture" ,0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind(); 
        shader.Unbind();*/

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        /*glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);
        
        float r = 0.0f;
        float increment = 0.05f;*/

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

            /* Render here */
            renderer.Clear();

            //glBegin(GL_TRIANGLES);  //Legacy openGL
            //glVertex2f(-0.5f, -0.5f);
            //glVertex2f( 0.0f,  0.5f);
            //glVertex2f( 0.5f, -0.5f);
            //glEnd();

            ImGui_ImplGlfwGL3_NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            //{
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            //    glm::mat4 mvp = proj * view * model;
            //    //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            //    shader.Bind();
            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}
            //
            //{
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            //    glm::mat4 mvp = proj * view * model;
            //    shader.Bind();
            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}

            //if (r > 10.f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;

            //r += increment;

            //{
            //    ImGui::SliderFloat3("translation A", &translationA.x, 0.0f, 960.0f);           // Edit 1 float using a slider from 0.0f to 1.0f    
            //    ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, 960.0f);
            //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //}

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}