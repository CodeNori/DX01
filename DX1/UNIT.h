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

#include "UnitMovement.h"



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