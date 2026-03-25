package com.zeroone.star.stumanager.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.stumanager.entity.Student;
import com.baomidou.mybatisplus.extension.service.IService;

/**
 * <p>
 * 学生表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IStudentService extends IService<Student> {
    /**
     * 分页查询学员列表
     */
    PageDTO<StudentListVO> listStudents(StudentListQuery query);
}
