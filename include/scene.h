#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>

struct SceneObject
{
    const char*  name;
    void*        first_index;
    int          num_indices;
    GLenum       rendering_mode;
};

#endif // SCENE_OBJECT_H

