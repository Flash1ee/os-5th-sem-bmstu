# Читатели-писателт

## Процессы-читатели
- могут только читать;  
- могут работать параллельно, поскольку они друг другу не мешают

# Процессы-писатели
- могут только писать(менять данные);
- могут работать только в режиме монопольного доступа: 
  - только один писатель может получить доступ к разделяемой переменной, причем, когда работает писатель, то другие писатели и читатели не могут получить доступ к этой переменной.
