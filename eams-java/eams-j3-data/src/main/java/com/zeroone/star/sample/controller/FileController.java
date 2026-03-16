package com.zeroone.star.sample.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.util.Objects;

/**
 * <p>
 * 描述：文件操作控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@Controller
@RequestMapping("/file")
@Api(tags = "file")
public class FileController {
    @Resource
    FastDfsClientComponent dfs;

    @Value("${fastdfs.nginx-servers}")
    private String urlPrefix;

    @SneakyThrows
    @PostMapping("/upload")
    @ApiOperation(value = "上传文件")
    @ResponseBody
    public JsonVO<String> uploadFile(MultipartFile file) {
        // 获取上传文件的后缀名
        String extName = Objects.requireNonNull(file.getOriginalFilename()).substring(file.getOriginalFilename().lastIndexOf(".") + 1);
        // 上传文件到dfs中
        FastDfsFileInfo info = dfs.uploadFile(file.getBytes(), extName);
        // 响应文件访问地址 http://ip:port/group1/M00/00/00/wKjThF0-hxWAQ5jXAAAjXxXQ5_Q.pdf
        if (info != null) {
            return JsonVO.success(dfs.fetchUrl(info, urlPrefix, true));
        }
        return JsonVO.fail(null);
    }

    @SneakyThrows
    @GetMapping(value = "/download", produces = "image/jpeg")
    @ApiOperation(value = "下载文件")
    public ResponseEntity<byte[]> downloadFile(String group, String storageId) {
        // 下载文件到服务器端内存中
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(storageId)
                .build();
        byte[] bytes = dfs.downloadFile(info);
        // 响应文件
        HttpHeaders headers = new HttpHeaders();
        String filename = "img-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".jpg";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.IMAGE_JPEG);
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }

    @SneakyThrows
    @DeleteMapping("/delete")
    @ApiOperation(value = "删除文件")
    @ResponseBody
    public JsonVO<Integer> deleteFile(String group, String storageId) {
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(storageId)
                .build();
        int res = dfs.deleteFile(info);
        if (res == 0) {
            return JsonVO.success(null);
        }
        return JsonVO.fail(res);
    }
}
