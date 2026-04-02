package com.zeroone.star.eamsj3data.controller;

import com.zeroone.star.eamsj3data.service.StudentService;
import com.zeroone.star.project.j3.data.StudentsStagesApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.data.newStudentsVO;
import com.zeroone.star.project.vo.j3.data.studentLessonCountsVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import springfox.documentation.spring.web.json.Json;

import java.time.LocalDateTime;
import java.util.List;

@RestController
@RequestMapping("j3/static")
@Api(tags = "学员统计")
public class StudentsStageController implements StudentsStagesApis {
    @Autowired
    private StudentService studentService;
    
    @Override
    @GetMapping("newStudentCounts")
    @ApiOperation("获取新学员信息")
    public JsonVO<List<newStudentsVO>> getNewStudentsStagesInfo(
            @RequestParam(required = false) @DateTimeFormat LocalDateTime beginTime,
            @RequestParam(required = false) @DateTimeFormat LocalDateTime endTime) {
        List<newStudentsVO> queryAns =
                studentService.getNewStudentsStagesInfo(beginTime,endTime);
        if(queryAns==null){
            return JsonVO.fail("查询失败。");
        }
        return JsonVO.success(queryAns);
    }

    @Override
    @GetMapping("studentLessonCounts")
    @ApiOperation("获取学院课时排行前20")
    public JsonVO<List<studentLessonCountsVO>> getStudentLessonCounts(
           @RequestParam(required = false) @DateTimeFormat LocalDateTime beginTime,
           @RequestParam(required = false) @DateTimeFormat LocalDateTime endTime) {
        return null;
    }
}
