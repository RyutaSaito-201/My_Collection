using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectManager : MonoBehaviour
{
    private List<GameObject> L_EffectObj = new List<GameObject>();

    // Start is called before the first frame update
    void Awake()
    {
        GameObject effectObj;

        effectObj = Resources.Load<GameObject>("Effect/CFX_Explosion_B_Smoke+Text");
        L_EffectObj.Add(effectObj);
        effectObj = Resources.Load<GameObject>("Effect/CardEff");
        L_EffectObj.Add(effectObj);
        effectObj = Resources.Load<GameObject>("Effect/Spark");
        L_EffectObj.Add(effectObj);
        effectObj = Resources.Load<GameObject>("Effect/Kieru");
        L_EffectObj.Add(effectObj);
        effectObj = Resources.Load<GameObject>("Effect/kemuri");    // 劇薬オーラ
        L_EffectObj.Add(effectObj);
    }

    public GameObject SpawnEffect(int SltEffectNo, Transform Pos)
    {
        switch (SltEffectNo)
        {
            case 0:
                Instantiate(L_EffectObj[SltEffectNo], Pos.position, Pos.rotation);
                break;
            case 1:
                Vector3 pos = Pos.position;
                pos.y += 0.02f;
                Instantiate(L_EffectObj[SltEffectNo], pos, Pos.rotation);
                break;
            case 2:
                Instantiate(L_EffectObj[SltEffectNo], Pos.position, Pos.rotation);
                break;
            case 3:
                Instantiate(L_EffectObj[SltEffectNo], Pos.position, Pos.rotation);
                break;
            case 4: // 劇薬オーラ
				return Instantiate(L_EffectObj[SltEffectNo], Pos.position, Pos.rotation);
        }

        return null;
    }

    // エフェクト削除(選択エフェクト時に使用
    public void DestoryEffect()
    {
        GameObject[] gameObjects2 = GameObject.FindGameObjectsWithTag("SelectEffect");
        for (int i = 0; i < gameObjects2.Length; i++)
        {
            Destroy(gameObjects2[i]);
        }
    }
}
