import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import sem, t

file_path = 'SSD_Mac.xlsx'
sheet_data = pd.read_excel(file_path, sheet_name='Sheet1')

# Calculate means and 95% confidence intervals
def calculate_means_and_cis(data, group_by_column, value_column):
    grouped = data.groupby(group_by_column)[value_column]
    means = grouped.mean()
    std_errors = grouped.apply(sem)
    confidence_intervals = std_errors * t.ppf(0.975, grouped.count() - 1)  # 95% CI
    return means, confidence_intervals

# Plot with error bars
def plot_with_error_bars(data, x_col, y_col, group_by_col, title, x_label, y_label):
    unique_groups = data[group_by_col].unique()
    plt.figure(figsize=(10, 6))
    for group in unique_groups:
        subset = data[data[group_by_col] == group]
        means, cis = calculate_means_and_cis(subset, x_col, y_col)
        plt.errorbar(means.index, means, yerr=cis, label=f'{group}', capsize=5, marker='o', linestyle='-')
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.legend(title=group_by_col)
    plt.grid(True)
    plt.show()

# Separate data for reads and writes and randoms
read_data = sheet_data[sheet_data['Operation'].str.contains("Read", case=False, na=False)]
write_data = sheet_data[sheet_data['Operation'].str.contains("Write", case=False, na=False)]
random_read_data = sheet_data[sheet_data['Operation'].str.contains("Random Read", case=False, na=False)]
random_write_data = sheet_data[sheet_data['Operation'].str.contains("Random Write", case=False, na=False)]

# Plot I/O Size for writes
plot_with_error_bars(write_data, 
                     x_col='Block Size (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Stride (bytes)', 
                     title='Write Throughput vs I/O Size',
                     x_label='Block Size (bytes)', 
                     y_label='Throughput (MB/s)')

# Plot I/O Size for reads
plot_with_error_bars(read_data, 
                     x_col='Block Size (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Stride (bytes)', 
                     title='Read Throughput vs I/O Size',
                     x_label='Block Size (bytes)', 
                     y_label='Throughput (MB/s)')

# I/O Stride Experiment: Plot throughput vs Stride for various block sizes (writes)
plot_with_error_bars(write_data, 
                     x_col='Stride (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Block Size (bytes)', 
                     title='Write Throughput vs I/O Stride',
                     x_label='Stride Size (bytes)', 
                     y_label='Throughput (MB/s)')

# I/O Stride Experiment: Plot throughput vs Stride for various block sizes (reads)
plot_with_error_bars(read_data, 
                     x_col='Stride (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Block Size (bytes)', 
                     title='Read Throughput vs I/O Stride',
                     x_label='Stride Size (bytes)', 
                     y_label='Throughput (MB/s)')

# Random I/Os Experiment: Plot throughput vs I/O Size for random I/Os (writes)
plot_with_error_bars(random_write_data, 
                     x_col='Block Size (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Stride (bytes)', 
                     title='Write Throughput vs I/O Size for Random I/Os',
                     x_label='Block Size (bytes)', 
                     y_label='Throughput (MB/s)')

# Random I/Os Experiment: Plot throughput vs I/O Size for random I/Os (reads)
plot_with_error_bars(random_read_data, 
                     x_col='Block Size (bytes)', 
                     y_col='Throughput (MB / s)', 
                     group_by_col='Stride (bytes)', 
                     title='Read Throughput vs I/O Size for Random I/Os',
                     x_label='Block Size (bytes)', 
                     y_label='Throughput (MB/s)')
