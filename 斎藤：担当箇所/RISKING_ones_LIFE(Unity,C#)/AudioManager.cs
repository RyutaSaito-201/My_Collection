using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Audio;
using static UnityEngine.Rendering.DebugUI;

public class AudioManager : MonoBehaviour
{
    // SEの種類
    public enum SE_KIND
    {
        SELECT,     // 選択
        SUCCESS,    // 成功
        FAILED,     // 失敗
        HEARTSOUND, // 心音
        CHAIN_UNLOCK, // 鎖　外れる音
        CHAIN_LOCK, // 鎖　つける音
        EAR_NOISE,  // 耳鳴り
        HORROR,     // 不気味な音
        DOOR,       // ドアが開く音
        DEAD,       // 死ぬ音
        STARTGAME,  // ゲームスタート
        STORYCLICK, // ストーリークリック音
        MAX_SE,
    }

    // BGMの種類
    enum BGM_KIND
    {
        GAMESCENE,   // ゲームシーン
        MAX_BGM,
    }
    [SerializeField] private AudioSource a1;
    [SerializeField] private AudioSource a2;
    [SerializeField] private AudioSource a3;
    [SerializeField] private AudioSource a4;
    [SerializeField] private AudioSource a5;
    [SerializeField] private AudioSource a6;
    [SerializeField] private AudioSource a7;
    [SerializeField] private AudioSource a8;
    [SerializeField] private AudioSource a9;
    [SerializeField] private AudioSource a10;
    [SerializeField] private AudioSource a11;
    [SerializeField] private AudioSource a12;

    SE_KIND e_KIND;
    BGM_KIND e_BGM;
    List<AudioClip> l_audioClips;
    AudioLowPassFilter BGM_Player;
    AudioSource BGMSource;
    AudioSource SE_Player;

    private float timeElapsed = 0f;
    private float duration = 2f; // 1秒で0から1に変更する

    private bool isPlaying = false;
    private bool isPaused = false;
    private string currentSEName = "";

    // Start is called before the first frame update
    void Start()
    {
        // SE読み込み
        AudioClip audioClips;
        l_audioClips = new List<AudioClip>();
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_SELECT");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_DISSOLVE");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_FAILED");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/HeartSound");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_CHAIN_UNLOCK");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_CHAIN_LOCK");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_EAR_NOISE");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_HORROR");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_DOOR");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_DEAD");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_STARTGAME");
        l_audioClips.Add(audioClips);
        audioClips = Resources.Load<AudioClip>("Audio/SE/SE_STORYCLICK");
        l_audioClips.Add(audioClips);
        
        BGM_Player = Camera.main.GetComponent<AudioLowPassFilter>();
		BGMSource = Camera.main.GetComponent<AudioSource>();

	}

    // Update is called once per frame
    void Update()
    {
        if (isPlaying)
        {
            if (isPaused)
            {
                float t = timeElapsed / duration;
                BGM_Player.cutoffFrequency = Mathf.Lerp(5000.0f, 1500f, t);
                BGM_Player.lowpassResonanceQ = Mathf.Lerp(1.0f, 2.0f, t);
                timeElapsed += Time.deltaTime;
                if (BGM_Player.lowpassResonanceQ >= 2.0f)
                {
                    timeElapsed = 0.0f;
                    isPlaying = false;
                }
            }
            else
            {
                float t = timeElapsed / duration;
                BGM_Player.cutoffFrequency = Mathf.Lerp(1500f, 5000.0f, t);
                BGM_Player.lowpassResonanceQ = Mathf.Lerp(2.0f, 1.0f, t);
                timeElapsed += Time.deltaTime;
                if (BGM_Player.lowpassResonanceQ <= 1.0f)
                {
                    timeElapsed = 0.0f;
                    isPlaying = false;
                }
            }
        }
    }

    // 特定の動作をしたときにSEを再生
    public void PlaySE(int BGMNo)
    {
        AudioClip audio = l_audioClips[BGMNo];
        switch (BGMNo)
        {
            case (int)SE_KIND.SELECT:
                a1.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.SUCCESS:
                a2.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.FAILED:
                a3.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.HEARTSOUND:
                a4.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.CHAIN_UNLOCK:
                a5.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.CHAIN_LOCK:
                a6.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.EAR_NOISE:
                a7.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.HORROR:
                a8.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.DOOR:
                a9.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.DEAD:
                a10.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.STARTGAME:
                a11.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            case (int)SE_KIND.STORYCLICK:
                a12.PlayOneShot(l_audioClips[BGMNo]);
                currentSEName = audio.name;
                break;
            default:
                break;
        }
    }

    public void PlayEarNoise()
    {
        isPlaying = true;
        isPaused = true;
    }

    public void StopEarNoise()
    {
        isPlaying = true;
        isPaused = false;
    }

    // 現在再生中のSE名を取得する
    public string GetCurrentSEName()
    {
        return currentSEName;
    }

    /**
     * @brief BGMをフェードアウトさせる
     * @param[in] float フェードアウトにかける時間
     */
	public void FadeOutBGM(float fadeTime)
	{
		StartCoroutine(FadeOutCoroutine(fadeTime));
	}

	private IEnumerator FadeOutCoroutine(float fadeTime)
	{
		float startVolume = BGMSource.volume;

		// 指定した時間をかけてボリュームを減らしていく
		for (float t = 0; t < fadeTime; t += Time.deltaTime)
		{
			BGMSource.volume = Mathf.Lerp(startVolume, 0, t / fadeTime);
			yield return null;
		}

		BGMSource.volume = 0;
		BGMSource.Stop(); // フェードアウト後にBGMを停止
	}
}
