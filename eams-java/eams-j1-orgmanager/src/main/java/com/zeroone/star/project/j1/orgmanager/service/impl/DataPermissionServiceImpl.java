package com.zeroone.star.project.j1.orgmanager.service.impl;

import com.alibaba.excel.util.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.DO.PositionDataPermissionDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.PositionDataPermissionDTO;
import com.zeroone.star.project.j1.orgmanager.mapper.position.DataPermissionMapper;
import com.zeroone.star.project.j1.orgmanager.mapstruct.DataPermissionConvert;
import com.zeroone.star.project.j1.orgmanager.service.DataPermissionService;
import com.zeroone.star.project.query.j1.org.PositionDataPermissionQuery;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 *
 */
@Service
public class DataPermissionServiceImpl extends ServiceImpl<DataPermissionMapper, PositionDataPermissionDO>
    implements DataPermissionService {

    @Resource
    DataPermissionConvert dataPermissionConvert;

    /**
     * 获取职位数据权限列表（条件+分页）
     *
     */
    @Override
    public PageDTO<PositionDataPermissionDTO> listAll(PositionDataPermissionQuery query) {
        // 构建分页查询对象
        Page<PositionDataPermissionDO> page = new Page<>(query.getPageIndex(),query.getPageSize());

        // 构建分页查询条件
        QueryWrapper<PositionDataPermissionDO> queryWrapper = new QueryWrapper<>();

        // 表名 模糊查询
        queryWrapper.like(!StringUtils.isEmpty(query.getEntity_name()),"entity_name",query.getEntity_name());

        // 权限范围类型 精确查询
        queryWrapper.eq(query.getScope_type() != null,"scope_type",query.getScope_type());

        // 数据负责人字段 精确匹配
        queryWrapper.eq(!StringUtils.isEmpty(query.getOwner_field()),"owner_field",query.getOwner_field());

        // 数据所属组织名字段 精确匹配
        queryWrapper.eq(!StringUtils.isEmpty(query.getOwner_org_field()),"owner_org_field",query.getOwner_org_field());

        // 分页查询
        Page<PositionDataPermissionDO> resultPage = baseMapper.selectPage(page,queryWrapper);

        return PageDTO.create(resultPage, src -> dataPermissionConvert.doToDto(src));
    }


}




