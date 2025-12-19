#!/bin/bash

target_chip="chip_id ch32v20x"
target_do="verify_image ../build/app.bin"   # Verify the binary file against the chip

wchocd -f wch-riscv.cfg -c "$target_chip" -c init -c halt -c "$target_do" -c exit
