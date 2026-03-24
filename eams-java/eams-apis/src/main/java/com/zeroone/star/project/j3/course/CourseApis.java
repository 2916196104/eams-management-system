package com.zeroone.star.project.j3.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.AddCourseDTO;
import com.zeroone.star.project.dto.j3.course.SubjectDTO;
import com.zeroone.star.project.query.j3.course.CourseListQuery;
import com.zeroone.star.project.query.j3.course.SubjectQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.course.CourseDetailVO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;


import javax.validation.constraints.NotEmpty;
import java.util.List;

/**
 * <p>
 * 描述：课程模块Api
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
public interface CourseApis {
    // 1. 获取课程列表（条件 + 分页）
    JsonVO<PageDTO<CourseListVO>> queryCourseList(CourseListQuery courseListQuery);

    //2. 获取课程详情
    JsonVO<CourseDetailVO> queryCourseDetail(Long courseId);

    //3. 保存课程
    JsonVO<String> addCourse(AddCourseDTO addCourseDTO);

    //4. 删除课程（支持批量删除）
    JsonVO<String> deleteCourses(List<String> courseIds);
    /**
     * 获取科目列表（条件 + 分页)
     * @param courseListQuery 查询参数
     * @return 查询结果
     */
    JsonVO<PageDTO<SubjectDTO>> querySubjectList(SubjectQuery courseListQuery);
    /**
     * 查询科目名称列表
     * @return 查询结果
     */
    JsonVO<List<String>> querySubjectNames();
    /**
     * 保存科目数据
     * @param subjectDto 科目数据
     */
    JsonVO<String> saveSubject(SubjectDTO subjectDto);
    /**
     * 删除科目(支持批量删除)
     * @param subjectIds 科目id列表
     */
    JsonVO<String> deleteSubjects( @NotEmpty(message = "列表不能为空") List<String> subjectIds);
}

