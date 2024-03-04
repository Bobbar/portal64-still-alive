#ifndef __SECURITY_CAMERA_H__
#define __SECURITY_CAMERA_H__

#include "../physics/collision_object.h"
#include "../levels/level_definition.h"
#include "../sk64/skelatool_armature.h"

#define SECURITY_CAMERA_RIGID_BODY_MASS 1.0f

struct SecurityCamera {
    struct CollisionObject collisionObject;
    struct RigidBody rigidBody;
    struct SKArmature armature;
    short dynamicId;
    float fizzleTime;
};

void securityCameraInit(struct SecurityCamera* securityCamera, struct SecurityCameraDefinition* definition);
void securityCameraUpdate(struct SecurityCamera* securityCamera);

void securityCamerasCheckPortal(struct SecurityCamera* securityCameras, int cameraCount, struct Box3D* portalBox);

float securityCameraMofI(); // utility for serialization

#endif