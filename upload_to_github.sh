#!/bin/bash

echo "========================================="
echo "🚀 光纤发送系统 - 上传到GitHub仓库"
echo "========================================="

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 检查Git状态
echo -e "${BLUE}1. 检查本地Git状态...${NC}"
git status

echo ""
echo -e "${YELLOW}请按照以下步骤操作：${NC}"
echo ""
echo -e "${GREEN}步骤1: 在GitHub上创建新仓库${NC}"
echo "   1.1 访问: https://github.com/new"
echo "   1.2 仓库名称建议: fiber-sender-system"
echo "   1.3 描述: 光纤发送系统 - 基于Qt和OpenCV的高性能光纤数据发送平台"
echo "   1.4 选择 Public 或 Private"
echo "   1.5 不要初始化README, .gitignore或License（我们已有）"
echo "   1.6 点击 'Create repository'"
echo ""

echo -e "${GREEN}步骤2: 获取仓库地址${NC}"
echo "   创建成功后，GitHub会显示仓库地址，类似："
echo "   https://github.com/yourusername/fiber-sender-system.git"
echo ""

read -p "请输入您的GitHub仓库地址: " REPO_URL

if [ -z "$REPO_URL" ]; then
    echo -e "${RED}❌ 仓库地址不能为空${NC}"
    exit 1
fi

echo ""
echo -e "${BLUE}2. 添加远程仓库...${NC}"
git remote add origin "$REPO_URL"

echo -e "${GREEN}✅ 远程仓库已添加: $REPO_URL${NC}"

echo ""
echo -e "${BLUE}3. 检查远程仓库配置...${NC}"
git remote -v

echo ""
echo -e "${BLUE}4. 推送代码到远程仓库...${NC}"
echo "推送主分支和标签..."

# 推送主分支
git push -u origin master

# 推送标签
git push origin --tags

echo ""
echo -e "${GREEN}========================================="
echo "🎉 代码上传完成！"
echo "=========================================${NC}"
echo ""
echo -e "${YELLOW}您可以访问以下地址查看您的仓库：${NC}"
echo "$REPO_URL"
echo ""
echo -e "${YELLOW}后续操作：${NC}"
echo "✅ 推送更新: git push origin master"
echo "✅ 拉取更新: git pull origin master"
echo "✅ 查看状态: git status"
echo "✅ 查看历史: git log --oneline"
echo ""
echo -e "${GREEN}恭喜！您的光纤发送系统已成功上传到GitHub！${NC}" 