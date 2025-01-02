/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4;
 * indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */

/* Group Member PIDs:
 * 730410170
 * 730518120
 * 730519181
 */

#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>  

int main(int argc, char **argv) {
  int option;
  int write_flag = 0; // Flag for writing (1 for write 0 for read)
  char *device_name = NULL; // Using abstraction that devices are treated as files
  char *results_file = NULL;
  size_t block_size = 0;
  size_t stride = 0;
  struct timeval start, end;
  int random_flag = 0; // Random flag

  // Optstring has all valid options (options that need arguements have colons after)
  // Accept device name, block size, stride size, and optionally random and write flags
  while ((option = getopt(argc, argv, "f:d:b:s:rw")) != -1) {
    switch (option) {
      case 'f': results_file = optarg; break;
      case 'd': device_name = optarg; break;
      case 'b': block_size = atoi(optarg); break;
      case 's': stride = atoi(optarg); break;
      case 'r': random_flag = 1; break;
      case 'w': write_flag = 1; break;
      default:
          printf("Usage: %s -f results_file -d device_name -b block_size (kb) -s stride (kb) [-r] [-w]\n", argv[0]);
    }
  }

  // Open results file (append results to end if it exists)
  int result_fd;
  result_fd = open(results_file, O_WRONLY | O_APPEND | O_CREAT, 0666);

  // Check for file open failure
  if (result_fd < 0) {
    perror("Failed to open result file");
    exit(EXIT_FAILURE);
  }

  // Open device (as file abstraction)
  // Opening with O_DIRECT flag requires memory to be aligned to the nearest 4KB
  int fd;
  if (write_flag) {
    fd = open(device_name, O_WRONLY | O_CREAT | O_DIRECT, 0666);
  } else {
    fd = open(device_name, O_RDONLY | O_CREAT | O_DIRECT, 0666);
  }

  // Check for file open failure
  if (fd < 0) {
    close(result_fd);
    perror("Failed to open device");
    exit(EXIT_FAILURE);
  }

  // Align specified block/stride size with size of 4KB (word alignment)
  block_size = block_size / 4; // 4 KB divide (floor)
  stride = stride / 4; // 4 KB divide (floor)
  block_size = 4 * block_size * 1024;
  stride = 4 * stride * 1024;

  // Allocate a buffer (used for reading and writing and is specified as the size)
  // Populate buffer if writing
  char *buffer;
  buffer = (char*) malloc(sizeof(char) * block_size);
  int elapsed_time_sec = 0;
  int elapsed_time_usec = 0;
  float total_time = 0;
  char result[128];
  float throughput = 0;

  // Populate buffer with visible progress if writing is occuring
  if (write_flag) {
    memset(buffer, 'M', block_size);
  }

  // Compute sizes
  size_t bytes;
  size_t total_size = 100 * 1024 * 1024; // 100 MB
  size_t num_of_blocks = total_size / block_size;

  // Perform specified operation five times (write each time to file for uncertainty and mean calculations)
  for (int run = 0; run < 5; run++) {
    gettimeofday(&start, NULL); // Start timer
    for (size_t i = 0; i < num_of_blocks; i++) {
      // Perform calibrated deterministic IO
      if (write_flag) {
          bytes = write(fd, buffer, block_size);
          fsync(fd); // Flush file contents after write (make sure it is written to disk)
      } else {
          bytes = read(fd, buffer, block_size);
      }

      if (bytes < 0 || bytes != block_size) {
          free(buffer);
          close(fd);
          close(result_fd);
          exit(EXIT_FAILURE);
      }
      
      // Seek by random amount if random flag is active (stride amount otherwise)
      if (random_flag) {
        // Randomly overwrite one of the blocks 
        int random_offset = rand() % num_of_blocks;
        lseek(fd, random_offset * block_size, SEEK_SET);
      } else {
        lseek(fd, stride, SEEK_CUR);
      }
    }
    gettimeofday(&end, NULL); // Stop timer

    // Calculate elapsed time and write results to results file
    elapsed_time_sec = (int)(end.tv_sec - start.tv_sec);
    elapsed_time_usec = (int)(end.tv_usec - start.tv_usec);
    
    // Check for wrapping issues
    if (elapsed_time_usec < 0) {
        elapsed_time_sec -= 1;
        elapsed_time_usec += 1000000;
    }

    total_time = elapsed_time_sec + (elapsed_time_usec * 0.000001);

    // Calculate throughput for this trial
    throughput = (float)total_size / (float)total_time / 1024;

    snprintf(result, sizeof(result), "%s %s: Block Size = %d Bytes, Stride = %d Bytes, Time = %f s, Throughput = %f MB/s\n", random_flag ? "Random" : "Deterministic", write_flag ? "Write" : "Read", (int)block_size, (int)stride, total_time, throughput);
    write(result_fd, result, strlen(result));

    // Print trial results to console and reset cursor for next iteration
    printf("%s %d blocks %s disk in %d seconds.\n", write_flag ? "Wrote" : "Read", (int)num_of_blocks, write_flag ? "to" : "from", elapsed_time_sec);
    lseek(fd, 0, SEEK_SET);
  }

  close(result_fd); // Close results file
  close(fd); // Close IO device or file
  free(buffer);
  exit(EXIT_SUCCESS);
}
