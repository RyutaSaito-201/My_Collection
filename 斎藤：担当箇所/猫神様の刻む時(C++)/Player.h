#ifndef __PLAYER_H__
#define __PLAYER_H__

// ==�C���N���[�h��==
#include "Time.h"
#include "DirectXMath.h"
#include "Geometory.h"
#include "Model.h"
#include "Shader.h"
#include "CameraDebug.h"
#include "LibEffekseer.h"
#include "ShaderList.h"

// ==�N���X==
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Update(float tick);
	void Draw();

	int GetDirection();	// �v���C���[�̌������Z�b�g

	void SetPos(DirectX::XMFLOAT3 playerpos);
	void SetCenter(DirectX::XMFLOAT3 playercenter);

	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetOldPos();
	DirectX::XMFLOAT3 GetCenter();
	DirectX::XMFLOAT3 GetSize();
	DirectX::XMFLOAT3 GetOldCenter();

	void DeathTick();

	void PunchTick(float tick);

	float GetPlayerflame(int Select);

	void PlayerDown();			// �v���C���[���|�ꂽ�����Ɉړ�������

	void AnimReset();			// �A�j���[�V�����̍Đ��E�I�����Ǘ�����֐�

	bool IsPlayAnimation();		// �A�j���[�V�������Đ������m�F����p�ϐ�

private:
	CTime* m_pTime;
	Model* m_pModel[2][3];
	VertexShader* m_pVS;
	CameraBase* m_pCamera;
	Model::AnimeNo Punchanime;
	Model::AnimeNo Moveanime;

	int m_nDirection;				// �v���C���[�̌����Ă������

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_OldPos;
	DirectX::XMFLOAT3 m_Center;
	DirectX::XMFLOAT3 m_Size;
	DirectX::XMFLOAT3 m_OldCenter;
	DirectX::XMFLOAT3 m_rad;
	DirectX::XMFLOAT3 m_CollSize;	// �����蔻��p�̃T�C�Y
	DirectX::XMFLOAT3 m_CameraPos;
	DirectX::XMFLOAT3 m_CameraLook;

	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;

	int m_nCnt = 0;
	bool m_bStartMove;				//�Q�[���J�n����
	bool m_bPlayerDownFinished;		//�v���C���[���|�ꂽ�ۂ̈ړ����I�������
	bool m_bNotStop;				// �X�e�[�W�J�n����̎��~�߂��ł��Ȃ��悤�ɂ���
	bool m_bAnimChange;				//�A�j���[�V�����̍����ւ�
	bool m_bPAnimFlagStart;			//�L�p���`�A�j���[�V�����J�n
	bool m_bPAnimFlagEnd;			//�L�p���`�A�j���[�V�����I��
	bool m_bDAnimFlagStart;			//�|���A�j���[�V�����J�n
	bool m_bDAnimFlagEnd;			//�|���A�j���[�V�����I��
	bool m_IsMove;					//�v���C���[�������Ă��邩

	int m_nChange;					//�A�j���[�V�����̐؂�ւ�


};

#endif