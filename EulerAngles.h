#pragma once

#include "EulerConstants.h"
#include "EulerOrder.h"
#include "Mathematics.h"
#include "Vector3D.h"

typedef struct EulerAngles {
public:
	Vector3D Angles;
	EulerOrder Order;

	EulerAngles();
	EulerAngles(Vector3D angles, EulerOrder order);

	String ToString();
} EulerAngles;
