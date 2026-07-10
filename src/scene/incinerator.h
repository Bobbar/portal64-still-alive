#ifndef __INCINERATOR_H__
#define __INCINERATOR_H__

#include "levels/level_definition.h"
#include "sk64/skeletool_animator.h"
#include "sk64/skeletool_armature.h"

struct Incinerator {
    struct SKAnimator animator;
    struct SKArmature armature;
    struct Transform transform;
    short signalIndex;
    short dynamicId;
};

void incineratorInit(struct Incinerator* incinerator, struct IncineratorDefinition* definition);

#endif
