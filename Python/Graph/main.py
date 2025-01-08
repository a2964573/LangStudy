import numpy as np
import matplotlib.pyplot as plt

# n 범위 설정
n_values = np.linspace(1, 10, 100)  # 1부터 10까지 100개 점
time_complexity = n_values ** 4     # O(n^4) 계산

# 그래프 그리기
plt.plot(n_values, time_complexity, label="O(n^4)", color="blue")
plt.xlabel("Input size (n)")
plt.ylabel("Operations (Time Complexity)")
plt.title("Time Complexity of O(n^4)")
plt.legend()
plt.yscale('log')  # y축 로그 스케일 설정(큰 값 시각화 도움)
plt.grid(True)
plt.show()
