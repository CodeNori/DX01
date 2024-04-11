#pragma once

namespace BT {

    enum BehaviorStatus
    {
        BH_INVALID,
        BH_SUCCESS,
        BH_FAILURE,
        BH_RUNNING
    };

    class IBehaviorBase
    {
    public:
        BehaviorStatus m_BHStatus = BH_INVALID;

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


    class IBehavior : public IBehaviorBase
    {
    public:
        IBehavior* m_Parent = nullptr;
        IBehavior* m_Child = nullptr;
        IBehavior* m_Next = nullptr;
        int m_NextNo = 0;

        IBehavior(IBehavior* parent) { 
            m_Parent = parent; 
            if(parent) parent->AddChildToLast(this);
        }

        void AddChild(IBehavior* newnode)
        {
            if (m_Child)
                newnode->m_Child = m_Child;

            m_Child = newnode;
        }
        void AddNext(IBehavior* newnode)
        {
            if (m_Next)
                newnode->m_Next = m_Next;

            m_Next = newnode;
        }
        void AddChildToLast(IBehavior* newnode)
        {
            IBehavior* ch = m_Child;
            if (!ch) {
                m_Child = newnode;
                m_Child->m_Next = nullptr;
                m_Child->m_NextNo = 0;
                return;
            }

            while (ch->m_Next)
                ch = ch->m_Next;

            ch->m_Next = newnode;
            ch->m_Next->m_NextNo = ch->m_NextNo + 1;
            ch->m_Next->m_Next = nullptr;

        }

        IBehavior* FindPrev()
        {
            if (m_Parent->m_Child == this)
                return nullptr;

            IBehavior* node = m_Parent->m_Child;

            while (node->m_Next) {
                if (node->m_Next == this)
                    return node;

                node = node->m_Next;
            }

            return nullptr;
        }
        void RemoveChildAll()
        {
            while (m_Child) {
                IBehavior* node = m_Child;
                m_Child = node->m_Next;

                node->RemoveChildAll();
                delete node;
            }
        }
        void RemoveLink()
        {
            RemoveChildAll();

            if (m_Parent->m_Child == this) {
                m_Parent->m_Child = m_Next;
            }
            else {
                IBehavior* prev = FindPrev();
                if (prev) {
                    prev->m_Next = m_Next;
                }
            }
        }
        void RemoveNext() {
            IBehavior* n = m_Next;
            if (n) {
                m_Next = n->m_Next;
                delete n;
            }
        }

        void All_ClearStatus() {
            m_BHStatus = BH_INVALID;
            IBehavior* ch = m_Child;
            while (ch) {
                ch->All_ClearStatus();
                ch = ch->m_Next;
            }

        }
    };


    class Sequence : public IBehavior
    {
    public:
        Sequence(IBehavior* parent) : IBehavior(parent) {}

        virtual BehaviorStatus Update() override
        {
            BehaviorStatus s = BH_RUNNING;

            IBehavior* bh = m_Child;

            while (bh)
            {
                s = bh->tick();
                switch (s)
                {
                case BH_SUCCESS:
                    bh = bh->m_Next;
                    break;
                case BH_FAILURE:
                    bh = nullptr;
                    break;
                case BH_RUNNING:
                    bh = nullptr;
                    break;
                }
            }

            return s;
        }
    };

    class Selector : public IBehavior
    {
    public:
        Selector(IBehavior* parent) : IBehavior(parent) {}

        virtual BehaviorStatus Update() override
        {
            BehaviorStatus s = BH_RUNNING;
            IBehavior* bh = m_Child;

            while (bh)
            {
                s = bh->tick();
                switch (s)
                {
                case BH_SUCCESS:
                    bh = nullptr;
                    break;
                case BH_FAILURE:
                    bh = bh->m_Next;
                    break;
                case BH_RUNNING:
                    bh = nullptr;
                    break;
                }
            }

            return s;
        }
    };

} // namespace BT