package com.zeroone.star.education.controller;

import com.zeroone.star.education.service.ClassService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.schedule.ClassApis;
import com.zeroone.star.project.query.j5.schedule.ClassByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.ClassOptionVO;
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
@RequestMapping("/j5/option")
public class ClassController implements ClassApis {

    @Autowired
    private ClassService classService;

    /*
     * 描述：获取班级下拉列表
     * */
    @GetMapping("/classes")
    @ApiOperation("获取班级下拉列表")
    @Override
    public JsonVO<PageDTO<ClassOptionVO>> getClassOption(ClassByNameQuery query) {
        log.info("查询参数：{}", query); // 添加日志
        PageDTO<ClassOptionVO> page = PageDTO.create(classService.listByClassName(query));
        return JsonVO.success(page);
    }
}
