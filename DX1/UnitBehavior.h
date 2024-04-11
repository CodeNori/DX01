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
    }
    virtual void onTerminate() override
    {
    }

    void Init(Unit* u, Vector3 target, float speed);

    virtual BT::BehaviorStatus Update() override
    {
        if (BT::BH_SUCCESS == m_BHStatus) 
            return m_BHStatus;

        m_Movement->m_Target = mTarget;
        m_Movement->m_Speed = mSpeed;
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

    void Init(Unit* u, Vector3 target, float speed, WPARAM key);


    virtual BT::BehaviorStatus Update() override
    {
        m_Movement->m_Target = mTarget;
        m_Movement->m_Speed = mSpeed;

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

