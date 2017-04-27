#include "version.h"

layout(location = 0) in vec3 i_position;
layout(location = 3) in vec2 i_texcoord;

layout(location = 0) out vec4 o_position;
layout(location = 3) out vec2 o_texcoord;

uniform mat4 u_MMatrix;
uniform mat4 u_VMatrix;
uniform mat4 u_PMatrix;

void main()
{
	// World-space position
	o_position = u_MMatrix * vec4(i_position.xyz, 1.0);

	// Texture coordinates
	o_texcoord = i_texcoord;
	
	// Rasterized triangle vertex transformation
	gl_Position = u_PMatrix * u_VMatrix * vec4(o_position.xyz, 1.0);
}
