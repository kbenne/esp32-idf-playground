# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands
- **Build project**: `idf.py build`
- **Clean build**: `idf.py clean`
- **Flash to device**: `idf.py -p PORT flash` (replace PORT with your device port)
- **Monitor output**: `idf.py -p PORT monitor`
- **Build & flash**: `idf.py -p PORT flash monitor`
- **Configure**: `idf.py menuconfig`

## Code Style Guidelines
- **C Standard**: C99
- **Formatting**: 4-space indentation, no tabs
- **Naming**:
  - Functions/variables: snake_case
  - Constants/macros: UPPER_CASE
  - File names: lowercase with hyphens for spaces
- **Headers**: Include guards with `#ifndef FILENAME_H_` pattern
- **Error Handling**: Use ESP-IDF's `ESP_LOGx` macros for logging
- **Documentation**: Follow Doxygen-style comments (see existing files)
- **BACnet**: Follow BACnet stack coding conventions for BACnet components