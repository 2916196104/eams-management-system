package com.homework.eamsj3class.controller;

import cn.hutool.core.collection.CollUtil;
import cn.hutool.core.date.DateTime;
import com.alibaba.excel.EasyExcel;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.dto.j3.course.CourseExportDTO;
import com.zeroone.star.project.dto.j3.course.CourseStatusDTO;
import com.zeroone.star.project.j3.course.CourseApi;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.SneakyThrows;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.PostConstruct;
import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.math.BigDecimal;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;

/**
 * 课程启用/禁用接口实现类
 * @author Longan
 * @description 实现课程状态的批量更新
 */
@Controller
@RequestMapping("j3/css")
@Api(tags = "课程管理")
public class ChangeSubjectStateController implements CourseApi {
    @Override
    @PutMapping
    @ApiOperation(value = "启/禁用课程")
    @ResponseBody
    public JsonVO<Void> updateStatus(@Validated @RequestBody CourseStatusDTO stateDTO) {
        // 防止前端传个空的过来
        if (stateDTO == null || CollUtil.isEmpty(stateDTO.getIds())) {
            return JsonVO.fail("请选择要操作的课程");
        }
        // 校验状态值是否合法（假设只允许 0 和 1）
        Integer status = stateDTO.getStatus();
        if (status == null || (status != 0 && status != 1)) {
            return JsonVO.fail("非法状态值");
        }
        // 2.TODO 这里的逻辑交给 Service 处理
//         boolean success = courseService.updateCourseStatus(stateDTO.getIds(), stateDTO.getStatus());

        // 3. 返回操作结果
//         if (success) {
        return JsonVO.success(null);
//         }
//         return JsonVO.fail("更新状态失败");
    }

    private List<CourseExportDTO> list;
    @Resource
    EasyExcelComponent excel;

    @PostConstruct
    public void initExcelData(){
        list = new ArrayList<>();
        //TODO 从数据库获取数据
    }

    @SneakyThrows
    @GetMapping(value = "/export", produces = "application/octet-stream")
    @ApiOperation(value = "导出课程数据")
    public ResponseEntity<byte[]> exportExcel(){
        //导出到文件流中
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        excel.export("report", out, CourseExportDTO.class, list);
        //响应文件
        HttpHeaders headers = new HttpHeaders();
        String fileName = "rep-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", fileName);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        byte[] bytes = out.toByteArray();
        out.close();
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }
}