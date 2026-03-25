package com.zeroone.star.student.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ClassDTO;
import com.zeroone.star.project.dto.j4.student.ClassStudentDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;

import java.util.List;

/**
 * 学员管理 Service 接口
 */
public interface IStudentService {

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