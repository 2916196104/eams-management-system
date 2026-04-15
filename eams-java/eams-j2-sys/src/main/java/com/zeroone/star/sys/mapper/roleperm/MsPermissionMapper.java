package com.zeroone.star.sys.mapper.roleperm;

import com.zeroone.star.project.dto.j2.sys.Roleperm.PermissionDTO;
import com.zeroone.star.sys.entity.SysPermission;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.Named;
import org.mapstruct.factory.Mappers;
import java.util.List;

/**
 * PermissionDTO ↔ SysPermission 映射接口
 * componentModel = "spring"：生成的实现类会被Spring管理，可直接@Autowired注入
 */
@Mapper(componentModel = "spring")
public interface MsPermissionMapper {

    // 非Spring环境使用（可选，建议用Spring注入）
    MsPermissionMapper INSTANCE = Mappers.getMapper(MsPermissionMapper.class);

    /**
     * SysPermission → PermissionDTO
     */

    PermissionDTO entityToDTO(SysPermission sysPermission);

    /**
     * 批量转换：SysPermission列表 → PermissionDTO列表
     */
    List<PermissionDTO> entitiesToDTOs(List<SysPermission> sysPermissions);

    /**
     * PermissionDTO → SysPermission
     */

    SysPermission dtoToEntity(PermissionDTO permissionDTO);

    /**
     * 批量转换：PermissionDTO列表 → SysPermission列表
     */
    List<SysPermission> dtosToEntities(List<PermissionDTO> permissionDTOs);


}