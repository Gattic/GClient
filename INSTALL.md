# Install, Compile, and Run

## Dependencies

`cmake`

`make`

`g++`

Python3

Optional:
`clang-format`
`gdb`

One-liner for convenience:
```
sudo apt-get install cmake make gcc g++ clang-format gdb
```

---

## Compilation

```
mkdir build
cd build
cmake ..
make
```

---

## Installation

make install

---

## Uninstall

make uninstall

## Run

```
cd build
make run
```

### Run Debugging (gdb)

```
cd build
make debug
backtrace # When it crashes
```
