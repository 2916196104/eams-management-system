package com.zeroone.star.j5.courseplan.controller;

import com.zeroone.star.j5.courseplan.service.ClassService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j5.courseplan.ClassByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseplan.ClassOptionVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/*
 * 描述：班级管理接口实现类
 * */
@Slf4j
@RestController
@Api(tags = "班级管理")
@RequestMapping("/j5-class-option")
public class ClassController {

    @Autowired
    private ClassService classService;

    /*
     * 描述：获取班级下拉列表
     * */
    @GetMapping("/classes")
    @ApiOperation("获取班级下拉列表")

    public JsonVO<PageDTO<ClassOptionVO>> getClassOption(ClassByNameQuery query) {
        log.info("查询参数：{}", query); // 添加日志
        PageDTO<ClassOptionVO> page = PageDTO.create(classService.listByClassName(query));
        return JsonVO.success(page);
    }
}
