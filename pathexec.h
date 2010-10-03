#ifndef PATHEXEC_H
#define PATHEXEC_H

extern void pathexec_run(char *file,char **argv,char **envp);
extern int pathexec_env(char *s,char *t);
extern void pathexec(char **argv);

#endif
