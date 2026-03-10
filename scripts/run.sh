#!/usr/bin/env bash

set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
  ./scripts/run.sh [--debug|--release] [problem-dir|source-file]

Examples:
  ./scripts/run.sh problems/codeforces/round-1000/a
  ./scripts/run.sh --debug problems/codeforces/round-1000/a
  ./scripts/run.sh problems/codeforces/round-1000/a/main.cpp

Behavior:
  - Compiles main.cpp into .build/main
  - Runs with input from input.txt if it exists
  - Prints stdout and saves it to output.txt
EOF
}

mode="release"
target="."

while [[ $# -gt 0 ]]; do
    case "$1" in
        --debug)
            mode="debug"
            ;;
        --release)
            mode="release"
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            if [[ "$target" != "." ]]; then
                echo "Only one problem path can be provided." >&2
                usage >&2
                exit 1
            fi
            target="$1"
            ;;
    esac
    shift
done

if [[ -d "$target" ]]; then
    problem_dir="$(cd "$target" && pwd)"
    source_file="$problem_dir/main.cpp"
elif [[ -f "$target" ]]; then
    source_file="$(cd "$(dirname "$target")" && pwd)/$(basename "$target")"
    problem_dir="$(dirname "$source_file")"
else
    echo "Target not found: $target" >&2
    exit 1
fi

if [[ ! -f "$source_file" ]]; then
    echo "Source file not found: $source_file" >&2
    exit 1
fi

build_dir="$problem_dir/.build"
binary_path="$build_dir/main"
input_file="$problem_dir/input.txt"
output_file="$problem_dir/output.txt"

mkdir -p "$build_dir"

common_flags=(
    -std=c++20
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
)

if [[ "$mode" == "debug" ]]; then
    compile_flags=(-O0 -g -DLOCAL)
else
    compile_flags=(-O2)
fi

echo "Compiling $source_file"
g++ "${common_flags[@]}" "${compile_flags[@]}" "$source_file" -o "$binary_path"

echo "Running $binary_path"
if [[ -f "$input_file" ]]; then
    "$binary_path" < "$input_file" | tee "$output_file"
else
    "$binary_path" | tee "$output_file"
fi

echo "Saved output to $output_file"
