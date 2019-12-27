#version 330 core

out vec4 Fragcolor;
in vec3 outColor;
in vec2 TexCoord;
uniform sampler2D outTexure;
void main()
{
	//Fragcolor = vec4(outColor, 1.0);
	Fragcolor=texture(outTexure,TexCoord)*vec4(outColor, 1.0);
}
