#!/bin/bash

# 清除代理环境变量
unset http_proxy
unset https_proxy
unset all_proxy
unset ftp_proxy
unset no_proxy

# 清除Git代理设置
git config --global --unset http.proxy 2>/dev/null
git config --global --unset https.proxy 2>/dev/null

# 输出清除结果
echo "========================================"
echo "代理设置已清除！"
echo "========================================"
echo "HTTP代理:  $http_proxy"
echo "HTTPS代理: $https_proxy"
echo "所有协议:  $all_proxy"
echo "FTP代理:   $ftp_proxy"
echo "========================================"
echo "✅ 环境变量代理已清除"
echo "✅ Git代理设置已清除"
echo "========================================"
echo "使用说明："
echo "1. 设置代理: source ./set_proxy.sh"
echo "2. 取消代理: source ./unset_proxy.sh"
echo "========================================" 