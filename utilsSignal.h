#if !defined(UTILSIGNAL_H)
#define UTILSIGNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/signal.h>
#include <unistd.h>

// Ignora os sinais emitidos geralmente pelo teclado
void setSignalsIgnore();

// Imprime a mensagem de Vacinado no caso de sinais enviados geralmente pelo teclado
void setSignalsVacinado();

// Configura os signals de um pai de sessão
void setPaiSignals();

#endif /*UTILSIGNAL_H*/