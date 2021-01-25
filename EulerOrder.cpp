#include "EulerOrder.h"

EulerOrder::EulerOrder() {
	//XYZ static/inertial frame of reference
	InitialAxis = Axis::X;
	AxisPermutation = Parity::Even;
	InitialAxisRepetition = AxisRepetition::No;
	FrameTaken = AxisFrame::Static;
	Permutation = Vector3D(0, 1, 2);
}

EulerOrder::EulerOrder(Axis axis, Parity parity, AxisRepetition axisRepetition, AxisFrame axisFrame, Vector3D permutation) {
	InitialAxis = axis;
	AxisPermutation = parity;
	InitialAxisRepetition = axisRepetition;
	FrameTaken = axisFrame;
	Permutation = permutation;
}

String EulerOrder::ToString() {
	return Permutation.ToString();
}
