#pragma once

#include "EulerConstants.h"
#include "EulerOrder.h"
#include "Mathematics.h"
#include "Vector3D.h"

typedef struct EulerAngles {
public:
	Vector3D Angles;
	EulerOrder Order;

	EulerAngles() 
		: Angles(Vector3D(0, 0, 0)),
		  Order(EulerConstants::EulerOrderXYZS) {}

	EulerAngles(const Vector3D angles, const EulerOrder order) 
		: Angles(angles),
		  Order(order) {}

	String ToString() const {
		String angles = Angles.ToString();
		String order = Order.ToString();

		return "[ " + angles + ", " + order + " ]";
	}
} EulerAngles;
