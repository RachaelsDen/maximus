#!/usr/bin/env python3
"""
Add proper includes and header guards to .h files
"""

import re
import sys
from pathlib import Path

def has_header_guard(content):
    """Check if file already has header guards"""
    return bool(re.search(r'#ifndef\s+\w+\s*\n\s*#define\s+\w+', content))

def add_header_guard(filepath, content):
    """Add header guard to a .h file"""

    # Generate guard name from filename
    guard_name = Path(filepath).stem.upper() + '_H_INCLUDED'
    guard_name = re.sub(r'[^A-Z0-9_]', '_', guard_name)

    # Find where to insert (after copyright header)
    lines = content.split('\n')

    # Find the end of copyright header (look for last */)
    copyright_end = 0
    for i, line in enumerate(lines):
        if '*/' in line:
            copyright_end = i + 1

    # Split content
    header_part = '\n'.join(lines[:copyright_end])
    body_part = '\n'.join(lines[copyright_end:])

    # Build new content with guards
    new_content = header_part + '\n\n'
    new_content += f'#ifndef {guard_name}\n'
    new_content += f'#define {guard_name}\n\n'

    # Check if we need common includes
    needs_compiler_h = 'near' in body_part or 'far' in body_part or '_stdc' in body_part
    needs_prog_h = 'byte' in body_part or 'dword' in body_part or 'NETADDR' in body_part
    needs_msgapi_h = 'XMSG' in body_part or 'HAREA' in body_part or 'HMSG' in body_part

    includes_added = []
    if needs_compiler_h:
        includes_added.append('#include "compiler.h"  /* For near, far, _stdc keywords */')
    if needs_prog_h:
        includes_added.append('#include "prog.h"      /* For byte, dword, NETADDR types */')
    if needs_msgapi_h:
        includes_added.append('#include "msgapi.h"    /* For XMSG, HAREA, HMSG */')

    if includes_added:
        new_content += '\n'.join(includes_added) + '\n\n'

    new_content += body_part.strip() + '\n\n'
    new_content += f'#endif /* {guard_name} */\n'

    return new_content

def main():
    if len(sys.argv) < 2:
        print("Usage: fix_headers.py <file.h>")
        sys.exit(1)

    filepath = sys.argv[1]

    if not Path(filepath).exists():
        print(f"Error: File {filepath} not found")
        sys.exit(1)

    if not filepath.endswith('.h'):
        print(f"Warning: {filepath} doesn't appear to be a header file")

    print(f"Processing: {filepath}")

    with open(filepath, 'r', encoding='latin-1', errors='ignore') as f:
        content = f.read()

    if has_header_guard(content):
        print("  ✓ Already has header guard")
        sys.exit(0)

    print("  + Adding header guard and includes")

    new_content = add_header_guard(filepath, content)

    # Write back
    with open(filepath, 'w', encoding='latin-1') as f:
        f.write(new_content)

    print("  ✓ Done")

if __name__ == '__main__':
    main()
