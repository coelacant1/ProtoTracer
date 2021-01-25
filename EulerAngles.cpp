#include "EulerAngles.h"

EulerAngles::EulerAngles() {
	Angles = Vector3D(0, 0, 0);
	Order = EulerConstants::EulerOrderXYZS;
}

EulerAngles::EulerAngles(Vector3D angles, EulerOrder order) {
	Angles = angles;
	Order = order;
}

String EulerAngles::ToString() {
	String angles = Angles.ToString();
	String order = Order.ToString();

	return "[ " + angles + ", " + order + " ]";
}
