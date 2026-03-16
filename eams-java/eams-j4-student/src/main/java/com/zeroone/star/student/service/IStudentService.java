package com.zeroone.star.student.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.student.domain.po.Student;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;

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
}
