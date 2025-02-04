#pragma once
// ===== ヘッダー・定数 =====
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
	EffectMng* m_pEffectMng[ARROW_EFFECT_MAX];		// エフェクト画像読み込み
	CameraBase* m_pCamera;							// エフェクト表示用カメラ
	bool m_bIsEffect[ARROW_EFFECT_MAX];				// フェーズごとに矢印が表示されているか判定用
	int m_nframe[ARROW_EFFECT_MAX];					// 現在の表示している画像フレームをカウント
	int m_nAnimeNo[ARROW_EFFECT_MAX];				// アニメーション切り替え用
	bool m_bIsPlay[ARROW_EFFECT_MAX];				// エフェクトが再生中かどうか判定用
	DirectX::XMFLOAT3 m_pos[3];


};