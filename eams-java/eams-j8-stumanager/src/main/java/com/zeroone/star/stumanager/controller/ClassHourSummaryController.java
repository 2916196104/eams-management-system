package com.zeroone.star.stumanager.controller;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j8.stumanager.ClassHourSummaryApis;
import com.zeroone.star.project.query.j8.stumanager.ClassHourSummaryQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ClassHourSummaryVO;
import com.zeroone.star.stumanager.service.IClassHourSummaryService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

/**
 * 课时汇总
 */
@Api(tags = "课时汇总")
@RequestMapping("/stu/class-hour-summary")
@RestController
public class ClassHourSummaryController implements ClassHourSummaryApis {

    @Resource
    private IClassHourSummaryService classHourSummaryService;

    @Override
    @GetMapping("/list")
    @ApiOperation("分页查询课时汇总列表")
    public JsonVO<PageDTO<ClassHourSummaryVO>> getLessonSummary(ClassHourSummaryQuery query) {
        PageDTO<ClassHourSummaryVO> pageDTO =classHourSummaryService.pageList(query);
        return JsonVO.success(pageDTO);
    }
}
