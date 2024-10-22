This repository contains reference examples of **OpenMP** API specification for _parallel programming_. It is based on the amazing [Introduction to OpenMP](https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG) by Tim Mattson (Intel).

### Contents

[pi_par.c](pi_par.c) — basic usage of `parallel` pragma, `single` construct and `atomic` sync primitive. Forks a few worker threads and aggregates the final result in a thread safe way.

...TBA

### Usage

Compile and run all the examples:\
`make test`

Complile and run one specific example:\
`make pi_par.exe && ./pi_par.exe`

_The .exe extension is used just becaue it's easier to ignore it in .gitignore._

Supported platforms are `macOs` and `Linux` (can be modified to run in Windows but nobody cares). See [Makefile](Makefile) for details.
