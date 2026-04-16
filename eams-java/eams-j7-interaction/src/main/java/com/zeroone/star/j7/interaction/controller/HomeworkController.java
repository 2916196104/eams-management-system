package com.zeroone.star.j7.interaction.controller;

import com.zeroone.star.j7.interaction.service.IHomeworkRecordService;
import com.zeroone.star.j7.interaction.service.IHomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkCommentDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkDeleteDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSaveDTO;
import com.zeroone.star.project.j7.interaction.HomeworkApis;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import com.zeroone.star.project.query.j7.interaction.HomeworkRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSubmitDTO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;

/**
 * <p>
 * 描述：课后作业控制器
 * </p>
 * @author lvincent di
 * @since 2026-03-16
 */
@RestController
@RequestMapping("/j7-interaction/j7-homework")
@Api(tags = "课后作业管理")
public class HomeworkController implements HomeworkApis {

    @Resource
    private IHomeworkService homeworkService;

    @Resource
    private IHomeworkRecordService homeworkRecordService;

    @Override
    @GetMapping("/list")
    @ApiOperation("获取作业列表")
    public JsonVO<PageDTO<HomeworkVO>> listHomework(@Validated HomeworkListQuery query) {
        return JsonVO.success(homeworkService.listHomeworks(query));
    }

    @Override
    @GetMapping("/info/{id}")
    @ApiOperation("获取作业详情")
    public JsonVO<HomeworkVO> getHomeworkById(
            @ApiParam(value = "作业ID", required = true) @PathVariable Long id) {
        return JsonVO.success(homeworkService.getHomeworkDetail(id));
    }

    @Override
    @GetMapping("/recordsList")
    @ApiOperation("获取作业提交列表")
    public JsonVO<PageDTO<HomeworkRecordVO>> listHomeworkRecords(@Validated HomeworkRecordQuery query) {
        return JsonVO.success(homeworkRecordService.listRecords(query));
    }

    @PostMapping("/save")
    @ApiOperation(value = "保存作业")
    //保存-提交作业(教师发布作业)
    public JsonVO<Long> saveHomework(@RequestBody @Valid HomeworkSaveDTO dto,
                                     @RequestHeader("user-id") Long operatorId) {
        if (operatorId == null || operatorId <= 0) {
            return JsonVO.fail("请求头user-id无效，请重新登录");
        }
        return JsonVO.success(homeworkService.saveHomework(dto, operatorId));
    }

    @PostMapping("/delete")
    @ApiOperation(value = "删除作业")
    public JsonVO<Void> deleteHomework(@RequestBody @Valid HomeworkDeleteDTO dto,
                                       @RequestHeader("user-id") Long operatorId) {
        if (operatorId == null || operatorId <= 0) {
            return JsonVO.fail("请求头user-id无效，请重新登录");
        }
        homeworkService.deleteHomework(dto, operatorId);
        return JsonVO.success(null);
    }

    @PostMapping("/comment")
    @ApiOperation(value = "点评作业")
    public JsonVO<Void> commentHomework(@RequestBody @Valid HomeworkCommentDTO dto,
                                        @RequestHeader("user-id") Long teacherId) {
        if (teacherId == null || teacherId <= 0) {
            return JsonVO.fail("请求头user-id无效，请重新登录");
        }
        homeworkService.commentHomework(dto, teacherId);
        return JsonVO.success(null);
    }
}
/**
 * 提交作业
    @PostMapping("/submit")
    @ApiOperation(value = "提交作业")
    public JsonVO<Long> submitHomework(@RequestBody @Valid HomeworkSubmitDTO dto,
                                       @RequestHeader("user-id") Long studentId) {
        if (studentId == null || studentId <= 0) {
               return JsonVO.fail("请求头user-id无效，请重新登录");
        }
        return JsonVO.success(homeworkService.submitHomework(dto, studentId));
    }
*/
