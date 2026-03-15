/*
Linker Script
*/

ENTRY(boot) /* カーネルのエントリーポイントは boot 関数である */

SECTIONS {
    . = 0x80200000; /* カーネルのベースアドレス */

    /* コード領域 */
    .text :{
        KEEP(*(.text.boot)); /* 必ず .text.boot セクションを先頭にする */
        *(.text .text.*);
    }

    /* 定数データ領域 Read-only data */
    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    /* Read-write data */
    .data : ALIGN(4) {
        *(.data .data.*);
    }

    /* Read-write data (初期値ゼロの変数) */
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    . = ALIGN(4);
    . += 128 * 1024; /* 128KB */
    __stack_top = .;
}
