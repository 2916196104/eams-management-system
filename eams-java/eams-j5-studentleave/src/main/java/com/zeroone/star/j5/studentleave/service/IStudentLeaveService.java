package com.zeroone.star.j5.studentleave.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.j5.studentleave.StudentLeaveDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.studentleave.StudentLeaveListDTO;
import com.zeroone.star.project.query.j5.studentleave.StudentLeaveQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 学员请假 服务类
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-22
 */
public interface IStudentLeaveService extends IService<StudentLeaveDO> {

    PageDTO<StudentLeaveListDTO> listStudentLeave(StudentLeaveQuery studentLeaveQuery);

    JsonVO<Integer> cancelLeaveRequest(List<Long> ids);
}
