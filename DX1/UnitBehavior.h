#pragma once
#include "Unit.h"
#include "Behavior.h"

float GetElapsedTime();

class UnitMoveBehavior : public IBehavior
{
public:
    UnitMoveBehavior(IBehavior* parent) : IBehavior(parent)
    {
        parent->AddChildToLast(this);
    }

    void Init(Unit* u, Vector3 target) {
        m_Movement = new UnitMovement(u);
        m_Movement->m_Target = target;
        m_Movement->m_Speed = 0.3f;
    }

    virtual BehaviorStatus Update() override
    {
        if (BH_SUCCESS == m_BHStatus) 
            return m_BHStatus;

        m_Movement->Update(GetElapsedTime());

        if (m_Movement->isMoving()) 
            m_BHStatus = BH_RUNNING;
        else 
            m_BHStatus = BH_SUCCESS;

        return m_BHStatus;
    }
protected:

    UnitMovement* m_Movement;
};


