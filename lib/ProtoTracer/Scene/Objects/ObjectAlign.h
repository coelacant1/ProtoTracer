/**
 * @file ObjectAlign.h
 * @brief Provides the ObjectAlign class for aligning 3D objects within defined 2D camera bounds.
 *
 * The ObjectAlign class is useful for positioning, scaling, and orienting 3D objects
 * (or collections of objects) relative to a 2D screen area (defined by min/max camera
 * coordinates). It calculates transformations needed to align objects in a plane while
 * providing options for mirroring and different justification modes.
 */

#pragma once

#include "../../Utils/Math/Plane.h"
#include "../../Scene/Objects/Object3D.h"

/**
 * @class ObjectAlign
 * @brief Handles aligning and transforming 3D objects to fit within specified 2D camera bounds.
 *
 * This class is primarily concerned with projecting objects into a plane, scaling them
 * to fit within camera bounds, and applying transformations (orientation, mirroring,
 * edge offsets, etc.). 
 */
class ObjectAlign {
public:
    /**
     * @enum Justification
     * @brief Describes how the object(s) should be justified within the bounding box.
     *
     * For instance, LowerLeft places the object in the lower-left corner (with potential
     * offsets), while Stretch attempts to fit or stretch objects to fill the entire area.
     */
    enum Justification {
        UpperLeft,    ///< Justify to the upper-left corner of the bounding area.
        UpperMiddle,  ///< Justify to the top center of the bounding area.
        UpperRight,   ///< Justify to the upper-right corner of the bounding area.
        MiddleLeft,   ///< Justify to the middle-left side of the bounding area.
        Middle,       ///< Center the object within the bounding area.
        MiddleRight,  ///< Align to the middle-right side of the bounding area.
        LowerLeft,    ///< Justify to the lower-left corner of the bounding area.
        LowerMiddle,  ///< Align to the bottom center of the bounding area.
        LowerRight,   ///< Justify to the lower-right corner of the bounding area.
        Stretch       ///< Attempt to scale the object(s) to fill the entire area.
    };

private:
    Justification jst = Middle;          ///< Current justification mode.
    Quaternion targetOrientation;        ///< Target orientation for aligning the object(s).
    Vector3D forwardVector = Vector3D(0.0f, 0.0f, 1.0f); ///< Default "forward" axis.
    Vector2D cameraCenter;               ///< Computed center between camMin and camMax.
    Vector2D camMin;                     ///< Minimum 2D camera bounds (lower-left).
    Vector2D camMax;                     ///< Maximum 2D camera bounds (upper-right).
    float offsetPlaneAngle = 0.0f;       ///< Additional rotation offset (plane offset angle in degrees or radians).
    float edgeMargin = 10.0f;            ///< Margin from the bounding edges, in screen-space units.
    float scaleX = 1.0f;                 ///< Scaling factor on the X-axis.
    float scaleY = 1.0f;                 ///< Scaling factor on the Y-axis.
    bool mirrorX = false;                ///< Whether to mirror objects along the X-axis.
    bool mirrorY = false;                ///< Whether to mirror objects along the Y-axis.

    /**
     * @brief Normalizes the orientation of multiple objects onto a plane.
     *
     * This function modifies the input objects so that they are oriented parallel
     * to a plane defined by \p planeOrientation, also adjusting their centers
     * to the specified \p center.
     *
     * @param objs Array of pointers to Object3D instances.
     * @param numObjects Number of objects in \p objs.
     * @param center Desired alignment center in 3D space.
     * @param planeOrientation Orientation (Quaternion) defining the plane normal.
     */
    void NormalizeObjectPlane(Object3D** objs, uint8_t numObjects, Vector3D center, Quaternion planeOrientation);

    /**
     * @brief Translates the center of multiple objects so that their average center
     *        matches the specified \p center.
     *
     * @param objs Array of pointers to Object3D instances.
     * @param numObjects Number of objects in \p objs.
     * @param center The target center position in 3D space.
     */
    void NormalizeObjectCenter(Object3D** objs, uint8_t numObjects, Vector3D center);

public:
    /**
     * @brief Constructor for ObjectAlign, setting up the camera bounds and orientation.
     * @param camMin The lower-left corner of the 2D camera region.
     * @param camMax The upper-right corner of the 2D camera region.
     * @param targetOrientation Optional desired orientation for aligned objects.
     */
    ObjectAlign(Vector2D camMin, Vector2D camMax, Quaternion targetOrientation = Quaternion());

    /**
     * @brief Computes the centroid of the given object's geometry.
     * @param obj Pointer to the Object3D.
     * @return A Vector3D representing the centroid position.
     */
    Vector3D GetCentroid(Object3D* obj);

    /**
     * @brief Computes the collective centroid of multiple objects.
     * @param objs Array of pointers to Object3D objects.
     * @param numObjects Number of objects in \p objs.
     * @return A Vector3D representing the combined centroid of all objects.
     */
    Vector3D GetCentroid(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Computes the "center" of a single object. Generally the same as centroid,
     *        but could be defined differently if an object's pivot or bounding logic
     *        is distinct.
     * @param obj Pointer to the Object3D.
     * @return The object's center as a Vector3D.
     */
    Vector3D GetObjectCenter(Object3D* obj);

    /**
     * @brief Computes the collective center for multiple objects.
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @return A Vector3D representing the combined center of all objects.
     */
    Vector3D GetObjectCenter(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Retrieves the bounding box size (width, height, depth) of a single object.
     * @param obj Pointer to the Object3D.
     * @return A Vector3D whose components represent the bounding box dimensions.
     */
    Vector3D GetObjectSize(Object3D* obj);

    /**
     * @brief Computes the combined bounding box size for multiple objects.
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @return A Vector3D representing the bounding box that encloses all objects.
     */
    Vector3D GetObjectSize(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Determines the plane normal (as a Quaternion) of the object based on its geometry.
     *
     * This might be computed from the surface normal if the object is considered planar,
     * or from an average of normals if the object is more complex.
     *
     * @param obj Pointer to the Object3D.
     * @return A Quaternion representing the plane's orientation (normal).
     */
    Quaternion GetPlaneNormal(Object3D* obj);

    /**
     * @brief Determines the average plane normal (as a Quaternion) for multiple objects.
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @return A Quaternion representing the average plane orientation.
     */
    Quaternion GetPlaneNormal(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Calculates the orientation needed to make the object's plane face the camera or
     *        align with a given centroid.
     *
     * @param obj Pointer to the Object3D.
     * @param centroid The computed centroid of the object.
     * @return A Quaternion representing the orientation for that plane.
     */
    Quaternion GetPlaneOrientation(Object3D* obj, Vector3D centroid);

    /**
     * @brief Calculates the orientation needed for multiple objects to share a consistent plane.
     *
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @param centroid The computed centroid of all objects.
     * @return A Quaternion representing the plane orientation for the combined objects.
     */
    Quaternion GetPlaneOrientation(Object3D** objs, uint8_t numObjects, Vector3D centroid);

    /**
     * @brief Computes the final Transform for aligning a single Object3D within the camera bounds.
     *
     * The Transform includes translation, rotation, and scaling as determined by the justification,
     * margins, and plane offset angle.
     *
     * @param obj Pointer to the Object3D to align.
     * @return A Transform struct containing position, rotation, and scale.
     */
    Transform GetTransform(Object3D* obj);

    /**
     * @brief Computes the final Transform for aligning multiple objects as a group.
     *
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @return A Transform for the combined alignment of the group.
     */
    Transform GetTransform(Object3D** objs, uint8_t numObjects);
    
    /**
     * @brief Computes how planar (flat) a single object is, typically as a ratio (0.0 = not planar, 1.0 = perfectly planar).
     * @param obj Pointer to the Object3D.
     * @return A float representing the planarity ratio.
     */
    float GetObjectPlanarityRatio(Object3D* obj);

    /**
     * @brief Computes an average planarity ratio for multiple objects.
     *
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     * @return A float representing the combined or averaged planarity ratio.
     */
    float GetObjectPlanarityRatio(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Sets the additional rotation offset (plane offset angle), in degrees or radians,
     *        that will be applied when calculating plane orientation.
     *
     * @param offsetPlaneAngle The rotation offset to apply.
     */
    void SetPlaneOffsetAngle(float offsetPlaneAngle);

    /**
     * @brief Sets the margin to keep from the edges when aligning objects.
     * @param edgeMargin How many screen-space units to leave as margin.
     */
    void SetEdgeMargin(float edgeMargin);

    /**
     * @brief Sets the forward vector, i.e., which axis is considered "forward" for the alignment logic.
     * @param forwardVector A Vector3D defining the forward axis.
     */
    void SetForwardVector(Vector3D forwardVector);

    /**
     * @brief Updates the minimum bounds for the 2D camera region.
     * @param camMin A Vector2D representing the lower-left corner.
     */
    void SetCameraMin(Vector2D camMin);

    /**
     * @brief Updates the maximum bounds for the 2D camera region.
     * @param camMax A Vector2D representing the upper-right corner.
     */
    void SetCameraMax(Vector2D camMax);

    /**
     * @brief Enables or disables mirroring along the X-axis for the aligned objects.
     * @param mirrorX True to mirror objects on X-axis, false to disable.
     */
    void SetMirrorX(bool mirrorX);

    /**
     * @brief Enables or disables mirroring along the Y-axis for the aligned objects.
     * @param mirrorY True to mirror objects on Y-axis, false to disable.
     */
    void SetMirrorY(bool mirrorY);

    /**
     * @brief Sets the justification mode for alignment.
     * @param jst One of the enum values (UpperLeft, Middle, Stretch, etc.).
     */
    void SetJustification(Justification jst);

    /**
     * @brief Sets the scaling factors that will be applied to objects during alignment.
     * @param scaleX The multiplier for width.
     * @param scaleY The multiplier for height.
     */
    void SetScale(float scaleX, float scaleY);

    /**
     * @brief Aligns a single Object3D within the camera bounds without applying the object's scaling factor.
     *
     * Only transforms the object to fit in the plane (translation + orientation); no scaling from the object itself.
     * @param obj Pointer to the Object3D to align.
     */
    void AlignObjectNoScale(Object3D* obj);

    /**
     * @brief Aligns multiple objects without applying the object's scaling factor.
     *
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     */
    void AlignObjectsNoScale(Object3D** objs, uint8_t numObjects);

    /**
     * @brief Aligns a single Object3D within the camera bounds, including applying scale factors as necessary.
     * @param obj Pointer to the Object3D to align.
     */
    void AlignObject(Object3D* obj);

    /**
     * @brief Aligns multiple objects within the camera bounds, including scale factors.
     * @param objs Array of pointers to Object3D.
     * @param numObjects Number of objects in \p objs.
     */
    void AlignObjects(Object3D** objs, uint8_t numObjects);
};
