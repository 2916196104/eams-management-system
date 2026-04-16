package com.zeroone.star.operation.controller;

import com.zeroone.star.operation.service.ICourseTrialService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CourseTrialDTO;
import com.zeroone.star.project.j9.operation.CourseTrialApis;
import com.zeroone.star.project.query.j9.operation.CourseTrialQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CourseTrialVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * 描述：试听卡前端控制器
 * @author paopao
 * @version 1.0.0
 */
@RestController
@RequestMapping("course-trial")
@Api(tags = "试听卡管理")
@Validated
public class CourseTrialController implements CourseTrialApis {

    @Resource
    private ICourseTrialService courseTrialService;

    @GetMapping
    @ApiOperation("获取试听卡列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<CourseTrialVO>> queryTrialList(@Validated CourseTrialQuery condition) {
        return JsonVO.success(courseTrialService.listCourseTrial(condition));
    }

    @GetMapping("/{id}")
    @ApiOperation("获取试听卡详情")
    @ApiImplicitParam(name = "id", value = "试听卡ID", required = true, example = "1", paramType = "path")
    @Override
    public JsonVO<CourseTrialVO> queryTrialDetail(@PathVariable Long id) {
        CourseTrialVO vo = courseTrialService.getCourseTrial(id);
        if (vo == null) {
            return JsonVO.fail("试听卡不存在");
        }
        return JsonVO.success(vo);
    }

    @PostMapping
    @ApiOperation("保存试听卡（新增或修改，有id则修改，无id则新增）")
    @Override
    public JsonVO<String> addCourseTrial(@Validated @RequestBody CourseTrialDTO dto) {
        boolean result = courseTrialService.saveCourseTrial(dto);
        return result ? JsonVO.success("保存成功") : JsonVO.fail("保存失败");
    }

    @DeleteMapping
    @ApiOperation("删除试听卡（支持批量删除）")
    @Override
    public JsonVO<String> removeCourseTrial(
            @ApiParam(value = "试听卡ID列表", required = true, example = "[1, 2, 3]")
            @RequestBody List<Long> ids) {
        List<Long> failIds = courseTrialService.removeCourseTrial(ids);
        return failIds.isEmpty() ? JsonVO.success("删除成功") : JsonVO.fail("部分删除失败，失败ID：" + failIds);
    }
}
