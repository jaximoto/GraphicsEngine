#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform float Time;
uniform float displacementScale;
uniform sampler2D texture1;
uniform sampler2D displacementMap;

void main()
{
	// For Scrolling displacement map:
	vec2 scrollingDisplacement = TexCoord + vec2(Time * 0.1f, Time * 0.1f);
	vec4 displacementColor = texture(displacementMap, scrollingDisplacement);

	// Standard luminance formula
	float displacement = dot(displacementColor.rgb, vec3(0.299, 0.587, 0.114));

	vec2 displacementOffset = vec2(displacement - 0.5) * displacementScale;

	
	// For Scrolling main texture:
	//vec2 scrollingCoord = TexCoord + vec2(Time * 0.1f , Time * 0.1f );
	//FragColor = texture(texture1, scrollingCoord + displacementOffset);

	FragColor = texture(texture1, TexCoord + displacementOffset);
	//FragColor = texture(texture1, TexCoord);
}
