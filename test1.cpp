SYSCALL_DEFINE3(GetMax, int a, int b, int c)
{
  if(a > b)
    b = a;
  if(b > c)
    c = b;
  return c;
}

SYSCALL_DEFINE0(GetPID)
{
    return current->pid;
}

SYSCALL_DEFINE1 (GetCMD, char *buf)
{
    strcpy(buf, current->comm);
    return 0;
}

asmlinkage long sys_GetMax(int a, int b, int c);
asmlinkage long sys_GetPID();
asmlinkage long GetCMD(char __user*, buf);


#define __NR_getmax 548
__SYSCALL(__NR_getmax, sys_GetMax)

#define __NR_getpid 549
__SYSCALL(__NR_getpid, sys_GetPID)

#define __NR_getcmd 550
__SYSCALL(__NR_getcmd, sys_GetCMD)
