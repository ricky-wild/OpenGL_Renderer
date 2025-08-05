#version 330 core

in vec2 v_TexCoord;
out vec4 FragColor;

uniform sampler2D my_U_texture;

void main()
{
    //FragColor = texture(my_U_texture, v_TexCoord);
    //FragColor = vec4(v_TexCoord, 0.0, 1.0); // visualize UVs as color
    
    
    FragColor = texture(my_U_texture, v_TexCoord);
    //vec4 sampled = texture(my_U_texture, v_TexCoord);
    //FragColor = vec4(sampled.rgb, 1.0);

    //FragColor = vec4(v_TexCoord, 0.0, 1.0);
    //FragColor = vec4(1.0, 0.0, 1.0, 1.0); // bright magenta
}
