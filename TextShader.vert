#version 330 core
layout (location = 1) in vec4 vertex; // (pos.xy, tex.xy)

//location 1 instead of 0 so we don't mix up with texture mesh location 0
//glEnableVertexAttribArray(1);
//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
