package com.zeroone.star.sample.controller;

import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import lombok.SneakyThrows;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

/**
 * @description  文件操作
 * @author silvan
 */
@Controller
@RequestMapping("/file")
@Api(tags = "文件操作")
@ResponseBody
public class FileController {

    @Autowired
    FastDfsClientComponent dfs;


    @Value("${fastdfs.nginx-servers}")
    private String urlPrefix;
    /**
     *
     *
     * @Params [file] 上传文件
     * @return com.zeroone.star.project.vo.JsonVO<java.lang.String>
     */

    @SneakyThrows
    public JsonVO<String> uploadFile(MultipartFile file){

//        获取上传文件的后缀名
        String extName = file.getOriginalFilename().substring(file.getOriginalFilename().lastIndexOf(".") + 1);
//        上传文件到dfs
        FastDfsFileInfo info = dfs.uploadFile(file.getBytes(), extName);
//        响应文件访问地址
        if(info!=null){
            return JsonVO.success(dfs.fetchUrl(info,urlPrefix,true));
        }

        return JsonVO.fail("上传失败");


    }

}
