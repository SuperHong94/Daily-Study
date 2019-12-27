using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class moveToTraget : MonoBehaviour
{
    Vector3 target = new Vector3(8.0f, 1.5f, 0);
    void Update()
    {
        //transform.position =
        //    Vector3.MoveTowards(transform.position, target, 1f);

        //SmoothDamp
        //  Vector3 velo = Vector3.zero;
        // // Vector3 velo = Vector3.up*50;
        //
        //  transform.position =
        //      Vector3.SmoothDamp(transform.position, target, ref velo, 0.5f);

        //3.Lerp
        // transform.position =
        //      Vector3.Lerp(transform.position, target, 0.05f);

        //4.SLerp(구면 선형 보간)
        transform.position =
             Vector3.Slerp(transform.position, target, 0.05f);

    }
}
