#include "version.h"

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec4 i_normal;
layout(location = 2) in mat3 o_tbnm;
layout(location = 3) in vec2 i_texcoord;

layout(location = 0) out vec4 o_color;

uniform vec3 u_col_albedo;
uniform sampler2D u_tex_albedo;

void main()
{
	// Some quick bad fake lighting for now
	vec3 light = normalize(vec3(0.25, 0.75, -0.50));

	// Test adding albedo texture and color
	o_color = vec4(max(dot(i_normal.xyz, light), 0.33) * texture2D(u_tex_albedo, i_texcoord).xyz, 1.0);
	//if (length(u_col_albedo) > 0.0)
	//{
	//	o_color *= vec4(u_col_albedo, 1.0);
	//} 
}
