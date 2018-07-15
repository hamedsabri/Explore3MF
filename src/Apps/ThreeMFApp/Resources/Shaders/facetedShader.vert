#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec4 worldPos;
out vec4 color;

void main() 
{
    color = vColor;

    worldPos = ViewMatrix * ModelMatrix * vec4(vPosition, 1.0);

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPosition, 1.0);
}