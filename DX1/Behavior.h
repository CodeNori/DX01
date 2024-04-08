#pragma once

enum BehaviorStatus
{
    BH_INVALID,
    BH_SUCCESS,
    BH_FAILURE,
    BH_RUNNING
};

class IBehavior
{
protected:
    BehaviorStatus m_BHStatus = BH_INVALID;
    class CompositeBH* m_Parent = nullptr;


public:
    virtual BehaviorStatus Update() = 0;
    virtual void onInitialize() {}
    virtual void onTerminate() {}

    BehaviorStatus tick()
    {
        if (m_BHStatus == BH_INVALID) {
            onInitialize();
            m_BHStatus = BH_RUNNING;
        }

        m_BHStatus = Update();

        if (m_BHStatus != BH_RUNNING)
            onTerminate();

        return m_BHStatus;
    }
};


struct BehaviorContext 
{
    class CompositeBH* m_Parent = nullptr;
    IBehavior* mCurrent;
    int        mIdx;

};

class CompositeBH : public IBehavior
{
protected:
    typedef std::vector<IBehavior*> IBehaviors;
    IBehaviors m_Children;    

public:
    CompositeBH()
    void AddChild(IBehavior* child) { m_Children.push_back(child); }
    void RemoveChild(IBehavior*);
    void ClearChildren();
};


class SequenceBH : public CompositeBH
{
    int  m_CurrentIdx = 0;
protected:
    virtual void onInitialize() override { m_CurrentIdx = 0; }

    virtual BehaviorStatus Update() override
    {
        BehaviorStatus r = BH_RUNNING;

        for(int i=0; i<)
        if (m_CurrentIdx < m_Children.size())
        {
            BehaviorStatus s = m_Children[m_CurrentIdx]->tick();
            
            switch (s)
            {
            case BH_SUCCESS: 
                ++m_CurrentIdx; 
                r = BH_RUNNING;
                break;
            case BH_FAILURE: 
                r = BH_FAILURE; 
                break;
            }
        }
        else {
            r = BH_SUCCESS;
        }

        return r;             
    }
};



class FallbackBH : public CompositeBH
{
    int  m_CurrentIdx = 0;
protected:
    virtual void onInitialize() override { m_CurrentIdx = 0; }

    virtual BehaviorStatus Update() override
    {
        BehaviorStatus re = BH_RUNNING;
        if (m_CurrentIdx < m_Children.size())
        {
            BehaviorStatus s = m_Children[m_CurrentIdx]->tick();

            switch (s)
            {
            case BH_FAILURE:  // ���� ���и� �ߴٸ�, Next Behavior�� �Ϸ� ���� �Ѵ�.
                ++m_CurrentIdx; 
                re = BH_RUNNING;
                break;
            case BH_SUCCESS:   // if SUCCESS, �Ϸ��ϰ� ������ �ö󰡾� �Ѵ�.
                m_BHStatus = BH_SUCCESS; 
                re = BH_SUCCESS;
                break;
            }
        }
        else {
            re = BH_FAILURE;
        }

        return re;
    }
};


