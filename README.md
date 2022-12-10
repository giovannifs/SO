# SO

## FORK

Temos um trecho de código com exemplo do uso do comando fork, responsável por criar um processo filho a partir do processo em execução.

### Compilando o programa
```gcc exemplo_fork.c -o exemplo_fork```

### Executando o programa
```./exemplo_fork```

## WORD COUNT

Temos diferentes versões para um programa que conta a quantidade de palavras de uma árvore de arquivos específica.
* *wc_single_proc.c:* versão que conta palavras considerando um único processo;
* *wc_multi_proc.c:* versão que conta palavras considerando um múltiplos processos, no entanto, sem comunicação entre os diferentes processos.

### Gerando a árvore de arquivos
```bash ./make_dataset```

A execução desse script bash vai gerar um diretório ```dataset```, que deve ser usado como argumento de entrada para as diferentes versões do programa.

### Compilando o programa
```gcc wc_single_proc.c -o wc_single_proc```

### Executando o programa
```./wc_single_proc dataset/```
