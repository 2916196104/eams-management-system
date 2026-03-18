package com.zeroone.star.project.j1.orgmanager;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionSetDTO;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述：职位管理接口
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
public interface PositionApis {
    /**
     * 职位列表
     *
     * @param condition 查询条件
     * @return 职位分页列表
     */
    JsonVO<PageDTO<PositionDTO>> list(PositionQueryCondition condition);

    /**
     * 创建和修改职位
     *
     * @param dto 职位数据对象
     * @return 操作结果
     */
    JsonVO<String> save(PositionDTO dto);

    /**
     * 删除职位
     *
     * @param ids 职位ID列表
     * @return 操作结果
     */
    JsonVO<String> delete(List<Long> ids);

    /**
     * 设置员工职位
     *
     * @param dto 设置员工职位对象
     * @return 操作结果
     */
    JsonVO<String> setStaffPosition(PositionSetDTO dto);
}
