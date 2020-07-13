# RWR_GPU

## Build 

```bash
mkdir build
cd build
cmake ..
make
./RWR
```

## Run

Execute a test on a random graph:

```bash
./RWR -T
```

Compare sequential and parallel on two input graph:

```bash
./RWR <graph_path> <expression_matrix_path>
```
