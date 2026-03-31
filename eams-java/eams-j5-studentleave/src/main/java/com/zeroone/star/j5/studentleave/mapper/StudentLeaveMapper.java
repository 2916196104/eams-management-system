package com.zeroone.star.j5.studentleave.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.DO.j5.studentleave.StudentLeaveDO;
import com.zeroone.star.project.vo.j5.studentleave.StudentLeaveListVO;
import com.zeroone.star.project.query.j5.studentleave.StudentLeaveQuery;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * 学员请假 Mapper 接口
 * </p>
 *
 * @author xiaoke
 * @since 2026-03-22
 */
@Mapper
public interface StudentLeaveMapper extends BaseMapper<StudentLeaveDO> {

    /**
     * 分页查询学生请假列表
     * @param page
     * @param query
     * @return
     */
    Page<StudentLeaveListVO> selectPageStudentLeave(Page<StudentLeaveListVO> page, StudentLeaveQuery query);

}
