package com.homework.eamsj3class.controller;

import com.baomidou.mybatisplus.extension.plugins.pagination.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import com.zeroone.star.project.j3.course.CourseLinkApis;
import com.zeroone.star.project.query.j3.course.CourseLinkQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;


/**
 * <p>
 * 描述：关联课程接口实现
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author j3组 KINGHOG
 * @version 1.0.0
 **/
@RestController
@RequestMapping("j3/cl")
@Api(tags = "关联课程")
public class CourseLinkController implements CourseLinkApis {
    @GetMapping
    @ApiOperation("获取关联课程列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<CourseLinkDTO>> queryPage(CourseLinkQuery condition) {
        return null;
    }
    @PostMapping
    @ApiOperation("添加关联课程（支持多选）")
    @Override
    public JsonVO<Long> saveCourseLink(CourseLinkDTO courseLinkDTO) {
        return null;
    }
    @DeleteMapping
    @ApiOperation("移除关联课程（支持多选）")
    @ApiImplicitParam(name = "ids", value = "关联课程id列表",type="Array",paramType = "body",required = true,example = "[\"1\",\"2\"]")
    @Override
    public JsonVO<List<Long>> deleteCourseLink(@RequestBody List<Long> ids) {
        return null;
    }
}
