package com.zeroone.star.student.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.dto.j4.student.ResponseDTO;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.entity.StudentCourse;
import org.springframework.web.multipart.MultipartFile;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import java.io.IOException;

/**
 * <p>
 * 学生表 服务类
 * </p>
 */
public interface IStudentService extends IService<Student> {

    /**
     * 导出全部意向学员
     */
    void exportIntentionStudent(HttpServletResponse response) throws Exception;
    /**
     * 导入意向学员 (含校验与双表操作)
     */
    void importIntentionStudent(MultipartFile file, HttpServletResponse response) throws Exception;

    /**
     * 修改学员顾问
     * @param studentDTO
     */
    Boolean modifyConsultant(StudentDTO studentDTO);

    /**
     * 导入在线学员
     * @param file
     * @return
     */
    Boolean importOnlineStudents(MultipartFile file) throws IOException;

    /**
     * 导出在线学员
     * @return
     */
    byte[] exportOnlineStudent(ServletOutputStream outputStream);

    /**
     * 保存学员（带业务校验）
     * @param student 学员实体
     * @return 保存是否成功
     */
    boolean saveStudent(Student student);

    /**
     * 获取学员课次数据
     * @param studentId 学员ID
     * @return 学员签约/课次实体
     */
    List<StudentCourse> listCourseTimesByStudentId(Long studentId);

    /**
     * 课时汇总列表（条件+分页）
     * 支持：学员ID、姓名、手机号查询
     * @param page 分页对象
     * @param query 查询条件
     * @return 分页结果
     */
    Page<StudentCourse> getLessonSummaryPage(Page<StudentCourse> page, StudentQuery query);

    PageDTO<ResponseDTO> listall(StudentQuery condition);

    PageDTO<StudentDTO> queryCourseStu(CourseQuery condition);

    /**
     * 分页查询班级列表
     */
    PageDTO<ClassDTO> queryClassPage(ClassQuery condition);

    /**
     * 加入班级
     */
    Long joinClass(ClassStudentDTO dto);

    /**
     * 退出班级
     */
    List<Long> quitClass(Long classId, Long studentId);

    PageDTO<FollowUpVO> queryFollowUpPage(FollowUpQuery condition);

    Long saveFollowUp(FollowUpDTO followUpDTO);

    Long removeFollowUp(Long id);

    FollowUpDTO getFollowUpDetail(Long id);

    /** 更新学员阶段，返回执行成败 */
    boolean updateStudentStage(StudentDTO studentDTO);

    /** 保存报名信息，返回执行成败 */
    boolean saveStudentEnroll(StudentEnrollDTO enrollDTO);

    /** 获取学员详情，返回原始数据对象 */
    StudentDTO getStudentDetail(Integer id);

}
