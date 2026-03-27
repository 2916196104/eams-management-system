package com.zeroone.star.j4.service;

import com.zeroone.star.j4.entity.Student;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j4.student.StudentDTO;

/**
 * <p>
 * 学员基础信息表 服务类
 * </p>
 *
 * @author alid
 * @since 2026-03-21
 */
public interface IStudentService extends IService<Student> {

    /**
     * 修改学员头像
     * @param studentId 学员ID
     * @param headImgUrl 头像URL
     * @return 是否修改成功
     */
    boolean updateHeadImg(Long studentId, String headImgUrl);

    /**
     * 根据ID获取学员信息（转换为DTO）
     * @param studentId 学员ID
     * @return 学员DTO
     */
    StudentDTO getStudentById(Long studentId);

}
