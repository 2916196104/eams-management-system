package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.ILessonService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.j5.courseschedule.LessonApis;
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
import java.util.List;

@RestController
@RequestMapping("j5/courseschedule/lesson")
@Api(tags = "课次管理")
public class LessonController implements LessonApis {

    @Resource
    private ILessonService lessonService;

    @GetMapping("list")
    @ApiOperation("分页查询课次列表")
    @Override
    public JsonVO<PageDTO<?>> listLesson(LessonParamDTO param) {
        return JsonVO.success(lessonService.queryList(param));
    }

    @PostMapping("stop")
    @ApiOperation("停课")
    @Override
    public JsonVO<Integer> stopLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        LessonChangeStateDTO dto = new LessonChangeStateDTO();
        dto.setLessonIds(lessonIds);
        dto.setTargetState(0);
        return JsonVO.success(lessonService.changeLessonState(dto));
    }

    @PostMapping("resume")
    @ApiOperation("复课")
    @Override
    public JsonVO<Integer> resumeLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        LessonChangeStateDTO dto = new LessonChangeStateDTO();
        dto.setLessonIds(lessonIds);
        dto.setTargetState(1);
        return JsonVO.success(lessonService.changeLessonState(dto));
    }

    @GetMapping("detail")
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<?> getLessonDetail(@ApiParam(value = "课次ID", required = true) @RequestParam Long lessonId) {
        return JsonVO.success(lessonService.queryDetail(lessonId));
    }
}
