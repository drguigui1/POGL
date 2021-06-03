#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hh"

enum ShaderType {
    VERTEX,
    FRAGMENT,
    PROGRAM
};

static void check_errors(unsigned int shader, ShaderType type) {
    int success;
    char buff[1024];
    std::string error;
    switch (type) {
    case VERTEX:
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success) return;

        glGetShaderInfoLog(shader, 1024, NULL, buff);
        error = "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
        break;

    case FRAGMENT:
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success) return;

        glGetShaderInfoLog(shader, 1024, NULL, buff);
        error = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
        break;

    default: // PROGRAM
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (success) return;

        glGetProgramInfoLog(shader, 1024, NULL, buff);
        error = "ERROR::SHADER::PROGRAM::LINKING_FAILED";
        break;
    }
    std::cout << error << '\n' << buff << std::endl;
}


static unsigned int create_shader(GLenum shader_type, const char* shader_code, ShaderType type) {
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    check_errors(shader, type);
    return shader;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = file::get_file_content(vertexPath);
    std::string fragmentCode = file::get_file_content(fragmentPath);

    const char* vertex_shader_code = vertexCode.c_str();
    const char * fragment_shader_code = fragmentCode.c_str();

    unsigned int fragment = create_shader(GL_FRAGMENT_SHADER, fragment_shader_code, FRAGMENT);
    unsigned int vertex = create_shader(GL_VERTEX_SHADER, vertex_shader_code, VERTEX);

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    check_errors(this->id, PROGRAM);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->id);
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void Shader::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::set_vec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::set_vec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::set_vec4(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::set_mat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::set_mat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
