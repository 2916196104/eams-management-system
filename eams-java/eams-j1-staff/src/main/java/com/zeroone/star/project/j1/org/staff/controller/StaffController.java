package com.zeroone.star.project.j1.org.staff.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.j1.org.staff.StaffMangerApis;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.io.Serializable;
import java.util.List;

/**
 * <p>
 * 描述：员工操作controller层
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c
 * @version 1.0.0
 */
@RestController()
@RequestMapping("j1/staff")
@Api(tags="员工管理")
public class StaffController implements StaffMangerApis {
    @GetMapping("/getpage")
    @ApiOperation("获取员工列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        return null;
    }
    @GetMapping("/get")
    @Override
    @ApiOperation("获取员工详情")
    public JsonVO<StaffVO> queryStaff(StaffQuery condition) {
        return null;
    }
       @PostMapping("/save")
    @Override
    @ApiOperation("保存员工")
    public JsonVO<Long> saveStaff(@RequestBody  StaffDTO condition) {
        return null;
    }
@DeleteMapping("/delete")
    @Override
    @ApiOperation("删除员工（支持批量）")
    public JsonVO<List<Long>> removeStaff(@RequestBody List<Long> ids) {
        return null;
    }

@PostMapping("/set")
    @Override
    @ApiOperation("设置角色（支持批量）")
    public JsonVO<List<Long>> setStaff(@RequestBody List<Long> ids) {
        return null;
    }
@PostMapping("/update")
    @Override
    @ApiOperation("在职状态（支持批量）")
    public JsonVO<List<Long>> updateStaffStatus(@RequestBody List<Long> ids) {
        return null;
    }
}
