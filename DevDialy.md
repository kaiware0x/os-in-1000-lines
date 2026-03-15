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


`Ctrl+A -> c` を押すとQEMUのデバッグコンソールに入れる。
`q` を押すと終了する。

```
C-a h    print this help
C-a x    exit emulator
C-a s    save disk data back to file (if -snapshot)
C-a t    toggle console timestamps
C-a b    send break (magic sysrq)
C-a c    switch between console and monitor
C-a C-a  sends C-a
```

###  起動の仕組み

- `kernel.ld` でメモリマップを定義
- `kernel.c` にカーネルのエントリーポイント `boot()` を実装
- `kernel_main()` にJumpしてそこからはカーネルが自由に処理を実行できる
- `run.sh` を実行するとカーネルのコンパイルと、QEMU上での起動が行われる
