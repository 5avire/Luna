#type vertex
#version 460 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_ModelPosition;

void main()
{
   v_TexCoord = a_TexCoord;
   gl_Position = u_ViewProjection * u_ModelPosition * vec4(a_Pos, 1.0f);
}



#type fragment
#version 460 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
   color = texture(u_Texture, v_TexCoord);
}
