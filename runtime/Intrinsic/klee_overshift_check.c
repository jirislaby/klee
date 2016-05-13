//===-- klee_overshift_check.c ---------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <klee/klee.h>

/* This instrumentation call is used to check for overshifting.
 * If we do try to do x << y or x >> y
 * where
 *   bitWidth = sizeof(x)*8
 *   shift = y
 *
 * then we can detect overshifting (which has undefined behaviour).
 */
void klee_overshift_check(unsigned long long bitWidth, unsigned long long shift) {
  extern int printf (const char *__restrict __format, ...);
  if (shift >= bitWidth) {
    /* Maybe we shouldn't throw an error because
     * overshifting can be non-fatal? Perhaps
     * we should generate a test case but carry
     * on executing the state with a warning?
     */
    if (klee_is_symbolic(shift)) {
	    printf("overflow BW=%llu < concr_S=%llu sym_S will follow\n",
			    bitWidth, klee_get_valuell(shift));
	    klee_print_expr("overflow", shift);
    } else
	    printf("overflow BW=%llu < S=%llu\n", bitWidth, shift);
    klee_report_error("IGNORED", 0 /*Ignored */, "overshift error", "overshift.err");
  }
}


