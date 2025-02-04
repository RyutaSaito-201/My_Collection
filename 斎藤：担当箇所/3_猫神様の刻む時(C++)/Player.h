#ifndef __PLAYER_H__
#define __PLAYER_H__

// ==インクルード部==
#include "Time.h"
#include "DirectXMath.h"
#include "Geometory.h"
#include "Model.h"
#include "Shader.h"
#include "CameraDebug.h"
#include "LibEffekseer.h"
#include "ShaderList.h"

// ==クラス==
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Update(float tick);
	void Draw();

	int GetDirection();	// プレイヤーの向きをセット

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

	void PlayerDown();			// プレイヤーが倒れた方向に移動させる

	void AnimReset();			// アニメーションの再生・終了を管理する関数

	bool IsPlayAnimation();		// アニメーションが再生中か確認する用変数

private:
	CTime* m_pTime;
	Model* m_pModel[2][3];
	VertexShader* m_pVS;
	CameraBase* m_pCamera;
	Model::AnimeNo Punchanime;
	Model::AnimeNo Moveanime;

	int m_nDirection;				// プレイヤーの向いている方向

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_OldPos;
	DirectX::XMFLOAT3 m_Center;
	DirectX::XMFLOAT3 m_Size;
	DirectX::XMFLOAT3 m_OldCenter;
	DirectX::XMFLOAT3 m_rad;
	DirectX::XMFLOAT3 m_CollSize;	// 当たり判定用のサイズ
	DirectX::XMFLOAT3 m_CameraPos;
	DirectX::XMFLOAT3 m_CameraLook;

	Effekseer::EffectRef effect;
	Effekseer::Handle efkHandle;

	int m_nCnt = 0;
	bool m_bStartMove;				//ゲーム開始時か
	bool m_bPlayerDownFinished;		//プレイヤーが倒れた際の移動が終わったか
	bool m_bNotStop;				// ステージ開始直後の時止めができないようにする
	bool m_bAnimChange;				//アニメーションの差し替え
	bool m_bPAnimFlagStart;			//猫パンチアニメーション開始
	bool m_bPAnimFlagEnd;			//猫パンチアニメーション終了
	bool m_bDAnimFlagStart;			//倒れるアニメーション開始
	bool m_bDAnimFlagEnd;			//倒れるアニメーション終了
	bool m_IsMove;					//プレイヤーが動いているか

	int m_nChange;					//アニメーションの切り替え


};

#endif