using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;//必要
using UnityEngine.Rendering.Universal;//必要;
using UnityEngine.UIElements;

public class PostProcessManager : MonoBehaviour
{
    // 状態異常の種類
    enum PostEffectKind
    {
        Heart,  // 心臓
        Eye,    // 目
        Lung,    // 肺
        Ear,    // 耳 
        MAX_KIND,
    }

    private Volume PostEffect;
    private ChromaticAberration Chromatic;      // 色収差
    private DepthOfField OfField;               // 被写体深度
    private ChannelMixer channelMixer;          // RGB
    private Vignette vignette;                  // 
    private UniversalAdditionalCameraData cameraData;   // ポストエフェクト(メイン)
    [SerializeField] private AudioSource PlaySE;
    private AudioManager audioManager;

    private Vector3 StartHeelPos;
    private Quaternion StartHeelRot;

    private bool _isPlayHealBlur = false;           // 薬フォーカスブラー再生中か
    private bool _IsPlayPostEffect = true;

    private int nPlayPostEffectNo = 3;

    private float duration = 2f;                    // 2秒で0から1に変更する
    private float duration2 = 5f;                   // 5秒で0から1に変更する
    private float duration3 = 0.7f;
    private float timeElapsed = 0f;
    private float timeElapsed1 = 0f;
    private float maxVignetteIntensity = 1.0f;      // ビネットの最大強度
    private float originalVignetteIntensity = 0.2f; // ビネットの元の強度
    private float elapsedTime = 0.0f;               // 経過時間
    private float TimeSpawn = 1.5f;
    private bool _isLung = false;
    private bool _isPlayheart;                      // 心臓エフェクト再生中か
    private bool _isPlayLung;                       // 肺エフェクト再生中か
    private bool _isPlayEye = false;
    private bool _lungCountStopFlg;                 // 肺のカウントダウンを一時停止する

    private List<int> nOldPostEffectNo;
    private List<int> CulletPlayEffect;
    List<int> toRemove = new List<int>();

    // Start is called before the first frame update
    void Start()
    {
        GameObject a = GameObject.Find("HeelObs");
        StartHeelPos = a.transform.position;
        StartHeelRot = a.transform.rotation;

        PostEffect = GameObject.Find("Global Volume").GetComponent<Volume>();
        CulletPlayEffect = new List<int>();
        nOldPostEffectNo = new List<int>();

        PostEffect.profile.TryGet(out OfField);
        PostEffect.profile.TryGet(out channelMixer);
        PostEffect.profile.TryGet(out vignette);
        PostEffect.profile.TryGet(out Chromatic);
        cameraData = Camera.main.GetComponent<UniversalAdditionalCameraData>();

        audioManager = Camera.main.GetComponent<AudioManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!_IsPlayPostEffect) return;

        if (nOldPostEffectNo != null && nOldPostEffectNo.Count > 0)  // エフェクトを戻す処理
        {
            Debug.Log(nOldPostEffectNo.Count);
            foreach (int i in nOldPostEffectNo)
            {
                switch (i)
                {
                    case (int)PostEffectKind.Eye:  // 目
                        _isPlayEye = false;
                        float t = timeElapsed / duration;
                        OfField.gaussianStart.value = Mathf.Lerp(0.0f, 1000.0f, t);
                        timeElapsed += Time.deltaTime;

                        float a = Mathf.Lerp(20.0f, 100.0f, t);
                        float b = Mathf.Lerp(20.0f, 0.0f, t);

                        channelMixer.redOutRedIn.value = a;
                        channelMixer.blueOutBlueIn.value = a;
                        channelMixer.greenOutGreenIn.value = a;

                        channelMixer.redOutBlueIn.value = b;
                        channelMixer.redOutGreenIn.value = b;
                        channelMixer.blueOutRedIn.value = b;
                        channelMixer.blueOutGreenIn.value = b;
                        channelMixer.greenOutRedIn.value = b;
                        channelMixer.greenOutBlueIn.value = b;
                        Debug.Log(OfField.gaussianStart.value);
                        if (OfField.gaussianStart.value > 999.0f)
                        {
                            Debug.Log("とおた");
                            timeElapsed = 0.0f;
                            toRemove.Add(i);

                        }
                        break;
                    case (int)PostEffectKind.Lung:      // 肺

                        float t2 = timeElapsed / duration;

                        vignette.intensity.value = Mathf.Lerp(vignette.intensity.value, 0.0f, t2);
                        timeElapsed += Time.deltaTime;
                        Debug.Log(vignette.intensity.value);
                        if (vignette.intensity.value < 0.01f)
                        {

                            timeElapsed = 0.0f;

                            Debug.Log(nOldPostEffectNo.Count);
                            toRemove.Add(i);

                            Debug.Log(nOldPostEffectNo.Count);
                        }
                        break;
                }
            }

        }

        if (toRemove.Count > 0)
        {
            Debug.Log(toRemove.Count);
            foreach (int number in toRemove)
            {
                nOldPostEffectNo.Remove(number);
            }
            toRemove.Clear();
        }
        else
        {
            toRemove.Clear();
        }

        if (CulletPlayEffect != null)
        {
            foreach (int No in CulletPlayEffect)                // エフェクトの数分だけ繰り返す
            {
                switch (No)                                     // エフェクト開始処理
                {
                    case (int)PostEffectKind.Heart:             // 心臓
                        if (PlaySE.isPlaying)
                        {
                            if (audioManager.GetCurrentSEName() == "HeartSound")
                            {

                                _isPlayheart = true;             // 心臓エフェクト再生中フラグ上げ

                                float[] samples = new float[256];
                                PlaySE.GetOutputData(samples, 0);

                                // 音量のピークを検出
                                float currentPeak = Mathf.Max(samples);

                                // ピークに応じてビネットの強度を変化させる
                                float vignetteIntensity = Mathf.Lerp(originalVignetteIntensity, maxVignetteIntensity, currentPeak);
                                vignette.intensity.value = vignetteIntensity;
                                Chromatic.intensity.value = Mathf.Lerp(originalVignetteIntensity, maxVignetteIntensity, currentPeak * 10.0f);
                            }
                        }
                        else
                        {
                            if (_isPlayheart)
                            {
                                elapsedTime += Time.deltaTime;
                                float t2 = elapsedTime / 1.0f;
                                vignette.intensity.value = Mathf.Lerp(0.2f, 0.0f, t2);
                                Chromatic.intensity.value = Mathf.Lerp(0.2f, 0.0f, t2);
                                if (vignette.intensity.value < 0.01f)
                                {
                                    _isPlayheart = false;    // 心臓エフェクト再生中フラグ下げ
                                    elapsedTime = 0.0f;
                                    vignette.intensity.value = 0.0f;
                                }
                            }

                        }
                        break;
                    case (int)PostEffectKind.Eye:   // 目のエフェクト
                        if (channelMixer.redOutRedIn.value != 20.0f)
                        {
                            _isPlayEye = true;
                            float t = timeElapsed / duration;
                            OfField.gaussianStart.value = Mathf.Lerp(1000.0f, 0f, t);
                            timeElapsed += Time.deltaTime;
                            
                            float a = Mathf.Lerp(100.0f, 20.0f, t);
                            float b = Mathf.Lerp(0.0f, 20.0f, t);

                            channelMixer.redOutRedIn.value = a;
                            channelMixer.blueOutBlueIn.value = a;
                            channelMixer.greenOutGreenIn.value = a;

                            channelMixer.redOutBlueIn.value = b;
                            channelMixer.redOutGreenIn.value = b;
                            channelMixer.blueOutRedIn.value = b;
                            channelMixer.blueOutGreenIn.value = b;
                            channelMixer.greenOutRedIn.value = b;
                            channelMixer.greenOutBlueIn.value = b;
                            if (OfField.gaussianStart.value < 0.01f)
                            {
                                
                                timeElapsed = 0.0f;
                            }
                        }
                        break;
                    case (int)PostEffectKind.Lung:          // 肺
                        if (!_isPlayLung) break;            // 肺演出再生フラグが立ってなければ以下を処理しない
                        if (_lungCountStopFlg) break;       // カウント停止フラグが立っていたら以下を処理しない

                        float t3 = elapsedTime / TimeSpawn;
                        float vignetteIntensity2 = Mathf.Lerp(originalVignetteIntensity, maxVignetteIntensity, t3);
                        vignette.intensity.value = vignetteIntensity2;
                        elapsedTime += Time.deltaTime;

                        if (elapsedTime >= TimeSpawn) _isPlayLung = false;

                        break;

                }
            }
        }
    }


    // =====  カメラフォーカス処理関数 =====
    public void PlayPostEffect(int SltPE)
    {
        switch (SltPE)  // エフェクト開始
        {
            case 0: // カメラの遷移する座標と開始地点を設定
                GameObject Heel = GameObject.Find("HeelObs");
                GameObject HeelPos = GameObject.Find("HeelPos");

                float t = timeElapsed1 / duration3;
                Heel.transform.position = Vector3.Lerp(Heel.transform.position, HeelPos.transform.position, t);
                Heel.transform.rotation = Quaternion.Lerp(Heel.transform.rotation, HeelPos.transform.rotation, t);

                float distance = Vector3.Distance(Heel.transform.position, HeelPos.transform.position);
                timeElapsed1 += Time.deltaTime;
                // 地点間の距離を正規化
                float normalizeDistance = 1 - (distance / 9);

                Debug.Log(distance);
                if (!_isPlayEye)
                {
                    OfField.gaussianStart.value = 1000.0f + (3.0f - 1000.0f) * normalizeDistance;
                }

                // 概ね目的座標についたか
                if (distance < 0.01f)
                {
                    Debug.Log("OK");
                    _isPlayHealBlur = false; 
                    timeElapsed1 = 0f;
                    return /*false*/;
                }
                _isPlayHealBlur = true;
                return /*true*/;

            case 1: // エフェクト終了
                GameObject Heel1 = GameObject.Find("HeelObs");

                float t1 = timeElapsed1 / duration3;
                Heel1.transform.position = Vector3.Lerp(Heel1.transform.position, StartHeelPos, t1);
                Heel1.transform.rotation = Quaternion.Lerp(Heel1.transform.rotation, StartHeelRot, t1);
                timeElapsed1 += Time.deltaTime;
                float distance1 = Vector3.Distance(StartHeelPos, Heel1.transform.position);

                Vector3 testf3 = Heel1.transform.position;
                Vector3 testf4 = StartHeelPos;
                // 地点間の距離を正規化
                float normalizeDistance2 = 1 - (distance1 / 9);

                Debug.Log(distance1);
                if (!_isPlayEye)
                {
                    OfField.gaussianStart.value = 4.0f + (1001.0f - 4.0f) * normalizeDistance2;
                }

                // 概ね目的座標についたか
                if (distance1 < 0.01f)
                {
                    Debug.Log("OK");
                    timeElapsed1 = 0f;
                    _isPlayHealBlur = false;
                    return /*true*/;
                }
                _isPlayHealBlur = true; 
                return /*false*/;
            default:
                return /*false*/;

        }
    }

    // ===== getter・setter =====
    public bool IsPlayHealBlur { get { return _isPlayHealBlur; } }
    public bool IsPlayPostEffect { get { return _IsPlayPostEffect; } }
    public bool isPlayheart { get { return _isPlayheart; } set { _isPlayheart = value; } }
    public bool isPlayLung { get { return _isPlayLung; } set { _isPlayLung = value; } }
    public bool lungCountStopFlg { get { return _lungCountStopFlg; } set { _lungCountStopFlg = value; } }

    // エフェクト開始処理
    public void PlayEffect(int EffectNo, float LungTimeSpawn = 1.5f)
    {
        _IsPlayPostEffect = true;
        TimeSpawn = LungTimeSpawn;
        CulletPlayEffect.Add(EffectNo);
        if (EffectNo == (int)PostEffectKind.Heart) _isPlayheart = true;    // 心臓エフェクトなら心臓再生中フラグ上げ
    }

    // エフェクト終了処理
    public void StopEffect(int EffectNo)
    {
        Debug.Log("1");
        for (int i = CulletPlayEffect.Count - 1; i >= 0; i--)
        {

            if (CulletPlayEffect[i] == EffectNo)
            {

                nOldPostEffectNo.Add(CulletPlayEffect[i]);
                CulletPlayEffect.RemoveAt(i);

            }
        }
    }
    public void ChangePostEffect(int EffectNo)
    {
        cameraData.SetRenderer(EffectNo);
    }

    public void TemporaryStopLung()
    {
        elapsedTime = 0.0f;
        vignette.intensity.value = 0.0f;
    }
}
