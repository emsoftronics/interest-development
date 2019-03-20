#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader(GLenum type, const char *shaderSrc)
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0)
        return 0;

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* infoLog = malloc(sizeof(char) * infoLen);

            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            printf("Error compiling shader:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

///


///
// Initialize the shader and program object
//
GLint getProgram()
{
//    UserData *userData = esContext->userData;
    GLchar vShaderStr[] =
        "attribute vec4 vPosition;    \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = vPosition;  \n"
        "}                            \n";

    GLchar fShaderStr[] =
        "precision mediump float;\n"
        "void main()                                  \n"
        "{                                            \n"
        "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
        "}                                            \n";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

    // Create the program object
    programObject = glCreateProgram();

    if (programObject == 0)
        return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;

        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* infoLog = malloc(sizeof(char) * infoLen);

            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:\n%s\n", infoLog);

            free(infoLog);
        }

        glDeleteProgram(programObject);
        return EGL_FALSE;
    }

    // Store the program object
    //userData->programObject = programObject;

    glClearColor(0.01f, 0.01f, 0.01f, 0.0f);
    return programObject;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(GLint program, EGLDisplay dpy, EGLSurface surf)
{
    static unsigned long btime = 0;
    static int frames = 0;
    unsigned long time = 0;
    int i;
    struct timeval tv;
    //UserData *userData = esContext->userData;
    if (program < 0) {
        printf("shader Program error\n");
        return;
    }

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (frames == 0) btime = time;
    if (time - btime > 1990) {
        printf("%d frames in %d seconds: %f fps\n", frames, 2,
               (float) frames / 2.0f);
        btime = time;
        frames = 0;
    }
    else frames++;

    GLfloat vVertices[] =
    { 0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f };

    for (i = 0; i < 8; i+=3) {
        vVertices[i] *= (frames/60.0f);
        vVertices[i + 1] *= (frames/60.0f);
    }

    // Set the viewport
    glViewport(0, 0, 1920, 1200);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(program);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    eglSwapBuffers(dpy, surf);
}


void testmain(EGLDisplay dpy, EGLSurface surf)
{
    GLint program = getProgram();
    while(1) {
        Draw(program, dpy, surf);
        usleep(10);
    }
}

