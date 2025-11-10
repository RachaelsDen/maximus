#!/bin/bash

# Script to add required MAX_* defines and protod.h to all .c files in max directory
# that are missing them

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Change to max directory (relative to script location)
cd "$SCRIPT_DIR/max"

for file in *.c; do
    # Skip if file doesn't exist
    [ -f "$file" ] || continue

    # Check if file already has MAX_INCL_VARS (already fixed)
    if grep -q "^#define MAX_INCL_VARS" "$file"; then
        echo "Skipping $file (already has MAX_INCL_VARS)"
        continue
    fi

    # Find the first #include line number
    first_include_line=$(grep -n "^#include" "$file" | head -1 | cut -d: -f1)

    if [ -z "$first_include_line" ]; then
        echo "Skipping $file (no #include found)"
        continue
    fi

    echo "Fixing $file (inserting at line $first_include_line)"

    # Create the defines to insert
    defines='
#define MAX_INCL_VARS     /* Include global variable declarations from max_v.h */
#define MAX_INCL_LANGUAGE /* Include language structures and definitions */
#define MAX_INCL_LANGLTH  /* Include english.lth language strings */
#define MAX_LANG_global   /* Global language strings */
'

    # Use awk to insert the defines before the first #include
    awk -v line="$first_include_line" -v defs="$defines" '
        NR == line {
            print defs
        }
        { print }
    ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"

    # Now add protod.h include after prog.h if not already present
    if ! grep -q '^#include "protod.h"' "$file"; then
        # Find prog.h include line
        prog_h_line=$(grep -n '^#include "prog.h"' "$file" | head -1 | cut -d: -f1)

        if [ -n "$prog_h_line" ]; then
            # Insert protod.h include after prog.h
            awk -v line="$prog_h_line" '
                NR == line {
                    print
                    print "#include \"protod.h\"  /* For function declarations */"
                    next
                }
                { print }
            ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
        fi
    fi
done

echo "Done!"
