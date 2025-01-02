# Disk Performance Analysis

## Overview
This project provides an in-depth analysis of disk performance on two systems: the **MacBook Air** and **Lenovo ThinkPad**. The experiments measure read and write throughput across various block sizes, I/O stride sizes, and access patterns (deterministic vs. random). These insights can help optimize file I/O operations and guide hardware or software-level enhancements.

---

## Experiments and Findings

### MacBook Air

#### Read Throughput vs. I/O Size:
- **Key Trends**:
  - Throughput increases with block size, peaking at **3.3-3.7 GB/s** for both deterministic and random reads.
  - Small block sizes (e.g., 4096 bytes) yield low throughput (**140-180 MB/s**), due to high I/O overhead.
  - Optimal performance plateaus beyond block sizes of **0.7(1e6) bytes**.

#### Write Throughput vs. I/O Size:
- **Key Trends**:
  - Throughput follows a similar pattern as reads, peaking between **1.4-1.6 GB/s** for deterministic writes.
  - Small block sizes exhibit poor performance (**60-70 MB/s**), highlighting inefficiencies in small transfer operations.

#### I/O Stride Experiment:
- **Key Observations**:
  - Small strides (e.g., 4096 bytes) show consistently higher throughput.
  - Larger strides introduce variability but maintain high throughput due to SSD architecture minimizing sector alignment overhead.

#### Random I/O Performance:
- **Key Observations**:
  - Random reads show slightly lower peak throughput than deterministic reads.
  - Random writes are on par with deterministic writes, indicating robust SSD controller optimizations.

---

### Lenovo ThinkPad

#### Read Throughput vs. I/O Size:
- **Key Trends**:
  - Sharp increase in throughput with block size, peaking at **350,000-370,000 MB/s**.
  - Smaller block sizes show very low throughput, while performance plateaus beyond **741,376 bytes**.

#### Write Throughput vs. I/O Size:
- **Key Trends**:
  - Throughput scales well with block size, peaking at **170,000 MB/s** for large blocks.
  - Small block sizes perform poorly (**1200-2200 MB/s**) but improve significantly with larger sizes.

#### I/O Stride Experiment:
- **Key Observations**:
  - Small strides result in consistent performance.
  - SSD architecture minimizes performance degradation with high strides.

#### Random I/O Performance:
- **Key Observations**:
  - Similar scaling trends to deterministic operations, with slightly reduced peak throughput.
  - Random writes improve with larger block sizes, peaking at **160,000-180,000 MB/s**.

---

## Key Insights
1. **Block Size Impacts Throughput**:
   - Larger block sizes improve throughput by reducing overhead, with pronounced gains on the MacBook Air.
   - Both systems plateau in performance with block sizes beyond specific thresholds (e.g., 0.7(1e6) bytes on MacBook Air).

2. **Random vs. Sequential Patterns**:
   - Random I/O operations show a slight performance hit compared to deterministic ones, reflecting minimal optimization for random workloads.

3. **Device-Specific Observations**:
   - The MacBook Air demonstrates robust SSD optimization, with read speeds consistently **2-2.3x** faster than write speeds.
   - The Lenovo ThinkPad shows effective scaling with block size but reaches performance limits earlier than the MacBook Air.

4. **SSD vs. HDD Implications**:
   - SSDs mitigate stride size and random access penalties effectively, unlike HDDs that would show significant degradation under similar conditions.

5. **Optimization Strategies**:
   - Use larger block sizes for better throughput.
   - Optimize small write operations using caching and buffering.
   - Implement intelligent prefetching to reduce random access penalties.

---

## Future Work
To gain a broader understanding of disk performance:
- Extend tests to include **HDDs** for comparison.
- Experiment with **mixed read/write workloads**.
- Evaluate performance across different file systems and hardware configurations.

---

## Conclusion
This analysis underscores the importance of tailoring file I/O operations to system-specific characteristics. By optimizing block sizes and leveraging SSD capabilities, applications can achieve significant performance gains. These insights are valuable for both developers and system architects looking to enhance storage performance.

---

## How to Use
This project contains various resources and scripts to analyze disk performance on MacBook Air and Lenovo ThinkPad. 
Below are the instructions for utilizing the different components of the project:

### Prerequisites
Ensure you have the following installed:
- Python (for graphing scripts)
- Make (to compile the C program)
- An environment that supports executing shell scripts

### Running the Performance Evaluation
1. **Compile the C Program**:
   Open your terminal, navigate to the project directory, and run:
   ```
   make
   ```
2. **Execute Tests**:
   You can run the tests by executing the `tests.sh` script:
   ```
   ./tests.sh
   ```
   
3. **Analyze Results**:
   After running the tests, the results will be logged. You can open the generated results file to analyze the performance metrics.
   
### Generating Graphs
1. **For Lenovo ThinkPad**:
   To visualize the data for Lenovo, run:
   ```
   python LenovoThinkpadGraphs.py
   ```
2. **For MacBook Air**:
   To visualize the data for MacBook Air, run:
   ```
   python MacAirGraphs.py
   ```
   
### Additional Resources
For a more detailed explanation of the methodology and findings, refer to the **Disk Performance Analysis (MacBook Air and Lenovo ThinkPad).pdf** document.
Feel free to contact me if you have any questions or need further assistance!

---

## License
This project is licensed under the MIT License.

## Contributors
I worked on this project with Ethan Crook and Martim Gaspar for our OS class.


