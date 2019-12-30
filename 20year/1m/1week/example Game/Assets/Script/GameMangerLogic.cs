using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
public class GameMangerLogic : MonoBehaviour
{
    // Start is called before the first frame update

    public int totalItemCount; //맵에 존재하는 아이템 총 갯수
    public int stage;
    public Text stageCountText;
    public Text playerCountText;

    private void Awake()
    {
        stageCountText.text = "/" + totalItemCount;
    }
    public void GetItem(int count)
    {
        playerCountText.text = count.ToString();
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
            SceneManager.LoadScene(stage);
    }
}
