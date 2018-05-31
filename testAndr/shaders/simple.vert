attribute vec3 a_Position;
attribute vec3 a_Normal;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 speclightColor;
uniform float shine;

varying vec3 colorWeight;

void main()
{
  gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(a_Position, 1.0);
  vec3 normal = normalize(vec3(cameraToView * worldToCamera * modelToWorld * vec4(a_Normal,0.0)));
  vec3 lightNorm = normalize(lightDir);
  float lightWeight = max(dot(normal,lightNorm),0.3);
  vec3 halfVec = normalize(lightDir - gl_Position.xyz);
  float specWeight = pow(max(dot(normal,halfVec),0.1),shine);
  colorWeight = vec3(0.0,0.0,0.0) + (lightWeight * lightColor) + (speclightColor*specWeight);
}
