package com.zeroone.star.j7.interaction.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j7.interaction.entity.Homework;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * homework 表的 Mapper 接口
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Mapper
public interface HomeworkMapper extends BaseMapper<Homework> {

    /**
     * 分页查询作业列表（含班级名称、教师姓名、完成人数、是否已完成）
     * @param page 分页参数
     * @param query 查询条件
     * @param studentId 当前登录学生 ID（用于判断是否已提交）
     * @return 作业 VO 列表
     */
    IPage<HomeworkVO> selectHomeworkPage(Page<?> page, @Param("query") HomeworkListQuery query, @Param("studentId") Long studentId);

    /**
     * 查询作业详情（含班级名称、教师姓名）
     * @param id 作业ID
     * @return 作业 VO
     */
    HomeworkVO selectHomeworkDetail(@Param("id") Long id);
}
