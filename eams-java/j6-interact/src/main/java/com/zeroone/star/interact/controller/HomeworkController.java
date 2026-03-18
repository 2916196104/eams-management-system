package com.zeroone.star.interact.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.j6.interact.HomeworkApis;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkSubmissionListVo;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
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
@RequestMapping("/j6/homework")
@Api(tags = "课后作业")
public class HomeworkController implements HomeworkApis {


    /**
     * 获取作业列表（条件+分页）
     *
     * @param homeworkQuery
     */
    @GetMapping("/list")
    @ApiOperation("获取作业列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<HomeworkListDto>> queryHomeworkList(HomeworkQuery homeworkQuery) {
        return null;
    }

    /**
     * 获取作业详情
     *
     * @param id
     */
    @GetMapping("/{id}")
    @ApiOperation("获取作业详情")
    @Override
    public JsonVO<HomeworkDetailDto> homeworkDetails(@PathVariable("id")Long id) {
        return null;
    }

    /**
     * 保存作业,新增和编辑作业是调用这个接口
     *
     * @param homeworkDetailDto 作业
     */
    @PostMapping
    @ApiOperation(" 保存作业")
    @Override
    public JsonVO<HomeworkDetailDto> saveHomework(@RequestBody HomeworkDetailDto homeworkDetailDto) {
        return null;
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
        return null;
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
        return null;
    }

    /**
     * 点评作业
     *
     * @param id
     */
    @PutMapping("/{id}")
    @ApiOperation("点评作业")
    @Override
    public JsonVO<Long> scoreHomework(@PathVariable("id") Long id) {
        return null;
    }
}
