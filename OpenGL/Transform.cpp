// Transform.cpp: implementation of the Transform class.
#include "Transform.h"
// Helper rotation function.  Please implement this.  
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

void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = eye * rotate(degrees,glm::normalize(up));
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
  eye = eye*rotate(degrees,glm::normalize(glm::cross(eye,up))); 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float n=zNear,f=zFar,
  d = glm::cos(glm::radians(fovy));
  float A = -(f+n)/(f-n),
      B = -(2*f*n)/(f-n);
  return mat4(d/aspect,0,0,0,
              0,d,0,0,
              0,0,A,B,
              0,0,-1,0);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
  // scaling 
  return mat4(sx,0,0,1,
              0,sy,0,1,
              0,0,sz,1,
              0,0,0,1.0);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
  // translation 
  return mat4(1,0,0,tx,
              0,1,0,ty,
              0,0,1,tz,
              0,0,0,1.0);
}
// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
  vec3 x = glm::cross(up,zvec) ; 
  vec3 y = glm::cross(zvec,x) ; 
  vec3 ret = glm::normalize(y) ; 
  return ret ; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
