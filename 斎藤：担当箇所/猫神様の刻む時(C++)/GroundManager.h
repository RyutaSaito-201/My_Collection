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
//	戻り値:なし
//
//	作者：斎藤
//
//	説明：ブロックを任意の位置に生成する関数です。
//	引数に大きさと位置と変換した値を格納するDirectX::XMFLOAT4X4を入れれば任意の位置にブロックが出現します。
//	まだ改良中のため何かあれば聞いてください。
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
	DirectX::XMFLOAT3 m_pos;		// 中心座標
	DirectX::XMFLOAT3 m_CameraPos;
	DirectX::XMFLOAT3 m_CameraLook;
	bool m_bStop;		// 時止め時のモデルか
};

#endif
