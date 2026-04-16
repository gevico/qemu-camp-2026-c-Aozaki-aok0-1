# 这是一个标准的 Dockerfile
# 它会在 CNB 默认环境的基础之上，额外安装你需要的工具

# 指定基础镜像（这里使用 Ubuntu 或平台默认的镜像层）
FROM ubuntu:22.04 

# 更新软件源并安装你需要的 C 语言开发工具链
RUN apt-get update && \
    apt-get install -y git gcc g++ make gdb clang-format jq curl pkg-config && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*