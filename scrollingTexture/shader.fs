#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform float Time;
uniform float deltaTime;
uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
	vec2 scrollingCoord = TexCoord + vec2(Time * 0.1f , Time * 0.1f );
	FragColor = texture(texture1, scrollingCoord);
	//FragColor = texture(texture1, TexCoord);
}
