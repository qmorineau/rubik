#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormale;
layout (location = 2) in vec3 aFaceColor;

out vec3 FragPos;
out vec3 Normal;
flat out vec3 FaceColor;

out vec3 vObjectPos;
out vec3 vObjectNormal;

uniform mat4 model;
uniform mat4 orient;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 translate;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;

    mat3 normalMatrix = mat3(transpose(inverse(model)));
    Normal = normalize(normalMatrix * aNormale);

    vObjectPos = aPos;
    vObjectNormal = aNormale;

    vec3 stableNormal = normalize(mat3(orient) * aNormale);

    float threshold = 0.5;
    float visible = step(threshold, dot(stableNormal, translate));
    FaceColor = mix(vec3(0.0), aFaceColor, visible);

    gl_Position = projection * view * worldPos;
}
