using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using UnityEngine.VFX;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.AddressableAssets;
using System.Net;
using UnityEngine.Rendering;
using TMPro;
using Unity.VisualScripting;
using static UnityEngine.Rendering.DebugUI.Table;

public class EffectManager : MonoBehaviour
{
    static AsyncOperationHandle<GameObject>[] AttackEffect;
    public GameObject Arc_Effect_LV1;
    public GameObject Arc_Effect_LV2;
    public GameObject Arc_Effect_LV3;
    public GameObject Arc_Effect_LV4;
    public GameObject Arc_Effect_LV5;

    public GameObject EnemyArc_Effect_LV1;
    public GameObject EnemyArc_Effect_LV2;
    public GameObject EnemyArc_Effect_LV3;
    public GameObject EnemyArc_Effect_LV4;

    public enum Effectkind
    {
        SLASH_LV1,      // アタッカー
        SLASH_LV2,
        SLASH_LV3,
        SLASH_LV4,
        SLASH_LV5,
        HEAL_LV1,       // ヒーラー
        HEAL_LV2,
        HEAL_LV3,
        HEAL_LV4,
        HEAL_LV5,
        SHOT_LV1,       // アーチャー
        SHOT_LV2,
        SHOT_LV3,
        SHOT_LV4,
        SHOT_LV5,
        ENEMY_SHOT_LV1, // 敵アーチャー
        ENEMY_SHOT_LV2,
        ENEMY_SHOT_LV3,
        ENEMY_SHOT_LV4,
        ENEMY_SLASH_LV1, // 敵アタッカー
        ENEMY_SLASH_LV2,
        ENEMY_SLASH_LV3,
        ENEMY_SLASH_LV4,
        BOSS_ATTCK,        // ボス
        MAX_KIND    // 最大数
    };

    List<float>[,] effectKind;
    List<GameObject> obj = new List<GameObject>();
    float X, Y;
    bool play;
    GameObject a;
    bool IsBoss = false;

    // Start is called before the first frame update
    void Start()
    {
        ParticleSystem particle = GetComponent<ParticleSystem>();
        AttackEffect = new AsyncOperationHandle<GameObject>[(int)Effectkind.MAX_KIND + 3];  // エフェクト実体保存用配列
        AsyncOperationHandle<GameObject>[] loadHandle = new AsyncOperationHandle<GameObject>[(int)Effectkind.MAX_KIND + 3];
        //--- エフェクトファイルロード ---
        for (int i = 0; i < (int)Effectkind.MAX_KIND + 3; ++i)
        {
            int nLV = i % 5;
            nLV++;
            string sLV = nLV.ToString();
            if (i < 5)
            {
                loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SLASH_LV" + sLV);    // スラッシュ
            }
            else if (i >= 5 && i < 10)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + sLV);     // ヒール
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + "1");     // ヒール
                }
            }
            else if (i >= 10 && i < 14)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + sLV);     // ショット
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + "1");     // ショット
                }
            }
            else if (i >= 15 && i < 19)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + sLV);    // エネミーショット
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + "1");    // エネミーショット
                }
            }
            else if (i >= 20 && i < 24)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + sLV);    // エネミースラッシュ

                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + "1");    // エネミースラッシュ

                }
            }
            else if (i == 25)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + 1)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + sLV);    // ボス
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + "1");    // エネミースラッシュ

                }
            }

            if (!AttackEffect[i].IsValid())
            {
                Debug.Log(i);// エフェクト格納処理
                Debug.Log(loadHandle[i].IsDone);// エフェクト格納処理
                AttackEffect[i] = loadHandle[i];// エフェクト格納処理
            }
        }
    }

    // エフェクトの生成場所の設定
    // void EffectPos :: y:Y軸,x:X軸,SltNo:表示するエフェクトの番号,Arc_ATKRange: プレイヤー攻撃開始位置,Ene_ATKRange: 敵攻撃位置
    public void EffectPos(float y, float x, int SltNo = (int)Effectkind.SLASH_LV1, int SltLV = 0, float Arc_ATKRange = 0.0f, float ENE_ATkRange = 0.0f)
    {
        int nLV = SltLV % 5; // 表示するエフェクトのレベルを事前に計算

        switch (SltNo)
        {
            case 0:
                // 敵近接攻撃エフェクト    
                nLV += (int)Effectkind.SLASH_LV1;
                Debug.Log("味方近接攻撃エフェクト" + nLV);
                Debug.Log(AttackEffect[nLV].IsValid());
                switch (nLV % 5)
                {
                    case 0:
                        Debug.Log("味方近接:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 1:
                        Debug.Log("味方近接:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 2:
                        Debug.Log("味方近接:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.5f, x - 0.2f, -3.0f), new Vector3(0.0f, 0.0f, 0.0f));
                        break;
                    case 3:
                        Debug.Log("味方近接:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 4:
                        Debug.Log("味方近接:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                }

                break;
            case 1:
                // ヒーラー回復エフェクト
                nLV += (int)Effectkind.HEAL_LV1;
                Debug.Log("ヒール:" + nLV);
                SpawnEffect(nLV, new Vector3(y, x - 0.2f, -3.0f), new Vector3(-90.0f, 0.0f, 0.0f));
                break;
            case 2:
                // アーチャー攻撃エフェクト
                nLV--;
                nLV += (int)Effectkind.SHOT_LV1;
                Transform[] children = new Transform[Arc_Effect_LV1.transform.childCount];
                switch (nLV % 5)
                {
                    case 0:
                        // エフェクト生成関数
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV1, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 1:
                        // エフェクト生成関数Lv2
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV2, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 2:
                        // エフェクト生成
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV3, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 3:
                        // エフェクト生成
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV4, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(-90.0f, 90.0f, 0.0f));
                        break;
                    case 4:
                        children = new Transform[Arc_Effect_LV1.transform.childCount];
                        for (int i = 0; i < Arc_Effect_LV1.transform.GetChild(0).childCount; i++)
                        {
                            children[i] = Arc_Effect_LV1.transform.GetChild(i); // GetChild()で子オブジェクトを取得
                            Vector3 newScale = Arc_Effect_LV1.transform.GetChild(i).localScale;
                            newScale.z = (ENE_ATkRange - y) * 0.03f;
                            Arc_Effect_LV1.transform.GetChild(i).localScale = newScale;
                            Debug.Log("アーチャー:" + nLV);
                            Debug.Log("アーチャー:" + AttackEffect[nLV]);
                            Debug.Log(AttackEffect);
                            AttackEffect[nLV].Result.transform.GetChild(0).transform.GetChild(i).localScale = Arc_Effect_LV1.transform.GetChild(i).localScale;
                            ParticleSystem particleSystem = AttackEffect[nLV].Result.transform.GetChild(0).transform.GetChild(i).GetComponent<ParticleSystem>();
                            particleSystem.time -= newScale.z;
                        }
                        SpawnEffect(nLV, new Vector3(y, x, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));

                        break;

                }
                break;
            case 3:
                // 敵アーチャ攻撃エフェクト
                nLV += (int)Effectkind.ENEMY_SHOT_LV1;
                Debug.Log("敵アーチャ攻撃エフェクト" + nLV);
                switch (nLV % 5)
                {
                    case 0:// 攻撃距離を計算
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, EnemyArc_Effect_LV1, nLV, new Vector3(x, y - 0.8f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                    case 1:
                        // ビームエフェクト
                        for (int i = 0; i < EnemyArc_Effect_LV2.transform.GetChild(0).childCount; i++)
                        {
                            Vector3 newScale = EnemyArc_Effect_LV2.transform.GetChild(0).localScale;
                            newScale.z = 0.1f;
                            newScale.x = 0.23f;
                            EnemyArc_Effect_LV2.transform.GetChild(0).localScale = newScale;

                            AttackEffect[nLV].Result.transform.GetChild(0).transform.GetChild(i).localScale = EnemyArc_Effect_LV2.transform.GetChild(0).localScale;
                        }
                        SpawnEffect(nLV, new Vector3(y - 0.8f, x, -3.0f), new Vector3(-90.0f, 0.0f, 180.0f));
                        break;
                    case 2:
                        Debug.Log("アーチャー:" + nLV);
                        SpawnEffect(nLV, new Vector3(y, x - 0.2f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                    case 3:
                        Debug.Log("アーチャー:" + nLV);
                        SpawnEffect(nLV, new Vector3(y, x - 0.5f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                }
                break;
            case 4:
                // 敵近接攻撃エフェクト
                nLV += (int)Effectkind.ENEMY_SLASH_LV1;
                Debug.Log("敵接攻撃攻撃エフェクト" + nLV);
                switch (nLV % 5)
                {
                    case 0:
                        SpawnEffect(nLV, new Vector3(x, y - 0.5f, -3.0f), new Vector3(0.0f, -90.0f, 0.0f));
                        break;
                    case 1:
                        SpawnEffect(nLV, new Vector3(x, y - 0.3f, -3.0f), new Vector3(0.0f, -90.0f, 0.0f));
                        break;
                    case 2:
                        SpawnEffect(nLV, new Vector3(x, y - 0.2f, -3.0f), new Vector3(0.0f, -90.0f, 0.0f));
                        break;
                    case 3:
                        SpawnEffect(nLV, new Vector3(x, y - 0.2f, -3.0f), new Vector3(-90.0f, -90.0f, 0.0f));
                        break;
                }
                break;
            case 5:
                // ボス近接攻撃エフェクト
                if (nLV == 4)
                    nLV -= 2;
                else
                    nLV += 2;
                nLV += (int)Effectkind.BOSS_ATTCK;
                Debug.Log("ボス接攻撃攻撃エフェクト" + nLV);
                switch (nLV % 5)
                {
                    case 0:
                        if (!IsBoss)
                        {
                            SpawnEffect(nLV, new Vector3(4, -4, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                            IsBoss = true;
                        }
                        else
                            IsBoss = false;
                    break;
                    case 1:
                        if (!IsBoss)
                        {
                            SpawnEffect(nLV, new Vector3(4, -4, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                            IsBoss = true;
                        }
                        else
                            IsBoss = false;
                        break;
                    case 2:
                        if (!IsBoss)
                        {
                            SpawnEffect(nLV, new Vector3(4, -4, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                            IsBoss = true;
                        }
                        else
                            IsBoss = false;
                        break;
                }

                break;

        }
    }
    // エフェクト生成場所を指定する関数
    // 引数(int:エフェクトの種類,Vector3 座標, Vector3回転)
    void SpawnEffect(int sltEffect, Vector3 pos, Vector3 Rot)
    {
        obj.Add(Instantiate(AttackEffect[sltEffect].Result,
        new Vector3(pos.x, pos.y, pos.z),
        Quaternion.Euler(Rot.x, Rot.y, Rot.z)));
    }

    // Arrow(弓矢)系のエフェクトの生成関数
    // 引数(攻撃者の座標、被弾者の座標,　エフェクトの種類,攻撃者のレベル, 出現座標、エフェクトの回転)
    void InitArrowEffect(float ArcATKRange, float EneATKRange, GameObject Effect, int nLV, Vector3 pos, Vector3 rot)
    {
        float fRange = EneATKRange - ArcATKRange; // 攻撃距離を計算
        Debug.Log("アーチャー:" + fRange);
        for (int i = 0; i < Effect.transform.GetChild(0).childCount; i++)
        {
            float Speed = fRange / (13.0f / 2.5f); // Effectのライフタイムを計算

            ParticleSystem particleSystem = AttackEffect[nLV].Result.transform.GetChild(0).transform.GetChild(i).GetComponent<ParticleSystem>();
            var startLifeSpeed = particleSystem.main;
            startLifeSpeed.startLifetime = Speed;
        }
        SpawnEffect(nLV, new Vector3(pos.y + 0.5f, pos.x, -3.0f), new Vector3(rot.x, rot.y, rot.z));
    }
}
