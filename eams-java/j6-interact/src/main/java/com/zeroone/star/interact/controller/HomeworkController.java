package com.zeroone.star.interact.controller;

import com.zeroone.star.interact.service.HomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkScoreDto;
import com.zeroone.star.project.j6.interact.HomeworkApis;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkSubmissionListVo;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import java.util.List;


/**
 * <p>
 * 作业接口实现类
 * </p>
 *
 * @author yuqiuchiling
 * @since 2026-03-16
 */
@RestController
@RequestMapping("/j6-interact/homework")
@Api(tags = "课后作业")
public class HomeworkController implements HomeworkApis {


    @Autowired
    private HomeworkService homeworkService;

    /**
     * 获取作业列表（条件+分页）
     *
     * @param homeworkQuery
     */
    @GetMapping("/list")
    @ApiOperation("获取作业列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<HomeworkListDto>> queryHomeworkList(HomeworkQuery homeworkQuery) {
        try {
            PageDTO<HomeworkListDto> result = homeworkService.pageQuery(homeworkQuery);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 获取作业详情
     *
     * @param id
     */
    @GetMapping("/{id}")
    @ApiOperation("获取作业详情")
    @Override
    public JsonVO<HomeworkDetailVO> homeworkDetails(@PathVariable("id")Long id) {
        try {
            HomeworkDetailVO result = homeworkService.getHomeworkDetail(id);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 保存作业,新增和编辑作业是调用这个接口
     * @param homeworkDetailDto
     * @return
     */
    @PostMapping
    @ApiOperation(" 保存作业")
    @Override
    public JsonVO<Long> saveHomework(@Validated @RequestBody HomeworkDetailDto homeworkDetailDto) {
        try {
            Long id = homeworkService.saveHomework(homeworkDetailDto);
            return JsonVO.success(id);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 删除作业
     *
     * @param ids
     */
    @DeleteMapping("/delete")
    @ApiOperation("删除作业")
    @Override
    public JsonVO<List<Long>> deleteHomeworks(@RequestBody List<Long> ids) {
        try {
            List<Long> result = homeworkService.deleteHomeworks(ids);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 获取作业提交列表（条件+分页）
     *
     * @param homeworkId
     */
    @GetMapping("/submit/{id}")
    @ApiOperation("获取作业提交列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<HomeworkSubmissionListVo>> queryHomeworkSubmissionList(@PathVariable("id") Long homeworkId) {
        try {
            PageDTO<HomeworkSubmissionListVo> result = homeworkService.queryHomeworkSubmissionList(homeworkId);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    /**
     * 点评作业
     *
     * @param homeworkScoreDto 点评信息（包含提交记录ID、分数、点评内容）
     */
    @PutMapping("/score")
    @ApiOperation("点评作业")
    @Override
    public JsonVO<Long> scoreHomework(@Validated @RequestBody HomeworkScoreDto homeworkScoreDto) {
        try {
            Long result = homeworkService.scoreHomework(homeworkScoreDto);
            if (result == null) {
                return JsonVO.fail("提交记录不存在");
            }
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }
}
