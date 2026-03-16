package com.zeroone.star.sample.test;

import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.sample.test.entity.User;
import lombok.SneakyThrows;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 描述：Excel测试类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@SpringBootTest
public class ExcelTest {

    @Resource
    EasyExcelComponent excel;

    @Test
    void testExport() {
        // 测试数据
        List<User> list = new ArrayList<>();
        for (int i = 1; i < 11; i++) {
            User user = new User();
            user.setId(i);
            user.setName("用户" + i);
            user.setPhone("1234567890" + i);
            list.add(user);
        }
        // 导出
        excel.export("test.xlsx", "test", User.class, list);
    }

    @Test
    void testParse() {
        List<User> list = excel.parseExcel("test.xlsx", "test", User.class);
        list.forEach(System.out::println);
    }

    @Resource
    FastDfsClientComponent dfs;

    @SneakyThrows
    @Test
    void testUploadExcel(){
        // 测试数据
        List<User> list = new ArrayList<>();
        for (int i = 1; i < 11; i++) {
            User user = new User();
            user.setId(i);
            user.setName("DFS用户" + i);
            user.setPhone("1234567890" + i);
            list.add(user);
        }
        // 导出到文件流中
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        excel.export("test", out, User.class, list);
        // 上传到DFS中
        FastDfsFileInfo info = dfs.uploadFile(out.toByteArray(),"xlsx");
        System.out.println(info);
        out.close();
    }
}
