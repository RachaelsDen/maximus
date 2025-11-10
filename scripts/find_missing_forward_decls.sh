#!/bin/bash
# Find functions that need forward declarations based on compile errors

if [ ! -f /tmp/build_errors.txt ]; then
    echo "Running make to capture errors..."
    cd /home/kgoodwin/maximus
    make squish 2>&1 > /tmp/build_errors.txt
fi

echo "=== Functions Needing Forward Declarations ==="
echo ""

# Extract functions with "static declaration follows non-static" error
grep "static declaration.*follows non-static" /tmp/build_errors.txt | \
    sed 's/.*error: static declaration of //' | \
    sed "s/' follows.*//" | \
    sed "s/'//g" | \
    sort -u | \
    while read func; do
        # Find which file defines this function
        file=$(grep -r "^static.*$func\s*(" --include="*.c" /home/kgoodwin/maximus 2>/dev/null | \
               head -1 | \
               cut -d: -f1)

        if [ -n "$file" ]; then
            echo "Function: $func"
            echo "  File: $file"

            # Extract the full signature
            grep -A5 "^static.*$func\s*(" "$file" | \
                grep -v "^--$" | \
                sed '/^{/,$d' | \
                tr '\n' ' ' | \
                sed 's/  */ /g' | \
                awk '{print "  Signature: " $0 ";"}'
            echo ""
        fi
    done
