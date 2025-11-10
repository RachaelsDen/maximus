# Maximus BBS & Squish - Modernized for Linux

**Version:** 3.03b (Modernized 2025-11-10)
**License:** GNU General Public License v2
**Status:** Active Modernization - Core Libraries Building Successfully

## Overview

Maximus is a legendary DOS/OS2 BBS (Bulletin Board System) software package originally developed by Lanius Corporation and Scott J. Dudley. Squish is the companion FidoNet message tosser/scanner. This repository contains a modernized version targeting modern Linux systems with GCC 14.2+.

### What's Included

- **Squish** - FidoNet message tosser/scanner (v1.11)
- **Maximus BBS** - Full-featured bulletin board system (v3.03)
- **MEX** - Maximus Extension Language scripting VM
- **Utilities** - SILT, MAID, MECCA, and other BBS tools

## 🎉 Recent Modernization (2025-11-10)

This codebase has undergone extensive modernization to compile with modern GCC 14.2 on Linux. Over **400+ compilation errors** have been systematically fixed.

### Key Improvements

#### ✅ Completed

1. **POSIX Compliance**
   - Replaced all BSD-style constants (`S_IREAD`/`S_IWRITE` → `S_IRUSR`/`S_IWUSR`)
   - Updated 20+ files across the codebase

2. **Header Modernization**
   - Added proper header guards to all `.h` files
   - Fixed circular dependencies
   - Added missing `#include` directives
   - Modern C standard headers (`<new>` instead of `<new.h>`)

3. **Type Safety**
   - Fixed forward declaration issues for static functions
   - Resolved type mismatches (int vs pointer types)
   - Added proper type definitions where missing

4. **Modern C/C++ Compatibility**
   - Removed obsolete `register` keyword (32 instances)
   - Renamed `nullptr` function to `is_nullptr` (C++ keyword conflict)
   - Fixed C++ extra qualifications
   - Removed `-fpermissive` flag (masks real errors)

5. **Feature Test Macros**
   - Added `_GNU_SOURCE` where needed (strdup, pthread functions)
   - Added `_DEFAULT_SOURCE` for file type constants

6. **Automation Tools Created**
   - `analyze_errors.sh` - Categorizes build errors
   - `generate_forward_decls.py` - Generates forward declarations
   - `fix_headers.py` - Adds header guards and includes
   - `find_missing_forward_decls.sh` - Finds needed declarations
   - `auto_modernize.sh` - Master automation script

### Build Status

| Component | Compilation | Linking | Status |
|-----------|-------------|---------|--------|
| **Squish** | ✅ All .c files | ⚠️ Needs msgapi | **Ready for linking** |
| **slib** | ✅ Complete | ✅ libmax.so (139KB) | **✅ BUILT** |
| **unix** | ✅ Complete | ✅ libcompat.so (28KB) | **✅ BUILT** |
| msgapi | ⚠️ In progress | ❌ | api_sdm.c needs fixes |
| max | ❌ Not started | ❌ | Pending msgapi |
| btree | ❌ | ❌ | C++ modernization needed |

**Latest Milestones:**
- ✅ All Squish source files (17 files) compile successfully
- ✅ slib library fully built - libmax.so (139KB, 100+ source files)
- ✅ unix library fully built - libcompat.so (28KB, DOS/OS2 emulation)
- 🔄 msgapi library in progress - most files compile, 1 file needs fixes

## Building

### Prerequisites

```bash
# Debian/Ubuntu
sudo apt-get install build-essential gcc g++ make bison libncurses-dev libpthread-stubs0-dev

# Required versions
gcc --version     # 14.2+ recommended (tested on 14.2.0)
make --version    # GNU Make 3.79+
```

### Configuration

```bash
# Default installation to /var/max
./configure

# Custom installation prefix
./configure --prefix=/opt/maximus
```

### Build Commands

```bash
# Build everything (when libraries are ready)
make build

# Build only Squish
make squish

# Build only Maximus
make max

# Clean build artifacts
make clean

# Complete clean including generated configs
make distclean
```

### Installation

```bash
# Install everything
make install

# Install only Squish
make squish_install

# Install only Maximus
make max_install

# Install configuration files only
make config_install
```

## Files Modified in Modernization

### Squish (All compile successfully!)

- `s_scan.c/h` - Added forward declarations, fixed missing variables
- `s_toss.c/h` - Added includes, header guards, POSIX constants
- `s_pack.c/h` - Forward declarations, includes
- `s_squash.c/h` - Includes, header guards, POSIX compliance
- `s_hole.c/h` - Fixed struct declarations, includes
- `s_link.c/h` - Comprehensive includes, forward declarations
- `s_match.h` - Header guards
- `s_stat.c` - POSIX constants
- `s_misc.c` - `_GNU_SOURCE`, POSIX constants
- `s_dupe.h` - Complete rewrite with proper includes
- `bld.c` - Various fixes

### Core Libraries (slib - ✅ Complete)

- `slib/compiler_align.h` - Added `<stddef.h>`
- `slib/progprot.h` - Renamed `nullptr` → `is_nullptr`
- `slib/ncheck.c` - Renamed `nullptr` → `is_nullptr`
- `slib/prog.h` - Fixed `shopen` macro
- `slib/typedefs.h` - Fixed ushort/ulong for modern Linux
- `slib/areaapi.c/h` - Added includes, `_GNU_SOURCE`
- `slib/userapi.c/h` - POSIX constants, includes
- `slib/sfopen.c`, `shfopen.c`, `bfile.c`, `cshopen.c`, `fd2n.c`, `lcopy.c` - POSIX constants
- `slib/isdevice.c` - `_DEFAULT_SOURCE`
- `slib/tdelay.c` - `_DEFAULT_SOURCE` for usleep
- `slib/canon.c` - `_DEFAULT_SOURCE` for realpath, added includes
- `slib/mktime.c` - `_DEFAULT_SOURCE` for timezone variable
- `slib/smalloc.c` - `_GNU_SOURCE` for strdup
- `slib/acomp.c` - `_DEFAULT_SOURCE` for strcasecmp
- `slib/vio.c` - `_DEFAULT_SOURCE` for putenv
- `slib/align.c` - `_GNU_SOURCE`, added malloc.h and string.h
- `slib/skiplist.h` - Added compiler.h and prog.h includes
- `slib/prmapi.h` - Added prm.h include for struct definitions
- `slib/strbuf.h` - Added compiler.h and prog.h includes

### Message API (msgapi - ⚠️ In Progress)

- `msgapi/api_sq.h` - Added includes for types
- `msgapi/sq_area.c` - POSIX constants
- `msgapi/sq_read.c` - Forward declarations, fixed cast
- `msgapi/sq_write.c` - Forward declaration for write_xmsg, removed invalid cast
- `msgapi/api_sdm.c` - Added 8 forward declarations (partial fix, more work needed)

### Unix Compatibility Layer (unix - ✅ Complete)

- `unix/include/viocurses.h` - Added `<stddef.h>`
- `unix/include/winstr.h` - Removed incorrect `inline` keywords
- `unix/include/wincomm.h` - Added typedefs.h for BYTE/WORD/DWORD types
- `unix/dossem.c` - `_GNU_SOURCE` for pthread
- `unix/process.c` - Fixed `__FUNCTION__` usage

### Maximus

- `max/prm.h` - Added prog.h include for word type
- `max/max_menu.c`, `max/display.c`, `max/max_init.c` - Updated nullptr calls

### B-Tree Library

- `btree/blkio.h` - Removed C++ extra qualification
- `btree/dbase.cc` - Changed `<new.h>` → `<new>`

### Build System

- `vars.mk` - Removed `-fpermissive` flag
- `vars.mk.configure` - Removed `-fpermissive` flag

## Known Issues & Limitations

### Current Limitations

1. **MEX VM is BROKEN** - Remove all .mex files for now
2. **No serial support** - Network/telnet only (termios implementation incomplete)
3. **Little-endian only** - Big-endian systems will fail on FidoNet packets
4. **File locking** - Multi-node systems may have race conditions
5. **Library builds incomplete** - Squish compiles but libraries need work

### Technical Debt Remaining

- 🔴 **2,059 unsafe `strcpy` calls** - Need conversion to `snprintf`/`strlcpy`
- 🔴 **DOS/OS2/NT conditionals** - 57 files with legacy platform code
- 🔴 **K&R function declarations** - ~10 files need ANSI C conversion
- 🟡 **C++ btree library** - Needs C++11 compliance work
- 🟡 **Memory leaks** - Valgrind analysis pending

### Security Considerations

⚠️ **WARNING:** This is legacy BBS software from the 1990s-2000s. It contains:
- Buffer overflow vulnerabilities (unsafe string functions)
- No modern input validation
- Legacy authentication mechanisms
- DOS memory model assumptions

**NOT RECOMMENDED for internet-facing production use without security audit and hardening.**

## Documentation

- `CLAUDE.md` - Developer guidance for working with this codebase
- `AUTOMATION_SUMMARY.md` - Detailed automation run summary
- `MODERNIZATION_PROGRESS.md` - Complete modernization status
- `HACKING` - Original porting notes from Wes Garland
- `docs/` - Original Maximus documentation

## Project History

- **1989-2003:** Original development by Lanius Corporation/Scott J. Dudley
- **2003:** UNIX port by Wes Garland (v3.03b)
- **2025-11-10:** Major modernization for GCC 14.2/modern Linux

## Contributing

Contributions welcome! Priority areas:

1. **Library builds** - Fix remaining compilation errors in slib, msgapi, unix, max
2. **Security** - Replace unsafe string functions, add input validation
3. **Testing** - Create test suites, verify FidoNet compatibility
4. **Serial I/O** - Complete termios-based serial support
5. **Endianness** - Add big-endian support with proper serialization
6. **Documentation** - Update build/configuration guides

### Development Workflow

```bash
# Make your changes
git add <files>
git commit -m "Description of changes"

# Use automation tools for repetitive fixes
bash scripts/analyze_errors.sh        # Analyze build errors
python3 scripts/fix_headers.py <file> # Fix header issues
bash scripts/auto_modernize.sh        # Run all automation
```

## License

GNU General Public License v2 (GPL-2.0)

Copyright © 1989-2003 Lanius Corporation and Scott J. Dudley
UNIX Port © 2003 Wes Garland
Modernization © 2025

See `LICENSE` file for full license text.

## Credits

- **Original Author:** Scott J. Dudley (Lanius Corporation)
- **UNIX Port:** Wes Garland
- **2025 Modernization:** Automated tooling + systematic fixes
- **Testing:** Bo Simonsen (Squish validation)

## Support & Resources

- **Original FidoNet Echo:** MUFFIN
- **Legacy Website:** maximus.sourceforge.net (may be offline)
- **License:** See `LICENSE` file
- **Bug Reports:** Check repository issues

---

**Last Updated:** 2025-11-10
**Build System:** GNU Make + GCC
**Target Platform:** Linux (x86_64, little-endian)
