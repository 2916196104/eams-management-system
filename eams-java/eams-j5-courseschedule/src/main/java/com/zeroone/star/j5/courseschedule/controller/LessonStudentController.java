package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.ILessonStudentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.j5.studentstatus.StudentLessonStatusApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("j5/courseschedule/lesson-student")
@Api(tags = "课次学员管理")
public class LessonStudentController implements StudentLessonStatusApis {

    @Resource
    private ILessonStudentService lessonStudentService;

    @GetMapping("list")
    @ApiOperation("分页查询学员上课状态列表")
    @Override
    public JsonVO<PageDTO<Map<String, Object>>> list(String keyword, String status, PageQuery query) {
        return JsonVO.success(lessonStudentService.queryStatusList(keyword, status, query));
    }

    @PostMapping("sign")
    @ApiOperation("签到保存")
    public JsonVO<Integer> saveSign(@ApiParam(value = "签到参数", required = true) @Valid @RequestBody LessonSignSaveDTO lessonSignSaveDTO) {
        return JsonVO.success(lessonStudentService.addOrUpdateRecord(lessonSignSaveDTO));
    }

    @PostMapping("batch-sign")
    @ApiOperation("批量签到")
    public JsonVO<Integer> batchSaveSign(@ApiParam(value = "签到参数列表", required = true) @Valid @RequestBody List<LessonSignSaveDTO> lessonSignSaveDTOs) {
        return JsonVO.success(lessonStudentService.batchAddOrUpdateRecord(lessonSignSaveDTOs));
    }

    @PostMapping("batch-set-status")
    @ApiOperation("批量设置课程状态")
    @Override
    public JsonVO<Integer> batchSetStatus(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds,
                                          @ApiParam(value = "目标状态", required = true) @RequestParam String status) {
        return JsonVO.success(lessonStudentService.batchSetStatus(lessonStudentIds, status));
    }

    @PostMapping("batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds) {
        return JsonVO.success(lessonStudentService.rollbackCourseNum(lessonStudentIds));
    }

    @GetMapping("count-log")
    @ApiOperation("分页查询课次变更流水")
    @Override
    public JsonVO<PageDTO<?>> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
        return JsonVO.success(lessonStudentService.queryLessonCountLog(queryDTO));
    }
}
