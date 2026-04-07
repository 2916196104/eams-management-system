package com.zeroone.star.eamsj3class.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.eamsj3class.service.ICourseLinkService;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import com.zeroone.star.project.j3.course.CourseLinkApis;
import com.zeroone.star.project.query.j3.course.CourseLinkQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 课程关联表 前端控制器
 * </p>
 *
 * @author j3-class-kinghog
 * @since 2026-03-25
 */
@RestController
@RequestMapping("j3-course")
@Api(tags = "关联课程")
public class CourseLinkController implements CourseLinkApis {
    @Resource
    ICourseLinkService service;

    @GetMapping
    @ApiOperation("获取关联课程列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<CourseLinkDTO>> queryPage(CourseLinkQuery condition) {
        PageDTO<CourseLinkDTO> page = service.listAll(condition);
        return JsonVO.success(page);
    }
    @PostMapping("/add-courselink")
    @ApiOperation("添加关联课程（支持多选）")
    @Override
    public JsonVO<Long> saveCourseLink(CourseLinkDTO courseLinkDTO) {
        Long sum=service.add(courseLinkDTO);
        if(sum>0){
            return JsonVO.success(sum);
        }
        return JsonVO.fail("新增失败：参数不完整、重复关联或业务校验未通过");
    }
    @DeleteMapping
    @ApiOperation("移除关联课程（支持多选）")
    @ApiImplicitParam(name = "ids", value = "关联课程id列表",type="Array",paramType = "body",required = true,example = "[\"1\",\"2\"]")
    @Override
    public JsonVO<List<Long>> deleteCourseLink(@RequestBody List<Long> ids) {
        List<Long> deletedIds = service.delete(ids);
        if (deletedIds == null || deletedIds.isEmpty()) {
            return JsonVO.fail("删除失败：请求id为空或记录不存在");
        }
        return JsonVO.success(deletedIds);
    }
}


