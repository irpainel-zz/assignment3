void main()
{
    vec4 v = gl_Vertex;

    gl_TexCoord[0] = v; 
    gl_Position  = gl_Vertex;
}