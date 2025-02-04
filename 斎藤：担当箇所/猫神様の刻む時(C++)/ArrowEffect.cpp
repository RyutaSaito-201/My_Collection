#include "ArrowEffect.h"

ArrowEffect::ArrowEffect()
{
	// 矢印画像読み取り処理
	for (int i = 0; i < ARROW_EFFECT_MAX; i++)
	{
		switch (i % 12)
		{
		case 0:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/greenUp.png");
			break;
		case 1:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/greenDown.png");
			break;
		case 2:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/greenRight.png");
			break;
		case 3:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/greenLeft.png");
			break;
		case 4:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/yellowUp.png");
			break;
		case 5:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/yellowDown.png");
			break;
		case 6:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/yellowRight.png");
			break;
		case 7:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/yellowLeft.png");
			break;
		case 8:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/redUp.png");
			break;
		case 9:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/redDown.png");
			break;
		case 10:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/redRight.png");
			break;
		case 11:
			m_pEffectMng[i] = new EffectMng("Assets/Texture/redLeft.png");
			break;
		default:
			break;
		}
	}


	// 矢印表示用のカメラの生成
	m_pCamera = new CameraDebug();

	// カメラ座標の設定
	m_pCamera->SetUp(0.0f, 0.0f, 1.0f);

	for (int i = 0; i < ARROW_EFFECT_MAX; i++)
	{
		m_bIsEffect[i] = false;
		m_bIsPlay[i] = true;
		m_nAnimeNo[i] = 0;
		m_nframe[i] = 0;
	}

}

ArrowEffect::~ArrowEffect()
{
	for (int i = 0; i < ARROW_EFFECT_MAX; i++)
	{
		if (m_pEffectMng[i])
		{
			delete m_pEffectMng[i];
			m_pEffectMng[i] = nullptr;
		}
	}
}

void ArrowEffect::Update(int Direction, int Phase, DirectX::XMFLOAT3 Pos[5], DirectX::XMFLOAT3 RockPos, bool IsEffect)
{
	// ブロックの数分だけ
	for (int i = 0; i < ROCK_MAX_NUM; i++)
	{
		m_pos[i] = Pos[i];
	}

	// === ブロック1 ===
	if (m_pos[0].x == RockPos.x &&
		m_pos[0].z == RockPos.z)
	{
		switch (Phase)
		{
		case 1:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(0, m_bIsEffect);
				if (m_bIsEffect[0])
				{
					if (m_nframe[0] >= 10)
					{
						m_nframe[0] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[0]++;
						if (m_nAnimeNo[0] >= 30)
							m_nAnimeNo[0] = 29;
					}
					m_pEffectMng[0]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[0], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z + 1.0f }, 8);
					m_nframe[0]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(1, m_bIsEffect);
				if (m_bIsEffect[1])
				{
					if (m_nframe[1] >= 10)
					{
						m_nframe[1] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[1]++;
						if (m_nAnimeNo[1] >= 29)
						{
							m_nAnimeNo[1] = 28;
						}
					}
					m_pEffectMng[1]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[1], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[1]++;
				}
				break;
			case 3: // 右

				UpdateSelect(2, m_bIsEffect);
				if (m_bIsEffect[2])
				{
					if (m_nframe[2] >= 10)
					{
						m_nframe[2] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[2]++;
						if (m_nAnimeNo[2] >= 30)
						{
							m_nAnimeNo[2] = 29;
						}
					}
					m_pEffectMng[2]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[2], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[2]++;
				}
				break;
			case 4: // 左
				UpdateSelect(3, m_bIsEffect);
				if (m_bIsEffect[3])
				{
					if (m_nframe[3] >= 10)
					{
						m_nframe[3] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[3]++;
						if (m_nAnimeNo[3] >= 29)
						{
							m_nAnimeNo[3] = 28;
						}
					}
					m_pEffectMng[3]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[3], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[3]++;
				}
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(4, m_bIsEffect);
				if (m_bIsEffect[4])
				{
					if (m_nframe[4] >= 10)
					{
						m_nframe[4] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[4]++;
						if (m_nAnimeNo[4] >= 30)
						{
							m_nAnimeNo[4] = 29;
						}
					}
					m_pEffectMng[4]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[4], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z + 1.0f }, 8);
					m_nframe[4]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(5, m_bIsEffect);
				if (m_bIsEffect[5])
				{
					if (m_nframe[5] >= 10)
					{
						m_nframe[5] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[5]++;
						if (m_nAnimeNo[5] >= 29)
						{
							m_nAnimeNo[5] = 28;
						}
					}
					m_pEffectMng[5]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[5], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[5]++;
				}
				break;
			case 3: // 右
				UpdateSelect(6, m_bIsEffect);
				if (m_bIsEffect[6])
				{
					if (m_nframe[6] >= 10)
					{
						m_nframe[6] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[6]++;
						if (m_nAnimeNo[6] >= 30)
						{
							m_nAnimeNo[6] = 29;
						}
					}
					m_pEffectMng[6]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[6], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[6]++;
				}
				break;
			case 4: // 左
				UpdateSelect(7, m_bIsEffect);
				if (m_bIsEffect[7])
				{
					if (m_nframe[7] >= 10)
					{
						m_nframe[7] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[7]++;
						if (m_nAnimeNo[7] >= 29)
						{
							m_nAnimeNo[7] = 28;
						}
					}
					m_pEffectMng[7]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[7], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f , m_pos[0].z - 1.0f }, 8);
					m_nframe[7]++;
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(8, m_bIsEffect);
				if (m_bIsEffect[8])
				{
					if (m_nframe[8] >= 10)
					{
						m_nframe[8] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[8]++;
						if (m_nAnimeNo[8] >= 30)
						{
							m_nAnimeNo[8] = 29;
						}
					}
					m_pEffectMng[8]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[8], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z + 1.0f }, 8);
					m_nframe[8]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(9, m_bIsEffect);
				if (m_bIsEffect[9])
				{
					if (m_nframe[9] >= 10)
					{
						m_nframe[9] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[9]++;
						if (m_nAnimeNo[9] >= 29)
						{
							m_nAnimeNo[9] = 28;
						}
					}
					m_pEffectMng[9]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[9], { m_pos[0].x, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[9]++;
				}
				break;
			case 3: // 右
				UpdateSelect(10, m_bIsEffect);
				if (m_bIsEffect[10])
				{
					if (m_nframe[10] >= 10)
					{
						m_nframe[10] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[10]++;
						if (m_nAnimeNo[10] >= 29)
						{
							m_nAnimeNo[10] = 28;
						}
					}
					m_pEffectMng[10]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[10], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[10]++;
				}
				break;
			case 4: // 左
				UpdateSelect(11, m_bIsEffect);
				if (m_bIsEffect[11])
				{
					if (m_nframe[11] >= 10)
					{
						m_nframe[11] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[11]++;
						if (m_nAnimeNo[11] >= 29)
						{
							m_nAnimeNo[11] = 28;
						}
					}
					m_pEffectMng[11]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[11], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f, m_pos[0].z - 1.0f }, 8);
					m_nframe[11]++;
				}
				break;
			default:
				break;
			}

		default:
			break;
		}
	}

	// === ブロック2 ===
	if (m_pos[1].x == RockPos.x &&
		m_pos[1].z == RockPos.z)
	{
		switch (Phase)
		{
		case 1:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(12, m_bIsEffect);
				if (m_bIsEffect[12])
				{
					if (m_nframe[12] >= 10)
					{
						m_nframe[12] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[12]++;
						if (m_nAnimeNo[12] >= 30)
						{
							m_nAnimeNo[12] = 29;
						}
					}
					m_pEffectMng[12]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[12], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z + 1.0f }, 8);
					m_nframe[12]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(13, m_bIsEffect);
				if (m_bIsEffect[13])
				{
					if (m_nframe[13] >= 10)
					{
						m_nframe[13] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[13]++;
						if (m_nAnimeNo[13] >= 29)
						{
							m_nAnimeNo[13] = 28;
						}
					}
					m_pEffectMng[13]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[13], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z - 2.0f }, 8);
					m_nframe[13]++;
				}
				break;
			case 3: // 右
				UpdateSelect(14, m_bIsEffect);
				if (m_bIsEffect[14])
				{
					if (m_nframe[14] >= 10)
					{
						m_nframe[14] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[14]++;
						if (m_nAnimeNo[14] >= 30)
						{
							m_nAnimeNo[14] = 29;
						}
					}
					m_pEffectMng[14]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[14], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f, m_pos[1].z - 0.75f }, 8);
					m_nframe[14]++;
				}
				break;
			case 4: // 左
				UpdateSelect(15, m_bIsEffect);
				if (m_bIsEffect[15])
				{
					if (m_nframe[15] >= 10)
					{
						m_nframe[15] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[15]++;
						if (m_nAnimeNo[15] >= 29)
						{
							m_nAnimeNo[15] = 28;
						}
					}
					m_pEffectMng[15]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[15], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f, m_pos[1].z - 0.75f }, 8);
					m_nframe[15]++;
				}
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(16, m_bIsEffect);
				if (m_bIsEffect[16])
				{
					if (m_nframe[16] >= 10)
					{
						m_nframe[16] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[16]++;
						if (m_nAnimeNo[16] >= 30)
						{
							m_nAnimeNo[16] = 29;
						}
					}
					m_pEffectMng[16]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[16], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z + 1.0f }, 8);
					m_nframe[16]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(17, m_bIsEffect);

				if (m_bIsEffect[17])
				{
					if (m_nframe[17] >= 10)
					{
						m_nframe[17] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[17]++;
						if (m_nAnimeNo[17] >= 29)
						{
							m_nAnimeNo[17] = 28;
						}
					}
					m_pEffectMng[17]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[17], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z - 1.0f }, 8);
					m_nframe[17]++;
				}
				break;
			case 3: // 右
				UpdateSelect(18, m_bIsEffect);
				if (m_bIsEffect[18])
				{
					if (m_nframe[18] >= 10)
					{
						m_nframe[18] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[18]++;
						if (m_nAnimeNo[18] >= 30)
						{
							m_nAnimeNo[18] = 29;
						}
					}
					m_pEffectMng[18]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[18], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f, m_pos[1].z - 0.75f }, 8);
					m_nframe[18]++;
				}
				break;
			case 4: // 左
				UpdateSelect(19, m_bIsEffect);
				if (m_bIsEffect[19])
				{
					if (m_nframe[19] >= 10)
					{
						m_nframe[19] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[19]++;
						if (m_nAnimeNo[19] >= 29)
						{
							m_nAnimeNo[19] = 28;
						}
					}
					m_pEffectMng[19]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[19], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f , m_pos[1].z - 0.75f }, 8);
					m_nframe[19]++;
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(20, m_bIsEffect);
				if (m_bIsEffect[20])
				{
					if (m_nframe[20] >= 10)
					{
						m_nframe[20] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[20]++;
						if (m_nAnimeNo[20] >= 30)
						{
							m_nAnimeNo[20] = 29;
						}
					}
					m_pEffectMng[20]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[20], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z + 1.0f }, 8);
					m_nframe[20]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(21, m_bIsEffect);
				if (m_bIsEffect[21])
				{
					if (m_nframe[21] >= 10)
					{
						m_nframe[21] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[21]++;
						if (m_nAnimeNo[21] >= 29)
						{
							m_nAnimeNo[21] = 28;
						}
					}
					m_pEffectMng[21]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[21], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z - 1.0f }, 8);
					m_nframe[21]++;
				}
				break;
			case 3: // 右
				UpdateSelect(22, m_bIsEffect);
				if (m_bIsEffect[22])
				{
					if (m_nframe[22] >= 10)
					{
						m_nframe[22] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[22]++;
						if (m_nAnimeNo[22] >= 30)
						{
							m_nAnimeNo[22] = 29;
						}
					}
					m_pEffectMng[22]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[22], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f, m_pos[1].z - 0.75f }, 8);
					m_nframe[22]++;
				}
				break;
			case 4: // 左
				UpdateSelect(23, m_bIsEffect);
				if (m_bIsEffect[23])
				{
					if (m_nframe[23] >= 10)
					{
						m_nframe[23] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[23]++;
						if (m_nAnimeNo[23] >= 29)
						{
							m_nAnimeNo[23] = 28;
						}
					}
					m_pEffectMng[23]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[23], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f, m_pos[1].z - 0.75f }, 8);
					m_nframe[23]++;
				}
				break;
			default:
				break;
			}

		default:
			break;
		}
	}

	// === ブロック3 ===
	if (m_pos[2].x == RockPos.x &&
		m_pos[2].z == RockPos.z)
	{
		switch (Phase)
		{
		case 1:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(24, m_bIsEffect);
				if (m_bIsEffect[24])
				{
					if (m_nframe[24] >= 10)
					{
						m_nframe[24] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[24]++;
						if (m_nAnimeNo[24] >= 30)
						{
							m_nAnimeNo[24] = 29;
						}
					}
					m_pEffectMng[24]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[24], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z + 1.0f }, 8);
					m_nframe[24]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(25, m_bIsEffect);
				if (m_bIsEffect[25])
				{
					if (m_nframe[25] >= 10)
					{
						m_nframe[25] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[25]++;
						if (m_nAnimeNo[25] >= 29)
						{
							m_nAnimeNo[25] = 28;

						}
					}
					m_pEffectMng[25]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[25], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z - 1.0f }, 8);
					m_nframe[25]++;
				}
				break;
			case 3: // 右
				UpdateSelect(26, m_bIsEffect);
				if (m_bIsEffect[26])
				{
					if (m_nframe[26] >= 10)
					{
						m_nframe[26] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[26]++;
						if (m_nAnimeNo[26] >= 29)
						{
							m_nAnimeNo[26] = 28;
						}
					}
					m_pEffectMng[26]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[26], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f, m_pos[2].z - 0.5f }, 8);
					m_nframe[26]++;
				}
				break;
			case 4: // 左
				UpdateSelect(27, m_bIsEffect);
				if (m_bIsEffect[27])
				{
					if (m_nframe[27] >= 10)
					{
						m_nframe[27] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[27]++;
						if (m_nAnimeNo[27] >= 29)
						{
							m_nAnimeNo[27] = 28;
						}
					}
					m_pEffectMng[27]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[27], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f, m_pos[2].z - 0.5f }, 8);
					m_nframe[27]++;
				}
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(28, m_bIsEffect);
				if (m_bIsEffect[28])
				{
					if (m_nframe[28] >= 10)
					{
						m_nframe[28] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[28]++;
						if (m_nAnimeNo[28] >= 30)
						{
							m_nAnimeNo[28] = 29;
						}
					}
					m_pEffectMng[28]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[28], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z + 1.0f }, 8);
					m_nframe[28]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(29, m_bIsEffect);
				if (m_bIsEffect[29])
				{
					if (m_nframe[29] >= 10)
					{
						m_nframe[29] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[29]++;
						if (m_nAnimeNo[29] >= 29)
						{
							m_nAnimeNo[29] = 28;
						}
					}
					m_pEffectMng[29]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[29], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z - 1.0f }, 8);
					m_nframe[29]++;
				}
				break;
			case 3: // 右
				UpdateSelect(30, m_bIsEffect);
				if (m_bIsEffect[30])
				{
					if (m_nframe[30] >= 10)
					{
						m_nframe[30] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[30]++;
						if (m_nAnimeNo[30] >= 30)
						{
							m_nAnimeNo[30] = 29;
						}
					}
					m_pEffectMng[30]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[30], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f, m_pos[2].z - 0.5f }, 8);
					m_nframe[30]++;
				}
				break;
			case 4: // 左
				UpdateSelect(31, m_bIsEffect);
				if (m_bIsEffect[31])
				{
					if (m_nframe[31] >= 10)
					{
						m_nframe[31] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[31]++;
						if (m_nAnimeNo[31] >= 29)
						{
							m_nAnimeNo[31] = 28;
						}
					}
					m_pEffectMng[31]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[31], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f , m_pos[2].z - 0.5f }, 8);
					m_nframe[31]++;
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(32, m_bIsEffect);
				if (m_bIsEffect[32])
				{
					if (m_nframe[32] >= 10)
					{
						m_nframe[32] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[32]++;
						if (m_nAnimeNo[32] >= 30)
						{
							m_nAnimeNo[32] = 29;
						}
					}
					m_pEffectMng[32]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[32], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z + 1.0f }, 8);
					m_nframe[32]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(33, m_bIsEffect);
				if (m_bIsEffect[33])
				{
					if (m_nframe[33] >= 10)
					{
						m_nframe[33] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[33]++;
						if (m_nAnimeNo[33] >= 29)
						{
							m_nAnimeNo[33] = 28;
						}
					}
					m_pEffectMng[33]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[33], { m_pos[2].x, m_pos[2].y + 2.0f, m_pos[2].z - 1.0f }, 8);
					m_nframe[33]++;
				}
				break;
			case 3: // 右
				UpdateSelect(34, m_bIsEffect);
				if (m_bIsEffect[34])
				{
					if (m_nframe[34] >= 10)
					{
						m_nframe[34] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[34]++;
						if (m_nAnimeNo[34] >= 30)
						{
							m_nAnimeNo[34] = 29;
						}
					}
					m_pEffectMng[34]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[34], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f, m_pos[2].z - 0.5f }, 8);
					m_nframe[34]++;
				}
				break;
			case 4: // 左
				UpdateSelect(35, m_bIsEffect);
				if (m_bIsEffect[35])
				{
					if (m_nframe[35] >= 10)
					{
						m_nframe[35] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[35]++;
						if (m_nAnimeNo[35] >= 29)
						{
							m_nAnimeNo[35] = 28;
						}
					}
					m_pEffectMng[35]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[35], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f, m_pos[2].z - 0.5f }, 8);
					m_nframe[35]++;
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	// === ブロック3 ===
	if (m_pos[3].x == RockPos.x &&
		m_pos[3].z == RockPos.z)
	{
		switch (Phase)
		{
		case 1:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(36, m_bIsEffect);
				if (m_bIsEffect[36])
				{
					if (m_nframe[36] >= 10)
					{
						m_nframe[36] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[36]++;
						if (m_nAnimeNo[36] >= 30)
						{
							m_nAnimeNo[36] = 29;
						}
					}
					m_pEffectMng[36]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[36], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z + 1.0f }, 8);
					m_nframe[36]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(37, m_bIsEffect);
				if (m_bIsEffect[37])
				{
					if (m_nframe[37] >= 10)
					{
						m_nframe[37] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[37]++;
						if (m_nAnimeNo[37] >= 29)
						{
							m_nAnimeNo[37] = 28;

						}
					}
					m_pEffectMng[37]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[37], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z - 1.0f }, 8);
					m_nframe[37]++;
				}
				break;
			case 3: // 右
				UpdateSelect(38, m_bIsEffect);
				if (m_bIsEffect[38])
				{
					if (m_nframe[38] >= 10)
					{
						m_nframe[38] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[38]++;
						if (m_nAnimeNo[38] >= 29)
						{
							m_nAnimeNo[38] = 28;
						}
					}
					m_pEffectMng[38]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[38], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f, m_pos[3].z - 0.5f }, 8);
					m_nframe[38]++;
				}
				break;
			case 4: // 左
				UpdateSelect(39, m_bIsEffect);
				if (m_bIsEffect[39])
				{
					if (m_nframe[39] >= 10)
					{
						m_nframe[39] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[39]++;
						if (m_nAnimeNo[39] >= 29)
						{
							m_nAnimeNo[39] = 28;
						}
					}
					m_pEffectMng[39]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[39], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f, m_pos[3].z - 0.5f }, 8);
					m_nframe[39]++;
				}
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(40, m_bIsEffect);
				if (m_bIsEffect[40])
				{
					if (m_nframe[40] >= 10)
					{
						m_nframe[40] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[40]++;
						if (m_nAnimeNo[40] >= 30)
						{
							m_nAnimeNo[40] = 29;
						}
					}
					m_pEffectMng[40]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[40], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z + 1.0f }, 8);
					m_nframe[40]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(41, m_bIsEffect);
				if (m_bIsEffect[41])
				{
					if (m_nframe[41] >= 10)
					{
						m_nframe[41] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[41]++;
						if (m_nAnimeNo[41] >= 29)
						{
							m_nAnimeNo[41] = 28;
						}
					}
					m_pEffectMng[41]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[41], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z - 1.0f }, 8);
					m_nframe[41]++;
				}
				break;
			case 3: // 右
				UpdateSelect(42, m_bIsEffect);
				if (m_bIsEffect[42])
				{
					if (m_nframe[42] >= 10)
					{
						m_nframe[42] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[42]++;
						if (m_nAnimeNo[42] >= 30)
						{
							m_nAnimeNo[42] = 29;
						}
					}
					m_pEffectMng[42]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[42], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f, m_pos[3].z - 0.5f }, 8);
					m_nframe[42]++;
				}
				break;
			case 4: // 左
				UpdateSelect(43, m_bIsEffect);
				if (m_bIsEffect[43])
				{
					if (m_nframe[43] >= 10)
					{
						m_nframe[43] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[43]++;
						if (m_nAnimeNo[43] >= 29)
						{
							m_nAnimeNo[43] = 28;
						}
					}
					m_pEffectMng[43]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[43], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f , m_pos[3].z - 0.5f }, 8);
					m_nframe[43]++;
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(44, m_bIsEffect);
				if (m_bIsEffect[44])
				{
					if (m_nframe[44] >= 10)
					{
						m_nframe[44] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[44]++;
						if (m_nAnimeNo[44] >= 30)
						{
							m_nAnimeNo[44] = 29;
						}
					}
					m_pEffectMng[44]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[44], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z + 1.0f }, 8);
					m_nframe[44]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(45, m_bIsEffect);
				if (m_bIsEffect[45])
				{
					if (m_nframe[45] >= 10)
					{
						m_nframe[45] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[45]++;
						if (m_nAnimeNo[45] >= 29)
						{
							m_nAnimeNo[45] = 28;
						}
					}
					m_pEffectMng[45]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[45], { m_pos[3].x, m_pos[3].y + 2.0f, m_pos[3].z - 1.0f }, 8);
					m_nframe[45]++;
				}
				break;
			case 3: // 右
				UpdateSelect(46, m_bIsEffect);
				if (m_bIsEffect[46])
				{
					if (m_nframe[46] >= 10)
					{
						m_nframe[46] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[46]++;
						if (m_nAnimeNo[46] >= 30)
						{
							m_nAnimeNo[46] = 29;
						}
					}
					m_pEffectMng[46]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[46], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f, m_pos[3].z - 0.5f }, 8);
					m_nframe[46]++;
				}
				break;
			case 4: // 左
				UpdateSelect(47, m_bIsEffect);
				if (m_bIsEffect[47])
				{
					if (m_nframe[47] >= 10)
					{
						m_nframe[47] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[47]++;
						if (m_nAnimeNo[47] >= 29)
						{
							m_nAnimeNo[47] = 28;
						}
					}
					m_pEffectMng[47]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[47], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f, m_pos[3].z - 0.5f }, 8);
					m_nframe[47]++;
				}
				break;
			default:
				break;
			}

		default:
			break;
		}
	}

	// === ブロック4 ===
	if (m_pos[4].x == RockPos.x &&
		m_pos[4].z == RockPos.z)
	{
		switch (Phase)
		{
		case 1:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(48, m_bIsEffect);
				if (m_bIsEffect[48])
				{
					if (m_nframe[48] >= 10)
					{
						m_nframe[48] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[48]++;
						if (m_nAnimeNo[48] >= 30)
						{
							m_nAnimeNo[48] = 29;
						}
					}
					m_pEffectMng[48]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[48], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z + 1.0f }, 8);
					m_nframe[48]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(49, m_bIsEffect);
				if (m_bIsEffect[49])
				{
					if (m_nframe[49] >= 10)
					{
						m_nframe[49] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[49]++;
						if (m_nAnimeNo[49] >= 29)
						{
							m_nAnimeNo[49] = 28;

						}
					}
					m_pEffectMng[49]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[49], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z - 1.0f }, 8);
					m_nframe[49]++;
				}
				break;
			case 3: // 右
				UpdateSelect(50, m_bIsEffect);
				if (m_bIsEffect[50])
				{
					if (m_nframe[50] >= 10)
					{
						m_nframe[50] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[50]++;
						if (m_nAnimeNo[50] >= 29)
						{
							m_nAnimeNo[50] = 28;
						}
					}
					m_pEffectMng[50]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[50], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f, m_pos[4].z - 0.5f }, 8);
					m_nframe[50]++;
				}
				break;
			case 4: // 左
				UpdateSelect(51, m_bIsEffect);
				if (m_bIsEffect[51])
				{
					if (m_nframe[51] >= 10)
					{
						m_nframe[51] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[51]++;
						if (m_nAnimeNo[51] >= 29)
						{
							m_nAnimeNo[51] = 28;
						}
					}
					m_pEffectMng[51]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[51], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f, m_pos[4].z - 0.5f }, 8);
					m_nframe[51]++;
				}
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(52, m_bIsEffect);
				if (m_bIsEffect[52])
				{
					if (m_nframe[52] >= 10)
					{
						m_nframe[52] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[52]++;
						if (m_nAnimeNo[52] >= 30)
						{
							m_nAnimeNo[52] = 29;
						}
					}
					m_pEffectMng[52]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[52], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z + 1.0f }, 8);
					m_nframe[52]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(53, m_bIsEffect);
				if (m_bIsEffect[53])
				{
					if (m_nframe[53] >= 10)
					{
						m_nframe[53] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[53]++;
						if (m_nAnimeNo[53] >= 29)
						{
							m_nAnimeNo[53] = 28;
						}
					}
					m_pEffectMng[53]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[53], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z - 1.0f }, 8);
					m_nframe[53]++;
				}
				break;
			case 3: // 右
				UpdateSelect(54, m_bIsEffect);
				if (m_bIsEffect[54])
				{
					if (m_nframe[54] >= 10)
					{
						m_nframe[54] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[54]++;
						if (m_nAnimeNo[54] >= 30)
						{
							m_nAnimeNo[54] = 29;
						}
					}
					m_pEffectMng[54]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[54], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f, m_pos[4].z - 0.5f }, 8);
					m_nframe[54]++;
				}
				break;
			case 4: // 左
				UpdateSelect(55, m_bIsEffect);
				if (m_bIsEffect[55])
				{
					if (m_nframe[55] >= 10)
					{
						m_nframe[55] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[55]++;
						if (m_nAnimeNo[55] >= 29)
						{
							m_nAnimeNo[55] = 28;
						}
					}
					m_pEffectMng[55]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[55], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f , m_pos[4].z - 0.5f }, 8);
					m_nframe[55]++;
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (Direction)
			{
			case 1:	// 上
				UpdateSelect(56, m_bIsEffect);
				if (m_bIsEffect[56])
				{
					if (m_nframe[56] >= 10)
					{
						m_nframe[56] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[56]++;
						if (m_nAnimeNo[56] >= 30)
						{
							m_nAnimeNo[56] = 29;
						}
					}
					m_pEffectMng[56]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[56], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z + 1.0f }, 8);
					m_nframe[56]++;
				}
				break;
			case 2:	// 下
				UpdateSelect(57, m_bIsEffect);
				if (m_bIsEffect[57])
				{
					if (m_nframe[57] >= 10)
					{
						m_nframe[57] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[57]++;
						if (m_nAnimeNo[57] >= 29)
						{
							m_nAnimeNo[57] = 28;
						}
					}
					m_pEffectMng[57]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[57], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z - 1.0f }, 8);
					m_nframe[57]++;
				}
				break;
			case 3: // 右
				UpdateSelect(58, m_bIsEffect);
				if (m_bIsEffect[58])
				{
					if (m_nframe[58] >= 10)
					{
						m_nframe[58] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[58]++;
						if (m_nAnimeNo[58] >= 30)
						{
							m_nAnimeNo[58] = 29;
						}
					}
					m_pEffectMng[58]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[58], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f, m_pos[4].z - 0.5f }, 8);
					m_nframe[58]++;
				}
				break;
			case 4: // 左
				UpdateSelect(59, m_bIsEffect);
				if (m_bIsEffect[59])
				{
					if (m_nframe[59] >= 10)
					{
						m_nframe[59] = 0;
						//アニメのコマを切り替え
						m_nAnimeNo[59]++;
						if (m_nAnimeNo[59] >= 29)
						{
							m_nAnimeNo[59] = 28;
						}
					}
					m_pEffectMng[59]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[59], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f, m_pos[4].z - 0.5f }, 8);
					m_nframe[59]++;
				}
				break;
			default:
				break;
			}

		default:
			break;
		}
	}
}

void ArrowEffect::Draw(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	if (m_bIsEffect[0])
	{
		m_pEffectMng[0]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[0], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z + 1.0f }, 8);
		m_pEffectMng[0]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[1])
	{
		m_pEffectMng[1]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[1], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[1]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[2])
	{
		m_pEffectMng[2]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[2], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[2]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[3])
	{
		m_pEffectMng[3]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[3], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[3]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[4])
	{
		m_pEffectMng[4]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[4], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z + 1.0f }, 8);
		m_pEffectMng[4]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[5])
	{
		m_pEffectMng[5]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[5], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[5]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[6])
	{
		m_pEffectMng[6]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[6], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[6]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[7])
	{
		m_pEffectMng[7]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[7], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[7]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[8])
	{
		m_pEffectMng[8]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[8], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z + 1.0f }, 8);
		m_pEffectMng[8]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[9])
	{
		m_pEffectMng[9]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[9], { m_pos[0].x, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[9]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[10])
	{
		m_pEffectMng[10]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[10], { m_pos[0].x + 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[10]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[11])
	{
		m_pEffectMng[11]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[11], { m_pos[0].x - 2.0f, m_pos[0].y + 2.0f ,m_pos[0].z - 1.0f }, 8);
		m_pEffectMng[11]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[12])
	{
		m_pEffectMng[12]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[12], { m_pos[1].x, m_pos[1].y + 2.0f ,m_pos[1].z + 1.0f }, 8);
		m_pEffectMng[12]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[13])
	{
		m_pEffectMng[13]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[13], { m_pos[1].x, m_pos[1].y + 2.0f, m_pos[1].z - 2.0f }, 8);
		m_pEffectMng[13]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[14])
	{
		m_pEffectMng[14]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[14], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[14]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[15])
	{
		m_pEffectMng[15]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[15], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[15]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[16])
	{
		m_pEffectMng[16]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[16], { m_pos[1].x, m_pos[1].y + 2.0f ,m_pos[1].z + 1.0f }, 8);
		m_pEffectMng[16]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[17])
	{
		m_pEffectMng[17]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[17], { m_pos[1].x , m_pos[1].y + 2.0f ,m_pos[1].z - 1.0f }, 8);
		m_pEffectMng[17]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[18])
	{
		m_pEffectMng[18]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[18], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[18]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[19])
	{
		m_pEffectMng[19]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[19], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[19]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[20])
	{
		m_pEffectMng[20]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[20], { m_pos[1].x, m_pos[1].y + 2.0f ,m_pos[1].z + 1.0f }, 8);
		m_pEffectMng[20]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[21])
	{
		m_pEffectMng[21]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[21], { m_pos[1].x, m_pos[1].y + 2.0f ,m_pos[1].z - 1.0f }, 8);
		m_pEffectMng[21]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[22])
	{
		m_pEffectMng[22]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[22], { m_pos[1].x + 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[22]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[23])
	{
		m_pEffectMng[23]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[23], { m_pos[1].x - 2.0f, m_pos[1].y + 2.0f ,m_pos[1].z - 0.75f }, 8);
		m_pEffectMng[23]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}

	if (m_bIsEffect[24])
	{
		m_pEffectMng[24]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[24], { m_pos[2].x , m_pos[2].y + 2.0f ,m_pos[2].z + 1.0f }, 8);
		m_pEffectMng[24]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[25])
	{
		m_pEffectMng[25]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[25], { m_pos[2].x, m_pos[2].y + 2.0f ,m_pos[2].z - 1.0f }, 8);
		m_pEffectMng[25]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[26])
	{
		m_pEffectMng[26]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[26], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[26]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[27])
	{
		m_pEffectMng[27]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[27], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[27]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[28])
	{
		m_pEffectMng[28]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[28], { m_pos[2].x , m_pos[2].y + 2.0f ,m_pos[2].z + 1.0f }, 8);
		m_pEffectMng[28]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[29])
	{
		m_pEffectMng[29]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[29], { m_pos[2].x, m_pos[2].y + 2.0f ,m_pos[2].z - 1.0f }, 8);
		m_pEffectMng[29]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[30])
	{
		m_pEffectMng[30]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[30], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[30]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[31])
	{
		m_pEffectMng[31]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[31], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[31]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[32])
	{
		m_pEffectMng[32]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[32], { m_pos[2].x, m_pos[2].y + 2.0f ,m_pos[2].z + 1.0f }, 8);
		m_pEffectMng[32]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[33])
	{
		m_pEffectMng[33]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[33], { m_pos[2].x, m_pos[2].y + 2.0f ,m_pos[2].z - 1.0f }, 8);
		m_pEffectMng[33]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[34])
	{
		m_pEffectMng[34]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[34], { m_pos[2].x + 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[34]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[35])
	{
		m_pEffectMng[35]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[35], { m_pos[2].x - 2.0f, m_pos[2].y + 2.0f ,m_pos[2].z - 0.5f }, 8);
		m_pEffectMng[35]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}

	if (m_bIsEffect[36])
	{
		m_pEffectMng[36]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[36], { m_pos[3].x , m_pos[3].y + 2.0f ,m_pos[3].z + 1.0f }, 8);
		m_pEffectMng[36]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[37])
	{
		m_pEffectMng[37]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[37], { m_pos[3].x, m_pos[3].y + 2.0f ,m_pos[3].z - 1.0f }, 8);
		m_pEffectMng[37]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[38])
	{
		m_pEffectMng[38]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[38], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[38]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[39])
	{
		m_pEffectMng[39]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[39], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[39]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[40])
	{
		m_pEffectMng[40]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[40], { m_pos[3].x , m_pos[3].y + 2.0f ,m_pos[3].z + 1.0f }, 8);
		m_pEffectMng[40]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[41])
	{
		m_pEffectMng[41]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[41], { m_pos[3].x, m_pos[3].y + 2.0f ,m_pos[3].z - 1.0f }, 8);
		m_pEffectMng[41]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[42])
	{
		m_pEffectMng[42]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[42], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[42]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[43])
	{
		m_pEffectMng[43]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[43], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[43]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[44])
	{
		m_pEffectMng[44]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[44], { m_pos[3].x, m_pos[3].y + 2.0f ,m_pos[3].z + 1.0f }, 8);
		m_pEffectMng[44]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[45])
	{
		m_pEffectMng[45]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[45], { m_pos[3].x, m_pos[3].y + 2.0f ,m_pos[3].z - 1.0f }, 8);
		m_pEffectMng[45]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[46])
	{
		m_pEffectMng[46]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[46], { m_pos[3].x + 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[46]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[47])
	{
		m_pEffectMng[47]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[47], { m_pos[3].x - 2.0f, m_pos[3].y + 2.0f ,m_pos[3].z - 0.5f }, 8);
		m_pEffectMng[47]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}

	if (m_bIsEffect[48])
	{
		m_pEffectMng[48]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[48], { m_pos[4].x, m_pos[4].y + 2.0f, m_pos[4].z + 1.0f }, 8);
		m_pEffectMng[48]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}

	if (m_bIsEffect[49])
	{
		m_pEffectMng[49]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[49], { m_pos[4].x, m_pos[4].y + 2.0f ,m_pos[4].z - 1.0f }, 8);
		m_pEffectMng[49]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[50])
	{
		m_pEffectMng[50]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[50], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[50]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[51])
	{
		m_pEffectMng[51]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[51], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[51]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[52])
	{
		m_pEffectMng[52]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[52], { m_pos[4].x , m_pos[4].y + 2.0f ,m_pos[4].z + 1.0f }, 8);
		m_pEffectMng[52]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[53])
	{
		m_pEffectMng[53]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[53], { m_pos[4].x, m_pos[4].y + 2.0f ,m_pos[4].z - 1.0f }, 8);
		m_pEffectMng[53]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[54])
	{
		m_pEffectMng[54]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[54], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[54]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[55])
	{
		m_pEffectMng[55]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[55], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[55]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[56])
	{
		m_pEffectMng[56]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[56], { m_pos[4].x, m_pos[4].y + 2.0f ,m_pos[4].z + 1.0f }, 8);
		m_pEffectMng[56]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[57])
	{
		m_pEffectMng[57]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[57], { m_pos[4].x, m_pos[4].y + 2.0f ,m_pos[4].z - 1.0f }, 8);
		m_pEffectMng[57]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[58])
	{
		m_pEffectMng[58]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[58], { m_pos[4].x + 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[58]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
	if (m_bIsEffect[59])
	{
		m_pEffectMng[59]->Update({ 8.0f, 4.0f }, { 8.0f, 4.0f }, m_nAnimeNo[59], { m_pos[4].x - 2.0f, m_pos[4].y + 2.0f ,m_pos[4].z - 0.5f }, 8);
		m_pEffectMng[59]->Draw(view, proj, -90.0f, { 2.0f, 2.0f });
	}
}

// どの矢印を表示するかを判定する関数
void ArrowEffect::UpdateSelect(int EffectNo, bool IsEffect)
{
	switch (EffectNo % 4)
	{
	case 1:
		// 現在のフェーズで他の方向の矢印が出ていないか
		if (m_bIsEffect[EffectNo - 1] || m_bIsEffect[EffectNo + 1] || m_bIsEffect[EffectNo + 2])
		{
			m_bIsEffect[EffectNo - 1] = false;
			m_bIsPlay[EffectNo - 1] = true;
			m_nAnimeNo[EffectNo - 1] = 0;

			for (int i = EffectNo + 1; i < EffectNo + 3; ++i)
			{
				m_bIsEffect[i] = false;
				m_bIsPlay[i] = true;
				m_nAnimeNo[i] = 0;
			}
		}

		if (m_bIsPlay[EffectNo])
		{
			m_bIsPlay[EffectNo] = false;
			m_bIsEffect[EffectNo] = IsEffect;
		}
		break;
	case 2:
		// 現在のフェーズで他の方向の矢印が出ていないか
		if (m_bIsEffect[EffectNo - 2] || m_bIsEffect[EffectNo - 1] || m_bIsEffect[EffectNo + 1])
		{
			m_bIsEffect[EffectNo + 1] = false;
			m_bIsPlay[EffectNo + 1] = true;
			m_nAnimeNo[EffectNo + 1] = 0;

			for (int i = EffectNo - 2; i < EffectNo; ++i)
			{
				m_bIsEffect[i] = false;
				m_bIsPlay[i] = true;
				m_nAnimeNo[i] = 0;
			}
		}
		if (m_bIsPlay[EffectNo])
		{
			m_bIsPlay[EffectNo] = false;
			m_bIsEffect[EffectNo] = IsEffect;
		}
		break;
	case 3:	
		// 現在のフェーズで他の方向の矢印が出ていないか
		if (m_bIsEffect[EffectNo - 3] || m_bIsEffect[EffectNo - 2] || m_bIsEffect[EffectNo - 1])
		{
			for (int i = EffectNo - 3; i < EffectNo; ++i)
			{
				m_bIsEffect[i] = false;
				m_bIsPlay[i] = true;
				m_nAnimeNo[i] = 0;
			}
		}

		if (m_bIsPlay[EffectNo])
		{
			m_bIsPlay[EffectNo] = false;
			m_bIsEffect[EffectNo] = IsEffect;
		}
		break;
	}

	// 現在のフェーズで他の方向の矢印が出ていないか
	if ((EffectNo % 4) == 4 || (EffectNo % 4) == 0)
	{
		if (m_bIsEffect[EffectNo + 1] || m_bIsEffect[EffectNo + 2] || m_bIsEffect[EffectNo + 3])
		{
			for (int i = EffectNo + 1; i < EffectNo + 4; ++i)
			{
				m_bIsEffect[i] = false;
				m_bIsPlay[i] = true;
				m_nAnimeNo[i] = 0;
			}
		}
		if (m_bIsPlay[EffectNo])
		{
			m_bIsPlay[EffectNo] = false;
			m_bIsEffect[EffectNo] = IsEffect;
		}
	}
}