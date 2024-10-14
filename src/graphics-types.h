#ifndef _GRAPHICS_DEFS_H_
#define _GRAPHICS_DEFS_H_

typedef struct Object *object_t;
typedef struct Shader *shader_t;
typedef struct Texture *texture_t;
typedef struct Mesh *mesh_t;

typedef enum ownflags_t {
	OWN_NONE = 0,
	OWN_MESH = 1,
	OWN_TEXTURE = 2,
	OWN_SHADER = 4,
	OWN_ALL = OWN_MESH | OWN_TEXTURE | OWN_SHADER,
	OWN_ALL_BUT_SHADER = OWN_MESH | OWN_TEXTURE
} ownflags_t;

#endif // _GRAPHICS_DEFS_H_