package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.ILessonService;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.j5.courseschedule.LessonApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：课次管理控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
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
        return JsonVO.success(null);
    }

    @PostMapping("stop")
    @ApiOperation("停课")
    @Override
    public JsonVO<Integer> stopLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        return JsonVO.success(0);
    }

    @PostMapping("resume")
    @ApiOperation("复课")
    @Override
    public JsonVO<Integer> resumeLesson(@ApiParam(value = "课次ID列表", required = true) @RequestBody List<Long> lessonIds) {
        return JsonVO.success(0);
    }

    @GetMapping("detail")
    @ApiOperation("获取课次详情")
    @Override
    public JsonVO<?> getLessonDetail(@ApiParam(value = "课次ID", required = true) @RequestParam Long lessonId) {
        return JsonVO.success(null);
    }
}
