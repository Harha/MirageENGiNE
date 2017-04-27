#include "version.h"

layout(location = 0) in vec4 i_position;
layout(location = 3) in vec2 i_texcoord;

layout(location = 0) out vec4 o_color;

uniform vec3 u_col_diffuse;
uniform sampler2D u_tex_diffuse;

void main()
{
	//o_color = texture2D(u_tex_diffuse, i_texcoord);
	o_color = vec4(u_col_diffuse, 1.0);
}
