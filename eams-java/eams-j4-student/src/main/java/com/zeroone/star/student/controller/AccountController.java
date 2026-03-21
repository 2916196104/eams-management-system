package com.zeroone.star.student.controller;

import com.zeroone.star.project.vo.j4.student.CommonResponseVO;
import com.zeroone.star.project.dto.j4.student.AccountQueryDTO;
import com.zeroone.star.project.dto.j4.student.AccountUpdateDTO;
import com.zeroone.star.project.dto.j4.student.PasswordUpdateDTO;
import com.zeroone.star.project.vo.j4.student.AccountVO;
import com.zeroone.star.project.vo.j4.student.PageVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * 账号管理接口（条件分页查询+修改账号+修改密码）
 */
@RestController
@RequestMapping("/j4/account")
@Api(tags = "账号管理")
public class AccountController {
    /**
     * 1. 获取账号列表（条件+分页）
     */
    @PostMapping("/list")
    @ApiOperation(value = "账号列表查询（条件+分页）", notes = "支持账号名称/状态/部门ID模糊查询，分页返回")
    public CommonResponseVO<PageVO<AccountVO>> getAccountList(
            @ApiParam(value = "查询条件+分页参数", required = true)
            @RequestBody AccountQueryDTO queryDTO) {
        // 模拟分页查询结果（无业务逻辑，仅保证接口可调试）
        PageVO<AccountVO> pageVO = new PageVO<>();
        pageVO.setTotal(100L);
        pageVO.setPages(10);
        pageVO.setPageNum(queryDTO.getPageNum());
        pageVO.setPageSize(queryDTO.getPageSize());

        // 模拟数据列表
        List<AccountVO> accountList = new ArrayList<>();
        AccountVO account = new AccountVO();
        account.setAccountId(10001L);
        account.setAccountName(queryDTO.getAccountName() == null ? "admin" : queryDTO.getAccountName());
        account.setRealName("管理员");
        account.setPhone("13800138001");
        account.setStatus(queryDTO.getStatus() == null ? 1 : queryDTO.getStatus());
        account.setDeptId(queryDTO.getDeptId() == null ? 1001L : queryDTO.getDeptId());
        account.setDeptName("技术部");
        account.setCreateTime(LocalDateTime.of(2024, 6, 30, 15, 30));
        account.setLastLoginTime(LocalDateTime.of(2024, 6, 30, 16, 0));
        accountList.add(account);

        pageVO.setList(accountList);
        return CommonResponseVO.success(pageVO);
    }

    /**
     * 2. 修改账号信息
     */
    @PutMapping("/update")
    @ApiOperation(value = "修改账号信息", notes = "支持修改账号名称/真实姓名/手机号/状态/所属部门")
    public CommonResponseVO<String> updateAccount(
            @ApiParam(value = "账号修改参数", required = true)
            @Valid @RequestBody AccountUpdateDTO updateDTO) {
        // 模拟修改成功（无业务逻辑，仅保证接口可调试）
        if (updateDTO.getAccountId() == null) {
            return CommonResponseVO.fail("账号ID不能为空");
        }
        return CommonResponseVO.success("账号修改成功，账号ID：" + updateDTO.getAccountId());
    }

    /**
     * 3. 修改密码
     */
    @PutMapping("/update/password")
    @ApiOperation(value = "修改账号密码", notes = "验证旧密码，新密码需8-16位字母数字组合")
    public CommonResponseVO<String> updatePassword(
            @ApiParam(value = "密码修改参数", required = true)
            @Valid @RequestBody PasswordUpdateDTO passwordDTO) {
        // 模拟密码修改逻辑（无真实校验，仅保证接口可调试）
        if (!passwordDTO.getNewPassword().equals(passwordDTO.getConfirmPassword())) {
            return CommonResponseVO.fail("新密码与确认密码不一致");
        }
        if (passwordDTO.getOldPassword().equals("123456")) { // 模拟旧密码验证
            return CommonResponseVO.success("密码修改成功，账号ID：" + passwordDTO.getAccountId());
        } else {
            return CommonResponseVO.fail("旧密码错误");
        }
    }
}
