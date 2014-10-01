#include "Arcball.h"

//------------------------------------------------------------------------------
Arcball::Arcball(const glm::vec3& center, glm::float_t radius, const glm::mat4& screenToTCS) :
    mCenter(center),
    mRadius(radius),
    mScreenToTCS(screenToTCS)
{
  // glm uses the following format for quaternions: w,x,y,z.
  //        w,    x,    y,    z
  glm::quat qOne(1.0, 0.0, 0.0, 0.0);
  glm::vec3 vZero(0.0, 0.0, 0.0);

  mVDown    = vZero;
  mVNow     = vZero;
  mQDown    = qOne;
  mQNow     = qOne;

  //PAN
  tPanVector = glm::vec3(0,0,0);

  //ZOOM
  sZoom = 1;
}

//------------------------------------------------------------------------------
Arcball::~Arcball()
{
}

//------------------------------------------------------------------------------
glm::vec3  Arcball::mouseOnSphere(const glm::vec3& tscMouse)
{
  glm::vec3 ballMouse;

  // (m - C) / R
  ballMouse.x = (tscMouse.x - mCenter.x) / mRadius;
  ballMouse.y = (tscMouse.y - mCenter.y) / mRadius;

  glm::float_t mag = ballMouse.x*ballMouse.x + ballMouse.y*ballMouse.y;
  if (mag > 1.0)
  {
	//std::cout << "mag > 1"<< std::endl;
    // Since we are outside of the sphere, map to the visible boundary of
    // the sphere.
    ballMouse.x *= 1.0 / sqrtf(mag);
    ballMouse.y *= 1.0 / sqrtf(mag);
    ballMouse.z = 0.0;
  }
  else
  {
    // We are not at the edge of the sphere, we are inside of it.
    // Essentially, we are normalizing the vector by adding the missing z
    // component.
    ballMouse.z = sqrtf(1.0 - mag);
  }

  return ballMouse;
}

//------------------------------------------------------------------------------
void  Arcball::beginDrag(const glm::vec2& msc)
{
  // The next two lines are usually a part of end drag. But end drag introduces
  // too much statefullness, so we are shortcircuiting it.
  mQDown      = mQNow;

  // Normal 'begin' code.
  mVDown.x = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).x;
  mVDown.y = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).y;
  mVDown.z = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).z;
  //mVDown      = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).xyz();
}

//------------------------------------------------------------------------------
void  Arcball::drag(const glm::vec2& msc)
{
  // Regular drag code to follow...

  //4mVNow       = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0, 1.0)).xyz();
  mVNow.x = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).x;
  mVNow.y = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).y;
  mVNow.z = (mScreenToTCS * glm::vec4(msc.x, msc.y, 0.0f, 1.0)).z;

  mVSphereFrom= mouseOnSphere(mVDown);
  mVSphereTo  = mouseOnSphere(mVNow);

  // Construct a quaternion from two points on the unit sphere.
  mQDrag = quatFromUnitSphere(mVSphereFrom, mVSphereTo); 
  mQNow = mQDrag * mQDown;

  // Perform complex conjugate
//  glm::quat q = mQNow;
//  q.x = -q.x;
//  q.y = -q.y;
//  q.z = -q.z;
  //q.w =  q.w;
  mMatNow = glm::mat4_cast(glm::conjugate(mQNow));
//	int j =0;
//	for (int i = 0; i < 4; ++i) {
//		for (j = 0; j < 4; ++j) {
//			std::cout << mMatNow[i][j] << "|";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
}

//------------------------------------------------------------------------------
glm::quat  Arcball::quatFromUnitSphere(const glm::vec3& from, const glm::vec3& to)
{
  glm::quat q;
  q.x = from.y*to.z - from.z*to.y;
  q.y = from.z*to.x - from.x*to.z;
  q.z = from.x*to.y - from.y*to.x;
  q.w = from.x*to.x + from.y*to.y + from.z*to.z;
  return q;
}

//------------------------------------------------------------------------------
glm::mat4  Arcball::getTransformation() const
{
  return mMatNow;
}

//------------------------------------------------------------------------------
glm::vec3  Arcball::getPan() const
{
  return tPanVector;
}

//------------------------------------------------------------------------------
void Arcball::setPanDrag(glm::vec3 t)
{
	tPanVector += t;
}

//------------------------------------------------------------------------------
void Arcball::setZoom(float v)
{

	sZoom += v;
	if (sZoom < 1)
		sZoom = 1;
}

float Arcball::getZoom() const
{
	return sZoom;
}


