package com.zeroone.star.project.j1.orgmanager.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.PositionDataPermissionDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;

import java.util.List;


/**
 * 职位数据权限管理模块
 */
public interface DataPermissionService extends IService<PositionDataPermissionDO> {


    PageDTO<PositionDataPermissionDTO> listAll (PositionDataPermissionQuery query);

}
