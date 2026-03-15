package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ChangeCreditDTO;
import com.zeroone.star.project.dto.j4.student.CreditLogDTO;
import com.zeroone.star.project.dto.j4.student.LessonCountDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.CreditSelectQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {
    @GetMapping
    @ApiOperation("获取消课记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<LessonCountDTO>> queryOmyLessonCount(@RequestParam(value = "name",required = true) String StudentID) {
        return null;
    }

    @GetMapping
    @ApiOperation("获取积分记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<CreditLogDTO>> queryCreditLog(@RequestBody CreditSelectQuery creditSelectQuery) {
        return null;
    }

    @GetMapping
    @ApiOperation("调整积分")
    @Override
    public JsonVO<Long> saveCreditLog(@RequestBody ChangeCreditDTO changeCreditDTO) {
        return null;
    }
}
