// ==インクルード部==
#include "Player.h"
#include "Geometory.h"
#include "Input.h"
#include <Xinput.h>

// ==グローバル変数==
XINPUT_STATE state;

// ==定数定義==
#define PLAYER_MOVE (0.08f)	// 移動速度
#define EFFEKSEER_UPDATE (20)	
#define PLAYER_SIZE (0.065f)	// プレイヤーサイズ
#define SHADOW_SIZE (0.8f)		// 影の大きさ
#define SHADOW_X_SIZE (0.3f)	// 影のX方向の大きさ(Load関数のオーバーロード部分で使用

CPlayer::CPlayer()
// メンバイニシャライザ
	: m_nDirection(2)
	, m_pos(0.0f, 0.0f, 0.0f)		 //プレイヤーの現在座標
	, m_OldPos(-6.0f, 0.0f, 0.0f)    //プレイヤーの過去座標
	, m_Center(m_pos.x, 0.0f, m_pos.z)    //プレイヤーの中心座標を設定(x,zはプレイヤーの座標と同じ)
	, m_Size(0.5f, 1.0f, 0.5f)       //ここでプレイヤーの当たり判定のサイズを変更
	, m_OldCenter(m_OldPos.x, 0.0f, m_OldPos.z)    //プレイヤーの過去中心座標
	, m_rad(0.0f, 0.0f, 0.0f)	// 回転角度
	, m_CollSize(m_Size.x, m_Size.y, m_Size.z)
	, m_CameraPos(-6.0f, 3.0f, -5.0f)
	, m_CameraLook(-6.0f, 0.0f, 0.0f)
	, m_bStartMove(true)	//ゲーム開始時
	, m_bPlayerDownFinished(false) //プレイヤーが倒れた時の移動が終わったか
	, m_bNotStop(false)
	, m_bAnimChange(false)
	, m_bPAnimFlagStart(false)
	, m_bPAnimFlagEnd(false)
	, m_bDAnimFlagStart(false)
	, m_bDAnimFlagEnd(false)
	, Punchanime(NULL)
	, m_IsMove(false)	//プレイヤーが動いているか
	, m_nChange(2)		//デフォが歩きモーション
{
	DWORD dwResult;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// 接続されているかを変数に格納
	dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// コントローラーが接続されている
	}
	else
	{
		//// コントローラーが接続されていない
		//MessageBox(NULL, "Not Connect", "Controller", MB_OK);
	}

	for (int j = 0; j < 3; j++) {
		// モデル初期化
		m_pModel[0][j] = new Model();	//j = 0 倒れるモーション, 1 猫パンチモーション
		m_pModel[1][0] = new Model();
		if (!m_pModel[0][j]->Load("Assets/Model/Player/NewRigCat001.fbx", PLAYER_SIZE, Model::XFlip))
		{
			MessageBox(NULL, "Rock", "Error", MB_OK);
		}

		if (!m_pModel[1][0]->Load("Assets/Model/Player/shadow.fbx", SHADOW_SIZE, Model::XFlip, SHADOW_X_SIZE))
		{
			MessageBox(NULL, "Rock", "Error", MB_OK);
		}

		// 頂点シェーダーを読み込んでモデルに設定
		m_pVS = new VertexShader();
		if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))
		{
			MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
		}
		//モデルへ読み込んだ頂点シェーダーを設定
		m_pModel[0][j]->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));	
		m_pModel[1][0]->SetVertexShader(m_pVS);						
	}
	//　モーション読み込み
	Model::AnimeNo Deathanime = m_pModel[0][0]->AddAnimation("Assets/Model/Player/NewRigCatDeath001.fbx"); 
	Punchanime = m_pModel[0][1]->AddAnimation("Assets/Model/Player/NewRigCat_punch001.fbx");
	Moveanime = m_pModel[0][2]->AddAnimation("Assets/Model/Player/NewRigCat_move003.fbx"); 
	m_pModel[0][0]->Play(Deathanime, false);	//倒れるモーション
	m_pModel[0][1]->Play(Punchanime, false);	//猫パンチモーション
	m_pModel[0][2]->Play(Moveanime, true);		//歩きモーション
	m_pCamera = new CameraDebug();

	// 作成
	m_pTime = new CTime;

	effect = LibEffekseer::Create("Assets/Effect/Smoke1/Smoke1.efkefc");// 砂埃エフェクト読み込み
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update(float tick)
{
	XInputGetState(0, &state);

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
	else
	{
		m_bNotStop = true;
	}

	//現在のプレイヤー座標を退避
	m_OldPos.x = m_pos.x;
	m_OldPos.y = m_pos.y;
	m_OldPos.z = m_pos.z;

	m_OldCenter.x = m_pos.x;
	m_OldCenter.z = m_pos.z;

	if (m_bNotStop)		//敵が出現してから時止めをできるようにしている
	{
		// プレイヤーの移動(アナログパッド)
		if (state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	// 上
		{
			m_pos.z += PLAYER_MOVE;
			m_Center.z = m_pos.z;
			m_nDirection = 1;
			m_rad.y = 3.14f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x, m_pos.y, m_pos.z - 1.0f },
					{ 0.0f, 0.0f, 0.0f }, { 0.5f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	// 下
		{
			m_pos.z -= PLAYER_MOVE;
			m_Center.z = m_pos.z;
			m_nDirection = 2;
			m_rad.y = 0.0f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x, m_pos.y, m_pos.z + 1.0f },
					{ 0.0f, 180.0f, 0.0f }, { 0.5f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	// 右
		{
			m_pos.x += PLAYER_MOVE;
			m_Center.x = m_pos.x;
			m_nDirection = 3;
			m_rad.y = -1.57f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x - 1.0f, m_pos.y, m_pos.z },
					{ 0.0f, 90.0f, 0.0f }, { 1.0f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	// 左
		{
			m_pos.x -= PLAYER_MOVE;
			m_Center.x = m_pos.x;
			m_nDirection = 4;
			m_rad.y = 1.57f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x + 1.0f, m_pos.y, m_pos.z },
					{ 0.0f, -90.0f, 0.0f }, { 1.0f,1.0f,1.0f });
			}
		}

		// プレイヤーの移動(十字ボタン)
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP || IsKeyPress('W'))
		{
			m_pos.z += PLAYER_MOVE;
			m_Center.z = m_pos.z;
			m_nDirection = 1;
			m_rad.y = 3.14f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x, m_pos.y, m_pos.z - 1.0f },
					{ 0.0f, 0.0f, 0.0f }, { 0.5f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN || IsKeyPress('S'))
		{
			m_pos.z -= PLAYER_MOVE;
			m_Center.z = m_pos.z;
			m_nDirection = 2;
			m_rad.y = 0.0f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x, m_pos.y, m_pos.z + 1.0f },
					{ 0.0f, 180.0f, 0.0f }, { 0.5f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT || IsKeyPress('D'))
		{
			m_pos.x += PLAYER_MOVE;
			m_Center.x = m_pos.x;
			m_nDirection = 3;
			m_rad.y = -1.57f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x - 1.0f, m_pos.y, m_pos.z },
					{ 0.0f, 90.0f, 0.0f }, { 1.0f,1.0f,1.0f });
			}
		}
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT || IsKeyPress('A'))
		{
			m_pos.x -= PLAYER_MOVE;
			m_Center.x = m_pos.x;
			m_nDirection = 4;
			m_rad.y = 1.57f;
			m_IsMove = true;
			if (m_nCnt > EFFEKSEER_UPDATE)
			{
				m_nCnt = 0;
				efkHandle = LibEffekseer::GetManager()->Play(effect, 0, 0, 0);
				//Effekseerの行列変換(pos,rotate,scale)
				LibEffekseer::TransformEffekseer(efkHandle, { m_pos.x + 1.0f, m_pos.y, m_pos.z },
					{ 0.0f, -90.0f, 0.0f }, { 1.0f,1.0f,1.0f });
			}
		}
	}
	m_nCnt++;//砂埃描画間隔の調整用
	//一度だけアニメーションを再生する
	if (m_bStartMove)
	{
		for (int j = 0; j < 3; j++)
		{
			m_pModel[0][j]->Step(tick);
		}
		m_bStartMove = false;
	}

	//プレイヤーが動いていたらアニメーションを再生する
	if (m_IsMove)
	{
		m_pModel[0][2]->Step(tick);
	}
	m_IsMove = false;
}

void CPlayer::Draw()
{
	//	int tmp;
	DirectX::XMFLOAT4X4 mat[3];
	//--- Geometory用の変換行列を計算
	DirectX::XMMATRIX world =
		DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f)*
		DirectX::XMMatrixRotationX(m_rad.x) * DirectX::XMMatrixRotationY(m_rad.y) * DirectX::XMMatrixRotationZ(m_rad.z) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 1.0f, m_pos.z);
	world = DirectX::XMMatrixTranspose(world);	// 転移行列に変換
	DirectX::XMStoreFloat4x4(&mat[0], world);	// XMMATRIX型からXMFLOAT4x4型(mat[0])へ変換して格納
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjyectionMatrix();

	// 行列をシェーダーへ設定
	m_pVS->WriteBuffer(0, mat);

	//--- Geometory用の変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	//影モデル表示
	m_pModel[1][0]->Draw();


	if (m_pModel[0])
	{
		// モデル,アニメーション表示
		ShaderList::SetWVP(&mat[0]);

		int tmp = 2;	//歩きモーション
		//アニメーションの切り替え
		switch (m_nChange)
		{
		case 0:
			tmp = 0;	//倒れるモーション
			break;
		case 1:
			tmp = 1;   //猫パンチアニメーション
			break;
		case 2:
			tmp = 2;   //歩きモーション
			break;
		default:
			break;
		}

		m_pModel[0][tmp]->Draw(nullptr, [this, tmp](int index)
		{
			const Model::Mesh* pMesh = m_pModel[0][tmp]->GetMesh(index);
			const Model::Material* pMaterial = m_pModel[0][tmp]->GetMaterial(pMesh->materialID);
			ShaderList::SetMaterial(*pMaterial);

			DirectX::XMFLOAT4X4 bones[200];
			for (int i = 0; i < pMesh->bones.size() && i < 200; ++i)
			{
				// この計算はゲームつくろー「スキンメッシュの仕組み」が参考になる
				DirectX::XMStoreFloat4x4(&bones[i], DirectX::XMMatrixTranspose(
					pMesh->bones[i].invOffset *
					m_pModel[0][tmp]->GetBone(pMesh->bones[i].index)
				));
			}
			ShaderList::SetBones(bones);
		});
	}

	//転置されていないview,projを取得する
	DirectX::XMFLOAT4X4 efkMat[2];
	efkMat[0] = m_pCamera->GetViewMatrix();
	efkMat[1] = m_pCamera->GetProjyectionMatrix();
	//カメラの行列はGPUに渡す際に転置されているため、逆行列の計算のために一度元に戻す
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&efkMat[0]);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&efkMat[1]);
	view = DirectX::XMMatrixTranspose(view);
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&efkMat[0], view);
	DirectX::XMStoreFloat4x4(&efkMat[1], proj);
	LibEffekseer::SetViewPosition({ 0.0f,0.0f,0.0f });
	LibEffekseer::SetCameraMatrix(efkMat[0], efkMat[1]);
}

int CPlayer::GetDirection()
{
	return m_nDirection;
}

void CPlayer::SetPos(DirectX::XMFLOAT3 playerpos)
{
	m_pos = playerpos;
}

void CPlayer::SetCenter(DirectX::XMFLOAT3 playercenter)
{
	m_Center = playercenter;
}

DirectX::XMFLOAT3 CPlayer::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CPlayer::GetOldPos()
{
	return m_OldPos;
}

DirectX::XMFLOAT3 CPlayer::GetCenter()
{
	return m_Center;
}

DirectX::XMFLOAT3 CPlayer::GetSize()
{
	m_CollSize = m_Size;
	if (m_nDirection == 1 || m_nDirection == 2)	// 上下方向を向いているか
	{
		m_CollSize.z = m_Size.z * 2.5f;
	}
	else										// 左右方向を向いている
	{
		m_CollSize.x = m_Size.x * 2.5f;
	}
	return m_CollSize;
}

DirectX::XMFLOAT3 CPlayer::GetOldCenter()
{
	return m_OldCenter;
}

float CPlayer::GetPlayerflame(int Select)
{
	for (int i = 0; i < 2; i++)
	{
		switch (Select)
		{
		case 1:
			return m_pModel[i][0]->GetToalTime(0);//合計時間を取得
			break;
		case 2:
			return m_pModel[i][0]->GetnowTime(0);	//現在時間を取得
			break;
		default:
			break;
		}
	}
}

void CPlayer::DeathTick()
{
	if (!m_bAnimChange)
	{
		m_nChange = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		m_pModel[i][0]->Step(0.05);
	}
}

void CPlayer::PunchTick(float tick)
{
	m_nChange = 1;

	m_pModel[0][1]->Step(tick);
}

void CPlayer::PlayerDown()
{

	switch (m_nDirection)
	{
	case 1:
		m_pos.x += 0.1f;
		break;
	case 2:
		m_pos.x -= 0.1f;
		break;
	case 3:
		m_pos.z -= 0.1f;
		break;
	case 4:
		m_pos.z += 0.1f;
		break;
	default:
		break;
	}
}

void CPlayer::AnimReset()
{
	//アニメーションのリセット
	m_pModel[0][1]->SetAnimationTime(0, 0.0f);
	m_nChange = 2;
}

bool CPlayer::IsPlayAnimation()
{
	return m_pModel[0][1]->IsPlay(0);
}
