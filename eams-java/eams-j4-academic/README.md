common模块 -> resource -> config -> bootstrap-dev.properties
修改以下两个配置
nacos.namespace=4833404f-4b82-462e-889a-3c508160c6b4->
eams-dev(根据你自己nacos来, 暂时使用阿伟学长演示项目中的配置,用到的服务器跟着演示视频配就好)
nacos.addr=192.168.220.128:8848->
自己的ip:port
同理使用sentinel时也记得修改

nacos中data-source.yaml数据库的数据库名称hzb_ems
