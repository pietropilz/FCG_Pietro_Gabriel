#include "../include/draws.h"


GLuint vertex_array_floor;
GLuint vertex_array_track;
GLuint vertex_array_track2;

void desenhaMapa(GLint model_uniform)
{
    glm::mat4 model = Matrix_Identity();
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    //Desenha o chão do jogo
    glBindVertexArray(vertex_array_floor);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    //Desenha a pista do jogo
    glBindVertexArray(vertex_array_track);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glBindVertexArray(vertex_array_track2);
    glDrawElements(GL_TRIANGLE_STRIP,34, GL_UNSIGNED_BYTE, 0);

    model = Matrix_Rotate_Y(1.57f);
    glBindVertexArray(vertex_array_track);
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    // "Desligamos" o VAO, evitando assim que operações posteriores venham a
    // alterar o mesmo. Isso evita bugs.
    glBindVertexArray(0);
}

void inicializaMapa(){
    vertex_array_floor = BuildFloor();
    vertex_array_track = BuildTrack();
    vertex_array_track2 = BuildTrackCircle();
}


GLuint BuildTrack()
{
    constexpr float largura = 4.0f;
    constexpr float comprimento = 500.f;
    GLfloat NDC_coefficients[] =
    {
        //    X      Y     Z     W
        largura, 0.01f, -comprimento, 1.0f,
        -largura, 0.01f, -comprimento, 1.0f,
        largura, 0.01f, comprimento, 1.0f,
        -largura, 0.01f, comprimento, 1.0f,
    };

    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLfloat color_coefficients[] =
    {
        //  R     G     B     A
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };


    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLubyte indices[] = { 0,2,1, 1,2,3 };



    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);
    return vertex_array_object_id;
}




GLuint BuildFloor()
{
    constexpr float tam = 500.0f;
    GLfloat NDC_coefficients[] =
    {
        //    X      Y     Z     W
        tam, 0.0f, -tam, 1.0f,
        -tam, 0.0f, -tam, 1.0f,
        tam, 0.0f, tam, 1.0f,
        -tam, 0.0f, tam, 1.0f
    };

    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLfloat color_coefficients[] =
    {
        //  R     G     B     A
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f
    };


    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    GLubyte indices[] = { 0,2,1, 1,2,3 }; // GLubyte: valores entre 0 e 255 (8 bits sem sinal).



    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);
    return vertex_array_object_id;
}

GLuint BuildCube()
{
    constexpr float tam = 1.0f; // Tamanho reduzido para melhor visualização

    GLfloat NDC_coefficients[] =
    {
        //      X      Y      Z     W
        -tam, -tam, -tam, 1.0f, // 0
            tam, -tam, -tam, 1.0f, // 1
            tam,  tam, -tam, 1.0f, // 2
            -tam,  tam, -tam, 1.0f, // 3
            -tam, -tam,  tam, 1.0f, // 4
            tam, -tam,  tam, 1.0f, // 5
            tam,  tam,  tam, 1.0f, // 6
            -tam,  tam,  tam, 1.0f  // 7
        };


    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLfloat color_coefficients[] =
    {
        //  R     G     B     A
        0.0f, 0.0f, 1.0f, 1.0f, // 0
        0.0f, 0.0f, 1.0f, 1.0f, // 1
        0.0f, 0.0f, 1.0f, 1.0f, // 2
        0.0f, 0.0f, 1.0f, 1.0f, // 3
        0.0f, 0.0f, 1.0f, 1.0f, // 4
        0.0f, 0.0f, 1.0f, 1.0f, // 5
        0.0f, 0.0f, 1.0f, 1.0f, // 6
        0.0f, 0.0f, 1.0f, 1.0f  // 7
    };


    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLubyte indices[] =
    {
        0, 1, 2,  2, 3, 0,
        4, 5, 6,  6, 7, 4,
        0, 3, 7,  7, 4, 0,
        1, 5, 6,  6, 2, 1,
        0, 1, 5,  5, 4, 0,
        3, 2, 6,  6, 7, 3
    };


    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);
    return vertex_array_object_id;
}


GLuint BuildTrackCircle()
{
    int num = 17;
    GLfloat NDC_coefficients[num*8];

    int ext_pontos = num-1;
    float raioMaior = 200.0f;
    float raioMenor = 190.0f;
    const float PI = 3.14159265358979323846f;
    float angulo = 2.0f * PI / ext_pontos;
    for (int i = 0; i < ext_pontos; i++)
    {
        float angle = angulo * i;
        int index = i*8;
        NDC_coefficients[index] = raioMaior * cos(angle);
        NDC_coefficients[index + 2] = -raioMaior * sin(angle);
        NDC_coefficients[index + 1] = 0.1f;
        NDC_coefficients[index + 3] = 1.0f;

        NDC_coefficients[index+4] = raioMenor * cos(angle);
        NDC_coefficients[index + 6] = -raioMenor * sin(angle);
        NDC_coefficients[index + 5] = 0.1f;
        NDC_coefficients[index + 7] = 1.0f;
    }

    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLfloat color_coefficients[num*8];



    for(int i=0; i<ext_pontos; i++)
    {
        int indice = i*8;
        color_coefficients[indice] = 0.0f;
        color_coefficients[1+indice] = 0.0f;
        color_coefficients[2+indice] = 1.0f;
        color_coefficients[3+indice] = 1.0f;

        color_coefficients[4+indice] = 1.0f;
        color_coefficients[5+indice] = 0.0f;
        color_coefficients[6+indice] = 0.0f;
        color_coefficients[7+indice] = 1.0f;
    }

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLubyte indices[num*2]; // GLubyte: valores entre 0 e 255 (8 bits sem sinal).
    for (int i=0; i<num*2-2; i++) indices[i] =i;
    indices[num*2-2] = 0;
    indices[num*2-1]=1;

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

    // Alocamos memória para o buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

    // Copiamos os valores do array indices[] para dentro do buffer.
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glBindVertexArray(0);

    return vertex_array_object_id;
}
