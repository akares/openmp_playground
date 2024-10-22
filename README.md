This repository contains my reference examples of **OpenMP** API specification for _parallel programming_. It is based on the amazing [Introduction to OpenMP](https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG) by Tim Mattson (Intel).

### Contents

[hello.c](hello.c) — demonstrates how parallelisation is useless without synchronisation.

[pi.c](pi.c) — calculates `Pi` in a good old one-threaded serial way. Used just as a starting point for performance improvements.

[pi_par.c](pi_par.c) — basic usage of `parallel` pragma, `single` construct and `atomic` sync primitive. Forks a few worker threads and aggregates the final result in a thread safe way.

[pi_par_loop.c](pi_par_loop.c) — basic usage of `parallel for` and `reduction` to parallelize the loop and aggregate
the result. Compared to parallel approach above it keeps the code structure close to its serial version.

[utilise_cores.c](utilise_cores.c) — example of how to properly force exactly one thread per core.

...TBA

### Usage

Compile and run all the examples:\
`make test`

Complile and run one specific example:\
`make pi_par.exe && ./pi_par.exe`

_The .exe extension is used just becaue it's easier to ignore it in .gitignore._

Supported platforms are `macOS` and `Linux` (can be modified to run in Windows but nobody cares). See [Makefile](Makefile) for details.
