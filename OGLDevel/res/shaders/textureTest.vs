

attribute vec3 aPosition;
attribute vec3 aColor;
attribute vec2 aTexCoord;
//attribute vec3 aNormal;

varying vec3 ourColor;
varying vec2 TexCoord;

uniform mat4 uTranslate;
uniform mat4 uScale;
uniform mat4 uRotate;
uniform mat4 uView;
uniform mat4 uProjection;

mat4 model ()
{
    return uTranslate*uRotate*uScale;
}

void main()
{
    ourColor = aColor;
    TexCoord = aTexCoord;
    gl_Position = uProjection*uView*model()*vec4 (aPosition, 1.0);
}

