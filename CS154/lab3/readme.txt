lnordquist

svn update errors:
==1750706== Warning: invalid file descriptor -1 in syscall close()
==1750706== 
==1750706== HEAP SUMMARY:
==1750706==     in use at exit: 145,853 bytes in 1,512 blocks
==1750706==   total heap usage: 17,105 allocs, 15,593 frees, 2,076,632 bytes allocated
==1750706== 
==1750706== LEAK SUMMARY:
==1750706==    definitely lost: 0 bytes in 0 blocks
==1750706==    indirectly lost: 0 bytes in 0 blocks
==1750706==      possibly lost: 2,784 bytes in 27 blocks
==1750706==    still reachable: 131,189 bytes in 1,396 blocks
==1750706==                       of which reachable via heuristic:
==1750706==                         length64           : 1,256 bytes in 20 blocks
==1750706==                         newarray           : 1,744 bytes in 29 blocks
==1750706==         suppressed: 0 bytes in 0 blocks
==1750706== Rerun with --leak-check=full to see details of leaked memory

1) Errors in vgme 0,1,2: all three are 
"Conditional jump or move depends on uninitialised value(s)"
2) vgme 0 was created by a stack allocation error, the other two are heap
alloc issues
3) valgrind outputs almost exactly the same thing, the only difference is line
numbers -- not sure what I'm supposed to be seeing here
4)