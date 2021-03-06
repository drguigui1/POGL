#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "file.hh"

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath=nullptr);
    ~Shader();

    /* Methods */
    void use();
    void set_projection_view_model(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model);

    /* Setters */
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;

    void set_vec2(const std::string& name, const glm::vec2& value) const;
    void set_vec2(const std::string& name, float x, float y) const;

    void set_vec3(const std::string& name, const glm::vec3& value) const;
    void set_vec3(const std::string& name, float x, float y, float z) const;

    void set_vec4(const std::string& name, const glm::vec4& value) const;
    void set_vec4(const std::string& name, float x, float y, float z, float w);

    void set_mat2(const std::string& name, const glm::mat2& mat) const;
    void set_mat3(const std::string& name, const glm::mat3& mat) const;
    void set_mat4(const std::string& name, const glm::mat4& mat) const;

    /* Getters */
    unsigned int get_id() const { return id; }

private:
    /* Attributes */
    unsigned int id;
};

using shared_shader = std::shared_ptr<Shader>;
