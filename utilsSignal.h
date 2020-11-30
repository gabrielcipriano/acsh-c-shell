#if !defined(UTILSIGNAL_H)
#define UTILSIGNAL_H

void setSignalsIgnore();

void handlerVACINADO(int sig);

void setSignalsVacinado();

void handlerSIGUSR1(int signal);

void handler_MORTEDOACSH(int sig);

void setPaiSignals();

#endif /*UTILSIGNAL_H*/