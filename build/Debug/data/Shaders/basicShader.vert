#version 440

in vec3 in_position;
in vec3 in_normal;
in vec2 in_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

//mat3(transpose(inverse(model))) *

void main (void)
{
	fragPosition = model * vec4(in_position,1.0f);
	fragNormal = mat3(transpose(inverse(model))) * in_normal;
	fragTexCoord = in_texCoord;
    gl_Position = projection * view * model * vec4(in_position,1.0f);
}