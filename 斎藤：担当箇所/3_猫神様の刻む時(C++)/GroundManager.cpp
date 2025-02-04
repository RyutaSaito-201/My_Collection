#include "GroundManager.h"

CGroundManager::CGroundManager()
	: m_CameraPos(-6.0f, 3.0f, -5.0f)
	, m_CameraLook(-6.0f, 0.0f, 0.0f)
{
	// �n��
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
	m_pModel[0]->SetVertexShader(m_pVS[0]);	//���f���֓ǂݍ��񂾒��_�V�F�[�_�[��ݒ�

	// �n��(���~��)
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
	m_pModel[1]->SetVertexShader(m_pVS[1]);	//���f���֓ǂݍ��񂾒��_�V�F�[�_�[��ݒ�

	m_pCamera = new CameraDebug();
}
// �I�u�W�F�N�g�����֐�(���� : float:�傫��(x,y,z) float:���W(x,y,z),bool:�~�܂��Ă��邩�ǂ���)
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
	// �J�����̃A�b�v�f�[�g
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
	//--- Geometory�p�̕ϊ��s����v�Z
	world =
		DirectX::XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z)*
		DirectX::XMMatrixRotationX(0.0f) * DirectX::XMMatrixRotationY(0.0f) * DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	world = DirectX::XMMatrixTranspose(world);	// �]�ڍs��ɕϊ�
	DirectX::XMStoreFloat4x4(&mat[0], world);	// XMMATRIX�^����XMFLOAT4x4�^(mat[0])�֕ϊ����Ċi�[
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjyectionMatrix();

	// �s����V�F�[�_�[�֐ݒ�
	m_pVS[0]->WriteBuffer(0, mat);
	m_pVS[1]->WriteBuffer(0, mat);

	//--- Geometory�p�̕ϊ��s���ݒ�
	Geometory::SetWorld(mat[0]);
	//Geometory::DrawBox();
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// ���f���\��
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