#version 330

out vec4 Fragcolor;
in vec3 outColor;
void main()
{
	Fragcolor = vec4(outColor.r, outColor.g, outColor.b, 1.0);
}