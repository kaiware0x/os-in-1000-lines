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

## 2026-03-22

### 生バイナリ

ベースアドレスから実際にメモリ上に展開される内容が入ったもの。
今回は簡単のために生バイナリを使う。

一般的なOSでは、以下2つは分かれた形式を使う。

- 展開先の定義 (elf相当)
- メモリ上のデータ

### addr2line

```sh
$ ls /usr/bin/llvm-addr2line*
/usr/bin/llvm-addr2line-11  /usr/bin/llvm-addr2line-14
```

## 2026-03-24

### ディスクリプタ

「何かを記述した構造体」のこと。
OS/ハードウェアの文脈では「処理してほしい内容を書いたメモ」のようなイメージ。

### ページテーブルエントリ

```
合計 32-bit

[Page Frame Number]  [Flags]
^^^^^^^^^^^^^^^^^^^   ^^^^^
上位20-bit            下位12-bit (4KiB)
物理ページ番号        そのページについてのフラグ
```

ページフレームは 4KiB アラインメントされているため、各ページテーブルエントリ(32-bit) のうち、12-bit(4KiB) を除いた 20-bit 分の情報があれば良い。
余った 12-bit は各ページフレームにおけるフラグを格納するスペースとして有効活用する。
