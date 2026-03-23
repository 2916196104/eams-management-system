package com.zeroone.eams.user.controller;

import com.zeroone.eams.api.j26.user.UserAccountApi;
import com.zeroone.eams.common.core.domain.R;
import com.zeroone.eams.common.core.page.PageResult;
import com.zeroone.eams.domain.j26.user.dto.UserAccountDTO;
import com.zeroone.eams.domain.j26.user.dto.UserPasswordDTO;
import com.zeroone.eams.domain.j26.user.query.UserAccountQuery;
import com.zeroone.eams.domain.j26.user.vo.UserAccountVO;
import com.zeroone.eams.user.service.UserAccountService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

/**
 * 学员家长账号管理Controller
 *
 * @author j26
 */
@Slf4j
@RestController
@RequiredArgsConstructor
@Api(tags = "学员家长账号管理")
@RequestMapping("/user/account")
public class UserAccountController implements UserAccountApi {

    private final UserAccountService userAccountService;

    /**
     * 获取账号列表
     */
    @Override
    @GetMapping("/list")
    @ApiOperation(value = "获取账号列表", notes = "分页查询学员家长账号列表，支持按姓名、手机号、状态等条件筛选")
    public R<PageResult<UserAccountVO>> getAccountList(UserAccountQuery query) {
        log.info("获取账号列表, 查询条件: {}", query);
        PageResult<UserAccountVO> pageResult = userAccountService.getAccountList(query);
        return R.ok(pageResult);
    }

    /**
     * 获取账号详情
     */
    @Override
    @GetMapping("/{id}")
    @ApiOperation(value = "获取账号详情", notes = "根据用户ID查询账号详细信息")
    public R<UserAccountVO> getAccountDetail(
            @ApiParam(value = "用户ID", required = true, example = "1")
            @PathVariable("id") Long id) {
        log.info("获取账号详情, 用户ID: {}", id);
        UserAccountVO accountVO = userAccountService.getAccountDetail(id);
        if (accountVO == null) {
            return R.fail("账号不存在");
        }
        return R.ok(accountVO);
    }

    /**
     * 修改账号
     */
    @Override
    @PutMapping("/update")
    @ApiOperation(value = "修改账号", notes = "修改学员家长账号基本信息，包括姓名、手机号、邮箱等")
    public R<Boolean> updateAccount(@Valid @RequestBody UserAccountDTO dto) {
        log.info("修改账号, 参数: {}", dto);

        // 检查手机号是否重复
        if (userAccountService.checkMobileDuplicate(dto.getId(), dto.getMobile())) {
            return R.fail("手机号已被其他账号使用");
        }

        boolean result = userAccountService.updateAccount(dto);
        return result ? R.ok(true, "修改成功") : R.fail("修改失败");
    }

    /**
     * 修改密码
     */
    @Override
    @PutMapping("/password")
    @ApiOperation(value = "修改密码", notes = "修改学员家长账号密码，需验证原密码")
    public R<Boolean> updatePassword(@Valid @RequestBody UserPasswordDTO dto) {
        log.info("修改密码, 用户ID: {}", dto.getId());

        // 校验两次密码是否一致
        if (!dto.getNewPassword().equals(dto.getConfirmPassword())) {
            return R.fail("两次输入的密码不一致");
        }

        // 校验原密码
        if (!userAccountService.verifyOldPassword(dto.getId(), dto.getOldPassword())) {
            return R.fail("原密码错误");
        }

        boolean result = userAccountService.updatePassword(dto.getId(), dto.getNewPassword());
        return result ? R.ok(true, "密码修改成功") : R.fail("密码修改失败");
    }
}
