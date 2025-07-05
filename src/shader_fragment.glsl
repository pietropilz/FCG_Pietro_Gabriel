#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da cor de cada vértice, definidas em "shader_vertex.glsl" e
// "main.cpp" (array color_coefficients).
in vec4 cor_interpolada_pelo_rasterizador;

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define REX 0
#define PLANE 1
#define TREE 2
#define FOLHAS 3
#define STEG 4
#define SPHERE 5

uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0; //rex
uniform sampler2D TextureImage1; //rex2
uniform sampler2D TextureImage2; //tronco
uniform sampler2D TextureImage3; //folhas
uniform sampler2D TextureImage4; //steg
uniform sampler2D TextureImage5; //grass
uniform sampler2D TextureImage6; //sky


// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{

     // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    //vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
    float W = 0.0;


    /////////////////////////////////////////
    if ( object_id == REX )
    {
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float x = position_model.x;
        float y = position_model.y;

        U = (x - minx) / (maxx - minx);
        V = (y - miny) / (maxy - miny);

        vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
        vec3 Kd1 = texture(TextureImage1, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd0 * Kd1 * (lambert + 0.5);

    }else if( object_id == TREE ){
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float x = position_model.x;
        float y = position_model.y;

        U = (x - minx) / (maxx - minx);
        V = (y - miny) / (maxy - miny);

        vec3 Kd2 = texture(TextureImage2, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd2 * (lambert + 0.5);

    }else if( object_id == FOLHAS ){
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        float x = position_model.x;
        float y = position_model.y;
        float z = position_model.z;

        U = (x - minx) / (maxx - minx);
        V = (y - miny) / (maxy - miny);
        W = (z - minz) / (maxz - minz);
        vec3 Kd0 = texture(TextureImage3, vec2(V,U)).rgb;
        vec3 Kd1 = texture(TextureImage3, vec2(W,U)).rgb;
        vec3 Kd2 = texture(TextureImage3, vec2(V,W)).rgb;
        vec3 Kd3 = texture(TextureImage3, vec2(U,V)).rgb;
        vec3 Kd4 = texture(TextureImage3, vec2(U,W)).rgb;
        vec3 Kd5 = texture(TextureImage3, vec2(W,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd0 * Kd1 * Kd2 * Kd3 * Kd4 * Kd5 * (lambert + 0.5);

    }else if( object_id == STEG ){
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        float x = position_model.x;
        float y = position_model.y;
        float z = position_model.z;

        V = (y - miny) / (maxy - miny);
        W = (z - minz) / (maxz - minz);

        vec3 Kd0 = texture(TextureImage4, vec2(V,W)).rgb;
        vec3 Kd1 = texture(TextureImage4, vec2(V,W)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd0 * (lambert + 0.5);

    }else if( object_id == PLANE ){
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        float x = position_model.x;
        float y = position_model.y;
        float z = position_model.z;

        float repeat = 500.0;
        U = (x - minx) / (maxx - minx)*repeat;
        V = (y - miny) / (maxy - miny*repeat);
        W = (z - minz) / (maxz - minz)*repeat;


        vec3 Kd0 = texture(TextureImage5, vec2(U,W)).rgb;
                // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd0 * (lambert + 0.5);
    }else if( object_id == SPHERE ){
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float x = position_model.x;
        float y = position_model.y;

        U = (x - minx) / (maxx - minx);
        V = (y - miny) / (maxy - miny);

        vec3 Kd0 = texture(TextureImage6, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd0;
    }else{
        //discard;
        //color = cor_interpolada_pelo_rasterizador;
        color.rgb = vec3(1,0,0);
        color.a = 1;
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }

   //color.a = 1;

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    //color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}

