# cp
Competitive programming solutions, algorithms, and templates.

## Templates
- C++ template: `templates/cpp_template.cpp`

## Problem Scaffolding
- Create a new task with `./scripts/new_problem.sh <group/problem>`
- Or use `./scripts/new_problem.sh <group> <problem>`
- Example: `./scripts/new_problem.sh codeforces/round-1000 a`
- This creates `problems/<group>/<problem>/` with `main.cpp`, `input.txt`, `output.txt`, and `README.md`

## Run Workflow
- Run a problem with `./scripts/run.sh <problem-dir>`
- Example: `./scripts/run.sh problems/codeforces/round-1000/a`
- Use `--debug` to compile with `-DLOCAL` and debug symbols
- The binary is written to `.build/main`, input is read from `input.txt`, and stdout is also saved to `output.txt`
