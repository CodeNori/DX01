#include "pch.h"
#include "ObjModel.h"
#include "SHADER.h"
#include "UNIT.h"
#include "UnitBehavior.h"

#define SAFE_DELETE(x) if(x){ delete (x); (x)=nullptr;}


Unit::Unit()
{
    mModelTM = Matrix::Identity;
    mPos = Vector3(0, 0, 0);
	mRot = Vector3(0, 0, 0);
	mScale = Vector3(1.f, 1.f, 1.f);

    mShader = new BoxShader;
    mShader->Init();
    mShader->SetAmbientLight(0.2f);
    mShader->SetLightDir(XMFLOAT3(-0.577f, 0.577f, -0.577f));
    mShader->SetDiffuseTexture(L"cup.jpg");
    mShader->SetWorld(Matrix::Identity);

    mMesh = new CUP_MESH;
    mMesh->Init();
    mMesh->SetShader(mShader);
}

Unit::~Unit()
{
    SAFE_DELETE(mShader);
    SAFE_DELETE(mMesh);
}

void Unit::Update(float fElapsedTime)
{
}

void Unit::Render(ID3D11DeviceContext* d3dContext)
{
    Matrix w = mModelTM;
    w *= Matrix::CreateScale(mScale);
    w *= Matrix::CreateFromYawPitchRoll(mRot);
    w *= Matrix::CreateTranslation(mPos);

    mShader->SetWorld(w);
    mShader->Apply(d3dContext);
    mMesh->Render(d3dContext);
}

void UActor::Init()
{
    m_Unit = new Unit();
	m_Unit->mModelTM = XMMatrixScaling(3.f, 3.f, 3.f);
    m_Unit->mModelTM *= XMMatrixTranslation(0.f, 1.f, 0.f);

    m_UnitMovement = new UnitMovement(m_Unit);
    m_UnitMovement->m_Target = Vector3(5.f, 0.f, 5.f);

    InitAI();
}

void UActor::Release()
{
	SAFE_DELETE(m_Unit);
	SAFE_DELETE(m_UnitMovement);
}

void UActor::InitAI()
{
    m_AI = new BTSequence(nullptr);

    UnitMoveBehavior* xz1 = new UnitMoveBehavior(m_AI);
    xz1->Init(m_Unit, Vector3(5.f, 0.f, 5.f));
    UnitMoveBehavior* xz2 = new UnitMoveBehavior(m_AI);
    xz2->Init(m_Unit, Vector3(5.f, 0.f, -5.f));
    UnitMoveBehavior* xz3 = new UnitMoveBehavior(m_AI);
    xz3->Init(m_Unit, Vector3(-5.f, 0.f, -5.f));
    UnitMoveBehavior* xz4 = new UnitMoveBehavior(m_AI);
    xz4->Init(m_Unit, Vector3(-5.f, 0.f, 5.f));

}

void UActor::Update(float fElapsedTime)
{
    if (m_AI) 
        m_AI->tick();
    //if (m_UnitMovement) m_UnitMovement->Update(fElapsedTime);
    if (m_Unit) m_Unit->Update(fElapsedTime);
}

void UActor::Render(ID3D11DeviceContext* pd3dContext)
{
	if (m_Unit) m_Unit->Render(pd3dContext);
}
