package com.zeroone.star.homework.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.homework.HomeworkDTO;
import com.zeroone.star.project.j6.homework.HomeworkApis;
import com.zeroone.star.project.query.j6.homework.HomeworkQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * 作业管理接口实现
 */
@RestController
@RequestMapping("/j6/homework")
@Api(tags = "作业管理")
public class HomeworkController implements HomeworkApis {

    /**
     * 查询作业列表
     * @param query
     * @return
     */
    @GetMapping
    @ApiOperation("查询作业列表(分页+条件)")
    @Override
    public JsonVO<PageDTO<HomeworkDTO>> queryPage(HomeworkQuery query) {
        return null;
    }

    /**
     * 获取作业详情
     * @param id
     * @return
     */
    @GetMapping("/{id}")
    @ApiOperation("获取作业详情")
    @Override
    public JsonVO<HomeworkDTO> getGradeById(Integer id) {
        return null;
    }

    /**
     * 保存作业
     * @param homeworkDto
     * @return
     */
    @PostMapping
    @ApiOperation("保存作业")
    @Override
    public JsonVO<HomeworkDTO> saveGrade(HomeworkDTO homeworkDto) {
        return null;
    }
}
