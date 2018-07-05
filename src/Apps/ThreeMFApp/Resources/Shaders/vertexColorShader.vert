#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 color;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    color = vColor;

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPosition, 1.0);
}