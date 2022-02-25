# Branch trace

Pin tool to collect information about branch instructions during a program's execution.

## Build
 * Download [Intel's Pin framework](https://www.intel.com/content/www/us/en/developer/articles/tool/pin-a-dynamic-binary-instrumentation-tool.html) (tested with version 3.21)
 * Extract to a directory of your choice
 * From this directory (`branch_traces`, not the Pin framework)
   * `export PIN_ROOT=path/to/your/pin/framework`
   * `make`

## Use
```
$PIN_ROOT/pin -t obj-intel64/branch_traces.so -o branches.out -- <your program here>
```

The specified output file will be a CSV file with one line per branch executed. Each line contains the branch's program counter, the target branch address, and whether the branch was taken or not.

```
pc, target, taken
0x7f25b1748e41, 0x7f25b1748eb6, 0
0x7f25b1748e72, 0x7f25b1748e9f, 1
0x7f25b1748ea3, 0x7f25b1748e78, 0
0x7f25b1748eb4, 0x7f25b1748e9f, 1
0x7f25b1748ea3, 0x7f25b1748e78, 0
0x7f25b1748eb4, 0x7f25b1748e9f, 1
0x7f25b1748ea3, 0x7f25b1748e78, 1
0x7f25b1748e82, 0x7f25b1749070, 1
```

