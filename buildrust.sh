#!/bin/sh
RUSTFLAGS="-C relocation-model=pic"
cargo build --release
mv target/release/raw .
strip -s raw
objcopy -O binary raw raw.bin
# ld --oformat=binary --pic-executable raw -o raw.bin
