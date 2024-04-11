#pragma once

#define SAFE_DELETE(x) if(x){ delete (x); (x)=nullptr; }

class UActor;

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

    UActor* m_Actor;

    void Update(float fElapsedTime);
    void Render(ID3D11DeviceContext* pd3dContext);
};

#include "UnitMovement.h"


