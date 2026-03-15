package com.zeroone.star.student.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collections;
import java.util.List;

@RestController
public class StudentController implements StudentApis {

    // 1. 保存学员：测试返回成功
    @Override
    public JsonVO<String> saveStudent(StudentDTO dto) {
        return JsonVO.success("学员保存成功：" + dto.getStudentName());
    }

    // 2. 获取学员课次数据：返回测试 StudentDetailVO
    @Override
    public JsonVO<StudentDetailVO> queryCourseTimes(String studentId) {
        StudentDetailVO vo = new StudentDetailVO();
        vo.setStudentId(studentId);
        vo.setStudentName("测试学员");
        return JsonVO.success(vo);
    }

    // 3. 获取课时汇总列表：适配PageDTO的真实字段（rows/total/pages等）
    @Override
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 1. 构造课时汇总测试数据
        LessonSummaryVO summary = new LessonSummaryVO();
        List<LessonSummaryVO> rows = Collections.singletonList(summary); // 对应PageDTO的rows字段

        // 2. 构造分页对象（严格匹配你们的PageDTO字段）
        PageDTO<LessonSummaryVO> pageDTO = new PageDTO<>();
        // 注意：PageDTO的pageIndex/pageSize是Long类型，需要转换
        pageDTO.setPageIndex(Long.valueOf(query.getPageIndex()));
        pageDTO.setPageSize(Long.valueOf(query.getPageSize()));
        pageDTO.setTotal(1L); // 总条数
        pageDTO.setPages(1L); // 总页数
        pageDTO.setRows(rows); // 当前页数据列表

        // 3. 返回分页数据
        return JsonVO.success(pageDTO);
    }
}