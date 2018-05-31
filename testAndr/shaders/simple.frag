precision mediump float;

uniform vec3 color;
varying vec3 colorWeight;

void main()
{
   gl_FragColor = vec4(color * colorWeight, 1.0f);
}
