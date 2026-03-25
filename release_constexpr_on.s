	.file	"main.cpp"
# GNU C++20 (GCC) version 15.2.1 20260209 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 15.2.1 20260209, GMP version 6.3.0, MPFR version 4.2.2, MPC version 1.3.1, isl version isl-0.27-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O3 -std=c++20
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB2152:
	.cfi_startproc
# /usr/include/c++/15.2.1/bits/locale_facets.h:1094:       do_widen(char __c) const
	movl	%esi, %eax	# __c, __c
# /usr/include/c++/15.2.1/bits/locale_facets.h:1095:       { return __c; }
	ret	
	.cfi_endproc
.LFE2152:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0:
.LFB3023:
	.cfi_startproc
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx	# __os, __os
	subq	$16, %rsp	#,
	.cfi_def_cfa_offset 32
# /usr/include/c++/15.2.1/ostream:67:     { return flush(__os.put(__os.widen('\n'))); }
	movq	(%rdi), %rax	# __os_1(D)->_vptr.basic_ostream, __os_1(D)->_vptr.basic_ostream
	movq	-24(%rax), %rax	# MEM[(long int *)_2 + -24B], MEM[(long int *)_2 + -24B]
	movq	240(%rdi,%rax), %rdi	# MEM[(const struct __ctype_type * *)_5 + 240B], _14
# /usr/include/c++/15.2.1/bits/basic_ios.h:51:       if (!__f)
	testq	%rdi, %rdi	# _14
	je	.L8	#,
# /usr/include/c++/15.2.1/bits/locale_facets.h:884: 	if (_M_widen_ok)
	cmpb	$0, 56(%rdi)	#, MEM[(const struct ctype *)_14]._M_widen_ok
	je	.L5	#,
# /usr/include/c++/15.2.1/bits/locale_facets.h:885: 	  return _M_widen[static_cast<unsigned char>(__c)];
	movsbl	67(%rdi), %esi	# MEM[(const struct ctype *)_14]._M_widen[10],
.L6:
# /usr/include/c++/15.2.1/ostream:67:     { return flush(__os.put(__os.widen('\n'))); }
	movq	%rbx, %rdi	# __os,
	call	_ZNSo3putEc@PLT	#
# /usr/include/c++/15.2.1/ostream:67:     { return flush(__os.put(__os.widen('\n'))); }
	addq	$16, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 16
# /usr/include/c++/15.2.1/ostream:89:     { return __os.flush(); }
	movq	%rax, %rdi	# _8,
# /usr/include/c++/15.2.1/ostream:67:     { return flush(__os.put(__os.widen('\n'))); }
	popq	%rbx	#
	.cfi_def_cfa_offset 8
# /usr/include/c++/15.2.1/ostream:89:     { return __os.flush(); }
	jmp	_ZNSo5flushEv@PLT	#
.L5:
	.cfi_restore_state
# /usr/include/c++/15.2.1/bits/locale_facets.h:886: 	this->_M_widen_init();
	movq	%rdi, 8(%rsp)	# _14, %sfp
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT	#
# /usr/include/c++/15.2.1/bits/locale_facets.h:887: 	return this->do_widen(__c);
	movq	8(%rsp), %rdi	# %sfp, _14
	movl	$10, %esi	#,
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx	#, tmp114
	movq	(%rdi), %rax	# MEM[(const struct ctype *)_14].D.51947._vptr.facet, MEM[(const struct ctype *)_14].D.51947._vptr.facet
	movq	48(%rax), %rax	# MEM[(int (*) () *)_24 + 48B], _25
	cmpq	%rdx, %rax	# tmp114, _25
	je	.L6	#,
	movl	$10, %esi	#,
	call	*%rax	# _25
	movsbl	%al, %esi	# _22,
	jmp	.L6	#
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold:
.LFSB3023:
.L8:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -16
# /usr/include/c++/15.2.1/bits/basic_ios.h:52: 	__throw_bad_cast();
	call	_ZSt16__throw_bad_castv@PLT	#
	.cfi_endproc
.LFE3023:
	.text
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	.section	.text.unlikely
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	" + "
.LC2:
	.string	" = "
.LC3:
	.string	" - "
.LC4:
	.string	" * "
.LC5:
	.string	" / "
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB2412:
	.cfi_startproc
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:104:     std::cout << a << " + " << b << " = " << s << std::endl;
	movl	$5, %esi	#,
	leaq	_ZSt4cout(%rip), %rdi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC1(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:104:     std::cout << a << " + " << b << " = " << s << std::endl;
	movq	%rax, %rbx	#, _3
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _3,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:104:     std::cout << a << " + " << b << " = " << s << std::endl;
	movq	%rbx, %rdi	# _3,
	movl	$10, %esi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC2(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:104:     std::cout << a << " + " << b << " = " << s << std::endl;
	movq	%rax, %rbx	#, _5
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _5,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:104:     std::cout << a << " + " << b << " = " << s << std::endl;
	movl	$15, %esi	#,
	movq	%rbx, %rdi	# _5,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:121: 	return __pf(*this);
	movq	%rax, %rdi	# _7,
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:105:     std::cout << a << " - " << b << " = " << dif << std::endl;
	movl	$5, %esi	#,
	leaq	_ZSt4cout(%rip), %rdi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC3(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:105:     std::cout << a << " - " << b << " = " << dif << std::endl;
	movq	%rax, %rbx	#, _9
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _9,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:105:     std::cout << a << " - " << b << " = " << dif << std::endl;
	movq	%rbx, %rdi	# _9,
	movl	$10, %esi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC2(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:105:     std::cout << a << " - " << b << " = " << dif << std::endl;
	movq	%rax, %rbx	#, _11
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _11,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:105:     std::cout << a << " - " << b << " = " << dif << std::endl;
	movl	$-5, %esi	#,
	movq	%rbx, %rdi	# _11,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:121: 	return __pf(*this);
	movq	%rax, %rdi	# _13,
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:106:     std::cout << a << " * " << b << " = " << mult << std::endl;
	movl	$5, %esi	#,
	leaq	_ZSt4cout(%rip), %rdi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC4(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:106:     std::cout << a << " * " << b << " = " << mult << std::endl;
	movq	%rax, %rbx	#, _15
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _15,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:106:     std::cout << a << " * " << b << " = " << mult << std::endl;
	movq	%rbx, %rdi	# _15,
	movl	$10, %esi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC2(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:106:     std::cout << a << " * " << b << " = " << mult << std::endl;
	movq	%rax, %rbx	#, _17
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _17,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:106:     std::cout << a << " * " << b << " = " << mult << std::endl;
	movl	$50, %esi	#,
	movq	%rbx, %rdi	# _17,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:121: 	return __pf(*this);
	movq	%rax, %rdi	# _19,
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:107:     std::cout << a << " / " << b << " = " << div << std::endl;
	movl	$5, %esi	#,
	leaq	_ZSt4cout(%rip), %rdi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC5(%rip), %rsi	#,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:107:     std::cout << a << " / " << b << " = " << div << std::endl;
	movq	%rax, %rbx	#, _21
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movq	%rax, %rdi	# _21,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:107:     std::cout << a << " / " << b << " = " << div << std::endl;
	movq	%rbx, %rdi	# _21,
	movl	$10, %esi	#,
	call	_ZNSolsEi@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	movl	$3, %edx	#,
	leaq	.LC2(%rip), %rsi	#,
	movq	%rax, %rdi	# _23,
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:107:     std::cout << a << " / " << b << " = " << div << std::endl;
	movq	%rax, %rbx	#, _23
# /usr/include/c++/15.2.1/bits/ostream.h:739: 	__ostream_insert(__out, __s,
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:232:       { return _M_insert(__f); }
	movsd	.LC6(%rip), %xmm0	#,
	movq	%rbx, %rdi	# _23,
	call	_ZNSo9_M_insertIdEERSoT_@PLT	#
# /usr/include/c++/15.2.1/bits/ostream.h:121: 	return __pf(*this);
	movq	%rax, %rdi	# _24,
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0	#
# /mnt/HDD_DataStore/! 01 Programming_Project_Save/01 C++/Learn/main.cpp:111: }
	xorl	%eax, %eax	#
	popq	%rbx	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE2412:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC6:
	.long	0
	.long	1071644672
	.ident	"GCC: (GNU) 15.2.1 20260209"
	.section	.note.GNU-stack,"",@progbits
