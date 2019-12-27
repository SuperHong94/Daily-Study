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
        //rigid.velocity = new Vector3(2, 4, 3);

        if (Input.GetButtonDown("Jump"))
        {
            rigid.AddForce(Vector3.up * 25, ForceMode.Impulse);
        }

        Vector3 vec = new Vector3(Input.GetAxisRaw("Horizontal"), 0, Input.GetAxisRaw("Vertical"));

        rigid.AddForce(vec, ForceMode.Impulse);
        //rigid.AddTorque(Vector3.up);

    }
    void OnTriggerStay(Collider other)
    {
        if(other.name=="cube")
            rigid.AddForce(Vector3.up * 25, ForceMode.Impulse);
    }
}
