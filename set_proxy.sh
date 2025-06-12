#!/bin/bash

# 设置代理服务器地址
PROXY_SERVER="192.168.1.120:7890"

# 设置环境变量
export http_proxy=http://$PROXY_SERVER
export https_proxy=http://$PROXY_SERVER
export all_proxy=http://$PROXY_SERVER
export ftp_proxy=http://$PROXY_SERVER

# 设置不使用代理的地址列表
export no_proxy=localhost,127.0.0.1,192.168.1.*,10.*,172.16.*,172.17.*,172.18.*,172.19.*,172.20.*,172.21.*,172.22.*,172.23.*,172.24.*,172.25.*,172.26.*,172.27.*,172.28.*,172.29.*,172.30.*,172.31.*

# 输出设置结果
echo "========================================"
echo "代理设置完成！"
echo "========================================"
echo "HTTP代理:  $http_proxy"
echo "HTTPS代理: $https_proxy"
echo "所有协议:  $all_proxy"
echo "FTP代理:   $ftp_proxy"
echo "排除地址:  $no_proxy"
echo "========================================"

# 测试代理连接
echo "正在测试代理连接..."
if curl -s --max-time 10 --proxy $http_proxy http://www.google.com > /dev/null; then
    echo "✅ 代理连接成功！"
else
    echo "❌ 代理连接失败，请检查代理服务器设置"
fi

# 设置Git代理
echo "正在设置Git代理..."
git config --global http.proxy http://$PROXY_SERVER
git config --global https.proxy http://$PROXY_SERVER
echo "✅ Git代理设置完成"

echo "========================================"
echo "使用说明："
echo "1. 运行此脚本: source ./set_proxy.sh"
echo "2. 取消代理: source ./unset_proxy.sh"
echo "3. 当前终端代理有效，新终端需重新设置"
echo "========================================" 