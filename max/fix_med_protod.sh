#!/bin/bash

cd /home/kgoodwin/maximus/max

for file in med_*.c; do
  if grep -q "^#include \"protod.h\"" "$file"; then
    echo "Skipping $file (already has protod.h)"
  else
    echo "Adding protod.h to $file"
    # Find the line with 'include "maxed.h"'
    line=$(grep -n "^#include \"maxed.h\"" "$file" | head -1 | cut -d: -f1)
    if [ -n "$line" ]; then
      # Insert protod.h after maxed.h
      awk -v n="$line" 'NR==n {print; print "#include \"protod.h\"  /* For function declarations */"; next} {print}' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
    fi
  fi
done

echo "Done!"
