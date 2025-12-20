#!/bin/bash

target_chip="chip_id ch32v20x"
target_do="flash erase_sector wch_riscv 0 last"

wchocd -f wch-riscv.cfg -c "$target_chip" -c init -c halt -c "$target_do" -c exit
