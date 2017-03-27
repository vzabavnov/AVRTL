---
title: Welcome to the AVR Template Library
---

Few days ago, I started my home project and wanted to use AVR microcontroller. I
found a lot of information about hot to program it in C and assembler and almost
nothing in C++. I started my own research and realize – most microcontroller
developers very good know bit/bytes/code performance/size and thinking this why,
but they do not think “abstract” way. When they think about C++ - in their mind
it is heavy abstraction with virtual method and method’s overrides. Of course
C++ will be rejected by this reason, but! ...

This library is my try to reach microcontroller world using power of C++ **templates**.

The AVR Template library provides set of C++ templates to use to program of AVR

MCUs. The goal of this project to bring modern way of coding to microcontroller

World without sacrifice of performance.

Here is simple example to blink a LED:

#include \<atlport.h\>

int main(void) {
	atl::std::PortB.Direction.AsOutput();
	while(1) {
		atl::std::PortB.Set(1 \<\< 3);
		\_delay\_ms(1000);
		atl::std::PortB.Set(0);
		\_delay\_ms(1000);
	}
}
