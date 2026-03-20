package com.zeroone.star.j5.courseschedule.controller;

import com.zeroone.star.j5.courseschedule.service.ILessonStudentService;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.j5.studentstatus.StudentLessonStatusApis;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * 描述：课次学员管理控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
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
        return JsonVO.success(null);
    }

    @PostMapping("sign")
    @ApiOperation("签到保存")
    public JsonVO<Integer> saveSign(@ApiParam(value = "签到参数", required = true) @RequestBody LessonSignSaveDTO lessonSignSaveDTO) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-sign")
    @ApiOperation("批量签到")
    public JsonVO<Integer> batchSaveSign(@ApiParam(value = "签到参数列表", required = true) @RequestBody List<LessonSignSaveDTO> lessonSignSaveDTOs) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-set-status")
    @ApiOperation("批量设置课程状态")
    @Override
    public JsonVO<Integer> batchSetStatus(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds,
                                            @ApiParam(value = "目标状态", required = true) @RequestParam String status) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-toggle-status")
    @ApiOperation("批量停课/复课")
    @Override
    public JsonVO<Integer> batchToggleLessonStatus(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds,
                                                      @ApiParam(value = "操作类型：STOP/RESUME", required = true) @RequestParam String actionType) {
        return JsonVO.success(0);
    }

    @PostMapping("batch-restore")
    @ApiOperation("批量还原课程进度")
    @Override
    public JsonVO<Integer> batchRestore(@ApiParam(value = "课次学员记录ID列表", required = true) @RequestBody List<Long> lessonStudentIds) {
        return JsonVO.success(0);
    }
}
