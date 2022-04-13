package com.example.demo;

import java.util.HashMap;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

@RestController
public class TestRestController {
    @RequestMapping(value="/rest/{bseq}",method=RequestMethod.GET)  //hello라는 주소들엉오면 아래 메소드실행한다.

    public HashMap<String,Object>  hello3(@PathVariable int bseq) throws Exception{
        HashMap<String,Object> map=new HashMap<String,Object>();
        map.put("besq",bseq);
        map.put("title","rest--title");
        map.put("regid","park");
        return map;
    }
}
