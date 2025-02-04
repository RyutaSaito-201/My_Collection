using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.Rendering.DebugUI;
public class CameraManager : MonoBehaviour
{
    enum CameraState
    {
        MEETING,    // 相手と対面
        GAME,       // ゲーム画面(カード選択画面
        MAX_STATE,
    }

    public GameObject[] TargetPosition;
    private Vector3 p_StartPosition;
    private Quaternion p_StartRotation;

    private Vector3 p_Position;
    private Quaternion p_Rotation;

    private float moveTime = 0.6f; // 2秒で0から1に変更する
    private float timeElapsed = 0f;
    private float moveCameraRange = 0.01f;

    private bool IsMove;
    private bool[] CameraMove = { false, false };
    private bool _isMoveOder;       // カメラ移動要請フラグ

    private CameraState cameraPosition;
    private PlayerDrawOrDrinkState playerDrawOrDrinkState;
    private PlayerDrinkState playerDrinkState;
    private PlayerDrawState playerDrawState;
    private PlayerStateContext PlayerState;

    // Start is called before the first frame update
    void Start()
    {
        cameraPosition = CameraState.MEETING;  // カメラの初期位置

        p_StartPosition = Camera.main.transform.position;
        p_StartRotation = Camera.main.transform.rotation;

        float sin = Mathf.Sin(Time.time);
        sin /= 1000.0f;

        Camera.main.transform.position = new Vector3(p_StartPosition.x += sin, p_StartPosition.y += sin, p_StartPosition.z);
    }

    // Update is called once per frame
    void Update()
    {
        // 現在のゲームの状態を確認
        if (GameObject.Find("PlayerDrawOrDrinkState(Clone)") != null)
        {
            playerDrawOrDrinkState = GameObject.Find("PlayerDrawOrDrinkState(Clone)").GetComponent<PlayerDrawOrDrinkState>();
            playerDrinkState = null;
            playerDrawState = null;
        }
        if (GameObject.Find("PlayerDrinkState(Clone)") != null)
        {
            playerDrinkState = GameObject.Find("PlayerDrinkState(Clone)").GetComponent<PlayerDrinkState>();
            playerDrawOrDrinkState = null;
            playerDrawState = null;
        }
        if (GameObject.Find("PlayerDrawState(Clone)") != null)
        {
            playerDrawState = GameObject.Find("PlayerDrawState(Clone)").GetComponent<PlayerDrawState>();
            playerDrawOrDrinkState = null;
            playerDrinkState = null;
        }

        // 選択画面からゲーム画面へ
        if (_isMoveOder || IsMove)
        {
            IsMove = true; // カメラ遷移中


            if (!CameraMove[1] && cameraPosition == CameraState.MEETING || CameraMove[0])
            {
                cameraPosition = CameraState.GAME;

                CameraMove[0] = true;   // 現在動いているか 
                                        // カメラの現在位置を取得
                p_Position = Camera.main.transform.position;
                p_Rotation = Camera.main.transform.rotation;

                Transform TargetLocation = TargetPosition[0].GetComponent<Transform>();
                float t = timeElapsed / moveTime;
                // 線形補間でカメラを遷移
                Camera.main.transform.position = Vector3.Lerp(p_Position, TargetLocation.position, t);
                Camera.main.transform.rotation = Quaternion.Lerp(p_Rotation, TargetLocation.rotation, t);

                timeElapsed += Time.deltaTime;
                float distance = Vector3.Distance(p_Position, TargetLocation.position);

                // 概ね正しい位置に来ているか
                if (distance < moveCameraRange)
                {
                    IsMove = false;
                    CameraMove[0] = false;
                    timeElapsed = 0f;
                }
            }
            else if (cameraPosition == CameraState.GAME || CameraMove[1])
            {
                cameraPosition = CameraState.MEETING;

                CameraMove[1] = true;

                p_Position = Camera.main.transform.position;
                p_Rotation = Camera.main.transform.rotation;

                float t = timeElapsed / moveTime;

                Camera.main.transform.position = Vector3.Lerp(p_Position, p_StartPosition, t);
                Camera.main.transform.rotation = Quaternion.Lerp(p_Rotation, p_StartRotation, t);

                timeElapsed += Time.deltaTime;
                float distance = Vector3.Distance(p_StartPosition, p_Position);
                if (distance < moveCameraRange)
                {
                    IsMove = false;
                    CameraMove[1] = false;
                    timeElapsed = 0f;
                }
            }
        }
        _isMoveOder = false;
    }
    // カメラがゲームなっているか確認用
    public bool CheckCamera()
    {
        if (cameraPosition == CameraState.GAME && !CameraMove[0] || IsMove)
            return true;
        return false;
    }

    /**
     * @brief カメラの移動を外部から命令する
     */
    public void MoveOder()
    {
        _isMoveOder = true;
    }
}
