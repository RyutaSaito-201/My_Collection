#include "GroundManager.h"

CGroundManager::CGroundManager()
	: m_CameraPos(-6.0f, 3.0f, -5.0f)
	, m_CameraLook(-6.0f, 0.0f, 0.0f)
{
	// 地面
	m_pModel[0] = new Model();
	if (!m_pModel[0]->Load("Assets/Model/Ground/Ground.fbx", 1.0f, Model::XFlip))
	{
		MessageBox(NULL, "Ground", "Error", MB_OK);
	}
	m_pVS[0] = new VertexShader();
	if (FAILED(m_pVS[0]->Load("Assets/Shader/VS_Model.cso"))) 
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel[0]->SetVertexShader(m_pVS[0]);	//モデルへ読み込んだ頂点シェーダーを設定

	// 地面(時止め)
	m_pModel[1] = new Model();
	if (!m_pModel[1]->Load("Assets/Model/Ground/Ground_noarl.fbx", 1.0f, Model::XFlip))
	{
		MessageBox(NULL, "Ground", "Error", MB_OK);
	}
	m_pVS[1] = new VertexShader();
	if (FAILED(m_pVS[1]->Load("Assets/Shader/VS_Model.cso")))
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel[1]->SetVertexShader(m_pVS[1]);	//モデルへ読み込んだ頂点シェーダーを設定

	m_pCamera = new CameraDebug();
}
// オブジェクト生成関数(引数 : float:大きさ(x,y,z) float:座標(x,y,z),bool:止まっているかどうか)
void CGroundManager::CreateGround(float ScalingX, float ScalingY, float ScalingZ, float posX, float posY, float posZ, bool isStop)
{
	m_Size.x = ScalingX;
	m_Size.y = ScalingY;
	m_Size.z = ScalingZ;
	m_pos.x = posX;
	m_pos.y = posY;
	m_pos.z = posZ;
	m_bStop = isStop;
}

void CGroundManager::Draw(DirectX::XMFLOAT4X4 mat[3])
{
	// カメラのアップデート
	m_CameraPos.x += 6.0f / 60.0f;
	m_CameraPos.y += 9.0f / 60.0f;
	m_CameraLook.x += 6.0f / 60.0f;
	m_CameraLook.y -= 0.3f / 60.0f;
	if (m_CameraLook.x <= 0.0f)
	{
		m_pCamera->SetPos(m_CameraPos.x, m_CameraPos.y, -5.0f);
		m_pCamera->Setlook(m_CameraLook.x, m_CameraLook.y, 0.0f);
	}
	DirectX::XMMATRIX world;
	//--- Geometory用の変換行列を計算
	world =
		DirectX::XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z)*
		DirectX::XMMatrixRotationX(0.0f) * DirectX::XMMatrixRotationY(0.0f) * DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	world = DirectX::XMMatrixTranspose(world);	// 転移行列に変換
	DirectX::XMStoreFloat4x4(&mat[0], world);	// XMMATRIX型からXMFLOAT4x4型(mat[0])へ変換して格納
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjyectionMatrix();

	// 行列をシェーダーへ設定
	m_pVS[0]->WriteBuffer(0, mat);
	m_pVS[1]->WriteBuffer(0, mat);

	//--- Geometory用の変換行列を設定
	Geometory::SetWorld(mat[0]);
	//Geometory::DrawBox();
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// モデル表示
	if (!m_bStop)
	{
		if (m_pModel[0]) { m_pModel[0]->Draw(); }
	}
	else
	{
		if (m_pModel[1]) { m_pModel[1]->Draw(); }
	}
}

DirectX::XMFLOAT3 CGroundManager::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CGroundManager::GetSize()
{
	return m_Size;
}

void CGroundManager::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}