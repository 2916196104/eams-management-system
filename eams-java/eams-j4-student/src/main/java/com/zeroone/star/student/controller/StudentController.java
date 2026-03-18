package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import org.springframework.web.bind.annotation.RestController;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.Collections;
import java.util.List;

@RestController
public class StudentController implements StudentApis {

    // 1. 保存学员（匹配前端真实参数+数据库字段）
    @Override
    public JsonVO<String> saveStudent(StudentDTO dto) {
        return JsonVO.success("学员保存成功：" + dto.getName());
    }

    // 2. 查询学员课程次数（匹配student_course表）
    @Override
    public JsonVO<StudentDetailVO> queryCourseTimes(String studentId) {
        StudentDetailVO vo = new StudentDetailVO();
        vo.setStudentId(studentId);
        vo.setStudentName("sdadadsdsadd");
        vo.setCountLessonTotal(20);
        vo.setCountLessonComplet(12);
        vo.setCountLessonRefund(2);
        vo.setRemainingTimes(6);
        vo.setStartDate(LocalDate.of(2025, 3, 1));
        vo.setExpireDate(LocalDate.of(2026, 3, 1));
        vo.setCourseAmount(new BigDecimal("2000.00"));
        vo.setPaidAmount(new BigDecimal("1800.00"));
        return JsonVO.success(vo);
    }

    // 3. 分页查询课时汇总（匹配lesson_student表+前端分页参数）
    @Override
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 构造课时汇总数据
        LessonSummaryVO summary = new LessonSummaryVO();
        summary.setId(1L);
        summary.setLessonId(1001L);
        summary.setClassId(2001);
        summary.setStudentId(query.getStudentId());
        summary.setName(query.getName());
        summary.setMobile(query.getMobile());
        summary.setDecLessonCount(1);
        summary.setLessonCount(10);
        summary.setSignType(1);
        summary.setSignState(1);

        List<LessonSummaryVO> rows = Collections.singletonList(summary);

        // 构造分页对象
        PageDTO<LessonSummaryVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex((long) query.getPageIndex());
        pageDTO.setPageSize((long) query.getPageSize());
        pageDTO.setTotal(1L);
        pageDTO.setPages(1L);
        pageDTO.setRows(rows);

        return JsonVO.success(pageDTO);
    }
}