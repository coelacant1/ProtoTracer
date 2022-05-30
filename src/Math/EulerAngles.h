#pragma once

#include "EulerConstants.h"
#include "EulerOrder.h"
#include "Mathematics.h"
#include "Vector3D.h"

class EulerAngles {
public:
	Vector3D Angles;
	EulerOrder Order;

	EulerAngles() {
		Angles = Vector3D(0, 0, 0);
		Order = EulerConstants::EulerOrderXYZS;
	}

	EulerAngles(Vector3D angles, EulerOrder order) {
		Angles = angles;
		Order = order;
	}

	String ToString() {
		String angles = Angles.ToString();
		String order = Order.ToString();

		return "[ " + angles + ", " + order + " ]";
	}

};
