package com.zeroone.star.course.controller;

import com.zeroone.star.course.service.IRelatedCourseService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseDTO;
import com.zeroone.star.project.dto.j9.course.CourseLinkDTO;
import com.zeroone.star.project.j9.course.RelatedCourseApis;
import com.zeroone.star.project.query.j9.course.CourseLinkPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;
import lombok.extern.slf4j.Slf4j;

import javax.annotation.Resource;
import java.util.List;


/**
 * 关联课程接口实现
 */
@Slf4j
@Api(tags = "关联课程")
@RestController
@RequestMapping("course/link")
public class RelatedCourseController implements RelatedCourseApis {

    @Resource
    private IRelatedCourseService relatedCourseService;

    @ApiOperation("获取关联课程列表")
    @Override
    @GetMapping
    public JsonVO<PageDTO<CourseLinkDTO>> queryPage(CourseLinkPageQuery condition) {
        PageDTO<CourseLinkDTO> result = relatedCourseService.listPage(condition);
        return JsonVO.success(result);
    }

    @PostMapping
    @ApiOperation("新增关联课程")
    @Override
    public JsonVO<Long> addCourseLink(@ApiParam(value = "课程ID", required = true, example = "1001") @RequestParam("courseId") Long courseId, @ApiParam(value = "关联课程ID列表", required = true, example = "[102,103,104]") @RequestParam("linkedCourseIds") List<Long> linkedCourseIds) {
        Long result = relatedCourseService.saveCourseLink(courseId, linkedCourseIds);
        return JsonVO.success(result);
    }

    @DeleteMapping
    @ApiOperation("删除关联课程")
    @Override
    public JsonVO<?> removeCourseLink(@ApiParam(value = "课程ID", required = true, example = "101") @RequestParam("courseId") Long courseId, @ApiParam(value = "关联课程ID列表", required = true, example = "[102,103,104]") @RequestParam("linkedCourseIds") List<Long> linkedCourseIds) {
        List<Long> deletedIds = relatedCourseService.removeCourseLink(courseId, linkedCourseIds);
        
        // 构建详细的返回结果
        java.util.Map<String, Object> result = new java.util.HashMap<>();
        result.put("deletedIds", deletedIds);
        
        // 计算未删除的ID
        java.util.List<Long> notDeletedIds = new java.util.ArrayList<>();
        boolean hasSelfLink = false;
        for (Long linkedId : linkedCourseIds) {
            if (!deletedIds.contains(linkedId)) {
                notDeletedIds.add(linkedId);
                if (courseId.equals(linkedId)) {
                    hasSelfLink = true;
                }
            }
        }
        result.put("notDeletedIds", notDeletedIds);
        
        // 根据删除结果返回不同的消息
        if (deletedIds.isEmpty()) {
            if (hasSelfLink) {
                return JsonVO.fail("操作失败, 不能关联自身"+ result);
            } else {
                return JsonVO.fail("操作失败, 所有课程不存在关联关系"+ result);
            }
        } else if (!notDeletedIds.isEmpty()) {
            return JsonVO.success("部分课程删除成功，部分课程不存在关联关系" + result);
        } else {
            return JsonVO.success("所有课程删除成功"+ result);
        }
    }
}
