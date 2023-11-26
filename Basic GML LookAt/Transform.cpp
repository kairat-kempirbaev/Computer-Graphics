// Transform.cpp: implementation of the Transform class.
#include "Transform.h"

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float rad = glm::radians(degrees);
  vec3 normal_axis = glm::normalize(axis);
  return glm::cos(rad) * glm::mat3(1.0f) + 
    (1-glm::cos(rad))*glm::mat3(normal_axis[0]*normal_axis[0],normal_axis[0]*normal_axis[1],normal_axis[0]*normal_axis[2],
                                normal_axis[1]*normal_axis[0],normal_axis[1]*normal_axis[1],normal_axis[1]*normal_axis[2],
                                normal_axis[2]*normal_axis[0],normal_axis[2]*normal_axis[1],normal_axis[2]*normal_axis[2])
    + glm::sin(rad)*glm::mat3(0,-normal_axis[2],normal_axis[1],
                              normal_axis[2],0,-normal_axis[0],
                              -normal_axis[1],normal_axis[0],0) ;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = eye * rotate(degrees,glm::normalize(up));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  eye = eye*rotate(degrees,glm::normalize(glm::cross(eye,up))); 
}

mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up,eye));
  vec3 v = glm::cross(w,u);
  glm::mat4 base(u[0],u[1],u[2],0,
                   v[0],v[1],v[2],0,
                   w[0],w[1],w[2],0,
                   0,0,0,1);
  glm::mat4 translate(1,0,0,-eye[0],
                      0,1,0,-eye[1],
                      0,0,1,-eye[2],
                      0,0,0,1.0);
  return translate*base;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
