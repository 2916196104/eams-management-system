package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j8.stumanager.common.LessonCountRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.common.LessonCountRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.common.LessonCountRecordVO;
import com.zeroone.star.stumanager.service.IStudentLessonCountLogService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
@Validated
@RequestMapping("/stu/common/lesson-count-records")
@Api(tags = "学员公用接口 - 消课记录")
public class LessonCountRecordsController implements LessonCountRecordsApis {

    @Resource
    private IStudentLessonCountLogService studentLessonCountLogService;

    @ApiOperation("获取消课记录")
    @GetMapping("/query-lesson-count-records")
    @Override
    public JsonVO<PageDTO<LessonCountRecordVO>> queryLessonCountRecords(@Validated LessonCountRecordQuery query) {
        try {
            return JsonVO.success(studentLessonCountLogService.queryLessonCountRecords(query));
        } catch (IllegalArgumentException exception) {
            return JsonVO.fail(exception.getMessage());
        }
    }
}
