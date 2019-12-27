using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class OtherBall : MonoBehaviour
{
    // Start is called before the first frame update
    MeshRenderer mesh;
    Material mat;
    void Start()
    {
        mesh = GetComponent<MeshRenderer>();
        mat = mesh.material;
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "myBall")
            mat.color = new Color(Random.Range(0, 255), Random.Range(0, 255), 0);
    }
    //void OnCollisionStay(Collision collision)
    //{

    //}
    void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.name == "myBall")
            mat.color = new Color(1, 1, 1);
    }
}
