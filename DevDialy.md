# DevDialy

## 2026-03-15

### セットアップ

```sh
sudo apt update && sudo apt install -y clang llvm lld qemu-system-riscv32 curl
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
```

### [Compiler Explorer](https://godbolt.org/z/8cbvEdbc9)

オンラインコンパイラ。Cソースとそのアセンブリを見れる。

### インラインアセンブリ

```
__asm__ __volatile__("アセンブリ" : 出力オペランド : 入力オペランド : アセンブリ中で破壊するレジスタ);
```
