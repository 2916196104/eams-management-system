package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.query.j4.student.*;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.vo.j4.student.StudentDetailVO;
import com.zeroone.star.project.vo.j4.student.LessonSummaryVO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;


@Api(tags = "Student Course Interface")


public interface StudentApis {
    /**
     * 获取跟进记录列表（条件+分页）
     * GET /j4/student/follow-up/page
     */
    JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(FollowUpQuery condition);

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

    /**
     * 导出在线学员
     */
    ResponseEntity<byte[]> exportOnlineStudents();

    @ApiOperation("Save student information")
    @PostMapping("/student/save-student")
    JsonVO<String> saveStudent(@RequestBody StudentDTO dto);

    @ApiOperation("Query student course times")
    @GetMapping("/student/query-course-times")
    JsonVO<StudentDetailVO> queryCourseTimes(@RequestParam String studentId);

    @ApiOperation("List hour summary with condition and pagination")
    @PostMapping("/student/list-hour-summary")
    JsonVO<PageDTO<LessonSummaryVO>> listHourSummary(@RequestBody StudentQuery query);

    JsonVO<PageDTO<ResponseDTO>> queryCourseStudent(CourseQuery condition);

    JsonVO<PageDTO<ResponseDTO>> listAllStudent(StudentQuery condition);

}