package com.zeroone.star.stumanager.controller;

import cn.hutool.db.PageResult;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.UserAccountDTO;
import com.zeroone.star.project.dto.j8.stumanager.UserPasswordDTO;
import com.zeroone.star.project.j8.stumanager.ParentAccountApis;
import com.zeroone.star.project.query.j8.stumanager.UserAccountQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.UserAccountVO;
import com.zeroone.star.stumanager.service.UserAccountService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;

/**
 * 家长账号
 */
@Slf4j
@Api(tags = "家长账号")
@RequestMapping("/stu/parent-account")
@RestController
public class ParentAccountController implements ParentAccountApis {
    @Resource
    private UserAccountService userAccountService;

    /**
     * 获取账号列表
     */
    @Override
    @GetMapping("/list")
    @ApiOperation(value = "获取账号列表", notes = "分页查询学员家长账号列表，支持按姓名、手机号、状态等条件筛选")
    public JsonVO<PageDTO<UserAccountVO>> getAccountList(UserAccountQuery query) {
        log.info("获取账号列表, 查询条件: {}", query);
//        PageResult<UserAccountVO> pageResult = userAccountService.getAccountList(query);
        PageDTO<UserAccountVO> pageResult = userAccountService.getAccountList(query);
        return JsonVO.success(pageResult);
    }

//    /**
//     * 获取账号详情
//     */
//    @Override
//    @GetMapping("/{id}")
//    @ApiOperation(value = "获取账号详情", notes = "根据用户ID查询账号详细信息")
//    public JsonVO<UserAccountVO> getAccountDetail(
//            @ApiParam(value = "用户ID", required = true, example = "1")
//            @PathVariable("id") Long id) {
//        log.info("获取账号详情, 用户ID: {}", id);
//        UserAccountVO accountVO = userAccountService.getAccountDetail(id);
//        if (accountVO == null) {
//            return JsonVO.fail("账号不存在");
//        }
//        return JsonVO.success(accountVO);
//    }

    /**
     * 修改账号
     */
    @Override
    @PutMapping("/update")
    @ApiOperation(value = "修改账号", notes = "修改学员家长账号基本信息，包括姓名、手机号、邮箱等")
    public JsonVO updateAccount(@Valid @RequestBody UserAccountDTO dto) {
        log.info("修改账号, 参数: {}", dto);

        // 检查手机号是否重复
        if (userAccountService.checkMobileDuplicate(dto.getId(), dto.getMobile())) {
            return JsonVO.fail("手机号已被其他账号使用");
        }

        boolean result = userAccountService.updateAccount(dto);
        return result ? JsonVO.success("修改成功") : JsonVO.fail("修改失败");
    }

    /**
     * 修改密码
     */
    @Override
    @PutMapping("/password")
    @ApiOperation(value = "修改密码", notes = "修改学员家长账号密码，需验证原密码")
    public JsonVO updatePassword(@Valid @RequestBody UserPasswordDTO dto) {
        log.info("修改密码, 用户ID: {}", dto.getId());

        // 校验两次密码是否一致
        if (!dto.getNewPassword().equals(dto.getConfirmPassword())) {
            return JsonVO.fail("两次输入的密码不一致");
        }

        // 校验原密码
        if (!userAccountService.verifyOldPassword(dto.getId(), dto.getOldPassword())) {
            return JsonVO.fail("原密码错误");
        }

        boolean result = userAccountService.updatePassword(dto.getId(), dto.getNewPassword());
        return result ? JsonVO.success("密码修改成功") : JsonVO.fail("密码修改失败");
    }
}
