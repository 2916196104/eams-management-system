package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j8.stumanager.common.StuClassQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;
import com.zeroone.star.stumanager.entity.Class;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 班级 Mapper 接口
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Mapper
public interface ClassMapper extends BaseMapper<Class> {
    IPage<StuClassVO> selectStuClassByPage(IPage<StuClassVO> page, @Param("query") StuClassQuery stuClassQuery);

    IPage<ClassScheduleVO> selectClassScheduleByPage(IPage<ClassScheduleVO> pages, @Param("query") StuClassQuery stuClassQuery);
}
