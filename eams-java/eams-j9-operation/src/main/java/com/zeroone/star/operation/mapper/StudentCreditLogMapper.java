package com.zeroone.star.operation.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.operation.entity.StudentCreditLogDO;
import com.zeroone.star.project.query.j9.operation.StudentCreditLogQuery;
import com.zeroone.star.project.vo.j9.operation.StudentCreditLogVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import org.apache.ibatis.annotations.Update;

/**
 * 学生积分变动记录 Mapper 接口
 */
@Mapper
public interface StudentCreditLogMapper extends BaseMapper<StudentCreditLogDO> {

    /**
     * 分页查询积分记录（关联学生姓名）
     * @param page 分页参数
     * @param condition 查询条件
     * @return 分页结果
     */
    Page<StudentCreditLogVO> selectCreditLogPage(Page<StudentCreditLogVO> page, @Param("condition") StudentCreditLogQuery condition);

    /**
     * 更新学生表中的当前积分
     * @param studentId 学生ID
     * @param credit 变动后的积分总额
     * @return 影响行数
     */
    @Update("UPDATE student SET credit = #{credit} WHERE id = #{studentId}")
    int updateStudentCredit(@Param("studentId") Long studentId, @Param("credit") Integer credit);
}
