package com.zeroone.star.project.j1.orgmanager.service;

import com.zeroone.star.project.dto.j1.orgmanager.PositionSetDTO;

/**
 * <p>
 * 描述：员工组织信息业务层接口
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
public interface IStaffOrgInfoService {
    boolean setStaffPosition(PositionSetDTO dto);
}
