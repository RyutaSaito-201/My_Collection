#pragma once
// ===== �w�b�_�[�E�萔 =====
#include "EffectMng.h"
#include "CameraDebug.h"
#include "CameraBase.h"

#define ARROW_EFFECT_MAX (36)

class ArrowEffect
{
public:
	ArrowEffect();
	~ArrowEffect();
	void Update(int Direction, int Phase, DirectX::XMFLOAT3 Pos[3], DirectX::XMFLOAT3 RockPos, bool IsEffect);
	void Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);

private:
	EffectMng* m_pEffectMng[ARROW_EFFECT_MAX];		// �G�t�F�N�g�摜�ǂݍ���
	CameraBase* m_pCamera;							// �G�t�F�N�g�\���p�J����
	bool m_bIsEffect[ARROW_EFFECT_MAX];				// �t�F�[�Y���Ƃɖ�󂪕\������Ă��邩����p
	int m_nframe[ARROW_EFFECT_MAX];					// ���݂̕\�����Ă���摜�t���[�����J�E���g
	int m_nAnimeNo[ARROW_EFFECT_MAX];				// �A�j���[�V�����؂�ւ��p
	bool m_bIsPlay[ARROW_EFFECT_MAX];				// �G�t�F�N�g���Đ������ǂ�������p
	DirectX::XMFLOAT3 m_pos[3];


};