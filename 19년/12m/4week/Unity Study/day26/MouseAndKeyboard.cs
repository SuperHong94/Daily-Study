using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseAndKeyboard : MonoBehaviour
{

    void Update()
    {
        if (Input.anyKeyDown)
            Debug.Log("플레이어가 아무키를 눌렀습니다.");
        //if (Input.anyKey)
        //    Debug.Log("플레이어가 아무키를 누르고 있습니다.");
        //if (Input.GetKeyDown(KeyCode.Return)) //Return 엔터키
        //    Debug.Log("아이템을 구입하였습니다.");

        //if (Input.GetKey(KeyCode.LeftArrow))
        //    Debug.Log("왼쪽으로 이동 중");

        //if (Input.GetKeyUp(KeyCode.RightArrow))
        //    Debug.Log("오른쪽 이동을 멈추었습니다.");


        //마우스
        //if (Input.GetMouseButtonDown(0))
        //    Debug.Log("미사일 발사");
        //if (Input.GetMouseButton(0))
        //    Debug.Log("미사일 모으는 중...");
        //if (Input.GetMouseButtonUp(0))
        //    Debug.Log("슈퍼 미사일 발사!!");

        //버튼방식
        //if (Input.GetButtonDown("Jump"))
        //    Debug.Log("점프!");
        //if (Input.GetButton("Jump"))
        //    Debug.Log("점프 모으는 중...");
        //if (Input.GetButtonUp("Jump"))
        //    Debug.Log("슈퍼점프!!");
        if (Input.GetButton("Horizontal"))
        {
           // Debug.Log("횡 이동 중 ..." + Input.GetAxis("Horizontal")); //가중치있음
           Debug.Log("횡 이동 중 ..." + Input.GetAxisRaw("Horizontal"));
 
        }
        if (Input.GetButtonUp("Jump"))
            Debug.Log("슈퍼점프!!");
    }
}
