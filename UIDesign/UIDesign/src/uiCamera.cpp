#include "uiCamera.h"
#include "uiMath.h"
#include "uiWindowManager.h"

void Camera::Initialize()
{

}

void Camera::OnDestroy()
{

}

void Camera::PropagateTransform(const Transform2D& newTransform)
{
  setCenter(newTransform.position + m_offset->position);
}

void Camera::Update(const float& delta)
{
  WindowManager::Instance().m_mainWindow->setView(*this);
}
