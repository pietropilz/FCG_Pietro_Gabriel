#version 330 core

// Atributos de entrada
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 color_coefficients;
layout (location = 2) in vec4 normal_coefficients;
layout (location = 3) in vec2 texture_coefficients;

// Saídas para o fragment shader
out vec4 cor_interpolada_pelo_rasterizador;
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec2 UV_coords; // novo: coordenadas UV manuais

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool render_as_black;

// Novos uniforms para cálculo de UV manual
uniform vec4 bbox_min;
uniform vec4 bbox_max;

void main()
{
    // Transforma posição do vértice
    gl_Position = projection * view * model * model_coefficients;

    // Calcula posições no mundo e no modelo
    position_model = model_coefficients;
    position_world = model * model_coefficients;

    // Corrige normal com transformações não-uniformes
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // Coordenadas de textura do modelo (caso existam no OBJ)
    texcoords = texture_coefficients;

    // Calcular UV manualmente a partir da posição no modelo e bounding box
    float miny = bbox_min.y;
    float maxy = bbox_max.y;
    float minz = bbox_min.z;
    float maxz = bbox_max.z;

    float y = position_model.y;
    float z = position_model.z;

    float U = (y - miny) / (maxy - miny);
    float V = (z - minz) / (maxz - minz);

    UV_coords = vec2(V, U); // enviar para fragment shader

    // Define cor (iluminação Gouraud pode ser feita aqui se quiser)
    if (render_as_black)
    {
        cor_interpolada_pelo_rasterizador = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }else{
        cor_interpolada_pelo_rasterizador = color_coefficients;
    }
}
