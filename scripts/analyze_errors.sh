#!/bin/bash
# Analyze compilation errors and categorize them

cd /home/kgoodwin/maximus

echo "=== Compilation Error Analysis ==="
echo ""

# Try to build and capture errors
make squish 2>&1 > /tmp/build_errors.txt

echo "1. Static declaration follows non-static errors:"
grep "static declaration.*follows non-static" /tmp/build_errors.txt | \
    sed 's/.*error: static declaration of //' | \
    sed "s/' follows.*//" | \
    sort -u | \
    awk '{print "   - " $0}'

echo ""
echo "2. Type mismatch errors (int vs pointer):"
grep -E "makes (integer from pointer|pointer from integer)" /tmp/build_errors.txt | \
    wc -l | \
    awk '{print "   Count: " $0}'

echo ""
echo "3. Invalid type argument errors:"
grep "invalid type argument of" /tmp/build_errors.txt | \
    wc -l | \
    awk '{print "   Count: " $0}'

echo ""
echo "4. Incompatible pointer type errors:"
grep "incompatible pointer type" /tmp/build_errors.txt | \
    wc -l | \
    awk '{print "   Count: " $0}'

echo ""
echo "5. Files with errors:"
grep "error:" /tmp/build_errors.txt | \
    sed 's/:.*$//' | \
    sort -u | \
    awk '{print "   - " $0}'

echo ""
echo "Full error log saved to: /tmp/build_errors.txt"
