# Docker镜像无法下载解决方案

由于**乳包**问题访问国内的镜像源经常无法下载，所以我这里将本项目中我本地下载过的镜像源推送到阿里云镜像仓库

如果大家下载不了`DockerHub`或某些镜像网站的镜像时，可以考虑拉取我推送到阿里云的镜像源

## 镜像列表

下面是我目前推送的镜像如下：

| 版本                     |
| ------------------------ |
| php-5.4-fpm              |
| alpine-3.16              |
| openjdk-8                |
| nacos-2.1.0              |
| elasticsearch-7.6.2      |
| logstash-7.6.2           |
| kibana-7.6.2             |
| rocketmq-dashboard       |
| rocketmq-4.9.3           |
| nginx                    |
| redis-6.2.7              |
| mongo-4.4.17             |
| mysql-8.0.20             |
| mysql-5.6.51             |
| shardingsphere-proxy     |
| minio                    |
| dfs-6.09                 |
| sentinel-dashboard-1.8.4 |
| seata-server-1.5.1       |
| jenkins                  |
|                          |
|                          |

## 镜像使用

完整镜像名组成规则如下：

```shell
crpi-5yw4kk2bxbk3nj6k.cn-hangzhou.personal.cr.aliyuncs.com/01xq/awei:版本
```

镜像使用，只需要替换掉安装文档中的对应镜像即可。

比如`MySQL`安装文档中的某些步骤

```shell
# 拉取镜像
docker pull mysql:8.0.20
# 创建容器
docker run -id ...... mysql:8.0.20
```

替换成我的镜像

```shell
# 拉取镜像
docker pull crpi-5yw4kk2bxbk3nj6k.cn-hangzhou.personal.cr.aliyuncs.com/01xq/awei:mysql-8.0.20
# 创建容器
docker run -id ...... crpi-5yw4kk2bxbk3nj6k.cn-hangzhou.personal.cr.aliyuncs.com/01xq/awei:mysql-8.0.20
```

再比如`Nacos`安装文档中`standalone-derby.yaml`中配置镜像

```yaml
version: "2"
services:
  nacos:
    image: nacos/nacos-server:v2.1.0
    container_name: nacos-standalone
# ......
```

替换成我的镜像

```yaml
version: "2"
services:
  nacos:
    image: crpi-5yw4kk2bxbk3nj6k.cn-hangzhou.personal.cr.aliyuncs.com/01xq/awei:nacos-2.1.0
    container_name: nacos-standalone
# ......
```

