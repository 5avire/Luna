#type vertex
#version 460 core

layout (location = 0) in vec3 a_Pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_ModelPosition;

void main()
{
   gl_Position = u_ViewProjection * u_ModelPosition * vec4(a_Pos, 1.0f);
}



#type fragment
#version 460 core

layout (location = 0) out vec4 color;

uniform vec3 u_Color;

void main()
{
   color = vec4(u_Color, 1.0);
}
