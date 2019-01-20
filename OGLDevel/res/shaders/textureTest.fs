
precision mediump float;
varying vec3 ourColor;
varying vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
//    gl_FragColor = texture2D(texture1, TexCoord)*vec4(ourColor, 1.0);
//    vec4 tcol = texture2D(texture1, TexCoord);
//    if (tcol.rgb == vec3(0,0,0)) tcol = vec4(ourColor, 1.0);
    //gl_FragColor = mix(texture2D(texture1, TexCoord), vec4(1.0, 1.0, 1.0, 1.0), 0.8);
    gl_FragColor = texture2D(texture1, TexCoord);
//    gl_FragColor = vec4(tcol.r, tcol.g,tcol.b, 1.0);
}


