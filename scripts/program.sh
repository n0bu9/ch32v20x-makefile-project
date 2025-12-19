#!/bin/bash

target_chip="chip_id ch32v20x"
target_do="program ../build/app.elf"    # Program the ELF file to the chip
target_do_other="wlink_reset_resume"    # Reset and resume the chip

wchocd -f wch-riscv.cfg -c "$target_chip" -c init -c halt -c "$target_do" -c $target_do_other -c exit
