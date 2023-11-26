#include "CameraBase.h"

CameraBase::CameraBase() {}

CameraLayout* CameraBase::GetCameraLayout() {
    return cameraLayout;
}

Transform* CameraBase::GetTransform() {
    return transform;
}

bool CameraBase::Is2D() {
    return is2D;
}

void CameraBase::Set2D(bool is2D) {
    this->is2D = is2D;
}

void CameraBase::SetLookOffset(Quaternion lookOffset) {
    this->lookOffset = lookOffset;
}

Quaternion CameraBase::GetLookOffset() {
    return lookOffset;
}
