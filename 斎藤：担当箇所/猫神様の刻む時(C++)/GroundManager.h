#ifndef ___GROUND_MNG_H___
#define ___GROUND_MNG_H___

#include <DirectXMath.h>
#include "Geometory.h"
#include "Model.h"
#include "Shader.h"
#include "CameraDebug.h"

///////////////////////////////////////////////
//	void CreateGround(float ScalingX, float ScalingY, float ScalingZ, float posX, float posY, float posZ, bool isStop)
//	
//	�߂�l:�Ȃ�
//
//	��ҁF�֓�
//
//	�����F�u���b�N��C�ӂ̈ʒu�ɐ�������֐��ł��B
//	�����ɑ傫���ƈʒu�ƕϊ������l���i�[����DirectX::XMFLOAT4X4������ΔC�ӂ̈ʒu�Ƀu���b�N���o�����܂��B
//	�܂����ǒ��̂��߉�������Ε����Ă��������B
//
/////////////////////////////////////////////
class CGroundManager
{
public:
	CGroundManager();
	void CreateGround(float ScalingX, float ScalingY, float ScalingZ, 
		float posX, float posY, float posZ, bool isStop = false);
	//virtual void Update() = 0;
	void Draw(DirectX::XMFLOAT4X4 mat[3]);

	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetSize();
	void SetPos(DirectX::XMFLOAT3 pos);

protected:
	Model* m_pModel[2];
	VertexShader* m_pVS[2];
	CameraBase* m_pCamera;

	DirectX::XMFLOAT3 m_Size;
	DirectX::XMFLOAT3 m_pos;		// ���S���W
	DirectX::XMFLOAT3 m_CameraPos;
	DirectX::XMFLOAT3 m_CameraLook;
	bool m_bStop;		// ���~�ߎ��̃��f����
};

#endif
