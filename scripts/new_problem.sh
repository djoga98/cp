#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEMPLATE_PATH="$ROOT_DIR/templates/cpp_template.cpp"
PROBLEMS_DIR="$ROOT_DIR/problems"

usage() {
    cat <<'EOF'
Usage:
  ./scripts/new_problem.sh <group/problem>
  ./scripts/new_problem.sh <group> <problem>

Examples:
  ./scripts/new_problem.sh codeforces/round-1000/a
  ./scripts/new_problem.sh codeforces/round-1000 a

Creates:
  problems/<group>/<problem>/main.cpp
  problems/<group>/<problem>/input.txt
  problems/<group>/<problem>/output.txt
EOF
}

slugify_path() {
    local value="$1"
    value="${value// /-}"
    value="$(printf '%s' "$value" | tr '[:upper:]' '[:lower:]')"
    value="$(printf '%s' "$value" | sed -E \
        -e 's/[^a-z0-9._\/-]+/-/g' \
        -e 's@/+@/@g' \
        -e 's@(^|/)-+@\1@g' \
        -e 's@-+($|/)@\1@g' \
        -e 's@(^/|/$)@@g')"
    printf '%s' "$value"
}

if [[ ! -f "$TEMPLATE_PATH" ]]; then
    echo "Template not found: $TEMPLATE_PATH" >&2
    exit 1
fi

group_raw=""
problem_raw=""

case "$#" in
    1)
        group_raw="$(dirname "$1")"
        problem_raw="$(basename "$1")"
        if [[ "$group_raw" == "." ]]; then
            group_raw="misc"
        fi
        ;;
    2)
        group_raw="$1"
        problem_raw="$2"
        ;;
    *)
        usage
        exit 1
        ;;
esac

group_path="$(slugify_path "$group_raw")"
problem_name="$(slugify_path "$problem_raw")"

if [[ -z "$group_path" || -z "$problem_name" ]]; then
    echo "Group and problem name must contain at least one valid character." >&2
    exit 1
fi

problem_dir="$PROBLEMS_DIR/$group_path/$problem_name"

if [[ -d "$problem_dir" ]] && find "$problem_dir" -mindepth 1 -print -quit | grep -q .; then
    echo "Problem already exists: $problem_dir" >&2
    exit 1
fi

mkdir -p "$problem_dir"

cp "$TEMPLATE_PATH" "$problem_dir/main.cpp"
: > "$problem_dir/input.txt"
: > "$problem_dir/output.txt"

cat > "$problem_dir/README.md" <<EOF
# $problem_raw

Group: $group_raw
Path: ${group_path}/${problem_name}
EOF

echo "Created problem scaffold:"
echo "  $problem_dir/main.cpp"
echo "  $problem_dir/input.txt"
echo "  $problem_dir/output.txt"
echo "  $problem_dir/README.md"
