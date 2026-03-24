package com.zeroone.star.project.j1.org;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionSetDTO;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;


/**
 * 职位数据权限相关接口
 */
public interface PositionDataPermissionApis {

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



    /**
     * 分页查询数据权限信息
     * @param condition 分页条件
     * @return 数据权限信息
     */
    JsonVO<PageDTO<PositionDataPermissionDTO>> queryPage(PositionDataPermissionQuery condition);

    /**
     * 保存职位数据权限信息（新增/修改）
     * @param positionDataPermissionDTO 职位数据权限信息
     * @return 保存结果对应的id(新增则无)
     */
    JsonVO<Long> addPositionDataPermission(PositionDataPermissionDTO positionDataPermissionDTO);

    /**
     * 批量删除职位数据权限信息
     * @param ids 要删除的职位数据权限信息的id列表
     * @return 删除结果对应的id
     */
    JsonVO<List<Long>> removePositionDataPermission(List<Long> ids);
}
