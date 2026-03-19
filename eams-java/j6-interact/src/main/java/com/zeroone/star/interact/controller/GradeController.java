package com.zeroone.star.interact.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.j6.interact.GradeApis;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("j6/grade")
@Api(tags = "成绩单")
public class GradeController implements GradeApis {

    @Override
    @GetMapping
    @ApiOperation("获取成绩单列表（条件+分页）")
    public JsonVO<PageDTO<GradeFormDTO>> queryPage(GradeFormQuery condition) {
        return null;
    }

}
