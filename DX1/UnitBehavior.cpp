#include "pch.h"
#include "UNIT.h"
#include "UActor.h"
#include "UnitBehavior.h"

void UnitSelectBehavior::Init(Unit* u, Vector3 target, float speed, WPARAM key)
{
    mUnit = u;
    mTarget = target;
    mSpeed = speed;
    keyOrder = key;

    m_Movement = mUnit->m_Actor->m_UnitMovement;
    m_Movement->m_Target = mTarget;
    m_Movement->m_Speed = mSpeed;

}

void UnitMoveBehavior::Init(Unit* u, Vector3 target, float speed)
{
    mUnit = u;
    mTarget = target;
    mSpeed = speed;

    m_Movement = mUnit->m_Actor->m_UnitMovement;
    m_Movement->m_Target = mTarget;
    m_Movement->m_Speed = mSpeed;
}
