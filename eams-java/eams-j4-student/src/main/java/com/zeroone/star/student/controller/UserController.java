package com.zeroone.star.student.controller;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j4.student.UserQueryDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdateDTO;
import com.zeroone.star.project.dto.j4.student.UserUpdatePwdDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.student.UserVO;
import com.zeroone.star.student.service.IUserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import org.springframework.web.bind.annotation.RequestMapping;
import javax.annotation.Resource;

import org.springframework.web.bind.annotation.RestController;

/**
 * <p>
 * 家长端用户表 前端控制器
 * </p>
 *
 * @author zrt
 * @since 2026-03-16
 */
@Api(tags = "账号管理")
@RestController
@RequestMapping("/user")
public class UserController {
    @Resource
    private IUserService userService;

    /**
     * 1. 获取账号列表（条件+分页）
     */
    @PostMapping("/list")
    @ApiOperation("获取账号列表（条件+分页）")
    public JsonVO<Page<UserVO>> listUser(@RequestBody UserQueryDTO query) {
        return JsonVO.success(userService.listUser(query));
    }

    /**
     * 2. 修改账号信息
     */
    @PutMapping("/update")
    @ApiOperation("修改账号信息")
    public JsonVO<String> updateUser(@Validated @RequestBody UserUpdateDTO dto) {
        userService.updateUser(dto);
        return JsonVO.success("修改成功");
    }

    /**
     * 3. 修改密码
     */
    @PutMapping("/updatePwd")
    @ApiOperation("修改密码")
    public JsonVO<String> updatePassword(@Validated @RequestBody UserUpdatePwdDTO dto) {
        userService.updatePassword(dto);
        return JsonVO.success("密码修改成功");
    }
}