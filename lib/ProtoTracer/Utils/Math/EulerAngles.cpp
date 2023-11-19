#include "EulerAngles.h"
#include "EulerConstants.h"

// Default constructor.
EulerAngles::EulerAngles() 
    : Angles(0, 0, 0), Order(EulerConstants::EulerOrderXYZS) {}

// Constructor with angles and order.
EulerAngles::EulerAngles(Vector3D angles, EulerOrder order) 
    : Angles(angles), Order(order) {}

// Convert EulerAngles to a string representation.
String EulerAngles::ToString() {
    String angles = Angles.ToString();
    String order = Order.ToString();

    return "[ " + angles + ", " + order + " ]";
}
