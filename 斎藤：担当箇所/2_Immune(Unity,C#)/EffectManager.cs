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
        SLASH_LV1,      // �A�^�b�J�[
        SLASH_LV2,
        SLASH_LV3,
        SLASH_LV4,
        SLASH_LV5,
        HEAL_LV1,       // �q�[���[
        HEAL_LV2,
        HEAL_LV3,
        HEAL_LV4,
        HEAL_LV5,
        SHOT_LV1,       // �A�[�`���[
        SHOT_LV2,
        SHOT_LV3,
        SHOT_LV4,
        SHOT_LV5,
        ENEMY_SHOT_LV1, // �G�A�[�`���[
        ENEMY_SHOT_LV2,
        ENEMY_SHOT_LV3,
        ENEMY_SHOT_LV4,
        ENEMY_SLASH_LV1, // �G�A�^�b�J�[
        ENEMY_SLASH_LV2,
        ENEMY_SLASH_LV3,
        ENEMY_SLASH_LV4,
        BOSS_ATTCK,        // �{�X
        MAX_KIND    // �ő吔
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
        AttackEffect = new AsyncOperationHandle<GameObject>[(int)Effectkind.MAX_KIND + 3];  // �G�t�F�N�g���̕ۑ��p�z��
        AsyncOperationHandle<GameObject>[] loadHandle = new AsyncOperationHandle<GameObject>[(int)Effectkind.MAX_KIND + 3];
        //--- �G�t�F�N�g�t�@�C�����[�h ---
        for (int i = 0; i < (int)Effectkind.MAX_KIND + 3; ++i)
        {
            int nLV = i % 5;
            nLV++;
            string sLV = nLV.ToString();
            if (i < 5)
            {
                loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SLASH_LV" + sLV);    // �X���b�V��
            }
            else if (i >= 5 && i < 10)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + sLV);     // �q�[��
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_HEAL_LV" + "1");     // �q�[��
                }
            }
            else if (i >= 10 && i < 14)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + sLV);     // �V���b�g
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_SHOT_LV" + "1");     // �V���b�g
                }
            }
            else if (i >= 15 && i < 19)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + sLV);    // �G�l�~�[�V���b�g
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSHOT_LV" + "1");    // �G�l�~�[�V���b�g
                }
            }
            else if (i >= 20 && i < 24)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + sLV)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + sLV);    // �G�l�~�[�X���b�V��

                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_ENEMYSLASH_LV" + "1");    // �G�l�~�[�X���b�V��

                }
            }
            else if (i == 25)
            {
                if (Addressables.ReleaseInstance(Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + 1)))
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + sLV);    // �{�X
                }
                else
                {
                    loadHandle[i] = Addressables.LoadAssetAsync<GameObject>("FX_BOSSLv" + "1");    // �G�l�~�[�X���b�V��

                }
            }

            if (!AttackEffect[i].IsValid())
            {
                Debug.Log(i);// �G�t�F�N�g�i�[����
                Debug.Log(loadHandle[i].IsDone);// �G�t�F�N�g�i�[����
                AttackEffect[i] = loadHandle[i];// �G�t�F�N�g�i�[����
            }
        }
    }

    // �G�t�F�N�g�̐����ꏊ�̐ݒ�
    // void EffectPos :: y:Y��,x:X��,SltNo:�\������G�t�F�N�g�̔ԍ�,Arc_ATKRange: �v���C���[�U���J�n�ʒu,Ene_ATKRange: �G�U���ʒu
    public void EffectPos(float y, float x, int SltNo = (int)Effectkind.SLASH_LV1, int SltLV = 0, float Arc_ATKRange = 0.0f, float ENE_ATkRange = 0.0f)
    {
        int nLV = SltLV % 5; // �\������G�t�F�N�g�̃��x�������O�Ɍv�Z

        switch (SltNo)
        {
            case 0:
                // �G�ߐڍU���G�t�F�N�g    
                nLV += (int)Effectkind.SLASH_LV1;
                Debug.Log("�����ߐڍU���G�t�F�N�g" + nLV);
                Debug.Log(AttackEffect[nLV].IsValid());
                switch (nLV % 5)
                {
                    case 0:
                        Debug.Log("�����ߐ�:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 1:
                        Debug.Log("�����ߐ�:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 2:
                        Debug.Log("�����ߐ�:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.5f, x - 0.2f, -3.0f), new Vector3(0.0f, 0.0f, 0.0f));
                        break;
                    case 3:
                        Debug.Log("�����ߐ�:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 4:
                        Debug.Log("�����ߐ�:" + nLV);
                        SpawnEffect(nLV, new Vector3(y - 0.55f, x - 0.2f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                }

                break;
            case 1:
                // �q�[���[�񕜃G�t�F�N�g
                nLV += (int)Effectkind.HEAL_LV1;
                Debug.Log("�q�[��:" + nLV);
                SpawnEffect(nLV, new Vector3(y, x - 0.2f, -3.0f), new Vector3(-90.0f, 0.0f, 0.0f));
                break;
            case 2:
                // �A�[�`���[�U���G�t�F�N�g
                nLV--;
                nLV += (int)Effectkind.SHOT_LV1;
                Transform[] children = new Transform[Arc_Effect_LV1.transform.childCount];
                switch (nLV % 5)
                {
                    case 0:
                        // �G�t�F�N�g�����֐�
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV1, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 1:
                        // �G�t�F�N�g�����֐�Lv2
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV2, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 2:
                        // �G�t�F�N�g����
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV3, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(0.0f, 90.0f, 0.0f));
                        break;
                    case 3:
                        // �G�t�F�N�g����
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, Arc_Effect_LV4, nLV, new Vector3(x, y + 0.5f, -3.0f), new Vector3(-90.0f, 90.0f, 0.0f));
                        break;
                    case 4:
                        children = new Transform[Arc_Effect_LV1.transform.childCount];
                        for (int i = 0; i < Arc_Effect_LV1.transform.GetChild(0).childCount; i++)
                        {
                            children[i] = Arc_Effect_LV1.transform.GetChild(i); // GetChild()�Ŏq�I�u�W�F�N�g���擾
                            Vector3 newScale = Arc_Effect_LV1.transform.GetChild(i).localScale;
                            newScale.z = (ENE_ATkRange - y) * 0.03f;
                            Arc_Effect_LV1.transform.GetChild(i).localScale = newScale;
                            Debug.Log("�A�[�`���[:" + nLV);
                            Debug.Log("�A�[�`���[:" + AttackEffect[nLV]);
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
                // �G�A�[�`���U���G�t�F�N�g
                nLV += (int)Effectkind.ENEMY_SHOT_LV1;
                Debug.Log("�G�A�[�`���U���G�t�F�N�g" + nLV);
                switch (nLV % 5)
                {
                    case 0:// �U���������v�Z
                        InitArrowEffect(Arc_ATKRange, ENE_ATkRange, EnemyArc_Effect_LV1, nLV, new Vector3(x, y - 0.8f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                    case 1:
                        // �r�[���G�t�F�N�g
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
                        Debug.Log("�A�[�`���[:" + nLV);
                        SpawnEffect(nLV, new Vector3(y, x - 0.2f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                    case 3:
                        Debug.Log("�A�[�`���[:" + nLV);
                        SpawnEffect(nLV, new Vector3(y, x - 0.5f, -3.0f), new Vector3(-90.0f, 0.0f, -90.0f));
                        break;
                }
                break;
            case 4:
                // �G�ߐڍU���G�t�F�N�g
                nLV += (int)Effectkind.ENEMY_SLASH_LV1;
                Debug.Log("�G�ڍU���U���G�t�F�N�g" + nLV);
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
                // �{�X�ߐڍU���G�t�F�N�g
                if (nLV == 4)
                    nLV -= 2;
                else
                    nLV += 2;
                nLV += (int)Effectkind.BOSS_ATTCK;
                Debug.Log("�{�X�ڍU���U���G�t�F�N�g" + nLV);
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
    // �G�t�F�N�g�����ꏊ���w�肷��֐�
    // ����(int:�G�t�F�N�g�̎��,Vector3 ���W, Vector3��])
    void SpawnEffect(int sltEffect, Vector3 pos, Vector3 Rot)
    {
        obj.Add(Instantiate(AttackEffect[sltEffect].Result,
        new Vector3(pos.x, pos.y, pos.z),
        Quaternion.Euler(Rot.x, Rot.y, Rot.z)));
    }

    // Arrow(�|��)�n�̃G�t�F�N�g�̐����֐�
    // ����(�U���҂̍��W�A��e�҂̍��W,�@�G�t�F�N�g�̎��,�U���҂̃��x��, �o�����W�A�G�t�F�N�g�̉�])
    void InitArrowEffect(float ArcATKRange, float EneATKRange, GameObject Effect, int nLV, Vector3 pos, Vector3 rot)
    {
        float fRange = EneATKRange - ArcATKRange; // �U���������v�Z
        Debug.Log("�A�[�`���[:" + fRange);
        for (int i = 0; i < Effect.transform.GetChild(0).childCount; i++)
        {
            float Speed = fRange / (13.0f / 2.5f); // Effect�̃��C�t�^�C�����v�Z

            ParticleSystem particleSystem = AttackEffect[nLV].Result.transform.GetChild(0).transform.GetChild(i).GetComponent<ParticleSystem>();
            var startLifeSpeed = particleSystem.main;
            startLifeSpeed.startLifetime = Speed;
        }
        SpawnEffect(nLV, new Vector3(pos.y + 0.5f, pos.x, -3.0f), new Vector3(rot.x, rot.y, rot.z));
    }
}
