# Aibreann #

This is a smoke test to ensure the kernel is suitable for testing.  We have created a small disk image with a collection of files, symlinks, directories and fifos. We will run every operation, from our library, and target every file object on the disk image.  We expect the kernel to not core.  And we expect the file system images to fsck cleanly.

If the kernel does core, you should be able to remove functions from the operational set to determine which kernel call is causing the problems.  This example does not use any special test strategies to reduce the test code to the minimum required to reproduce the kernel core.

Here are some example bugs that should be easy to reproduce with this smoke test:
  * [kern/98064: Crash with FIFOs (named pipes) and truncate()](http://www.freebsd.org/cgi/query-pr.cgi?pr=98064)
  * [kern/98116: Crash with sparse files and execve()](http://www.freebsd.org/cgi/query-pr.cgi?pr=98116)


```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# run the smoke test
AIBREAN=${DIR?}/file-system-stress-testing-framework-read-only/src/aibreann
gmake -C ${AIBREAN?} check
```

# Brannagh #

This is a classic kernel stress test. This example does not use any special test strategies to reduce the test code to the minimum required to reproduce the kernel core. We run every test operation randomly waiting for the kernel to core.  This test may take hours to cause the core and we have no idea what operations are critical to reproducing the kernel bug.

```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# run the classic stress test
BRANNAGH=${DIR?}/file-system-stress-testing-framework-read-only/src/brannagh
gmake -C ${BRANNAGH?} check

```

# Clodagh #

This is the first example test to use a special test strategy reduce the test code to the minimum required to reproduce the kernel core.

```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# setup /mnt to be your filesystem under test
cd /mnt
mkdir 111 222 333 444 555 666 777 888 999 aaa bbb ccc ddd eee fff
install  -c -s -f uchg -m 0777 /usr/bin/true true
install  -c -s -f uchg -m 0777 /usr/bin/true 111/true

CLODAGH=${DIR?}/file-system-stress-testing-framework-read-only/src/clodagh
cd ${CLODAGH?}

# create a list of operations to execute
LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -c -f big.tgz

# now execute our list of operations
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh big.tgz

```

To start with, the test executation is similar to Brannagh.  But this time, we used `mkpax` to generate a list of operations.  And `clodagh` is just an execution engine -- it will only execute the operations in the order found in the archive.  Now we can [create strategies](FreeBSDKern159971.md) to reduce the archive to a minimal number of operations require to reproduce the kernel core.