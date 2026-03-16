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

/**
 * 学员接口实现类
 * 适配 PageQuery 为 long 基本类型的规范，解决类型判断错误
 */
@RestController
public class StudentController implements StudentApis {

    /**
     * 保存学员信息
     * @param dto 学员DTO（包含ID、姓名等基础信息）
     * @return 保存结果
     */
    @Override
    public JsonVO<String> saveStudent(StudentDTO dto) {
        // 安全处理：防止dto或字段为空导致NPE
        String studentId = (dto.getStudentId() == null) ? "未知ID" : dto.getStudentId();
        String studentName = (dto.getStudentName() == null) ? "未知姓名" : dto.getStudentName();
        return JsonVO.success(String.format("学员保存成功：ID=%s，姓名=%s", studentId, studentName));
    }

    /**
     * 查询学员课程次数
     * @param studentId 学员ID（字符串类型）
     * @return 学员课次详情
     */
    @Override
    public JsonVO<StudentDetailVO> queryCourseTimes(String studentId) {
        // 安全处理：防止studentId为空
        String targetStudentId = (studentId == null) ? "默认ID" : studentId;

        // 构造返回VO（给所有字段赋值，避免空对象序列化报错）
        StudentDetailVO vo = new StudentDetailVO();
        vo.setStudentId(targetStudentId);
        vo.setStudentName("测试学员");
        vo.setCourseTimes(20); // 课程次数（示例值）
        vo.setRemainingTimes(5); // 剩余次数（示例值）

        return JsonVO.success(vo);
    }

    /**
     * 分页查询学员课时汇总
     * @param query 查询条件（包含学员ID+分页参数）
     * @return 分页课时汇总数据
     */
    @Override
    public JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query) {
        // 1. 安全处理查询参数：PageQuery 是 long 基本类型，永远不会为 null
        // 直接使用 query 自带的 pageIndex/pageSize（已被 @Min 约束保证 ≥1）
        long pageIndex = query.getPageIndex();
        long pageSize = query.getPageSize();
        String studentId = (query.getStudentId() == null) ? "" : query.getStudentId();

        // 2. 构造课时汇总VO（给核心字段赋值）
        LessonSummaryVO summaryVO = new LessonSummaryVO();
        summaryVO.setStudentId(studentId);
        summaryVO.setTotalHour(15.5); // 总课时（示例值）
        summaryVO.setUsedHour(8.0);   // 已用课时（示例值）
        summaryVO.setRemainingHour(7.5); // 剩余课时（示例值）
        List<LessonSummaryVO> dataList = Collections.singletonList(summaryVO);

        // 3. 构造分页DTO（类型匹配，无需装箱）
        PageDTO<LessonSummaryVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(pageIndex);
        pageDTO.setPageSize(pageSize);
        pageDTO.setTotal(1L); // 总条数
        pageDTO.setPages(1L); // 总页数
        pageDTO.setRows(dataList); // 当前页数据

        // 4. 返回分页结果
        return JsonVO.success(pageDTO);
    }
}