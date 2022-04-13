package com.example.demo;

import java.util.HashMap;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

@Controller //컨트롤러사용 @은 어노테이션 옆에 문구를 이용해서 스프링내부엔진은 이 자바 파일을 컨트롤러러 인식한다.
public class TestController {

    @RequestMapping("/hello")  //hello라는 주소들엉오면 아래 메소드실행한다.
    public ModelAndView hello() throws Exception{
        ModelAndView mav=new ModelAndView();
        mav.addObject("KEY_SUBJECT", "kdigital client"); //key: 데이터임
        mav.setViewName("hello_view");  //  /jsp_path/__.jsp
        return mav;
    }

    @RequestMapping("/hello2")  //hello라는 주소들엉오면 아래 메소드실행한다.
    public ModelAndView hello2() throws Exception{
        ModelAndView mav=new ModelAndView();
        mav.addObject("KEY_SUBJECT", "kdigital client"); //key: 데이터임
        mav.setViewName("thyme_path/hello_thyme_view");  //  /jsp_path/__.jsp
        return mav;
    }

    @RequestMapping(value="/hello3/{bseq}",method=RequestMethod.GET)  //hello라는 주소들엉오면 아래 메소드실행한다.
    @ResponseBody() //JSON
    public HashMap<String,Object>  hello3(@PathVariable int bseq) throws Exception{
        HashMap<String,Object> map=new HashMap<String,Object>();
        map.put("besq",bseq);
        map.put("title","hello--title");
        map.put("regid","kim");
        return map;
    }

}
