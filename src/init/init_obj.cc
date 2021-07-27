#include <vector>
#include <glm/glm.hpp>

#include "model.hh"
#include "init_obj.hh"
#include "variadic.hh"
#include "save.hh"
#include "noise.hh"
#include "noise2.hh"
#include "random.hh"

static void add_position_texture(std::vector<float>& vertices, const glm::vec3& pos, const glm::vec2& uv) {
    variadic::push_all(vertices, 3, pos.x, pos.y, pos.z);
    variadic::push_all(vertices, 2, uv.x, uv.y);
}

Object create_heightmap_plane(const glm::vec2& center, float width, float height, float step_w, float step_h) {
    const float h_width = width / 2.0;
    const float h_height = height / 2.0;

    std::vector<float> vertices = std::vector<float>();
    for (float i = center.x - h_width; i < center.x + h_width; i += step_w) {
        for (float j = center.y - h_height; j < center.y + h_height; j += step_h) {
            // x0 --- x1
            // |      |
            // x2 --- x3

            glm::vec3 p0(i          , 0, j);
            glm::vec3 p1(i + step_w , 0, j);
            glm::vec3 p2(i          , 0, j + step_h);
            glm::vec3 p3(i + step_w , 0, j + step_h);

            glm::vec2 uv0((i + h_width) / width, (j + h_height) / height);
            glm::vec2 uv1((i + step_w + h_width) / width, (j + h_height) / height);
            glm::vec2 uv2((i + h_width) / width, (j + step_h + h_height) / height);
            glm::vec2 uv3((i + step_w + h_width) / width, (j + step_h + h_height) / height);

            add_position_texture(vertices, p0, uv0);
            add_position_texture(vertices, p1, uv1);
            add_position_texture(vertices, p3, uv3);

            add_position_texture(vertices, p3, uv3);
            add_position_texture(vertices, p2, uv2);
            add_position_texture(vertices, p0, uv0);
        }
    }

    return Object(vertices, false, false, true);
}

Object create_plane(float dist, const float x_center, const float z_factor, const glm::vec3 offset) {
    std::vector<float> plane_vertices {
        // position          // colors         //normal          // texture
        -dist + x_center + offset.x, -0.5f + offset.y, -dist * z_factor + offset.z, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
         dist + x_center + offset.x, -0.5f + offset.y, -dist * z_factor + offset.z, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
         dist + x_center + offset.x, -0.5f + offset.y,  dist * z_factor + offset.z, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         dist + x_center + offset.x, -0.5f + offset.y,  dist * z_factor + offset.z, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -dist + x_center + offset.x, -0.5f + offset.y,  dist * z_factor + offset.z, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -dist + x_center + offset.x, -0.5f + offset.y, -dist * z_factor + offset.z, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    };
    return Object(plane_vertices, true, true, true);
}

Object create_vertical_plane(float dist) {
    std::vector<float> plane_vertices {
        // position         // colors         //normal          // texture
        -dist, -dist, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         dist, -dist, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         dist,  dist, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         dist,  dist, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -dist,  dist, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -dist, -dist, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    };
    return Object(plane_vertices, false, false, true);
}

Object create_vertical_plane(const float& dist_z, const float& dist_y, const glm::vec3& center) {
    std::vector<float> plane_vertices {
        // position                                       // texture
        center.x, -dist_y + center.y, -dist_z + center.z, 0.0f, 0.0f,
        center.x, -dist_y + center.y,  dist_z + center.z, 1.0f, 0.0f,
        center.x,  dist_y + center.y,  dist_z + center.z, 1.0f, 1.0f,
        center.x,  dist_y + center.y,  dist_z + center.z, 1.0f, 1.0f,
        center.x,  dist_y + center.y, -dist_z + center.z, 0.0f, 1.0f,
        center.x, -dist_y + center.y, -dist_z + center.z, 0.0f, 0.0f,
    };
    return Object(plane_vertices, false, false, true);
}

static void add_quad(std::vector<float>& vec, const glm::vec3& p0, const glm::vec3& p1,
        const glm::vec3& p2, const glm::vec3& p3) {
    variadic::push_all(vec, 3, p0.x, p0.y, p0.z);
    variadic::push_all(vec, 3, p1.x, p1.y, p1.z);
    variadic::push_all(vec, 3, p3.x, p3.y, p3.z);

    variadic::push_all(vec, 3, p3.x, p3.y, p3.z);
    variadic::push_all(vec, 3, p2.x, p2.y, p2.z);
    variadic::push_all(vec, 3, p0.x, p0.y, p0.z);
}

Object create_plane2(float center_x, float center_y, int width, int height, float step_w, float step_h, const Noise& noise) {
    std::vector<float> vertices = std::vector<float>();
    float y_max = 0;
    float y_min = 0;
    for (float i = center_x - width / 2.0; i < width / 2.0 + center_x; i += step_w) {
        for (float j = center_y - height / 2.0; j < height / 2.0 + center_y; j += step_h) {
            // x0 --- x1
            // |      |
            // x2 --- x3

            glm::vec3 p0(i          , 0, j);
            glm::vec3 p1(i + step_w , 0, j);
            glm::vec3 p2(i          , 0, j + step_h);
            glm::vec3 p3(i + step_w , 0, j + step_h);
            p0.y = noise.compute(p0.x, 0, p0.z) - 1.0f;
            p1.y = noise.compute(p1.x, 0, p1.z) - 1.0f;
            p2.y = noise.compute(p2.x, 0, p2.z) - 1.0f;
            p3.y = noise.compute(p3.x, 0, p3.z) - 1.0f;

            add_quad(vertices, p0, p1, p2, p3);
            variadic::min(y_min, 4, p0.y, p1.y, p2.y, p3.y);
            variadic::max(y_max, 4, p0.y, p1.y, p2.y, p3.y);
        }
    }

    Object obj(vertices, false, false, false);
    obj.set_y_max(y_max);
    obj.set_y_min(y_min);
    return obj;
}

Object create_plane_from_heightmap(const char* path, float center_x, float center_y, float step_w, float step_h) {
    Image height_map_img = file::ppm_to_image(path);

    std::vector<float> vertices = std::vector<float>();
    for (float i = 0, x = center_x - height_map_img.get_width() / 2 * step_w; i < height_map_img.get_width() - 1; ++i, x += step_w) {
        for (float j = 0, z = center_y - height_map_img.get_height() / 2 * step_h; j < height_map_img.get_height() - 1; ++j, z += step_h) {

            glm::vec3 p0(x,          height_map_img.get_pixel_at(i,     j    ), z);
            glm::vec3 p1(x + step_w, height_map_img.get_pixel_at(i + 1, j    ), z);
            glm::vec3 p2(x,          height_map_img.get_pixel_at(i,     j + 1), z + step_h);
            glm::vec3 p3(x + step_w, height_map_img.get_pixel_at(i + 1, j + 1), z + step_h);

            add_quad(vertices, p0, p1, p2, p3);
        }
    }

    std::vector<float> vertices_colors = std::vector<float>();
    for (size_t i = 0; i < vertices.size(); i += 3) {
        // Image contains values between 0 and 255
        variadic::push_all(vertices_colors, 3, vertices[i], vertices[i + 1] / 64.f - 1.0f, vertices[i + 2]);

        float h = vertices[i + 1];
        if (h == 0)
            variadic::push_all(vertices_colors, 3, 0.0f, 0.0f, 0.6f);
        else {
            float h_scale = h / 255.0f * 2.0f - 1e-10;
            h = std::floor(h_scale);
            float r = 0.1 * h_scale + 0.4 * (1 - h_scale);
            float g = 0.3 * h_scale + 0.8 * (1 - h_scale);
            float b = 0.1 * h_scale + 0.4 * (1 - h_scale);
            variadic::push_all(vertices_colors, 3, r, g, b);
        }
    }

    return Object(vertices_colors, true, false, false);
}

shared_particles create_particles(const float& nb_particles, shared_obj model, const glm::vec3& pos_min, const glm::vec3& pos_max, const float& scale_min, const float& scale_max, const float rotation) {
    Particles particles(model);

    particles.set_position_min(pos_min);
    particles.set_position_max(pos_max);

    particles.set_velocity_min(glm::vec3(-0.5f, 0.5f, 0.0f));
    particles.set_velocity_max(glm::vec3(-0.25f, 0.8f, 0.0f));

    particles.set_scale_min(scale_min);
    particles.set_scale_max(scale_max);

    if (rotation != 0)
        particles.set_rotation(rotation, glm::vec3(0.0f, 1.0f, 0.0f));

    particles.generate_particles(nb_particles);

    return std::make_shared<Particles>(particles);
}

Object create_plane_geom() {
    std::vector<float> vertices = {
        // position         // color
         0.00f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    return Object(vertices, true, false, false);
}
