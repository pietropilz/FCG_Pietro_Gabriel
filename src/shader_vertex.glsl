#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 color_coefficients;
layout (location = 2) in vec4 normal_coefficients;
layout (location = 3) in vec2 texture_coefficients;


out vec4 cor_interpolada_pelo_rasterizador;
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec2 UV_coords;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool render_as_black;


uniform vec4 bbox_min;
uniform vec4 bbox_max;

void main()
{

    gl_Position = projection * view * model * model_coefficients;


    position_model = model_coefficients;
    position_world = model * model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    texcoords = texture_coefficients;

    float miny = bbox_min.y;
    float maxy = bbox_max.y;
    float minz = bbox_min.z;
    float maxz = bbox_max.z;

    float y = position_model.y;
    float z = position_model.z;

    float U = (y - miny) / (maxy - miny);
    float V = (z - minz) / (maxz - minz);

    UV_coords = vec2(V, U);

    if (render_as_black)
    {
        cor_interpolada_pelo_rasterizador = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }else{
        cor_interpolada_pelo_rasterizador = color_coefficients;
    }
}
