#!/bin/bash
# Automated modernization script for Maximus CBCS

set -e

SRCDIR="/home/kgoodwin/maximus"
SCRIPTDIR="$SRCDIR/scripts"

echo "========================================"
echo "Maximus CBCS Automated Modernization"
echo "========================================"
echo ""

# Step 1: Analyze current errors
echo "[1/6] Analyzing compilation errors..."
bash "$SCRIPTDIR/analyze_errors.sh"
echo ""

# Step 2: Fix header files without guards
echo "[2/6] Adding header guards to .h files..."
header_count=0
for header in $(find "$SRCDIR" -name "*.h" -not -path "*/unix/*" -not -path "*/scripts/*"); do
    if ! grep -q "#ifndef.*_H" "$header" 2>/dev/null; then
        echo "  Processing: $(basename $header)"
        python3 "$SCRIPTDIR/fix_headers.py" "$header" 2>/dev/null || true
        ((header_count++))
    fi
done
echo "  Fixed $header_count header files"
echo ""

# Step 3: Generate forward declarations report
echo "[3/6] Finding functions needing forward declarations..."
bash "$SCRIPTDIR/find_missing_forward_decls.sh" > /tmp/forward_decls_needed.txt
func_count=$(grep -c "^Function:" /tmp/forward_decls_needed.txt || echo "0")
echo "  Found $func_count functions needing forward declarations"
echo "  Report saved to: /tmp/forward_decls_needed.txt"
echo ""

# Step 4: Remove register keywords (simple sed replacements)
echo "[4/6] Removing 'register' keyword..."
register_count=0
for cfile in $(find "$SRCDIR" -name "*.c" -o -name "*.h"); do
    if grep -q "\bregister\s" "$cfile" 2>/dev/null; then
        sed -i 's/\bregister\s\+/ /g' "$cfile"
        ((register_count++))
    fi
done
echo "  Processed $register_count files"
echo ""

# Step 5: Fix common missing includes in .c files
echo "[5/6] Adding common missing includes..."
include_count=0
for cfile in $(find "$SRCDIR/squish" "$SRCDIR/slib" -name "*.c"); do
    # Check if file uses strdup but doesn't have _GNU_SOURCE
    if grep -q "strdup\s*(" "$cfile" && ! grep -q "_GNU_SOURCE" "$cfile"; then
        # Add _GNU_SOURCE at the top after copyright
        sed -i '/\*\//a \\n#define _GNU_SOURCE  /* For strdup */' "$cfile"
        ((include_count++))
    fi

    # Check if file uses string functions but doesn't include string.h
    if grep -qE "(strcpy|strdup|strlen|strcmp)" "$cfile" && ! grep -q "#include <string.h>" "$cfile"; then
        # Add string.h after other system includes
        if grep -q "#include <" "$cfile"; then
            sed -i '/#include </a #include <string.h>' "$cfile" | head -1
        fi
    fi
done
echo "  Added includes to $include_count files"
echo ""

# Step 6: Summary
echo "[6/6] Summary"
echo "  ✓ Headers fixed: $header_count"
echo "  ✓ Functions needing forward decls: $func_count"
echo "  ✓ Register keywords removed: $register_count"
echo "  ✓ Missing includes added: $include_count"
echo ""
echo "Next steps:"
echo "  1. Review /tmp/forward_decls_needed.txt"
echo "  2. Add forward declarations to files listed"
echo "  3. Run 'make squish' to test"
echo ""
