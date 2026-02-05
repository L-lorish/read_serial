#!/usr/bin/env python3

import sys
print(sys.executable)

import pandas as pd
import matplotlib.pyplot as plt

# ====== 1) 读 CSV ======
csv_path = "distance.csv"  # 改成你的文件名
df = pd.read_csv(csv_path)

# 兼容你的表头：%time,field
# 有的 rostopic 导出可能叫 time, field 或 %time, field
time_col = df.columns[0]
value_col = df.columns[1]

# 转成数值类型（保险）
df[time_col] = pd.to_numeric(df[time_col], errors="coerce")
df[value_col] = pd.to_numeric(df[value_col], errors="coerce")
df = df.dropna()

# ====== 2) ns -> 秒（相对时间） ======
t0 = df[time_col].iloc[0]
t_sec = (df[time_col] - t0) / 1e9
y = df[value_col]

# ====== 3) 画图 ======
plt.figure()
plt.plot(t_sec, y, marker='.', linestyle='-')  # 不指定颜色，默认即可
plt.xlabel("Time (s) from start")
plt.ylabel(value_col)
plt.title(f"{value_col} vs time")
plt.grid(True)
plt.tight_layout()

# ====== 4) 保存 + 显示 ======
plt.savefig("plot.png", dpi=200)
plt.show()
