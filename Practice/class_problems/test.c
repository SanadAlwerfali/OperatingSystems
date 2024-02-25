#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>


int foo = 0;
int main ()
{
int bar [2] , baz ;
pipe ( bar );
pid_t pid = fork ();
if ( pid > 0)
{
wait (& baz );
printf ( "%d -%d -%d -%d \n" , foo , WEXITSTATUS ( baz ) , bar [0] , bar [1]);

read ( bar [0] , & bar [1] , sizeof ( int ));
printf ( "%d -%d -%d -%d \n" , foo , WEXITSTATUS ( baz ) , bar [0] , bar [1]);


}
else
{
foo = pid ;
write ( bar [1] , & pid , sizeof ( pid ));
printf ( "%d -%d \n" , pid , bar [0]);
return bar [0];
}
return 1;
}