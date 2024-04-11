#pragma once
#include "Behavior.h"
#include "Unit.h"

float GetElapsedTime();

class UnitMoveBehavior : public BT::IBehavior
{
public:
    UnitMoveBehavior(BT::IBehavior* parent) : BT::IBehavior(parent)
    {
        
    }

    virtual void onInitialize() override 
    {
        m_Movement = new UnitMovement(mUnit);
        m_Movement->m_Target = mTarget;
        m_Movement->m_Speed = mSpeed;
    }
    virtual void onTerminate() override
    {
        SAFE_DELETE(m_Movement);
    }

    void Init(Unit* u, Vector3 target, float speed)
    {
        mUnit = u;
        mTarget = target;
        mSpeed = speed;
    }

    virtual BT::BehaviorStatus Update() override
    {
        if (BT::BH_SUCCESS == m_BHStatus) 
            return m_BHStatus;

        m_Movement->Update(GetElapsedTime());

        if (m_Movement->isMoving()) 
            m_BHStatus = BT::BH_RUNNING;
        else 
            m_BHStatus = BT::BH_SUCCESS;

        return m_BHStatus;
    }

public:
    Unit* mUnit;
    Vector3 mTarget;
    float   mSpeed;
    UnitMovement* m_Movement;
};

class UnitSelectBehavior : public BT::IBehavior
{
public:
    UnitSelectBehavior(BT::IBehavior* parent, WPARAM& g)
        : BT::IBehavior(parent)
        , g_key(g)
    {
    }

    virtual void onInitialize() override
    {
        
    }
    virtual void onTerminate() override
    {
        //SAFE_DELETE(m_Movement);
    }

    void Init(Unit* u, Vector3 target, float speed, WPARAM key)
    {
        mUnit = u;
        mTarget = target;
        mSpeed = speed;
        keyOrder = key;

        m_Movement = new UnitMovement(mUnit);
        m_Movement->m_Target = mTarget;
        m_Movement->m_Speed = mSpeed;

    }


    virtual BT::BehaviorStatus Update() override
    {
        if (g_key != keyOrder) {
            return BT::BH_FAILURE;
        }
        else if (m_Movement->isMoving()) {
            m_Movement->Update(GetElapsedTime());
            return BT::BH_RUNNING;
        }

        return BT::BH_SUCCESS;
    }

public:
    Unit* mUnit;
    Vector3 mTarget;
    float   mSpeed;
    UnitMovement* m_Movement;
    WPARAM keyOrder;
    WPARAM& g_key;
};

