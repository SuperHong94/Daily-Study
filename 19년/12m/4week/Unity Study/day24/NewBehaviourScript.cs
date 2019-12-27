using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    void Start()
    {
        Debug.Log("Hello Unity");

        // 1.변수

        int level = 5;
        float strength = 15.5f;
        string playerName = "sdkdn";
        bool isFullLevel = false;
        Debug.Log("이름");
        Debug.Log(playerName);

        List<string> items = new List<string>();
        items.Add("마나물약30");

        //키워드

        string[] monstrers = { "슬라임", "괴물", "악마" };

        // for(int i = 0; i < monstrers.Length; ++i)
        // {
        //     Debug.Log("이지역안에 몬스터" + monstrers[i]);
        // }


        //새롭게안것
        foreach (string monster in monstrers)
            Debug.Log(" 이지역에 있는 몬스터:" + monster);

        //함수

        int health = 10;
        health = Heal(health);

        //클래스
        Player player = new Player();

        player.id = 0;


        

       
    }

    int Heal(int health)
    {
        health += 10;
        Debug.Log("힐받음");
        return health;
    }
}
