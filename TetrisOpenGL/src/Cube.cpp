#include "GL/glew.h"

#include "Cube.h"

#include <iostream>

#include "ImageCoordManager.h"
#include "stb/stb_image.h"

//---------------------------------------------------------------

unsigned int Cube::s_shaderProgram = 0;
const char* Cube::s_vertexShaderSource = nullptr;
const char* Cube::s_fragmentShaderSource = nullptr;
unsigned int Cube::s_fragmentShader = 0;
unsigned int Cube::s_vertexShader = 0;
unsigned int Cube::s_VAO = 0;
unsigned int Cube::s_VBO = 0;
unsigned int Cube::s_texture = 0;

//---------------------------------------------------------------

Cube::Cube(
    const bool staticImage,
    const std::vector<double>& positions,
    const std::vector<float>& colors,
    const int imageId)
    : Cube(positions, colors, imageId)
{
    m_staticImage = staticImage;
}

//---------------------------------------------------------------

Cube::Cube(const std::vector<double>& positions, const std::vector<float>& colors, const int imageId)
    : Entity(positions, imageId)
    , m_shouldMove(true)
    , m_count(4)
    , m_mode(GL_TRIANGLE_STRIP)
{
    m_colors = std::vector<float>();
    m_colors.reserve(colors.size());
    for (auto color : colors)
        m_colors.emplace_back(color);
}

//---------------------------------------------------------------

void Cube::CheckShaderCompilation(const unsigned int shader)
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

void Cube::CheckProgramLinking(const unsigned int program)
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

void Cube::CheckOpenGLError(const char* checkpoint)
{
    const unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
        std::cerr << "OpenGL error (" << checkpoint << "): " << error << '\n';
}

//---------------------------------------------------------------

void Cube::Color() const
{
    glBindTexture(GL_TEXTURE_2D, s_texture);
    // glUniform4f(
    //     glGetUniformLocation(s_shaderProgram, "triangleColor"),
    //     m_colors[0],
    //     m_colors[1],
    //     m_colors[2],
    //     m_colors[3]);
}

//---------------------------------------------------------------

void Cube::InitShader()
{
    CompileShaders();

    s_shaderProgram = glCreateProgram();
    glAttachShader(s_shaderProgram, s_vertexShader);
    glAttachShader(s_shaderProgram, s_fragmentShader);
    glLinkProgram(s_shaderProgram);

    // Check for program linking errors
    CheckProgramLinking(s_shaderProgram);

    glDeleteShader(s_vertexShader);
    glDeleteShader(s_fragmentShader);

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);

    glBindVertexArray(s_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_positions), nullptr, GL_DYNAMIC_DRAW);

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
        std::cerr << "Failed to load image" << '\n';

    // Generate texture
    glGenTextures(1, &s_texture);
    glBindTexture(GL_TEXTURE_2D, s_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    // Bind texture to sampler
    glUseProgram(s_shaderProgram);
    glUniform1i(glGetUniformLocation(s_shaderProgram, "u_Texture"), 0);
}

//---------------------------------------------------------------

bool Cube::IsStatic()
{
    return m_staticImage;
}

//---------------------------------------------------------------

void Cube::Loop() const
{
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_positions), m_positions);

    glUseProgram(s_shaderProgram);
    CheckProgramLinking(s_shaderProgram);
    Color();
    glBindVertexArray(s_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(m_mode, 0, m_count);
}

//---------------------------------------------------------------

void Cube::Move(const double& /*scaleFactor*/, const Key /*keyPressed*/)
{}

//---------------------------------------------------------------

void Cube::MoveForce(const double& /*scaleFactor*/)
{}

//---------------------------------------------------------------

void Cube::SetMove(const bool shouldMove)
{
    if (m_staticImage)
        return;

    m_shouldMove = shouldMove;
}

//---------------------------------------------------------------

void Cube::TerminateShader()
{
    glDeleteVertexArrays(1, &s_VAO);
    glDeleteBuffers(1, &s_VBO);
    glDeleteProgram(s_shaderProgram);
}

//---------------------------------------------------------------

void Cube::CompileShaders()
{
    s_vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 v_TexCoord;
        void main() {
            gl_Position = vec4(aPos, 1.0);
            v_TexCoord = aTexCoord;
        }
    )";

    s_fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 v_TexCoord;
        uniform sampler2D u_Texture;
        void main() {
            FragColor = texture(u_Texture, v_TexCoord);
        }
    )";

    s_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertexShader, 1, &s_vertexShaderSource, nullptr);
    glCompileShader(s_vertexShader);

    s_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragmentShader, 1, &s_fragmentShaderSource, nullptr);
    glCompileShader(s_fragmentShader);

    // Check for shader compilation errors
    CheckShaderCompilation(s_vertexShader);
    CheckShaderCompilation(s_fragmentShader);
}

//---------------------------------------------------------------
