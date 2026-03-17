package com.homework.eamsj3class.controller;

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

/**
 * @authore Longan
 * @description
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
    @ApiOperation("上传文件")
    @ResponseBody
    public JsonVO<String> uploadFile(MultipartFile file) {
        //上传文件的后缀名
        String extName = file.getOriginalFilename().substring(file.getOriginalFilename().lastIndexOf(".") + 1);
        //上传文件到dfs中
        FastDfsFileInfo info = dfs.uploadFile(file.getBytes(), extName);
        //响应文件访问地址 http://192.168.1.100:8080/file/download?fileId=group1/M00/00/00/wKjThF0-x0aAQ5jMAAQ5jMAQ5jMAAQ5jMAQ5jMAAQ5jMAAQ5jMAQ5j
        if (info != null){
            return JsonVO.success(dfs.fetchUrl(info, urlPrefix, true));
        }
        return JsonVO.fail(null);
    }

    @SneakyThrows
    @GetMapping(value = "/download", produces = "image/jpeg")
    @ApiOperation("下载文件")
    public ResponseEntity<byte[]> downloadFile(String group, String fileId) {
        //下载文件到服务端内存中
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(fileId)
                .build();
        byte[] bytes = dfs.downloadFile(info);
        //响应文件
        HttpHeaders headers = new HttpHeaders();
        String fileName = "img-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".jpg";
        headers.setContentDispositionFormData("attachment", fileName);
        headers.setContentType(MediaType.IMAGE_JPEG);
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }

    @SneakyThrows
    @DeleteMapping("/delete")
    @ResponseBody
    @ApiOperation("删除文件")
    public JsonVO<Integer> deleteFile(String group, String fileId) {
        //删除文件
        FastDfsFileInfo info = FastDfsFileInfo.builder()
                .group(group)
                .storageId(fileId)
                .build();
        int res = dfs.deleteFile(info);
        if (res == 0){
            return JsonVO.success(null);
        }
        return JsonVO.fail(res);
    }
}
