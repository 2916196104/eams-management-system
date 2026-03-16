package com.zeroone.star.sample.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sample.test.entity.User;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.SneakyThrows;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.PostConstruct;
import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 描述：Excel控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Controller
@RequestMapping("/excel")
@Api(tags = "excel")
public class ExcelController {
    private List<User> list;

    @Resource
    EasyExcelComponent excel;

    @PostConstruct
    public void initData() {
        list = new ArrayList<>();
        // 测试数据
        for (int i = 1; i < 11; i++) {
            User user = new User();
            user.setId(i);
            user.setName("控制器用户" + i);
            user.setPhone("1234567890" + i);
            list.add(user);
        }
    }

    @SneakyThrows
    @GetMapping(value = "export", produces = "application/octet-stream")
    @ApiOperation("导出Excel")
    public ResponseEntity<byte[]> exportExcel() {
        // 导出到文件流中
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        excel.export("test", out, User.class, list);
        // 响应文件
        HttpHeaders headers = new HttpHeaders();
        String filename = "rep-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        byte[] bytes = out.toByteArray();
        out.close();
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }

    @SneakyThrows
    @PostMapping("/import")
    @ApiOperation("导入Excel")
    @ResponseBody
    public JsonVO<String> importExcel(MultipartFile file) {
        // 解析Excel
        InputStream input = file.getInputStream();
        List<User> list = excel.parseExcel(input, "test1", User.class);
        // 保存到数据库的业务调用，使用打印测试解析效果
        if (list.size() > 0) {
            list.forEach(System.out::println);
            return JsonVO.success("导入成功");
        }
        return JsonVO.fail("导入失败");
    }
}
