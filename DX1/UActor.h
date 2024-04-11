#pragma once
#include "Behavior.h"

class UActor
{
public:
    Unit* m_Unit = nullptr;
    UnitMovement* m_UnitMovement = nullptr;
    BT::IBehavior* m_AI = nullptr;
    BT::IBehavior* m_Seq = nullptr;

    UActor() { Init();  }
    ~UActor() { Release(); }
    void InitAI();
    void Init();

    void Release();
    void Update(float fElapsedTime);
    void Render(ID3D11DeviceContext* pd3dContext);
};

