package com.zeroone.star.project.j3.data;

import com.zeroone.star.project.dto.j3.data.SalesFunnelDTO;
import com.zeroone.star.project.dto.j3.data.StudentAgeCompositionDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述：学员统计基础分析接口声明
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
public interface BaseAnalysisApis {
    /**
     * 查询销售漏斗模型
     * @return 销售漏斗模型数据
     */
    JsonVO<List<SalesFunnelDTO>> querySalesFunnelModel();

    /**
     * 查询在学学员年龄构成
     * @return 在学学员年龄构成数据
     */
    JsonVO<List<StudentAgeCompositionDTO>> queryStudentAgeComposition();
}
