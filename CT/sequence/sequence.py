def needleman_wunsch(seq1, seq2):
    # 初始化得分矩阵和路径矩阵
    n = len(seq1)
    m = len(seq2)
    score_matrix = [[0] * (m + 1) for _ in range(n + 1)]
    direction_matrix = [[0] * (m + 1) for _ in range(n + 1)]

    # 初始化第一列和第一行
    for i in range(1, n + 1):
        score_matrix[i][0] = score_matrix[i - 1][0] - 2
    for j in range(1, m + 1):
        score_matrix[0][j] = score_matrix[0][j - 1] - 2

    # 填充得分矩阵
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            # 根据得分机制更新每一格的值
            match = score_matrix[i - 1][j - 1] + (
                1 if seq1[i - 1] == seq2[j - 1] else -1
            )
            delete = score_matrix[i - 1][j] - 2
            insert = score_matrix[i][j - 1] - 2
            score_matrix[i][j] = max(match, delete, insert)

    # 回溯得到对齐序列
    aligned_seq1 = ""
    aligned_seq2 = ""
    i, j = n, m

    while i > 0 or j > 0:
        current_score = score_matrix[i][j]

        # 匹配或不匹配
        if (
            i > 0
            and j > 0
            and current_score
            == score_matrix[i - 1][j - 1] + (1 if seq1[i - 1] == seq2[j - 1] else -1)
        ):
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            i -= 1
            j -= 1
        # 删除
        elif i > 0 and current_score == score_matrix[i - 1][j] - 2:
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = "-" + aligned_seq2
            i -= 1
        # 插入
        elif j > 0 and current_score == score_matrix[i][j - 1] - 2:
            aligned_seq1 = "-" + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            j -= 1

    return score_matrix[n][m], aligned_seq1, aligned_seq2


def smith_waterman(seq1, seq2):
    # 初始化得分矩阵和路径矩阵
    n = len(seq1)
    m = len(seq2)
    score_matrix = [[0] * (m + 1) for _ in range(n + 1)]
    max_score = 0
    max_pos = (0, 0)

    # 填充得分矩阵
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            # 根据得分机制更新每一格的值
            match = score_matrix[i - 1][j - 1] + (
                1 if seq1[i - 1] == seq2[j - 1] else -1
            )
            delete = score_matrix[i - 1][j] - 2
            insert = score_matrix[i][j - 1] - 2
            score_matrix[i][j] = max(0, match, delete, insert)

            # 记录最高分及其位置
            if score_matrix[i][j] > max_score:
                max_score = score_matrix[i][j]
                max_pos = (i, j)

    # 回溯得到对齐的子序列
    aligned_seq1 = ""
    aligned_seq2 = ""
    i, j = max_pos

    while i > 0 and j > 0 and score_matrix[i][j] != 0:
        current_score = score_matrix[i][j]

        # 匹配或不匹配
        if (
            i > 0
            and j > 0
            and current_score
            == score_matrix[i - 1][j - 1] + (1 if seq1[i - 1] == seq2[j - 1] else -1)
        ):
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            i -= 1
            j -= 1
        # 删除
        elif i > 0 and current_score == score_matrix[i - 1][j] - 2:
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = "-" + aligned_seq2
            i -= 1
        # 插入
        elif j > 0 and current_score == score_matrix[i][j - 1] - 2:
            aligned_seq1 = "-" + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            j -= 1

    return max_score, aligned_seq1, aligned_seq2


def semi_global_alignment(seq1, seq2):
    # 初始化得分矩阵
    n = len(seq1)
    m = len(seq2)
    score_matrix = [[0] * (m + 1) for _ in range(n + 1)]

    # 初始化第一行（不对齐序列S的前缀）
    for j in range(1, m + 1):
        score_matrix[0][j] = 0  # 允许序列T的前缀不对齐

    # 初始化第一列
    for i in range(1, n + 1):
        score_matrix[i][0] = score_matrix[i - 1][0] - 2  # 序列S必须完全比对，故有罚分

    # 填充得分矩阵
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            match = score_matrix[i - 1][j - 1] + (
                1 if seq1[i - 1] == seq2[j - 1] else -1
            )
            delete = score_matrix[i - 1][j] - 2
            insert = score_matrix[i][j - 1] - 2
            score_matrix[i][j] = max(match, delete, insert)

    # 找到最后一行的最大值，即最佳半全局对齐得分
    max_score = max(score_matrix[n])

    # 回溯以获得对齐的序列
    aligned_seq1 = ""
    aligned_seq2 = ""
    j = score_matrix[n].index(max_score)  # 从最大分数处开始回溯
    i = n

    while i > 0 or j > 0:
        current_score = score_matrix[i][j]

        if (
            i > 0
            and j > 0
            and current_score
            == score_matrix[i - 1][j - 1] + (1 if seq1[i - 1] == seq2[j - 1] else -1)
        ):
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            i -= 1
            j -= 1
        elif i > 0 and current_score == score_matrix[i - 1][j] - 2:
            aligned_seq1 = seq1[i - 1] + aligned_seq1
            aligned_seq2 = "-" + aligned_seq2
            i -= 1
        elif j > 0 and current_score == score_matrix[i][j - 1] - 2:
            aligned_seq1 = "-" + aligned_seq1
            aligned_seq2 = seq2[j - 1] + aligned_seq2
            j -= 1
        else:
            break

    return max_score, aligned_seq1, aligned_seq2


# 测试例子
seq1 = "TACGAAAGACCGACCAGTAAAGGGGCCCATCCCCCGAGACATCAACCGCCGGCGACAGTCGGACGGCATCGTCTGATTGTGTGCTCGCGCAACAAGCGGA"
seq2 = "ACTCAGGGTTGCGTATCAAGCCACTGGGGCTCGCATGGTAACGTCACAACCTAGCAAGAGACGCGCATGCTGCAGTTCTTGTCGTAATTGATAGTAAGACGGGCTAAAAC"
score, aligned_seq1, aligned_seq2 = needleman_wunsch(seq1, seq2)
print(f"得分: {score}")
print(f"序列1: {aligned_seq1}")
print(f"序列2: {aligned_seq2}")

score, aligned_seq1, aligned_seq2 = smith_waterman(seq1, seq2)
print(f"得分: {score}")
print(f"序列1: {aligned_seq1}")
print(f"序列2: {aligned_seq2}")

score, aligned_seq1, aligned_seq2 = semi_global_alignment(seq1, seq2)
print(f"得分: {score}")
print(f"序列1: {aligned_seq1}")
print(f"序列2: {aligned_seq2}")
