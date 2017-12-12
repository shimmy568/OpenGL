R"(
#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float time;

void main()
{
    if(Texcoord.y < 0.5){
        outColor = texture(texKitten, Texcoord);
    } else {
        vec2 newCord = vec2(Texcoord.x - (sin((Texcoord.y * 50) + time * 2.0f) / 100.0f), 1.0f - Texcoord.y);
        outColor = texture(texKitten, newCord);
    }
}
)"