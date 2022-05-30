#pragma once

#include "EulerOrder.h"

typedef struct EulerConstants {
	//Static frame of reference, inertial reference frame
	static EulerOrder EulerOrderXYZS;
	static EulerOrder EulerOrderXYXS;
	static EulerOrder EulerOrderXZYS;
	static EulerOrder EulerOrderXZXS;
	static EulerOrder EulerOrderYZXS;
	static EulerOrder EulerOrderYZYS;
	static EulerOrder EulerOrderYXZS;
	static EulerOrder EulerOrderYXYS;
	static EulerOrder EulerOrderZXYS;
	static EulerOrder EulerOrderZXZS;
	static EulerOrder EulerOrderZYXS;
	static EulerOrder EulerOrderZYZS;

	//Rotating frame of reference, non-inertial reference frame
	static EulerOrder EulerOrderZYXR;
	static EulerOrder EulerOrderXYXR;
	static EulerOrder EulerOrderYZXR;
	static EulerOrder EulerOrderXZXR;
	static EulerOrder EulerOrderXZYR;
	static EulerOrder EulerOrderYZYR;
	static EulerOrder EulerOrderZXYR;
	static EulerOrder EulerOrderYXYR;
	static EulerOrder EulerOrderYXZR;
	static EulerOrder EulerOrderZXZR;
	static EulerOrder EulerOrderXYZR;
	static EulerOrder EulerOrderZYZR;

} EulerConstants;

//Static frame of reference, inertial reference frame
EulerOrder EulerConstants::EulerOrderXYZS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2));
EulerOrder EulerConstants::EulerOrderXYXS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 1, 2));
EulerOrder EulerConstants::EulerOrderXZYS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1));
EulerOrder EulerConstants::EulerOrderXZXS = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(0, 2, 1));
EulerOrder EulerConstants::EulerOrderYZXS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0));
EulerOrder EulerConstants::EulerOrderYZYS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 2, 0));
EulerOrder EulerConstants::EulerOrderYXZS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2));
EulerOrder EulerConstants::EulerOrderYXYS = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(1, 0, 2));
EulerOrder EulerConstants::EulerOrderZXYS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1));
EulerOrder EulerConstants::EulerOrderZXZS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 0, 1));
EulerOrder EulerConstants::EulerOrderZYXS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0));
EulerOrder EulerConstants::EulerOrderZYZS = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Static, Vector3D(2, 1, 0));

//Rotating frame of reference, non-inertial reference frame
EulerOrder EulerConstants::EulerOrderZYXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2));
EulerOrder EulerConstants::EulerOrderXYXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 1, 2));
EulerOrder EulerConstants::EulerOrderYZXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1));
EulerOrder EulerConstants::EulerOrderXZXR = EulerOrder(EulerOrder::Axis::X, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(0, 2, 1));
EulerOrder EulerConstants::EulerOrderXZYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0));
EulerOrder EulerConstants::EulerOrderYZYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 2, 0));
EulerOrder EulerConstants::EulerOrderZXYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2));
EulerOrder EulerConstants::EulerOrderYXYR = EulerOrder(EulerOrder::Axis::Y, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(1, 0, 2));
EulerOrder EulerConstants::EulerOrderYXZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1));
EulerOrder EulerConstants::EulerOrderZXZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Even, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 0, 1));
EulerOrder EulerConstants::EulerOrderXYZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::No, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0));
EulerOrder EulerConstants::EulerOrderZYZR = EulerOrder(EulerOrder::Axis::Z, EulerOrder::Parity::Odd, EulerOrder::AxisRepetition::Yes, EulerOrder::AxisFrame::Rotating, Vector3D(2, 1, 0));