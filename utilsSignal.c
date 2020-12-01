#include "utilsSignal.h"

// Ignora os sinais emitidos geralmente pelo teclado
void setSignalsIgnore() {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

//Lida com os sinais emitidos pelo teclado ao ACSH
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

// Imprime a mensagem de Vacinado no caso de sinais enviados geralmente pelo teclado
void setSignalsVacinado() {
    signal(SIGINT, handlerVACINADO);
    signal(SIGQUIT, handlerVACINADO);
    signal(SIGTSTP, handlerVACINADO);
}

// Caso o ACSH morra / receba o comando exit,
// seus processos filhos (Os pais das sessões) são avisados pelo sinal SIGUSR2
// e esse Handler faz o pai da sessão matar os filhos e a si mesmo
void handler_MORTEDOACSH(int sig) {
    kill(-1 * getpid(), SIGKILL);  //matando os comandos/processos filhos em execução
    exit(1);
}

// Configura os sinais do pai de uma sessão
void setPaiSignals() {
    signal(SIGUSR2, handler_MORTEDOACSH);
    prctl(PR_SET_PDEATHSIG, SIGUSR2);  //Recebe SIGUSR2 se o acsh morrer
}