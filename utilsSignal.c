#include "utilsSignal.h"
#include "utils.h"

//UTILSIGNAL
void setSignalsIgnore() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

//UTILSIGNAL
void handlerVACINADO(int sig) {
    setSignalsIgnore();
    char c;
    switch (sig) {
        case SIGINT:
            c = 'C';
            break;
        case SIGQUIT:
            c = '\\';
            break;
        case SIGTSTP:
            c = 'Z';
            break;
        default:  //Never gonna happen
            c = '.';
            break;
    }
    printf("Não adianta me enviar o sinal por Ctrl-%c. Estou vacinado!!\n", c);
    setSignalsVacinado();
}

//UTILSIGNAL
void setSignalsVacinado() {
    signal(SIGINT, handlerVACINADO);
    signal(SIGQUIT, handlerVACINADO);
    signal(SIGTSTP, handlerVACINADO);
}

//UTILSIGNAL
void handlerSIGUSR1(int signal) {
    printf("SIGNAL: %d PID: %d\n", signal, getpid());
    exit(signal);
}

//UTILSIGNAL
void handler_MORTEDOACSH(int sig) {
    kill(-1 * getpid(), SIGKILL);  //matando filhos
    exit(1);
}

//UTILSIGNAL
void setPaiSignals() {
    signal(SIGUSR2, handler_MORTEDOACSH);
    prctl(PR_SET_PDEATHSIG, SIGUSR2);  //Recebe SIGUSR2 se o acsh morrer
}