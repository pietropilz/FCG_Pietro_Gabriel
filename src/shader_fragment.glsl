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

    /////////////////////////////////////////
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 spotlightpos = vec4(0.0, 300.0, 0.0, 1.0);
    vec4 spotlightdir = normalize(vec4(-1.0, -1.0, 0.0,0.0));
    vec4 sentido = normalize(spotlightpos - p);

    //suavização
    float innerAngle = cos(radians(30.0)); // abertura interna do spot
    float outerAngle = cos(radians(60.0)); // abertura externa do spot
    float angulo = dot(sentido, -spotlightdir);

    float spotlight = smoothstep(outerAngle, innerAngle, angulo);

    //float abertura = cos(radians(30.0));
    //float spotlight = step(abertura, angulo);
    ///////////////////////////////////////////


    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = sentido;

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = reflect(-l, n);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    //vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
    float W = 0.0;

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong


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

        Kd = vec3(0.5, 0.5, 0.5);   // refletância difusa
        Ks = vec3(0.1, 0.1, 0.);    // refletância especular (branca)
        Ka = vec3(0.25, 0.25, 0.25);   // refletância ambiente (metade da difusa)
        q  = 10.0;                   // expoente especular de Phong


        // Espectro da fonte de iluminação
        vec3 I = vec3(0.5, 0.5, 0.5);

        // Espectro da luz ambiente
        vec3 Ia = vec3(0.5, 0.5, 0.5);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = spotlight * Kd * I * max(dot(n, l), 0.0);

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de iluminação de Phong
        vec3 phong_specular_term  = spotlight * Ks * I * pow(max(dot(r, v), 0.0), q);

        color.rgb =  (Kd0 + Kd1) * (lambert_diffuse_term + ambient_term + phong_specular_term);

    }else if( object_id == TREE ){

        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float x = position_model.x;
        float y = position_model.y;

        U = (x - minx) / (maxx - minx);
        V = (y - miny) / (maxy - miny);

        vec3 Kd0 = texture(TextureImage2, vec2(U,V)).rgb;

        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        Kd = vec3(1.0, 1.0, 1.0);   // refletância difusa
        Ks = vec3(0.0, 0.0, 0.0);    // refletância especular (branca)
        Ka = vec3(0.5, 0.5, 0.5);   // refletância ambiente (metade da difusa)
        q  = 1.0;                   // expoente especular de Phong


        // Espectro da fonte de iluminação
        vec3 I = vec3(1.0, 1.0, 1.0);

        // Espectro da luz ambiente
        vec3 Ia = vec3(1.0, 1.0, 1.0);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = spotlight * Kd * I * max(dot(n, l), 0.0);

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de iluminação de Phong
        vec3 phong_specular_term  = spotlight * Ks * I * pow(max(dot(r, v), 0.0), q);

        color.a = 1;

        color.rgb = Kd0 *(lambert_diffuse_term + ambient_term + phong_specular_term);


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
        vec3 Kd0 = texture(TextureImage3, vec2(U,V)).rgb;

        // Equação de Iluminação
        float lambert = max(0,dot(n,l));
        Kd = vec3(1.0, 1.0, 1.0);   // refletância difusa
        Ks = vec3(0.0, 0.0, 0.0);    // refletância especular (branca)
        Ka = vec3(0.5, 0.5, 0.5);   // refletância ambiente (metade da difusa)
        q  = 1.0;                   // expoente especular de Phong


        // Espectro da fonte de iluminação
        vec3 I = vec3(1.0, 1.0, 1.0);

        // Espectro da luz ambiente
        vec3 Ia = vec3(0.2, 0.2, 0.2);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = spotlight * Kd * I * max(dot(n, l), 0.0);

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de iluminação de Phong
        vec3 phong_specular_term  = spotlight * Ks * I * pow(max(dot(r, v), 0.0), q);

        color.rgb = Kd0 *(lambert_diffuse_term + ambient_term + phong_specular_term);

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
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        Kd = vec3(1.0, 1.0, 1.0);   // refletância difusa
        Ks = vec3(0.1, 0.1, 0.1);    // refletância especular (branca)
        Ka = vec3(0.5, 0.5, 0.5);   // refletância ambiente (metade da difusa)
        q  = 50.0;                   // expoente especular de Phong


        // Espectro da fonte de iluminação
        vec3 I = vec3(1.0, 1.0, 1.0);

        // Espectro da luz ambiente
        vec3 Ia = vec3(1.0, 1.0, 1.0);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = spotlight * Kd * I * max(dot(n, l), 0.0);

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de iluminação de Phong
        vec3 phong_specular_term  = spotlight * Ks * I * pow(max(dot(r, v), 0.0), q);

        color.rgb = Kd0 * (lambert_diffuse_term + ambient_term + phong_specular_term);

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

        Kd = vec3(1.0, 1.0, 1.0);   // refletância difusa
        Ks = vec3(0.1, 0.1, 0.1);    // refletância especular (branca)
        Ka = vec3(0.5, 0.5, 0.5);   // refletância ambiente (metade da difusa)
        q  = 10.0;                   // expoente especular de Phong


        // Espectro da fonte de iluminação
        vec3 I = vec3(1.0, 1.0, 1.0);

        // Espectro da luz ambiente
        vec3 Ia = vec3(1.0, 1.0, 1.0);

        // Termo difuso utilizando a lei dos cossenos de Lambert
        vec3 lambert_diffuse_term = spotlight * Kd * I * max(dot(n, l), 0.0);

        // Termo ambiente
        vec3 ambient_term = Ka * Ia;

        // Termo especular utilizando o modelo de iluminação de Phong
        vec3 phong_specular_term  = spotlight * Ks * I * pow(max(dot(r, v), 0.0), q);

        color.rgb = Kd0 * (lambert_diffuse_term + ambient_term + phong_specular_term);

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

        color.rgb = Kd0 * (lambert + 0.0);

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

