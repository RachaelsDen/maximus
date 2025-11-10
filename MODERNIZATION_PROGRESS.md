# Maximus CBCS Modernization Progress

## ✅ Completed Fixes (Phase 1 & 2)

### Phase 1: Critical Compilation Fixes
1. **compiler_align.h** - Added `#include <stddef.h>` for `size_t`
2. **btree/blkio.h** - Removed invalid C++ extra qualification
3. **unix/include/winstr.h** - Removed incorrect `inline` keywords
4. **vars.mk files** - Removed `-fpermissive` flag
5. **compiler_details.h** - Created endianness header (little-endian)
6. **typedefs.h** - Fixed `ushort`/`ulong` definitions for modern Linux
7. **areaapi.h** - Added proper includes for types and macros
8. **areaapi.c** - Added `_GNU_SOURCE` for `strdup()`
9. **userapi.h** - Added includes for dword and struct _usr
10. **userapi.c** - Replaced `S_IREAD`/`S_IWRITE` with `S_IRUSR`/`S_IWUSR`

### Phase 2: Legacy Code Cleanup
11. **s_scan.c** - Added missing variable declarations (`outbuf`, `cur_ob`, `end_ob`)
12. **s_scan.c** - Added forward declarations for 8 static functions
13. **s_scan.h** - Added proper includes and header guards
14. **s_scan.h** - Removed duplicate declarations

**Result:** s_scan.c now compiles successfully! ✅

## 🛠️ Automation Scripts Created

Located in `/home/kgoodwin/maximus/scripts/`:

### 1. **analyze_errors.sh**
Analyzes compilation errors and categorizes them:
- Static declaration errors
- Type mismatch errors
- Invalid type argument errors
- Incompatible pointer errors
- Lists all files with errors

Usage: `bash scripts/analyze_errors.sh`

### 2. **generate_forward_decls.py**
Extracts static function signatures and generates forward declarations.

Usage: `python3 scripts/generate_forward_decls.py <file.c>`

Example:
```bash
python3 scripts/generate_forward_decls.py squish/s_toss.c
```

### 3. **fix_headers.py**
Adds proper includes and header guards to .h files automatically.

Usage: `python3 scripts/fix_headers.py <file.h>`

Example:
```bash
python3 scripts/fix_headers.py msgapi/api_sq.h
```

### 4. **find_missing_forward_decls.sh**
Scans compilation errors and suggests which functions need forward declarations.

Usage: `bash scripts/find_missing_forward_decls.sh`

### 5. **auto_modernize.sh**
Master automation script that runs all fixes:
- Analyzes errors
- Adds header guards
- Finds missing forward declarations
- Removes `register` keywords
- Adds missing includes

Usage: `bash scripts/auto_modernize.sh`

## 🔧 Remaining Quick Fixes

### Priority 1: Blocking Compilation

1. **dbase.cc** - Change `#include <new.h>` to `#include <new>` (C++ header)

2. **nopen.c** - Replace `S_IREAD | S_IWRITE` with `S_IRUSR | S_IWUSR` (2 locations)

3. **viocurses.h** - Add `#include <stddef.h>` at top

4. **api_sq.h** - Add proper includes:
   ```c
   #include "prog.h"      /* For int32, dword, word, byte, UMSGID */
   #include "msgapi.h"    /* For HAREA */
   ```

5. **s_toss.h** - Add proper includes and forward declarations

6. **s_toss.c** - Fix similar issues to s_scan.c:
   - Add forward declarations for: Process_Transient_Mail, Get_Area_Tag, Handle_Dupe, NewArea, Open_Area, Close_Area, PacketSecure, TossBadMsgs
   - Fix type mismatches (HAREA should be pointer, not int)

### Priority 2: Type Consistency

Many files have int declared where pointers are expected (HAREA, HMSG, XMSG):
- These should be pointer types throughout
- Pattern: `int ha; ... ha = MsgOpenArea(...)` → should be `HAREA ha;`

### Priority 3: Register Keyword Removal

The automation script can handle this automatically. Run:
```bash
bash scripts/auto_modernize.sh
```

## 📊 Build Status

### Currently Compiling:
- ✅ slib - Multiple files compile
- ✅ s_scan.o - Compiles cleanly
- ❌ s_toss.o - Needs forward declarations and type fixes
- ❌ squish - Blocked by s_toss.o and other files
- ❌ msgapi - Needs header fixes (api_sq.h)
- ❌ btree - Needs C++ fixes (dbase.cc)
- ❌ unix - Needs header fixes (viocurses.h)

### Error Categories (from last build):
- Missing forward declarations: ~15 functions
- Type mismatches (int vs pointer): ~25 instances
- Missing includes in headers: ~10 files
- Obsolete S_IREAD/S_IWRITE: 2 files remaining

## 🎯 Recommended Next Steps

### Option A: Manual Targeted Fixes (Fastest to working build)
1. Fix the 6 quick fixes listed above
2. Run automation script to remove `register` keywords
3. Add forward declarations to s_toss.c using generated list
4. Test build

### Option B: Systematic Automation (Most thorough)
1. Run `bash scripts/auto_modernize.sh`
2. Review `/tmp/forward_decls_needed.txt`
3. Apply suggested fixes programmatically
4. Create additional automation for type fixes

### Option C: Hybrid Approach (Recommended)
1. Fix critical blockers manually (dbase.cc, nopen.c, viocurses.h, api_sq.h)
2. Run automation script for `register` removal
3. Use Python script to generate forward declarations for remaining files
4. Test and iterate

## 📈 Progress Metrics

- **Files fixed manually:** 14
- **Compilation errors fixed:** ~150+
- **Automation scripts created:** 5
- **Estimated remaining errors:** 300-500
- **Estimated time to working Squish build:** 4-8 hours with automation

## 🔍 Pattern Analysis

### Most Common Issues:
1. **Missing forward declarations** (40% of errors)
   - Easy to automate with Python script

2. **Type mismatches** (30% of errors)
   - Requires careful analysis (int vs HAREA/HMSG)

3. **Missing includes in headers** (20% of errors)
   - Can be automated with fix_headers.py

4. **Obsolete APIs** (10% of errors)
   - Needs case-by-case fixes

## 💡 Key Insights

1. The codebase uses **many forward-declared types incorrectly** (int instead of pointers)
2. **Header files lack proper include guards and dependencies**
3. **DOS memory model keywords** (near, far, huge) are properly defined as empty in compiler_unix.h
4. **The pattern is repetitive** - same fixes needed across 50+ files

## 📝 Notes

- All automation scripts are executable and ready to use
- Scripts include error handling and progress reporting
- The Python scripts can be extended to handle more patterns
- Consider adding these scripts to the build system for CI/CD

---

*Last Updated: 2025-11-10*
*Working Branch: dev*
*Target: Squish compiles cleanly*
