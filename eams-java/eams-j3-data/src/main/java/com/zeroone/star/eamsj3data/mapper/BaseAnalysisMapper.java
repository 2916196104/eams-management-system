package com.zeroone.star.eamsj3data.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.eamsj3data.entity.Student;
import com.zeroone.star.project.dto.j3.data.SalesFunnelDTO;
import com.zeroone.star.project.dto.j3.data.StudentAgeCompositionDTO;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 学员统计基础分析 Mapper 接口
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Mapper
public interface BaseAnalysisMapper extends BaseMapper<Student> {

    /**
     * 查询销售漏斗统计结果
     * @return 销售漏斗统计列表
     */
    List<SalesFunnelDTO> selectSalesFunnelStats();

    /**
     * 查询在学学员年龄构成
     * @return 年龄构成统计列表
     */
    List<StudentAgeCompositionDTO> selectStudentAgeComposition();
}
