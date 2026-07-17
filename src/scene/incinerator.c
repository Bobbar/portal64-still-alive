#include "incinerator.h"

#include "scene/dynamic_scene.h"
#include "util/dynamic_asset_loader.h"

#include "codegen/assets/materials/static.h"
#include "codegen/assets/models/dynamic_animated_model_list.h"
#include "codegen/assets/models/props_bts/glados_aperturedoor.h"

void incineratorRender(void* data, struct DynamicRenderDataList* renderList, struct RenderState* renderState) {
    struct Incinerator* incinerator = (struct Incinerator*)data;

    Mtx* matrix = renderStateRequestMatrices(renderState, 1);
    if (!matrix) {
        return;
    }

    transformToMatrixL(&incinerator->transform, matrix, SCENE_SCALE);

    Mtx* armature = renderStateRequestMatrices(renderState, incinerator->armature.numberOfBones);
    if (!armature) {
        return;
    }

    skCalculateTransforms(&incinerator->armature, armature);

    dynamicRenderListAddData(
        renderList,
        incinerator->armature.displayList,
        matrix,
        INCINERATOR_INDEX,
        &incinerator->transform.position,
        armature
    );
}

void incineratorInit(struct Incinerator* incinerator, struct IncineratorDefinition* definition) {
    struct SKArmatureWithAnimations* armature = dynamicAssetAnimatedModel(PROPS_BTS_GLADOS_APERTUREDOOR_DYNAMIC_ANIMATED_MODEL);
    skArmatureInit(&incinerator->armature, armature->armature);
    skAnimatorInit(&incinerator->animator, armature->armature->numberOfBones);

    incinerator->transform.position = definition->position;
    incinerator->transform.rotation = definition->rotation;
    incinerator->transform.scale = gOneVec;

    incinerator->signalIndex = definition->signalIndex;

    incinerator->dynamicId = dynamicSceneAdd(
        incinerator,
        incineratorRender,
        &incinerator->transform.position,
        2.0f
    );
    dynamicSceneSetRoomFlags(incinerator->dynamicId, ROOM_FLAG_FROM_INDEX(definition->roomIndex));
}
