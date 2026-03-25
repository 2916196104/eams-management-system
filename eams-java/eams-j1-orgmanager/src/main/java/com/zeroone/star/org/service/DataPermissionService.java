package com.zeroone.star.org.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.Do.j1.PositionDataPermissionDO;
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
