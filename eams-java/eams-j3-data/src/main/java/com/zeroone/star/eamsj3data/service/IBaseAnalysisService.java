package com.zeroone.star.eamsj3data.service;

import com.zeroone.star.project.dto.j3.data.SalesFunnelDTO;
import com.zeroone.star.project.dto.j3.data.StudentAgeCompositionDTO;

import java.util.List;

/**
 * <p>
 * 学员统计基础分析服务接口
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
public interface IBaseAnalysisService {

    /**
     * 获取销售漏斗统计
     * @return 销售漏斗模型数据
     */
    List<SalesFunnelDTO> getSalesFunnelStats();

    /**
     * 获取在学学员年龄构成
     * @return 在学学员年龄构成数据
     */
    List<StudentAgeCompositionDTO> getStudentAgeComposition();
}
