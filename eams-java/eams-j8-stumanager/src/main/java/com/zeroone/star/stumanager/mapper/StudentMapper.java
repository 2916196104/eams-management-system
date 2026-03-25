package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import com.zeroone.star.stumanager.entity.Student;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

import java.util.List;

/**
 * <p>
 * 学生表 Mapper 接口
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {

    /**
     * 分页获取学员列表
     */
    Page<StudentListVO> getList(Page<StudentListVO> page, @Param("query") StudentListQuery param);





}
