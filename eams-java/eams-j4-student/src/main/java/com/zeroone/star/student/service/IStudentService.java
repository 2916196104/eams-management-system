package com.zeroone.star.student.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.*;
import com.zeroone.star.project.dto.j4.student.ResponseDTO;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.CourseQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.student.entity.Student;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.util.List;

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
    Boolean importOnlineStudents(MultipartFile file);

    /**
     * 导出在线学员
     * @return
     */
    byte[] exportOnlineStudent();

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

    PageDTO<FollowUpDTO> queryFollowUpPage(FollowUpQuery condition);

    Long saveFollowUp(FollowUpDTO followUpDTO);

    Long removeFollowUp(Long id);

    FollowUpDTO getFollowUpDetail(Long id);
}
