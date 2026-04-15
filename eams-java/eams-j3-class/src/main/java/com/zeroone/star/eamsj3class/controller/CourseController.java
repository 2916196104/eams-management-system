package com.zeroone.star.eamsj3class.controller;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.StringUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.eamsj3class.entity.*;
import com.zeroone.star.eamsj3class.service.*;
import com.zeroone.star.eamsj3class.utils.CourseUtils;
import com.zeroone.star.eamsj3class.utils.PageTmpParam;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.j3.course.CourseApis;
import com.zeroone.star.project.query.j3.course.CourseListQuery;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j3.course.CourseDetailVO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.apache.commons.lang.BooleanUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * <p>
 * 描述：课程controller
 * </p>
 * @author fish
 * @version 1.0.0
 */
@RestController
@RequestMapping("/j3-course")
@Api(tags = "课程管理")
@Validated
public class CourseController implements CourseApis {

    @Resource
    private ISubjectService subjectService;

    @Resource
    private ICourseService courseService;

    @Resource
    private ICourseImageService courseImageService;

    @Resource
    private ICourseLinkService courseLinkService;

    @Resource
    private IShopOrderItemService shopOrderItemService;



    @GetMapping("/query-courses-list")
    @ApiOperation("获取课程列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery) {
        if(courseListQuery == null){
            return JsonVO.fail("参数错误");
        }
        try{
            Page<Course> page = new Page<>(courseListQuery.getPageIndex(), courseListQuery.getPageSize());
            Page<Course> pageResult = courseService.page(page,
                    new LambdaQueryWrapper<Course>()
                            .like(StringUtils.isNotBlank(courseListQuery.getName()), Course::getName, courseListQuery.getName())
                            .like(courseListQuery.getSubjectId() != null, Course::getSubjectId, courseListQuery.getSubjectId())
                            .like(courseListQuery.getGradeId() != null, Course::getGradeIds, courseListQuery.getGradeId())
                            .eq(BooleanUtils.isTrue(courseListQuery.getState()), Course::getState, courseListQuery.getState())
                            .eq(Course::getDeleted, 0)
            );
            PageDTO<CourseListVO> result = new PageDTO<>();
            result.setTotal(0L);
            result.setPageIndex(courseListQuery.getPageIndex());
            result.setPageSize(courseListQuery.getPageSize());
            result.setPages((pageResult.getTotal() + page.getSize() - 1) / page.getSize());
            if(pageResult.getTotal() == 0){
                return JsonVO.success(result);
            }
            // 补充数据
            List<Course> coursesRecords = pageResult.getRecords();
            // 得到科目名称map
            List<String> subjectIds = coursesRecords.stream()
                    .map(course -> course.getSubjectId().toString())
                    .collect(Collectors.toList());
            List<Subject> subjects = subjectService.list(new LambdaQueryWrapper<Subject>().in(Subject::getId, subjectIds));
            Map<Long, String> subjectMap = subjects.stream()
                    .collect(Collectors.toMap(
                            subject -> subject.getId(),
                            subject -> subject.getName()
                    ));
            // 得到关联数
            List<Long> courseIds = coursesRecords.stream()
                    .map(course -> course.getId())
                    .collect(Collectors.toList());
            List<CourseLink> courseLinks = courseLinkService.getCourseLinks(courseIds);
            Map<Long, Integer> linkCountMap = courseLinks.stream()
                    .collect(Collectors.groupingBy(
                            CourseLink::getCourseId,
                            Collectors.summingInt(e -> 1)  // 每个元素计数为1
                    ));
            // 销售额
            List<ShopOrderItem> shopOrderItems = shopOrderItemService.list(new LambdaQueryWrapper<ShopOrderItem>().in(ShopOrderItem::getItemId, courseIds));
            //  销售量 Integer saleCount;
            Map<Long, Integer> saleCountMap = new HashMap<>();
            //  销售额 Integer saleAmount;
            Map<Long, BigDecimal> saleAmountMap = new HashMap<>();
            for (ShopOrderItem shopOrderItem : shopOrderItems) {
                Integer saleCountTotal = 0;
                BigDecimal saleAmountTotal = BigDecimal.ZERO.setScale(2, BigDecimal.ROUND_HALF_UP);
                if(saleCountMap.containsKey(shopOrderItem.getItemId())){
                    saleCountTotal = saleCountMap.get(shopOrderItem.getItemId());
                    saleAmountTotal = saleAmountMap.get(shopOrderItem.getItemId());
                }
                saleCountMap.put(shopOrderItem.getItemId(), saleCountTotal + shopOrderItem.getQuantity());
                saleAmountMap.put(shopOrderItem.getItemId(), saleAmountTotal.add(shopOrderItem.getPrice()));
            }
            return JsonVO.success(CourseUtils.getPageDTOCourseListVO(new PageTmpParam(
                    coursesRecords, subjectMap, linkCountMap, saleCountMap, saleAmountMap,
                    page.getCurrent(), page.getSize(), (pageResult.getTotal() + page.getSize() - 1) / page.getSize()
            )));
        }catch (Exception e){
            e.printStackTrace();
            return JsonVO.create(null, ResultStatus.FAIL.getCode(),"查询失败");
        }

    }



    @GetMapping("/query-one-course/{courseId}")
    @Override
    @ApiOperation("获取课程详情")
    public JsonVO<CourseDetailVO> queryCourseDetail(@PathVariable Long courseId) {
        // 异常处理
        if(courseId == null || courseId <= 0){
            return JsonVO.fail("参数错误");
        }
        try{
            // 查询结果
            CourseDetailVO courseDetailVO = new CourseDetailVO();
            Course course = courseService.list(
                    new LambdaQueryWrapper<Course>()
                            .eq(Course::getDeleted, 0)
                            .eq(Course::getId, courseId)
            ).get(0);
            BeanUtils.copyProperties(course, courseDetailVO);
            // 手动再添加一些数据
            // 科目名称
            courseDetailVO.setSubjectName(subjectService.getById(course.getSubjectId()).getName());
            // salary
            courseDetailVO.setSalary(course.getSalary().toString());
            // price
            courseDetailVO.setPrice(course.getPrice().toString());
            // closeDate
            courseDetailVO.setCloseDate(course.getCloseDate().toString());
            if(course != null){
                List<CourseImage> list = courseImageService.list(
                        new LambdaQueryWrapper<CourseImage>()
                                .eq(CourseImage::getDeleted, 0)
                                .eq(CourseImage::getCourseId, courseId)
                );
                if(list != null && list.size() > 0){
                    CourseImage courseImage = list.get(0);
                    if(courseImage != null){
                        courseDetailVO.setImages(courseImage.getImageUrl());
                    }
                }
            }


            return JsonVO.success(courseDetailVO);
        }catch (Exception e){
            return JsonVO.fail("查询失败");
        }
    }

    @PostMapping("/add-course")
    @ApiOperation("保存课程")
    @Override
    public JsonVO<String> addCourse(@RequestBody AddCourseDTO addCourseDTO) {
        // 参数校验
        if(addCourseDTO == null){
            return JsonVO.fail("参数错误");
        }
        return courseService.addCourse(addCourseDTO);
    }

    @DeleteMapping("/delete-courses")
    @Override
    @ApiOperation("删除课程（支持批量删除）")
    public JsonVO<String> deleteCourses(@RequestBody List<String> courseIds) {
        try{
            List<Course> courses = new ArrayList<>();
            for (String courseId : courseIds) {
                Course course = new Course();
                course.setId(Long.parseLong(courseId));
                course.setDeleted(true);
                courses.add(course);
            }
            courseService.updateBatchById(courses);
            return JsonVO.success("删除成功");
        }catch (Exception e){
            return JsonVO.fail("删除失败");
        }
    }

    @GetMapping("query-subject-list")
    @Override
    @ApiOperation("获取科目列表（条件 + 分页）")
    public JsonVO<PageDTO<SubjectDTO>> querySubjectList(@Validated SubjectQuery courseListQuery) {
        return JsonVO.success(subjectService.querySubjectList(courseListQuery));
    }

    @GetMapping("query-subject-names")
    @ApiOperation(value = "查询科目名称列表")
    @Override
    public JsonVO<List<String>> querySubjectNames() {
        return JsonVO.success(subjectService.querySubjectNames());
    }

    @PutMapping("save-subject")
    @ApiOperation(value = "保存科目")
    @Override
    public JsonVO<String> saveSubject(@Validated @RequestBody SubjectDTO subjectDto) {
        return subjectService.saveSubject(subjectDto) ? JsonVO.success("保存成功") : JsonVO.fail("保存失败");
    }


    @DeleteMapping("delete-subject")
    @ApiOperation(value = "删除科目(支持批量删除)")
    @ApiImplicitParam(
            name = "subjectIds",
            value = "编号列表",
            required = true,
            dataType = "List",
            paramType = "body",
            example = "[\"1\",\"2\"]"
    )
    @Override
    public JsonVO<String> deleteSubjects(
            @ApiParam(value = "编号列表", required = true)
            @RequestBody
            List<String> subjectIds) {
        return subjectService.deleteSubjects(subjectIds) ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }


}
