```
mkdir build
cd build
cmake .. -DTOOLCHAIN_PREFIX=/opt/xpack-riscv-none-elf-gcc-12.2.0-3
```

Linker script could be found in [vendor/Ld/Link.ld](https://github.com/crosstyan/ch32v003-template/blob/f6d2296ecd3d0873e1d23d7e220adf67f61784e0/Ld/Link.ld).

To flash the firmware you need [minichlink](https://github.com/cnlohr/ch32v003fun/tree/master/minichlink).

```bash
minichlink -w <bin> flash -b
```

[macOS build tuning](https://github.com/crosstyan/ch32v003fun/commit/2aa519b999e90d2de7cc1589ee867941b4284522)

[wlink](https://github.com/crosstyan/wlink) is also interesting.

## See also

- [CH32V003 のファームウェアのビルド環境を整える](https://74th.hateblo.jp/entry/2023/03/12/092600)
