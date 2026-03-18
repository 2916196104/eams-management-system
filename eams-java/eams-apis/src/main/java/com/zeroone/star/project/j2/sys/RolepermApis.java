package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermDTO;
import com.zeroone.star.project.dto.j2.sys.RolepermStaffDTO;
import com.zeroone.star.project.query.j2.sys.RolepermQuery;
import com.zeroone.star.project.query.j2.sys.RolepermStaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.bind.annotation.RequestBody;

/**
 * @author isme
 * @description
 * @title com.zeroone.star.project.j2.sys
 * @date 2026/3/16
 */
public interface RolepermApis {
    /**
     * 角色权限删除
     * @param query 角色权限查询对象
     * @return 删除结果
     */
    JsonVO<PageDTO<RolepermDTO>> removeRoleperm(@RequestBody RolepermQuery query);
    /**
     * 角色管理的员工列表查询
     * @param query 查询条件
     * @return 角色权限员工列表
     */
    JsonVO<PageDTO<RolepermStaffDTO>> queryListRolepermStaff(RolepermStaffQuery query);
    /**
     * 角色管理的员工新增
     * @param rolepermStaffDTO 新增数据
     * @return 新增结果
     */
    JsonVO<String> addRolepermStaff(RolepermStaffDTO rolepermStaffDTO);
    /**
     * 角色管理的员工删除
     * @param id 要删除数据的编号
     * @return 删除结果
     */
    JsonVO<String> removeRolepermStaff(String id);
}
