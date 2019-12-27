using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeCycle : MonoBehaviour
{
   void Awake()
    {
        Debug.Log("플레이어 데이터가 준비되어있습니다.");

    }

    void OnEnable()
    {
        Debug.Log("플레이어가 로그인했습니다.");
    }


   void Start()
    {
        Debug.Log("사냥 준비를 챙겼습니다.");
    }

   void FixedUpdate()
    {
        Debug.Log("이동~");
    }
    void Update()
    {
        Debug.Log("몬스터 사냥!!");
    }

     void LateUpdate()
    {
        Debug.Log("경험치 획득.");
    }
    void OnDisable()
    {
        Debug.Log("플레이어가 로그아웃했습니다.");
    }
    void OnDestroy()
    {
        Debug.Log("플레이어 데이터가 해제되어있습니다.");
    }
}
