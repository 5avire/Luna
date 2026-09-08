#type vertex
#version 460 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TilingFactor;
layout (location = 4) in float a_TexID;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TilingFactor;
out float v_TexID;

uniform mat4 u_ViewProjection;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_TilingFactor = a_TilingFactor;
    v_TexID = a_TexID;
    gl_Position = u_ViewProjection * vec4(a_Pos, 1.0f);
}


#type fragment
#version 460 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TilingFactor;
in float v_TexID;

uniform sampler2D u_Texture[32];

void main()
{
    vec4 texColor = texture(u_Texture[int(v_TexID)], v_TexCoord * v_TilingFactor) * v_Color;
    if (texColor.a <= 0.01)
    {
        discard;
    }
    color = texColor;
}

