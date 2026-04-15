package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.query.j4.student.*;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.dto.j4.student.FinanceDTO;
import com.zeroone.star.project.query.j4.student.FinanceQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.*;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;

import java.util.List;

import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;

@Api(tags = "Student Course Interface")


public interface StudentApis {
    /**
     * 获取跟进记录列表（条件+分页）
     * GET /j4/student/follow-up/page
     */
    JsonVO<PageDTO<FollowUpVO>> queryFollowUpPage(FollowUpQuery condition);

    /**
     * 添加跟进记录
     * POST /j4/student/follow-up
     * 如果 DTO 中有 ID 则更新，无 ID 则新增
     */
    JsonVO<Long> saveFollowUp(FollowUpDTO followUpDTO);

    /**
     * 删除跟进记录
     * DELETE /j4/student/follow-up/{id}
     * @param id 跟进记录ID
     * @return 删除成功的ID
     */
    JsonVO<Long> deleteFollowUp(Long id);

    /**
     * 获取跟进记录详情 (用于编辑前回填)
     * GET /j4/student/follow-up/{id}
     */
    JsonVO<FollowUpDTO> getFollowUpDetail(Long id);

    /**
     * 获取班级列表（条件+分页）
     * 对应原型图：所在班级列表
     */
    JsonVO<PageDTO<ClassDTO>> queryClassPage(ClassQuery condition);

    /**
     * 加入班级
     * 对应原型图：给班级添加学员 -> 提交
     */
    JsonVO<Long> joinClass(ClassStudentDTO dto);

    /**
     * 退出班级
     * 对应原型图：所在班级列表 -> 操作列 -> 退出班级
     */
    JsonVO<List<Long>> quitClass(Long classId, Long studentId);
    /**
     * 获取消课记录（条件+分页）
     * 查询对应学员的消课记录
     * @return 分页的消课记录
     * @author MRME39
     */
    JsonVO<PageDTO<LessonCountDTO>> queryOmyLessonCount(String StudentID);

    /**
     * 获取积分记录（条件+分页）
     * 查询条件下的积分记录
     * @return 分页的积分记录
     * @author MRME39
     */
    JsonVO<PageDTO<CreditLogDTO>> queryCreditLog(CreditSelectQuery creditSelectQuery);

    /**
     * 调整积分
     * @author MRME39
     */
    JsonVO<Long> saveCreditLog(ChangeCreditQuery changeCreditDTO);

    /**
     * 修改顾问
     * @param studentDTO
     * @return
     */
    JsonVO<String> modifyConsultant(StudentDTO studentDTO);

    /**
     * 导入在线学员
     */
    JsonVO<String> importOnlineStudents(MultipartFile file);


    @ApiOperation("保存学员")
    @PostMapping("/student/save-student")
    JsonVO<String> saveStudent(@RequestBody StudentDTO dto);

    @ApiOperation("获取学员课次数据")
    @GetMapping("/student/query-course-times")
    JsonVO<List<StudentDetailVO>> queryCourseTimes(@RequestParam String studentId);

    // 改成这样（去掉 @RequestBody）：
    @GetMapping("/list-hour-summary")
    @ApiOperation(value = "获取课时汇总列表")


    JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(StudentQuery query);

    JsonVO<PageDTO<StudentDTO>> queryCourseStudent(CourseQuery condition);

    JsonVO<PageDTO<ResponseDTO>> listAllStudent(StudentQuery condition);


    @ApiOperation("修改学员头像")
    JsonVO<String> updateStudentAvatar(StudentDTO studentDTO);

    @ApiOperation("分页查询报名记录")
    JsonVO<PageDTO<EnrollmentDTO>> queryEnrollRecords(EnrollQuery query);

    @ApiOperation("获取报名记录详情")
    JsonVO<EnrollmentDTO> getEnrollRecord(Long id);
    /**
     * 分页查询缴欠费与退费记录。
     *
     * @param query 查询条件
     * @return 分页结果
     */
    JsonVO<PageDTO<FinanceDTO>> queryFinancePage(FinanceQuery query);

    /**
     * 办理缴欠费。
     *
     * @param financeDTO 缴费参数
     * @return 缴费结果
     */
    JsonVO<FinanceDTO> payDebt(FinanceDTO financeDTO);

    /**
     * 发起退费申请。
     *
     * @param financeDTO 退费参数
     * @return 退费申请结果
     */
    JsonVO<FinanceDTO> applyRefund(FinanceDTO financeDTO);

    /**
     * 审核退费申请。
     *
     * @param financeDTO 审核参数
     * @return 审核结果
     */
    JsonVO<FinanceDTO> auditRefund(FinanceDTO financeDTO);

    /**
     * 完成退费。
     *
     * @param financeDTO 办结参数
     * @return 办结结果
     */
    JsonVO<FinanceDTO> completeRefund(FinanceDTO financeDTO);

    /**
     * 获取课程统计
     * @param studentQuery
     * @return 课程统计
     */
    JsonVO<PageDTO<CourseCounterVO>> getCourseCounter(StudentQuery studentQuery);

    /**
     * 获取课表
     * @param studentQuery
     * @return 课表列表
     */
    JsonVO<List<StudentScheduleVO>> getStudentSchedule(StudentQuery studentQuery);
}