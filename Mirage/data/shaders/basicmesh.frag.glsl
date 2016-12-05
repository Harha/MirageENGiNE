#include "version.h"

layout(location = 0) in vec4 i_position;
layout(location = 2) in vec2 i_texcoord;

layout(location = 0) out vec4 o_color;

uniform sampler2D u_tex_diffuse;

void main()
{
	o_color = texture2D(u_tex_diffuse, i_texcoord);
}
