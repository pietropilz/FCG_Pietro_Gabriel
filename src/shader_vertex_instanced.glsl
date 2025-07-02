#version 330 core

// Atributos por VÉRTICE (iguais ao shader padrão)
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 color_coefficients;
layout (location = 2) in vec4 normal_coefficients;
layout (location = 3) in vec2 texture_coefficients;

// NOVO: Atributo por INSTÂNCIA
// Começa na localização 4 e ocupa as localizações 4, 5, 6, 7
layout (location = 4) in mat4 instanceModel;

// Saídas (iguais ao shader padrão)
out vec4 cor_interpolada_pelo_rasterizador;
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;

// Uniforms (note que 'uniform mat4 model' FOI REMOVIDO)
uniform mat4 view;
uniform mat4 projection;
uniform bool render_as_black;

void main()
{
    // A matriz 'model' foi substituída por 'instanceModel'
    gl_Position = projection * view * instanceModel * model_coefficients;

    // As outras saídas que dependiam de 'model' também devem ser atualizadas!
    position_world = instanceModel * model_coefficients;
    normal = inverse(transpose(instanceModel)) * normal_coefficients;

    // O resto permanece igual
    position_model = model_coefficients;
    normal.w = 0.0;
    texcoords = texture_coefficients;

    if ( render_as_black )
    {
        cor_interpolada_pelo_rasterizador = vec4(0.0f,0.0f,0.0f,1.0f);
    }
    else
    {
        cor_interpolada_pelo_rasterizador = color_coefficients;
    }
}
