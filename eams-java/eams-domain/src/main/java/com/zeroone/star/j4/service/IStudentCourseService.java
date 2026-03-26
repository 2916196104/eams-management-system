package com.zeroone.star.j4.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j4.entity.StudentCourse;
import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j4.student.EnrollmentDTO;

/**
 * 学员课程服务接口（报名记录）
 */
public interface IStudentCourseService extends IService<StudentCourse> {


    /**
     * 分页查询报名记录
     * @param extendPageDTO 分页参数（包含pageIndex、pageSize）
     * @return 分页结果
     */
    IPage<EnrollmentDTO> getEnrollmentList(ExtendPageDTO extendPageDTO);
}
