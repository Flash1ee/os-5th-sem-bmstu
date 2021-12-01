# include <iostream.h>
# include <signal.h>
void catch_sig(int sig_numb)
{
    signal(sig_numb, catch_sig);
    cout<<”catch_sig”<<sig_numb<<endl;
}
int main(void)
{
   signal(SIGNERM, catch_sig);
   signal(SIGINT, SIG_IGN);
   signal(SIGSEGV, SIG_DFL);
}