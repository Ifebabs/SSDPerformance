# Make tests executable
make

# Use file as substitute for devices
# -f results_file -d device/file -b block_size (in KB) -s stride_size (in KB) [-r optional random flag] [-w optional write flag]

## Writing tests
# Different IO Size (constant stride)
./tests -f results.txt -d scratch.txt -b 4 -s 4 -w
./tests -f results.txt -d scratch.txt -b 148 -s 4 -w
./tests -f results.txt -d scratch.txt -b 292 -s 4 -w
./tests -f results.txt -d scratch.txt -b 436 -s 4 -w
./tests -f results.txt -d scratch.txt -b 580 -s 4 -w
./tests -f results.txt -d scratch.txt -b 724 -s 4 -w
./tests -f results.txt -d scratch.txt -b 868 -s 4 -w
./tests -f results.txt -d scratch.txt -b 1024 -s 4 -w

# Different Stride Size (constant IO size)
# IO = 4 KB (every other granuality from above)
./tests -f results.txt -d scratch.txt -b 4 -s 4 -w
./tests -f results.txt -d scratch.txt -b 4 -s 292 -w
./tests -f results.txt -d scratch.txt -b 4 -s 580 -w
./tests -f results.txt -d scratch.txt -b 4 -s 868 -w

# IO = 292 KB
./tests -f results.txt -d scratch.txt -b 292 -s 4 -w
./tests -f results.txt -d scratch.txt -b 292 -s 292 -w
./tests -f results.txt -d scratch.txt -b 292 -s 580 -w
./tests -f results.txt -d scratch.txt -b 292 -s 868 -w

# IO = 580 KB
./tests -f results.txt -d scratch.txt -b 580 -s 4 -w
./tests -f results.txt -d scratch.txt -b 580 -s 292 -w
./tests -f results.txt -d scratch.txt -b 580 -s 580 -w
./tests -f results.txt -d scratch.txt -b 580 -s 868 -w

# IO = 868 KB
./tests -f results.txt -d scratch.txt -b 868 -s 4 -w
./tests -f results.txt -d scratch.txt -b 868 -s 292 -w
./tests -f results.txt -d scratch.txt -b 868 -s 580 -w
./tests -f results.txt -d scratch.txt -b 868 -s 868 -w

# Randomness
./tests -f results.txt -d scratch.txt -b 4 -s 4 -w -r 
./tests -f results.txt -d scratch.txt -b 148 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 292 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 436 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 580 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 724 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 868 -s 4 -w -r
./tests -f results.txt -d scratch.txt -b 1024 -s 4 -w -r

## Reading tests
./tests -f results.txt -d scratch.txt -b 4 -s 4
./tests -f results.txt -d scratch.txt -b 148 -s 4
./tests -f results.txt -d scratch.txt -b 292 -s 4
./tests -f results.txt -d scratch.txt -b 436 -s 4
./tests -f results.txt -d scratch.txt -b 580 -s 4
./tests -f results.txt -d scratch.txt -b 724 -s 4
./tests -f results.txt -d scratch.txt -b 868 -s 4
./tests -f results.txt -d scratch.txt -b 1024 -s 4

# Different Stride Size (constant IO size)
# IO = 4 KB (every other granuality from above)
./tests -f results.txt -d scratch.txt -b 4 -s 4
./tests -f results.txt -d scratch.txt -b 4 -s 292
./tests -f results.txt -d scratch.txt -b 4 -s 580
./tests -f results.txt -d scratch.txt -b 4 -s 868

# IO = 292 KB
./tests -f results.txt -d scratch.txt -b 292 -s 4
./tests -f results.txt -d scratch.txt -b 292 -s 292
./tests -f results.txt -d scratch.txt -b 292 -s 580
./tests -f results.txt -d scratch.txt -b 292 -s 868

# IO = 580 KB
./tests -f results.txt -d scratch.txt -b 580 -s 4
./tests -f results.txt -d scratch.txt -b 580 -s 292
./tests -f results.txt -d scratch.txt -b 580 -s 580
./tests -f results.txt -d scratch.txt -b 580 -s 868

# IO = 868 KB
./tests -f results.txt -d scratch.txt -b 868 -s 4
./tests -f results.txt -d scratch.txt -b 868 -s 292
./tests -f results.txt -d scratch.txt -b 868 -s 580
./tests -f results.txt -d scratch.txt -b 868 -s 868

# Randomness
./tests -f results.txt -d scratch.txt -b 4 -s 4 -r 
./tests -f results.txt -d scratch.txt -b 148 -s 4 -r
./tests -f results.txt -d scratch.txt -b 292 -s 4 -r
./tests -f results.txt -d scratch.txt -b 436 -s 4 -r
./tests -f results.txt -d scratch.txt -b 580 -s 4 -r
./tests -f results.txt -d scratch.txt -b 724 -s 4 -r
./tests -f results.txt -d scratch.txt -b 868 -s 4 -r
./tests -f results.txt -d scratch.txt -b 1024 -s 4 -r
