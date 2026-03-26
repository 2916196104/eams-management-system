package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ClassDTO;
import com.zeroone.star.project.dto.j4.student.ClassStudentDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;

import java.util.List;

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
}