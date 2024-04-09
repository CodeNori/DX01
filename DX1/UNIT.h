#pragma once

#define SAFE_DELETE(x) if(x){ delete (x); (x)=nullptr; }


class Unit
{
public:
    Unit();
    ~Unit();

    class CUP_MESH* mMesh = nullptr;
    class BoxShader* mShader = nullptr;
    Matrix mModelTM;

    Vector3 mPos;
	Vector3 mRot;
	Vector3 mScale;

    void Update(float fElapsedTime);
    void Render(ID3D11DeviceContext* pd3dContext);
};


class UnitMovement
{
public:
    Unit* m_Unit = nullptr;
    Vector3 m_Target = { 1.f, 0.f, 1.f };
    float m_Speed = 0.02f;

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

		//m_UnitPos = m_Unit->mPos;

        Vector3 dir = GetDirectionToTarget();
        m_UnitPos += (dir * m_Speed);
        float gap = m_Speed + m_Speed * 0.5f;

        if ((m_UnitPos - m_Target).Length() < gap)
            m_UnitPos = m_Target;

        //m_Unit->mPos = m_UnitPos;
    }

};



class UActor
{
public:
    Unit* m_Unit = nullptr;
    UnitMovement* m_UnitMovement = nullptr;
    class IBehavior* m_AI = nullptr;

    UActor() { Init();  }
    ~UActor() { Release(); }
    void InitAI();
    void Init();

    void Release();
    void Update(float fElapsedTime);
    void Render(ID3D11DeviceContext* pd3dContext);
};