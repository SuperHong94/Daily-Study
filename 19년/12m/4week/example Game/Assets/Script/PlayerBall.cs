using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBall : MonoBehaviour
{
    public int itemCount = 0;
    public float jumpPower;
    bool isJump;
    Rigidbody rigid;
    AudioSource audio;
    private void Awake()
    {
        audio = GetComponent<AudioSource>();
        rigid = GetComponent<Rigidbody>();
        isJump = false;
    }

    void FixedUpdate()
    {

        float h = Input.GetAxisRaw("Horizontal");
        float v = Input.GetAxisRaw("Vertical");
        rigid.AddForce(new Vector3(h, 0, v), ForceMode.Impulse);
    }

    private void Update()
    {
        if (Input.GetButtonDown("Jump") && !isJump)
        {
            isJump = true;

            rigid.AddForce(new Vector3(0, jumpPower, 0), ForceMode.Impulse);
        }
    }
    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "Floor")
            isJump = false;
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.name == "Item")
        {
            PlayerBall player = other.GetComponent<PlayerBall>();
            player.itemCount++;
            audio.Play();
            other.gameObject.SetActive(false);
           
        }
    }
}
