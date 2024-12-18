﻿#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <stb/stb_image.h>

#include <Engine/EngineEnums.hpp>
#include <Engine/Entity.hpp>
#include <Engine/Game.hpp>

#include <algorithm>
#include <iostream>
#include <stdexcept>

//---------------------------------------------------------------

Game::Game(const int screenWidth, const int screenHeight, const char* title)
    : m_height(screenHeight)
    , m_width(screenWidth)
    , m_scaleFactorX(70.0 * m_width / 1600 / m_width)
    , m_scaleFactorY(70.0 * m_height / 900 / m_height)
    , m_guiManager(static_cast<float>(m_width) / 1600)
    , m_dtFactor(0.1)
    , m_lastTime(0)
    , m_VAO()
    , m_VBO()
    , m_boundTexture(0)
{
    if (!glfwInit())
    {
        SetOutcome("Cannot initialize GLFW");
        return;
    }

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (!m_window)
    {
        SetOutcome("Cannot create window");
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        SetOutcome("Cannot initialize GLEW");
        return;
    }

    // Compile Shader
    m_vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 v_TexCoord;
        void main() {
            gl_Position = vec4(aPos, 1.0);
            v_TexCoord = aTexCoord;
        }
    )";

    m_fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 v_TexCoord;
        uniform sampler2D u_Texture;
        void main() {
            FragColor = texture(u_Texture, v_TexCoord);
        }
    )";

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(m_vertexShader);

    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, nullptr);
    glCompileShader(m_fragmentShader);

    // Check for shader compilation errors
    CheckShaderCompilation(m_vertexShader);
    CheckShaderCompilation(m_fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    // Check for program linking errors
    CheckProgramLinking(m_shaderProgram);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(double), nullptr, GL_DYNAMIC_DRAW);

    // Cube positions in m_positions (id 0, 1, 4, 5, 8, 9...)
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);

    // Image positions in m_positions (id 2, 3, 6, 7, 10, 11...)
    glVertexAttribPointer(
        1,
        2,
        GL_DOUBLE,
        GL_FALSE,
        4 * sizeof(double),
        reinterpret_cast<const void*>(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    unsigned char* image = stbi_load("res/textures/img.png", &width, &height, &channels, 4);
    if (!image)
    {
        std::cerr << "Failed to load image" << '\n';
        return;
    }

    constexpr int tileSize = 256;
    const int noOfRows = height / tileSize;
    const int noOfCols = width / tileSize;
    const int noOfTextures = noOfRows * noOfCols;
    m_textureIDs = std::make_unique<unsigned int[]>(noOfTextures);

    // Generate textures
    glGenTextures(noOfTextures, m_textureIDs.get());
    constexpr int noOfBlocks = tileSize * tileSize;
    constexpr int size = noOfBlocks * 4;
    auto* imageData = new unsigned char[size]; // Allocate memory for a 256x256 texture
    for (int i = 0; i < noOfTextures; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        const int row = i / noOfRows;
        const int col = i % noOfCols;

        for (int y = 0; y < tileSize; ++y)
        {
            for (int x = 0; x < tileSize; ++x)
            {
                // Calculate the position in the original image
                const int originalX = col * tileSize + x;
                const int originalY = row * tileSize + y;

                // Calculate the position in the current texture
                const int textureIndex = (y * tileSize + x) * 4;
                const int imageIndex = (originalY * width + originalX) * 4;

                // Copy pixel data
                for (int channel = 0; channel < 4; ++channel)
                {
                    // Calculation to prevent texture from being mirrored
                    const int arrIndex = textureIndex + channel;
                    const int blockIndex = arrIndex / 4;
                    const int indexInBlock = arrIndex % 4;
                    const int internalTextureIndex = (noOfBlocks - 1 - blockIndex) * 4 + indexInBlock;
                    imageData[internalTextureIndex] = image[imageIndex + channel];
                }
            }
        }

        // Load the texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tileSize, tileSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }
    delete[] imageData;
    stbi_image_free(image);

    // Set icon
    stbi_set_flip_vertically_on_load(0);
    image = stbi_load("res/textures/icon.png", &width, &height, &channels, 4);

    if (!image)
    {
        std::cerr << "Failed to load icon image" << '\n';
        return;
    }

    GLFWimage icons[1];
    icons[0].width = width;
    icons[0].height = height;
    icons[0].pixels = image;

    glfwSetWindowIcon(m_window, 1, icons);
    stbi_image_free(image);

    // Bind texture to sampler
    glUseProgram(m_shaderProgram);
    glUniform1i(glGetUniformLocation(m_shaderProgram, "u_Texture"), 0);

    m_guiManager.AddFont(InitImGui());
}

//---------------------------------------------------------------

Game::~Game()
{
    TerminateShader();
    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//---------------------------------------------------------------

void Game::CheckShaderCompilation(const unsigned int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error:\n" << infoLog << '\n';
    }
}

//---------------------------------------------------------------

bool Game::CheckTime()
{
    const double currentTime = glfwGetTime();
    const double dt = currentTime - m_lastTime;
    if (dt >= m_dtFactor)
    {
        m_lastTime = currentTime;
        return true;
    }

    return false;
}

//---------------------------------------------------------------

void Game::CheckProgramLinking(const unsigned int program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking error:\n" << infoLog << '\n';
    }
}

//---------------------------------------------------------------

void Game::CheckOpenGLError(const char* checkpoint)
{
    const unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
        std::cerr << "OpenGL error (" << checkpoint << "): " << error << '\n';
}

//---------------------------------------------------------------

bool Game::CheckPressedKey(const Key key) const
{
    const std::vector<int> glfwKeys = GetGLFWKeys(key);

    return std::ranges::any_of(
        glfwKeys.begin(),
        glfwKeys.end(),
        [&](const int glfwKey) { return glfwGetKey(m_window, glfwKey) == GLFW_PRESS; });
}

//---------------------------------------------------------------

void Game::DrawSquare(const std::shared_ptr<Entity>& entity)
{
    const int boundTexture = entity->m_imageID + entity->m_imageOffset;
    if (m_boundTexture != boundTexture)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureIDs[boundTexture]);
        m_boundTexture = boundTexture;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(entity->m_positions), entity->m_positions);

    glUseProgram(m_shaderProgram);
    CheckProgramLinking(m_shaderProgram);
    glBindVertexArray(m_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//---------------------------------------------------------------

void Game::DrawSquare(const Entity& entity)
{
    const int boundTexture = entity.m_imageID + entity.m_imageOffset;
    if (m_boundTexture != boundTexture)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureIDs[boundTexture]);
        m_boundTexture = boundTexture;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(entity.m_positions), entity.m_positions);

    glUseProgram(m_shaderProgram);
    CheckProgramLinking(m_shaderProgram);
    glBindVertexArray(m_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//---------------------------------------------------------------

ImGuiIO& Game::InitImGui() const
{
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return io;
}

//---------------------------------------------------------------

void Game::Loop()
{
    m_lastTime = glfwGetTime();
    while (!ShouldTerminate())
    {
        // Set the clear color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Poll for and process events
        glfwPollEvents();

        if (InternalLoop())
            break;

        // Swap front and back buffers
        glfwSwapBuffers(m_window);
    }
}

//---------------------------------------------------------------

std::vector<int> Game::GetGLFWKeys(const Key key)
{
    std::vector<int> glfwKeys;
    switch (key)
    {
        case Key::UP:
        {
            glfwKeys.reserve(2);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_W, GLFW_KEY_UP });
            break;
        }
        case Key::DOWN:
        {
            glfwKeys.reserve(2);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_S, GLFW_KEY_DOWN });
            break;
        }
        case Key::LEFT:
        {
            glfwKeys.reserve(2);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_A, GLFW_KEY_LEFT });
            break;
        }
        case Key::RIGHT:
        {
            glfwKeys.reserve(2);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_D, GLFW_KEY_RIGHT });
            break;
        }
        case Key::ROTATE:
        {
            glfwKeys.reserve(1);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_Q });
            break;
        }
        case Key::DEBUG_KEY_1:
        {
            glfwKeys.reserve(1);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_L });
            break;
        }
        case Key::ESC:
        {
            glfwKeys.reserve(1);
            glfwKeys.insert(glfwKeys.end(), { GLFW_KEY_ESCAPE });
            break;
        }
    }

    return glfwKeys;
}

//---------------------------------------------------------------

void Game::SetOutcome(const std::string& errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------

void Game::TerminateShader() const
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_shaderProgram);
}

//---------------------------------------------------------------

bool Game::ShouldTerminate() const
{
    return glfwWindowShouldClose(m_window);
}

//---------------------------------------------------------------
