# SmithWaterman
A C++ implementation of the famous local alignment algorithm.

## Compilation
To execute the program you can use the makefile provided.
```
make
```

## Usage
Execute main.x and give the input the program asks you.

## Example
```
./main
```

```
Input first sequence:
TGTTACGG
Input second sequence:
GGTTGACTA
Input gap penalty:
2
Input match score:
3
Input mismatch penalty:
3
computing alignment...
sequence 1: GGTT-AC
sequence 2: GGTTGAC
positions: 1 1 2 3 3 4 5 
scores: 3 3 6 9 7 10 13 
```
