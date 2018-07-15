#version 330 core

in vec4 worldPos;
in vec4 color;

layout (location = 0) out vec4 frag_color;

void main() 
{
    // use screen-space derivatives to find triangle normal.
    vec3 normal = cross(dFdx(worldPos.xyz), dFdy(worldPos.xyz));
    normal = normalize(normal);

    vec3 diffuse = vec3(0.0,0.0,0.0); 

    vec3 lightDir0 = normalize( vec3( 1.0, 5.0, 1.0 ) );
    vec3 lightColor0 = vec3(1.0, 1.0, 1.0);
    diffuse += lightColor0 * clamp(dot(normal,lightDir0), 0.0, 1.0);

    vec3 lightDir1 = normalize( vec3( 1.0, 1.0, 5.0 ) ); 
    vec3 lightColor1 = vec3(1.0, 1.0, 1.0);
    diffuse += lightColor1 * clamp(dot(normal,lightDir1), 0.0, 1.0);

    diffuse *= color.rgb;
    frag_color = vec4( diffuse.r, diffuse.g, diffuse.b, color.a );
}
