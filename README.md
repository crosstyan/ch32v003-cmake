# ch32v003 minimal example

use [ch32v003fun](https://github.com/cnlohr/ch32v003fun) as vendor library.

## build

Download [riscv-none-elf-gcc-xpack](https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack) and put it somewhere, e.g. `/opt/xpack-riscv-none-elf-gcc-12.2.0-3`

```bash
mkdir build
cd build
cmake .. -DTOOLCHAIN_PREFIX=/opt/xpack-riscv-none-elf-gcc-12.2.0-3 -G Ninja -DCMAKE_BUILD_TYPE=Release
```

## Note

- I'm using [clangd](https://clangd.llvm.org/) as LSP server, so I have to add `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to generate `compile_commands.json`
- an example of [`settings.json`](.vscode/settings.template.json) for [Visual Studio Code](https://code.visualstudio.com/) is provided
- Of course you could use [CLion](https://www.jetbrains.com/clion/)
- check [`src/config/funconfig.h`](src/config/funconfig.h) for configuration
