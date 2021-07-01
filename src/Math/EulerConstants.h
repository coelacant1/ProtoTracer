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
