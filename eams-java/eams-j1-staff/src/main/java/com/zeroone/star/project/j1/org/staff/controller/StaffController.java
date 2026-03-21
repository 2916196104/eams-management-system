package com.zeroone.star.project.j1.org.staff.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.org.StaffDTO;
import com.zeroone.star.project.dto.j1.org.ResetPasswordDTO;
import com.zeroone.star.project.j1.org.staff.StaffMangerApis;
import com.zeroone.star.project.j1.org.staff.service.StaffService;
import com.zeroone.star.project.query.j1.org.StaffQuery;
import com.zeroone.star.project.query.j1.org.ClassRecordQuery;
import com.zeroone.star.project.query.j1.org.TeachRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j1.org.StaffVO;
import com.zeroone.star.project.vo.j1.org.ClassRecordVO;
import com.zeroone.star.project.vo.j1.org.TeachRecordVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;
import java.util.Collections;

/**
 * <p>
 * 描述：员工操作controller层
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author type-c chichu
 * @version 1.0.0
 */
@RestController()
@RequestMapping("j1/staff")
@Api(tags="员工管理")
@Slf4j
public class StaffController implements StaffMangerApis {
    @Autowired
    private StaffService staffService;
    @GetMapping("/getpage")
    @ApiOperation("获取员工列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<StaffVO>> queryPage(StaffQuery condition) {
        return staffService.queryPage(condition);
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
    @PostMapping("/transferOrg")
    @ApiOperation("转出机构（支持批量）")
    @Override
    public JsonVO<List<Long>> transferStaffOrg(@RequestBody List<Long> staffIds, @RequestParam Long orgId) {
        return null;
    }

    @PostMapping("/resetPassword")
    @ApiOperation("修改密码")
    @Override
    public JsonVO<Boolean> resetStaffPassword(@RequestBody ResetPasswordDTO dto) {
        return null;
    }

    @GetMapping("/export")
    @ApiOperation("导出数据")
    @Override
    public JsonVO<Void> exportStaffList(StaffQuery condition) {
        return null;
    }

    @PostMapping("/updateAvatar")
    @ApiOperation("修改头像")
    @Override
    public JsonVO<String> updateStaffAvatar(@RequestParam Long staffId, @RequestParam MultipartFile file) {
        return null;
    }

    @GetMapping("/getTeachRecord")
    @ApiOperation("获取授课记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<TeachRecordVO>> getTeachRecord(TeachRecordQuery query) {
        return null;
    }

    @GetMapping("/getClassRecord")
    @ApiOperation("获取带班记录（条件+分页）")
    @Override
    public JsonVO<PageDTO<ClassRecordVO>> getClassRecord(ClassRecordQuery query) {
        return null;
    }
}
