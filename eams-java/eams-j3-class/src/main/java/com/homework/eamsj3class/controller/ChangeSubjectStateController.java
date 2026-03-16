package com.homework.eamsj3class.controller;

import cn.hutool.core.collection.CollUtil;
import com.alibaba.excel.EasyExcel;
import com.zeroone.star.project.dto.j3.course.CourseExportDTO;
import com.zeroone.star.project.dto.j3.course.CourseStatusDTO;
import com.zeroone.star.project.j3.course.CourseApi;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;

/**
 * 课程启用/禁用接口实现类
 * @author Longan
 * @description 实现课程状态的批量更新
 */
@RestController
@RequestMapping("j3/css")
@Api(tags = "课程管理")
public class ChangeSubjectStateController implements CourseApi {
    @Override
    @PutMapping
    @ApiOperation(value = "启/禁用课程")
    public JsonVO<Void> updateStatus(@RequestBody CourseStatusDTO stateDTO) {
        // 防止前端传个空的过来
        if (stateDTO == null || CollUtil.isEmpty(stateDTO.getIds())) {
            return JsonVO.fail("请选择要操作的课程");
        }
        // 校验状态值是否合法（假设只允许 0 和 1）
        Integer status = stateDTO.getStatus();
        if (status == null || (status != 0 && status != 1)) {
            return JsonVO.fail("非法状态值");
        }
        // 2. 这里的逻辑交给 Service 处理
//         boolean success = courseService.updateCourseStatus(stateDTO.getIds(), stateDTO.getStatus());

        // 3. 返回操作结果
//         if (success) {
        return JsonVO.success(null);
//         }
//         return JsonVO.fail("更新状态失败");
    }

    @ApiOperation(value = "导出课程数据")
    @GetMapping("/export")
    public void exportCourses(HttpServletResponse response) throws IOException {
        // 1. 设置响应内容类型和编码
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("utf-8");

        // 2. 防止中文文件名乱码
        String fileName = URLEncoder.encode("课程数据表", "UTF-8").replaceAll("\\+", "%20");
        response.setHeader("Content-disposition", "attachment;filename*=utf-8''" + fileName + ".xlsx");

        // 3. 获取数据（实际开发中请从数据库查询，这里模拟 mock 数据）
        List<CourseExportDTO> list = new ArrayList<>();
        // TODO: 调用 service.listAll() 转换成 DTO

        // 4. 使用 EasyExcel 写入流
        EasyExcel.write(response.getOutputStream(), CourseExportDTO.class)
                .sheet("课程列表")
                .doWrite(list);
    }
}