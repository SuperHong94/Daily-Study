using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class PlayerBall : MonoBehaviour
{
    public int itemCount = 0;
    public float jumpPower;
    public GameMangerLogic manager;
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
        if (collision.gameObject.tag == "Floor")
            isJump = false;
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Item")
        {
            PlayerBall player = other.GetComponent<PlayerBall>();
            itemCount++;
            audio.Play();
            other.gameObject.SetActive(false);
            manager.GetItem(itemCount);
        }
        else if (other.tag == "Point")
        {
            if (itemCount == manager.totalItemCount)
            {
                if (manager.stage == 1)
                    SceneManager.LoadScene(0);
                else
                    SceneManager.LoadScene((manager.stage + 1));
                //game Clear!
            }
            else
            {
                SceneManager.LoadScene(manager.stage);
                //Restart..
            }

        }
    }
}
