package com.zeroone.star.j7.interaction.controller;

import com.github.xiaoymin.knife4j.annotations.ApiOperationSupport;
import com.zeroone.star.j7.interaction.service.TeachEvaluationService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.TeachEvaluationVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@Api(tags = "学评教")
@RestController
@RequestMapping("/j7-interaction/j7-student-teacher")
public class TeachEvaluationController {

    private final TeachEvaluationService teachEvaluationService;

    public TeachEvaluationController(TeachEvaluationService teachEvaluationService) {
        this.teachEvaluationService = teachEvaluationService;
    }

    @ApiOperation(value = "获取学生点评列表（条件+分页）")
    @ApiOperationSupport(author = "开发人员", order = 1)
    @GetMapping("/list")
    public JsonVO<PageDTO<TeachEvaluationVO>> pageList(TeachEvaluationQuery query) {
        if (query == null) {
            query = new TeachEvaluationQuery();
        }
        if (query.getPageIndex() < 1) {
            query.setPageIndex(1L);
        }
        if (query.getPageSize() < 1) {
            query.setPageSize(30L);
        }
        PageDTO<TeachEvaluationVO> pageDTO = teachEvaluationService.pageList(query);
        return JsonVO.success(pageDTO);
    }
}