#pragma once


class UnitMovement
{
public:
    Unit* m_Unit = nullptr;
    Vector3 m_Target = { 1.f, 0.f, 1.f };
    float m_Speed = 0.1f;

	Vector3& m_UnitPos;

    UnitMovement(Unit* u) :m_Unit(u), m_UnitPos(m_Unit->mPos) 
    {
    }

    Vector3 GetDirectionToTarget() {
        Vector3 dir = m_Target - m_UnitPos;
        dir.Normalize();
        return dir;
    }

    bool isMoving() {
        return (m_UnitPos != m_Target);
    }

    void Update(float fElapsedTime)
    {
        if (!isMoving()) return;

		m_Unit->mRot.y += (fElapsedTime*2.f);

		//m_UnitPos = m_Unit->mPos;

        Vector3 dir = GetDirectionToTarget();
        m_UnitPos += (dir * m_Speed);
        float gap = m_Speed + m_Speed * 0.5f;

        if ((m_UnitPos - m_Target).Length() < gap)
            m_UnitPos = m_Target;

        //m_Unit->mPos = m_UnitPos;
    }

};


