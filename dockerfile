FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
	gcc-riscv64-unknown-elf \
	binutils-riscv64-unknown-elf \
	make \
	build-essential \
	&& rm -rf /var/lib/apt/lists/*
WORKDIR /workspace