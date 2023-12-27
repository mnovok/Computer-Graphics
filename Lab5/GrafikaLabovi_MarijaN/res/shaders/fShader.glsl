#version 330 core

in vec3 normal;
in vec2 TexCord;
in vec3 FragPos;

out vec4 fColor;

uniform sampler2D tex;
uniform float ambient_strength;
uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;
uniform float specular_strength;

void main()
{
	vec3 ambient = ambient_strength * light_color;

	vec3 light_direction = normalize(light_position - FragPos);
	vec3 diff = dot(normalize(normal), light_direction) * light_color;

	vec3 view_direction = normalize(view_position - FragPos);
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), 32);
	vec3 specular = specular_strength * spec * light_color;

	vec3 result = ambient + diff;
	fColor = vec4(result * object_color + specular, 1.0f);
}