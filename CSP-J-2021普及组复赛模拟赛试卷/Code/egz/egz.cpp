# 读取输入
N, M, P, K = map(int, input().split())

# 跳过 P 条现有的街道信息
for _ in range(P):
    input()

# 计算最大可能增加的起始街道数量
max_increase = min(K, N - 1)

# 输出结果
print(max_increase)
