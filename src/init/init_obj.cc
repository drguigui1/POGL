#include <vector>
#include <glm/glm.hpp>

#include "init_obj.hh"
#include "variadic.hh"

#include "noise.hh"

Object create_plane() {
    std::vector<float> plane_vertices {
        // position             // colors
         15.0f, -0.5f,  15.0f,  1.0f, 0.0f, 0.0f,
        -15.0f, -0.5f,  15.0f,  0.0f, 1.0f, 0.0f,
        -15.0f, -0.5f, -15.0f,  0.0f, 0.0f, 1.0f,

         15.0f, -0.5f,  15.0f,  1.0f, 0.0f, 0.0f,
        -15.0f, -0.5f, -15.0f,  0.0f, 0.0f, 1.0f,
         15.0f, -0.5f, -15.0f,  0.0f, 1.0f, 0.0f

    };

    return Object(plane_vertices, true, false, false);
}

Object create_cube() {
    std::vector<float> cube_vertices = {
        // position          // colors         //normal            // texture
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f
    };

    return Object(cube_vertices, true, true, true);
}

Object create_plane2(float center_x, float center_y, int width, int height, float step_w, float step_h) {
    Noise noise(5, NOISE);
    std::vector<float> vertices = std::vector<float>();
    std::vector<float> vertices_colors = std::vector<float>();

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

            variadic::push_all(vertices, 3, p0.x, p0.y, p0.z);
            variadic::push_all(vertices, 3, p1.x, p1.y, p1.z);
            variadic::push_all(vertices, 3, p3.x, p3.y, p3.z);

            variadic::push_all(vertices, 3, p3.x, p3.y, p3.z);
            variadic::push_all(vertices, 3, p2.x, p2.y, p2.z);
            variadic::push_all(vertices, 3, p0.x, p0.y, p0.z);
        }
    }

    for (size_t i = 0; i < vertices.size(); i += 3) {
        variadic::push_all(vertices_colors, 3, vertices[i], vertices[i + 1], vertices[i + 2]);

        float h = vertices[i + 1] + 1.0f;
        if (h <= 0)
            variadic::push_all(vertices_colors, 3, 0.2f, 0.7f, 1.0f);
        else if (h >= 1.5)
            //variadic::push_all(vertices_colors, 3, 0.2f * h, 0.7f * h, 0.0f * h);
            variadic::push_all(vertices_colors, 3, 1.0f, 1.0f, 1.0f);
        else
            variadic::push_all(vertices_colors, 3, 0.1f * h, 0.9f * h, 0.05f * h);
    }

    return Object(vertices_colors, true, false, false);
}
