package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ClassDTO;
import com.zeroone.star.project.dto.j4.student.ClassStudentDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.project.query.j4.student.ClassQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.student.service.IStudentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.constraints.NotNull;
import org.springframework.validation.annotation.Validated;
import java.util.List;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {

    @Resource
    private IStudentService studentService;

    @GetMapping("/follow-up/page")
    @ApiOperation("获取跟进记录列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FollowUpDTO>> queryFollowUpPage(@Validated FollowUpQuery condition) {
        return JsonVO.success(studentService.queryFollowUpPage(condition));
    }


    @PostMapping("/follow-up")
    @ApiOperation("添加/修改跟进记录")
    @Override
    public JsonVO<Long> saveFollowUp(@RequestBody @Validated FollowUpDTO followUpDTO) {
        // 基本业务校验
        if (followUpDTO.getStudentId() == null) return JsonVO.fail("学生ID不能为空");
        if (followUpDTO.getContactTime() == null) return JsonVO.fail("联系时间不能为空");

        Long id = studentService.saveFollowUp(followUpDTO);
        return JsonVO.success(id);
    }

    @DeleteMapping("/follow-up/{id}")
    @ApiOperation("删除跟进记录（单个删除）")
    @Override
    public JsonVO<Long> deleteFollowUp(@PathVariable Long id) {
        try {
            return JsonVO.success(studentService.removeFollowUp(id));
        } catch (Exception e) {
            return JsonVO.fail("删除失败：" + e.getMessage());
        }
    }

    @GetMapping("/follow-up/{id}")
    @ApiOperation("获取跟进记录详情")
    @Override
    public JsonVO<FollowUpDTO> getFollowUpDetail(@PathVariable Long id) {
        FollowUpDTO detail = studentService.getFollowUpDetail(id);
        return detail != null ? JsonVO.success(detail) : JsonVO.fail("记录不存在");
    }


    @Override
    @GetMapping("/class/page")
    @ApiOperation("获取班级列表（条件 + 分页）")
    public JsonVO<PageDTO<ClassDTO>> queryClassPage(@Validated ClassQuery condition) {
        try {
            PageDTO<ClassDTO> result = studentService.queryClassPage(condition);
            return JsonVO.success(result);
        } catch (Exception e) {
            return JsonVO.fail(e.getMessage());
        }
    }

    @Override
    @PostMapping("/class/join")
    @ApiOperation("加入班级")
    public JsonVO<Long> joinClass(@RequestBody @Validated ClassStudentDTO dto) {
        try {
            if (dto.getClassId() == null) {
                return JsonVO.fail("班级ID不能为空");
            }
            if (dto.getStudentId() == null) {
                return JsonVO.fail("学生ID不能为空");
            }
            Long result = studentService.joinClass(dto);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            return JsonVO.fail("加入班级失败：" + e.getMessage());
        }
    }

    @Override
    @DeleteMapping("/class/quit")
    @ApiOperation("退出班级")
    public JsonVO<List<Long>> quitClass(
            @ApiParam(value = "班级 ID", required = true, example = "2008418408985583620")
            @RequestParam @NotNull(message = "班级ID不能为空") Long classId,
            @ApiParam(value = "学生 ID", required = true, example = "2008418408985583617")
            @RequestParam @NotNull(message = "学生ID不能为空") Long studentId) {
        try {
            List<Long> result = studentService.quitClass(classId, studentId);
            return JsonVO.success(result);
        } catch (IllegalArgumentException e) {
            return JsonVO.fail(e.getMessage());
        } catch (Exception e) {
            return JsonVO.fail("退出班级失败：" + e.getMessage());
        }
    }
}