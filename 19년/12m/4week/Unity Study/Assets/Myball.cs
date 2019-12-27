using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Myball : MonoBehaviour
{

    Rigidbody rigid; //선언
    void Start()
    {
        rigid = GetComponent<Rigidbody>();
        //rigid.velocity = Vector3.left;
       
       
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float h = Input.GetAxisRaw("Horizontal");
        float v = Input.GetAxisRaw("Vertical");
        Vector3 vec = new Vector3(h, 0, v);
        rigid.AddForce(vec, ForceMode.Impulse);

    }
    void OnTriggerStay(Collider other)
    {
        if(other.name=="cube")
            rigid.AddForce(Vector3.up * 25, ForceMode.Impulse);
    }

    public void jump()
    {
        rigid.AddForce(Vector3.up * 50, ForceMode.Impulse);
    }
}
