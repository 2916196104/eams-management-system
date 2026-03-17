package com.zeroone.star.interact.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkRecordDTO;
import com.zeroone.star.project.j6.interact.HomeworkApis;
import com.zeroone.star.project.query.j6.interact.HomeworkRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
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
     * 删除作业(支持批量删除)
     *
     * @param ids 作业ID列表
     * @return 删除结果
     */
    @Override
    @ApiOperation("删除作业(支持批量删除)")
    @DeleteMapping
    public JsonVO<List<Long>> deleteHomework(@RequestBody List<Long> ids) {

        return null;
    }

    @GetMapping
    @ApiOperation("分页查询作业提交列表")
    @Override
    public JsonVO<PageDTO<HomeworkRecordDTO>> queryPage(HomeworkRecordQuery condition) {
        return null;
    }
}
