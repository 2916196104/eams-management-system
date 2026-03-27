package com.zeroone.star.j5.classmanager.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.DO.j5.classmanager.ClassStudentDO;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ClassStudentMapper extends BaseMapper<ClassStudentDO> {
    /**
     * 分页查询班级学生（关联学生表）
     * @param page 分页对象
     * @param classId 班级ID
     * @param query 查询参数
     * @return 分页结果
     */
    IPage<ClassStudentVO> selectClassStudentPage(Page<?> page,
                                                 @Param("classId") Long classId,
                                                 @Param("query") ClassStudentQuery query);
}
