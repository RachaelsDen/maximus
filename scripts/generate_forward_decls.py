#!/usr/bin/env python3
"""
Extract static function definitions and generate forward declarations
"""

import re
import sys
from pathlib import Path

def extract_static_functions(filepath):
    """Extract static function signatures from a C file"""

    with open(filepath, 'r', encoding='latin-1', errors='ignore') as f:
        content = f.read()

    # Pattern to match static function definitions
    # Matches: static <return_type> near <function_name>(<params>)
    pattern = r'^static\s+(\w+(?:\s+\w+)?)\s+(?:near|far|huge)?\s*(\w+)\s*\([^)]*\)'

    functions = []
    lines = content.split('\n')

    i = 0
    while i < len(lines):
        line = lines[i].strip()

        # Check if this looks like a static function definition
        if line.startswith('static ') and '(' in line:
            # Collect the full signature (might span multiple lines)
            signature = line

            # If line doesn't end with ) or {, keep collecting
            while i < len(lines) - 1 and not (')' in signature and ('{' in lines[i] or lines[i+1].strip().startswith('{'))):
                i += 1
                signature += ' ' + lines[i].strip()

            # Extract just the declaration part (before the {)
            if '{' in signature:
                signature = signature[:signature.index('{')].strip()

            # Clean up the signature
            signature = re.sub(r'\s+', ' ', signature)  # Normalize whitespace

            # Only add if it looks like a complete function signature
            if signature.endswith(')'):
                functions.append(signature + ';')

        i += 1

    return functions

def generate_forward_declarations(filepath):
    """Generate forward declaration block for a C file"""

    functions = extract_static_functions(filepath)

    if not functions:
        return None

    # Build the forward declaration block
    decls = ["/* Forward declarations for static functions */"]
    for func in functions:
        decls.append(func)

    return '\n'.join(decls)

def main():
    if len(sys.argv) < 2:
        print("Usage: generate_forward_decls.py <file.c>")
        sys.exit(1)

    filepath = sys.argv[1]

    if not Path(filepath).exists():
        print(f"Error: File {filepath} not found")
        sys.exit(1)

    print(f"Analyzing: {filepath}")
    print()

    decls = generate_forward_declarations(filepath)

    if decls:
        print(decls)
    else:
        print("No static functions found or all already have forward declarations")

if __name__ == '__main__':
    main()
