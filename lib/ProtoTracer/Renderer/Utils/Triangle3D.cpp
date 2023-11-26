#include "Triangle3D.h"

Triangle3D::Triangle3D() {}

Triangle3D::Triangle3D(Vector3D* p1, Vector3D* p2, Vector3D* p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;

    this->Normal();
}

Vector3D* Triangle3D::Normal() {
    edge1 = *p2 - *p1;
    edge2 = *p3 - *p1;
    normal = edge1.CrossProduct(edge2).UnitSphere();

    return &normal;
}

bool Triangle3D::DidIntersect(Vector3D ray, Vector3D direction, Vector3D* intersect, Vector3D* color) {
    Vector3D pvec = direction.CrossProduct(edge2);
    float det = edge1.DotProduct(pvec);
    float invDet = 1.0f / det;

    if (fabs(det) < 0.000001f) return false;

    Vector3D tvec = ray - *p1;
    float u = tvec.DotProduct(pvec) * invDet;
    if (u < 0.0f || u > 1.0f) return false;

    Vector3D qvec = tvec.CrossProduct(edge1);
    float v = direction.DotProduct(qvec) * invDet;
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = edge2.DotProduct(qvec) * invDet;

    if (t > 0.000001f) {
        Vector3D tempInt = *p1 + (edge2 * u) + (edge1 * v);

        tempInt = ray + direction.Multiply(t);

        intersect->X = tempInt.X;
        intersect->Y = tempInt.Y;
        intersect->Z = tempInt.Z;

        color->X = u;
        color->Y = v;
        color->Z = (1.0f - u - v);

        return true;
    }
    else {
        return false;
    }
}

String Triangle3D::ToString() {
    return p1->ToString() + " " + p2->ToString() + " " + p3->ToString();
}
