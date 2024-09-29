#!/bin/bash
clear

# 开始编译
echo "开始编译"
g++ T2.cpp -o T2

# 检查编译是否成功
if [ $? -ne 0 ]; then
    echo "编译失败"
    exit 1
fi
echo "编译结束"

# 输入和输出文件
echo "输入文件: "
read input_file
if [ "$input_file" == "" ]; then
    input_file="in.txt"
fi

echo "输出文件: "
read output_file
if [ "$output_file" == "" ]; then
    output_file="out.txt"
fi

# 运行程序
./T2 <"$input_file" >"$output_file"

# 提问是否需要比较答案
echo "你是否需要比较答案 (Y/N): "
read compare_ans

# 如果选择比较答案
if [ "$compare_ans" == "Y" ] || [ "$compare_ans" == "y" ] || [ "$compare_ans" == "" ]; then
    echo "答案文件: "
    read answer_file
    if [ "$answer_file" == "" ]; then
        answer_file="ans.txt"
    fi

    # 检查答案文件是否存在
    if [ ! -f "$answer_file" ]; then
        echo "答案文件不存在: $answer_file"
        exit 1
    fi

    # 比较输出和答案文件
    if diff "$output_file" "$answer_file" >/dev/null; then
        echo "输出与答案一致"
    else
        echo "输出与答案不一致"
        echo "差异如下:"
        diff "$output_file" "$answer_file"
    fi
else
    echo "不比较答案"
fi
