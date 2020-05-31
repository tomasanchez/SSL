==233== Memcheck, a memory error detector
==233== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==233== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==233== Command: ./test
==233== Parent PID: 138
==233== 
==233== error calling PR_SET_PTRACER, vgdb might block
==233== Conditional jump or move depends on uninitialised value(s)
==233==    at 0x10870A: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x1087D5: append (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x1087A7: power (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x1088AA: main (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233== 
==233== Conditional jump or move depends on uninitialised value(s)
==233==    at 0x10870A: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x10871B: getLength (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233== 
==233== Conditional jump or move depends on uninitialised value(s)
==233==    at 0x4C32D08: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==233==    by 0x4EBC9D1: puts (ioputs.c:35)
==233==    by 0x1088E0: main (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233== 
==233== Invalid free() / delete / delete[] / realloc()
==233==    at 0x4C30D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==233==    by 0x10893F: main (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==  Address 0x1089d4 is in a r-x mapped file /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test segment
==233== 
==233== 
==233== HEAP SUMMARY:
==233==     in use at exit: 270 bytes in 1 blocks
==233==   total heap usage: 2 allocs, 2 frees, 1,294 bytes allocated
==233== 
==233== 270 bytes in 1 blocks are definitely lost in loss record 1 of 1
==233==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==233==    by 0x108787: power (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233==    by 0x1088AA: main (in /mnt/c/Users/imtom/dev_utn/SSL/04-Strings/test)
==233== 
==233== LEAK SUMMARY:
==233==    definitely lost: 270 bytes in 1 blocks
==233==    indirectly lost: 0 bytes in 0 blocks
==233==      possibly lost: 0 bytes in 0 blocks
==233==    still reachable: 0 bytes in 0 blocks
==233==         suppressed: 0 bytes in 0 blocks
==233== 
==233== For counts of detected and suppressed errors, rerun with: -v
==233== Use --track-origins=yes to see where uninitialised values come from
==233== ERROR SUMMARY: 13 errors from 5 contexts (suppressed: 0 from 0)
