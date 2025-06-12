#!/bin/bash

# 快速上传脚本 - 光纤发送系统
echo "🚀 光纤发送系统 - 快速上传到Git仓库"
echo "====================================="

# 检查参数
if [ $# -eq 0 ]; then
    echo "用法: ./quick_upload.sh <仓库地址>"
    echo ""
    echo "示例:"
    echo "  ./quick_upload.sh https://github.com/username/repo.git"
    echo "  ./quick_upload.sh git@github.com:username/repo.git"
    echo ""
    exit 1
fi

REPO_URL="$1"

echo "📍 目标仓库: $REPO_URL"
echo ""

# 检查是否已配置远程仓库
if git remote get-url origin >/dev/null 2>&1; then
    echo "⚠️  检测到已存在的远程仓库:"
    git remote -v
    echo ""
    read -p "是否要替换为新的仓库地址? (y/N): " replace
    if [[ $replace =~ ^[Yy]$ ]]; then
        git remote set-url origin "$REPO_URL"
        echo "✅ 远程仓库地址已更新"
    else
        echo "❌ 操作已取消"
        exit 1
    fi
else
    # 添加远程仓库
    git remote add origin "$REPO_URL"
    echo "✅ 远程仓库已添加"
fi

echo ""
echo "📊 推送前状态检查:"
git status --short

echo ""
echo "🚀 开始推送..."

# 推送主分支
echo "推送主分支..."
if git push -u origin master; then
    echo "✅ 主分支推送成功"
else
    echo "❌ 主分支推送失败"
    echo "可能的原因:"
    echo "1. 网络连接问题"
    echo "2. 权限问题（需要SSH密钥或个人访问令牌）"
    echo "3. 仓库不存在"
    exit 1
fi

# 推送标签
echo ""
echo "推送版本标签..."
if git push origin --tags; then
    echo "✅ 标签推送成功"
else
    echo "⚠️  标签推送失败（但主分支已成功）"
fi

echo ""
echo "🎉 上传完成！"
echo "====================================="
echo "📋 仓库信息:"
echo "   地址: $REPO_URL"
echo "   分支: master"
echo "   版本: $(git tag -l | tail -1)"
echo ""
echo "🔗 在线查看:"
echo "   ${REPO_URL%.git}"
echo ""
echo "📝 后续操作:"
echo "   推送更新: git push"
echo "   拉取更新: git pull"
echo "   查看状态: git status" 