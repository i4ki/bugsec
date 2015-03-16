

## Introdução ##

Para  uma perfeita  compreensão do assembly é  essencial que se compreenda a
arquitetura do  computador, a organização  do sistema, o modelo de memória, etc, pois trabalharemos a nível de hardware.

Esse  capítulo será  apenas uma introdução  ao funcionamento do computador, voltaremos nesse assunto com bastante frequencia durante o curso.

## Pensando como um Computador ##

Antes de iniciar com o aprendizado de assembly é importante saber que você terá muito mais facilidade de compreender e programar em assembly se entender como que o processador interpreta seus programas.

A  CPU somente entende sequencias de zeros e uns lidos da memória. A única forma
de interagir com o hardware é desta forma, cada padrão de zeros e uns significam
uma  instrução diferente. Esses  códigos  são  chamados  "Operation Codes",  ou
opcodes.
Por exemplo, na arquitetura x86 a sequencia de bits:
```
     11000001
```
representa a instrução em assembly:
```
     mov ax, bx
```
É importante  saber que  há uma equivalência  1:1 entre assembly  e o  código de máquina, ou  seja, cada  instrução elementar  do  assembly  (mov, add, sub, jmp, push, pop,  etc) representa uma e  somente uma  instrução em código  de máquina.
Isso  não é 100% verdade  atualmente, devido à evolução dos assemblers (software
que converte  código ASM em objeto)  e das arquiteturas,  mas é muito bom pensar
deste modo.

Lembre-se que isto  é completamente diferente de como funcionam as linguagens de
alto nível, em que  um "for" por  exemplo, implementa  dezenas  de  operações em
código de máquina.
Entender isso é fundamental, pois você compreendendo o seu sistema operacional e
a arquitetura do seu computador, voce poderá programar cada passo (instrução) do
processador (step-by-step).

## Arquitetura de Computadores ##

A  "Arquitetura de um  computador" é a  teoria por  detrás do seu funcionamento,
esse termo abrange muito mais conceitos como a organização do hardware ou do seu
sistema operacional.

A arquitetura  80x86 é  baseada na arquitetura  de  [John Von Neumann.](http://en.wikipedia.org/wiki/John_von_Neumann)
Esse modelo  não teve mudanças significativas desde a década de 50 (época da sua
idealização  por Neumann), mas  os  conceitos,  implementações,  técnicas,  etc,
evoluíram muito.
Não vamos entrar em detalhes da implementação desta arquitetura,você pode buscar
material adicional nas referências `[2], [3] e [4]`.

Neste modelo  de arquitetura  todas as  operações (computações) são ocorridas na
CPU (Central Process Unit). Como já falei, a CPU irá ler as instruções que estão
na memória juntamente com os dados fornecidos de entrada (INPUT). Veja o
diagrama abaixo:

```
Diagrama 1: 
________________________________________________________________________________
               ┌────────────┐                        ┌────┐
               │            ├────────────────────────┤    │                         
               │    CPU     │           B            │ M  │
               │            ├────────┐  U  ┌─────────┤ E  │
               │  ┌──────┐  │        │  S  │         │ M  │
               │  │ ALU  │  │        │     │         │ O  │
               │  └──────┘  │    ┌───┴─────┴───┐     │ R  │
               │            │    │             │     │ I  │
               └────────────┘    │ Input/Output│     │ A  │
                                 │             │     │    │
                                 └─────────────┘     │    │
                                                     └────┘

                    Arquitetura de Von Neumann
________________________________________________________________________________
```

## System Bus (Barramento) ##

Chama-se  System Bus[5](5.md)  (Barramento em português) ao  que faz a  ligação  entre os
componentes do hardware do  computador. São chamados de linhas de  comunicação e
são encarregadas de transferir as informações entre os hardwares.

Existem  vários barramentos  diferentes,  todos têm a  mesma  função, transmitir
informações/dados a diferença é quem interligam, o que trasmitem e como o fazem.
Na arquitetura de Von Neumann existem três importantes Barramentos, que são:

  * Data Bus:     Transfere dados entre o CPU e a memória e/ou I/O. Veja mais em `[6]`.

  * Address Bus:  Provê os endereços de memória o qual serão transmitidos pelo Data Bus. Veja mais em `[7]`.

  * Control Bus:  Uma  coleção de  sinais elétricos  que dirão  como a  CPU irá se  comunicar com os Bus. Controla os outros barramentos, garantindo que não haja colisão nem perda de informações. Veja mais em `[8]`.

## CPU (Central Process Unit) ##

É aqui que a mágica acontece.
A CPU  ou a "Unidade  Central de Processamento"  pode ser  dividida em 4 partes:

  * Control Unit: Busca, decodifica e executa as instruções. É o cérebro do CPU.

  * Execution Unit: É onde são executadas as operações e cálculos do seu programa. Contém a  ALU (Arithmethic Logic Unit), onde  realiza-se  as operações aritméticas e lógicas.
  * Registradores:  São memórias de pequena capacidade  (16 ou 32 bits) usadas para armazenar informações  temporárias dentro do processador. Podem ser comparados à variáveis,  em que podemos  armazenar valores temporariamente. Serão extensamente abordados no decorrer do curso.
  * Flags: Armazena informações sobre o estado da última instrução do processador.

Veja no diagrama a seguir como esses componentes interagem:

```
Diagrama 2
________________________________________________________________________________

      ┌────────────┐          ┌────────────┐          ┌─────────────────┐ 
      │            │          │            │ <──────> │  Registradores  │          
      │  Control   │          │ Execution  │          └─────────────────┘
      │    Unit    │ <──────> │    Unit    │          ┌─────────────────┐
      │            │          │            │ <──────> │      Flags      │
      └────────────┘          └────────────┘          └─────────────────┘

                Interação entre os componentes do processador
________________________________________________________________________________
```

## Registradores ##

A maioria  das operações do  processador envolvem processar  dados. O problema é
há uma distância  real entre o processador e a  memória (onde esses dados  estão
guardados), então toda a vez que o processador precisa acessar dados na memória,
ele  precisa aguardar a  informação percorrer o trajeto entre o CPU e a memória.

Os  dados são transmitidos como sinais elétricos pelo barramento numa velocidade
muito alta, mas o grande tráfego de  informação CPU `<-->` Memoria gera um "delay"
considerável. Para minimizar  esse problema, o  CPU possui  memórias internas de
pequena capacidade para armazenarem informações temporárias.

Essas  memórias chamam-se  registradores e  variam em quantidade, capacidade  de
armazenamento, etc de  familia de processadores para  outra. Mas apesar de  eles
ajudarem muito na velocidade do processador há o contra de que só é possivel ter
um número limitado de registradores no processador e esses poucos  registradores
devem manipular os dados de quase todas as instruções da CPU.


### Tipos de Registradores do Intel 80386 ###

  * Propósito Geral:  8 registradores livres para armazenar dados enquanto esperam para serem processados.
  * Segmento:         6 registradores usados para manipular o acesso a memória.
  * Instrução:        1 registrador que aponta para a posição na memória da próxima instrução a ser executada pelo processador.
  * Ponto Flutuante:  8 registradores usados para arithméticas de ponto flutuante.
  * Controle:         5 registradores usados para determinar os modos de  operação do processador.
  * Debug:            8 registradores usados para manter informações de  debugging do processador.

### Registradores de Propósito Geral ###

Esses são registradores que podem ser utilizados para diversos fins, todos esses
8 registradores podem ser alterados livremente pelo programador mas é importante
saber que alguns deles possuem funções extras e seus valores podem ser alterados
pelo processador e/ou pelo compilador automaticamente. Então você deve saber que
enquanto estiver trabalhando com  registradores que possuem alguma função  extra
deve-se tomar algum cuidado. Trataremos desse detalhe no capítulo |FIXME|.

Os processadores Intel  da familia x86 anteriores ao 80386 operavam com 16 bits,
ou seja,  cada registrador de propósito geral podia  comportar 16 bits de dados.
Esses registradores eram: AX, BX, CX, DX, SI, DI, BP e SP.
Veja no diagrama 3 a relação dos registradores de propósito geral da família x86
anteriores ao 80386:

```
Diagrama 3:
________________________________________________________________________________

    ┌────┐
    │ AX │<───┬── Registrador Acumulador
    ├────┤    │
    │ BX │<───┼── Registrador Base
    ├────┤    │
    │ CX │<───┼── Registrador Contador
    ├────┤    │
    │ DX │<───┴── Registrador de dados
    └────┘

    ┌────┐
    │ DI │<───┬── Indice Destino (Destination Index)
    ├────┤    │
    │ SI │<───┴── Indice Fonte (Source Index)
    └────┘

    ┌────┐
    │ SP │<───┬── Apontador da Pilha (Stack Pointer)
    ├────┤    │
    │ BP │<───┴── Apontador Base (Base Pointer)
    └────┘
                    
                    Registradores de Uso Geral
________________________________________________________________________________
```

Os registradores AX, BX, CX e DX podem ser  sub-divididos em dois  registradores
de 8 bits cada. Por exemplo, os bits menos significativos (Least Significant Bit
ou LSB) do registrador AX podem ser acessados por AL (Low Order) e os bits  mais
significativos (Most Significant Bit ou MSB) podem ser acessados por AH. Veja no
diagrama 4.

```
Diagrama 4
________________________________________________________________________________

      ┌─────────────AX──────────────┐     ┌─────────────BX──────────────┐         
      │                             │     │                             │
      ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐     ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
      │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │     │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
      └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘     └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
      15            8 7             0     15            8 7             0
      │             │ │             │     │             │ │             │
      └──────AH─────┘ └──────AL─────┘     └──────BH─────┘ └──────BL─────┘

              Representação dos Registradores de 16 bits
________________________________________________________________________________
```

Os processadores 80386 em diante passaram a vir com  registradores de  uso geral
de  32 bits,  foram chamados  registradores extendidos e  substituíram todos  os
registradores de uso geral das versões anteriores acrescentando um 'E' na frente
do seu nome. Por exemplo, o registrador acumulador AX tornou-se EAX, BX passou a
se chamar EBX, e assim por diante.

Os registradores extendidos contém os registradores de 16 bits. Veja o  diagrama
5:

```
Diagrama 5:
────────────────────────────────────────────────────────────────────────────────
                                  
      ┌────────────────────────────EAX──────────────────────────────┐
      │                                                             │
      ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
      │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
      └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
     31                               15            8 7             0
                                      │             │ │             │
                                      └─────AH──────┘ └─────AL──────┘
                                      │                             │
                                      └─────────────AX──────────────┘

                Modelos dos Registradores Extendidos
────────────────────────────────────────────────────────────────────────────────
```

Assim podemos acessar os primeiros 16 bits de EAX como AX e os primeiros  8 bits
com AL.

### Registradores de Segmento ###

Os registradores de segmento são usados para referenciar endereços de memória no
sistema. O Intel 80386 permite três tipos diferentes de acesso à memória  do
sistema. Qual  destes métodos de  memória será usado fica  a escolha do  sistema
operacional. Os três tipos são:

  * Flat Memory Model (Modelo de Memória Plano)
  * Segmented Memory Model (Modelo de Memória Segmentada)
  * Real Address-Mode (Modo de Endereçamento Real)

O modelo Flat  apresenta toda a memória do  sistema como um espaço de  endereços
contiguo. Todos os códigos das instruções, os dados e a pilha (Stack) são
contidos no mesmo espaço de endereços. Nesse sistema cada local de memória pode
ser acessado por um endereço específico, chamado de "endereço linear".

No modelo de memória segmentada a memória do sistema é dividida em grupos de
segmentos independentes, referenciados por ponteiros nos registradores de
segmento. Cada registrador de segmento aponta para um espaço de dados diferente,
por exemplo, o registrador CS (Code Segment) aponta para o segmento de memória
das instruções do código do programa, o registrador de segmento DS
(Data Segment) aponta para os dados do programa e o registrador SS (Stack
Segment) aponta para a pilha (Stack).

Veja no diagrama 6, a relação dos registradores de segmento:

```
Diagrama 6:
────────────────────────────────────────────────────────────────────────────────
   ┌────┐
   │ CS │<───┬── Segmento de Código (Code Segment)
   ├────┤    │
   │ DS │<───┼── Segmento de Dados (Data Segment)
   ├────┤    │
   │ ES │<───┼── Segmento de Dados Extra (Extra Data Segment)
   ├────┤    │
   │ FS │<───┼── Segmento de Dados Extra
   ├────┤    │
   │ GS │<───┼── Segmento de Dados Extra
   ├────┤    │
   │ SS │<───┴── Segmento de Pilha (Stack Segment)
   └────┘
                  Registradores de Segmento do 80386
────────────────────────────────────────────────────────────────────────────────
```

Se o sistema operacional utiliza o modelo de endereços Real do processador,
então todos os registradores de segmento são inicializados com 0 e podem ser
usados livremente como se fossem registradores de propósito geral. Nesse modo,
os endereços de memória real são diretamente acessados pelo programa.

### Registrador Ponteiro de Instrução (Instruction Pointer) ###

O ponteiro de instruções ou IP para os processadores anteriores ao 80386 e EIP
após, aponta para a próxima instrução a ser executada pelo processador.

Uma aplicação não pode modificar diretamente o EIP, isso só pode ser feito com
os mnemonicos de saltos condicionais como JMP, JE, call, etc. Se o sistema
utiliza o modelo de memória Flat, então EIP aponta para um endereço linear da
memória, mas caso utilize o modelo segmentado, então EIP aponta para um endereço
de memória lógico, referenciado pelo registrador de segmento CS.

## Memória ##

Memória, ou  neste caso,  memória RAM  (Random Access Memory), é  um dispositivo
físico que possui a capacidade de armazenar dados temporários.
Ela pode ser pensada como um array de bytes, veja o diagrama abaixo:

```
Diagrama 6:
________________________________________________________________________________
                    _______________
                   |_______________| - 0
                   |_______________| - 1
                   |_______________| - 2
                   |      ...      | - ...
                   |_______________|
                   |_______________| - 4.294.967.292
                   |_______________| - 4.294.967.293
                   |_______________| - 4.294.967.294
                   |_______________| - 4.294.967.295

 Representação de uma memória para processadores 80386
 (32 bits).
 O máximo de endereços é: 2**32 = 4294967296 ~ 4 GB
________________________________________________________________________________
```

A  memória pode armazenar um máximo de 2<sup>n</sup> endereços. Onde n é número de bits
do barramento de  endereços (address bus). Esse número vária de processador para
processador e pode ser 16, 24, 32, etc.

Na arquitetura 80x86 cada  endereço de  memória pode ocupar apenas 1 byte. Então
se  desejarmos armazenar  outros  tipos de dados,  como um word  ou  doble  word
precisamos usar alguma técnica específica. Cada processador tem a sua maneira de
resolver  esse problema, a  familia 80x86  armazena a  parte menos significativa
(Low Order, L.O)  da word em um endereço  qualquer e a  parte mais significativa
(High Order, H.O) no próximo endereço.
Veja o diagrama 7:

```
Diagrama 7:
________________________________________________________________________________
              _______________
          __ |_______________| - ...
         |   |_______i_______| - 785   --> Caracter 'i' (1 byte)
         |   |_______4_______| - 786   --> Caracter '4' (1 byte)
     (A) |   |_______k_______| - 787   --> Caracter 'k' (1 byte)
         |__ |_____0x00______| - 788   --> Caracter '\0' (1 byte)
             |      ...      | - ...
             |_______________| - 2322
          __ |_______________| - 2323      
     (B) |   |___0000 0000___| - 2324  --> word (2 bytes)
         |__ |___0110 1001___| - 2325
             |_______________| - 2326

    A) Representação  da string "i4k" na  memória. Cada caracter  possui tamanho
       de 1 byte, ocupando assim um unico endereço de memória cada. Note  o 0x00
       no endereço  788, isso significa  que os  caracteres acima "k", "4", "i"
       formam uma string ("i4k").
    
    B) Representação da word 0000000001101001 na memória. Como uma word possui
       dois bytes, ela é dividida em duas partes de 1 byte. Ficando a parte
       menos significativa (L.O, Low Order) num endereço e a  mais significativa (H.O, High Order) no endereço seguinte.
________________________________________________________________________________
```

Note que os endereços de memória aumentam de cima para baixo.
Como o nome sugere, Random Access Memory, podemos acessar a memoria RAM de forma
aleatória,  recuperando ou  ajustando o valor  de qualquer endereço sem precisar
percorrer os  endereços de memória, ou seja, como num array:

`     address_ram[2326] = 'I'     `

Mas logo  você pode  se perguntar: Mas  se eu posso acessar qualquer endereço de
memória, então eu poderia escrever  um programa que  pudesse alterar os dados na
memória  de outro programa?
A resposta é "Sim" e "Não" ;P

Primeiramente "Sim" se o kernel do seu sistema operacional deixar você manipular
diretamente a memória real (física). Mas nenhum dos sistemas operacionais atuais
e modernos liberam isso. Além de ser uma falha de segurança grave, pois todas as
informações de todos os programas estariam abertas a quem quisesse ver e alterar,
também seria grave por bugs em um programa poder corromper outros programas ou o
kernel do sistema.


O linux, como a maioria dos sistemas operacionais, possui um sistema de "Memória
Virtual". Uma abstração do kernel que libera um endereço de memória fictício aos
programas e se encarrega de fazer a conversão para o endereço real de memória de
uma maneira segura, impedindo acessos indevidos e colisão de endereços entre  os
programas. Vamos ver esse funcionamento mais de perto.

### Memória Virtual ###

Como  já falei, memória virtual é uma abstração  criada pelo kernel e  provê uma
interface segura para os processos.É claro que o código e os dados dos programas
residem na memória real, mas em endereços manipulados pelo kernel.

Cada  endereço de memória virtual é  "mapeado" pelo kernel ao seu correspondente
endereço de memória física. Isso é feito com uma estrutura chamada "Page Table".
Veja no diagrama 8:

```
Diagrama 8:
________________________________________________________________________________
    _________________            ______________            ________________
   |_Memória Virtual_|          |__Page Table__|          |__Memória Real__|
         _______                 _____________                    
 0x0000 |_______|               |______|______|               |  ...  |  ...           
 0x0001 |___i___|________       |______|______|      _________|___i___| 0xde05
 0x0002 |___4___|_______ \      |______|______|     /  _______|___4___| 0xde06                 
 0x0003 |___k___|_____  \ \_____|0x0001|0xde05|____/  /       |_______| 0xde07
 0x0004 |_0x00__|     \  \______|0x0002|0xde06|______/        |_______| 0xde08
 0x0005 |_______|      \________|0x0003|0xde0b|____           |_______| 0xde09
 0x0006 |_______|               |0x0004|0xde0c|__  \          |_______| 0xde0a
 0x0007 |_______|               |______|______|  \  \_________|___k___| 0xde0b
  ...   |  ...  |               |______|______|   \___________|__0x00_| 0xde0c
                                |______|______|               |  ...  |  ...
________________________________________________________________________________
```

Veja que a Page Table faz a relação entre os endereços virtuais e os reais e que
os dados sequenciais na memória virtual não são  necessariamente sequenciais  na
memória real. Esse foi um exemplo, veja que  a string "i4k" não  está armazenada
sequecialmente  na memória  física, mas geralmente  caracteres  de strings ficam
ficam agrupados na memória real. Isto depende de o próximo  trecho de memória  a
a ser escrita ter o tamanho da string livre ou não.

Quando  um processo requisita uma informação de um endereço da memória virtual o
sistema operacional  verifica a qual endereço de memória real aquele endereço se
refere, pega a informação e devolve ao processo.

Como já foi falado, a memória virtual impede que os programas acessem ou alterem
a memória real de outros programas. Isso porque quando um processo é iniciado, o
kernel provê a cada um, uma memória virtual nova. Assim, o programa A pode ter o
caracter 'K' no endereço de memória virtual  0x7fee55, por exemplo, e o progroma
B pode ter o caracter 'I' no mesmo endereço  virtual sem colisão, pois o  kernel
se  encarrega de relacionar  os endereços  virtuais de  cada programa em  locais
diferentes da memória real, evitando conflitos. Veja o diagrama 9:

```
Diagrama 9:
________________________________________________________________________________

     Programa A                                         Memória Real
      _________              ___________________        _____________
     |_________|            |      KERNEL       |      |_____________| 0x000000
0x05 |____K____|______      |                   |      |_____________| 0x000001
     |         |      \     |   Page Table A    |      |     ...     |   ...
     |         |       \    |   _____________   |      |_____________|
     |         |        \   |  |______|______|  |      |_____________| 0x5ff301
     |         |         \  |  |______|______|  |  ____|______K______| 0x5ff302
     |         |          \_|__| 0x05 |5ff302|__|_/    |     ...     |   ...
     |_________|            |                   |      |_____________|
                            |   Page Table B    |      |_____________|
                            |   _____________   |      |_____________|
     Programa B             |  |______|______|  |      |_____________| 0x65ade0
      __________        ____|__| 0x05 |65ade3|__|_     |_____________| 0x65ade1
     |__________|      /    |  |______|______|  | \    |_____________| 0x65ade2
0x05 |____I_____|_____/     |___________________|  \___|______I______| 0x65ade3
     |          |                                      |_____________|
     |          |                                      |_____________|
     |          |                                      |     ...     |   ...
     |          |                                      |_____________| 0xffffff
     |          |
     |__________|

________________________________________________________________________________
```

Veja  que  cada programa  possui  a  sua memória virtual  e que o kernel que  se
encarrega de todo o acesso direto à  memória real. O kernel do Linux possui  uma
tabela privada para cada processo em execução, dando a impressão ao programa  de
que ele é único no sistema operacional, ou seja, ele só enxerga os dados dele na
memória.

Quando um programa requisita  uma área de  memória que não esteja na Page Table,
o sistema envia um "segmentation  fault". Podemos ver  isso se tentarmos acessar
o valor de ponteiro não inicializado em C.

Referências:

  1. http://en.wikipedia.org/wiki/John_von_Neumann
  1. http://en.wikipedia.org/wiki/Von_Neumann_architecture
  1. http://pt.wikipedia.org/wiki/Arquitetura_de_von_Neumann
  1. http://www.google.com/#hl=en&q=von+neumann+architecture&fp=292ac4760832f3c4
  1. http://pt.wikipedia.org/wiki/Barramento
  1. http://en.wikipedia.org/wiki/Data_bus
  1. http://en.wikipedia.org/wiki/Address_bus
  1. http://en.wikipedia.org/wiki/Control_bus
  1. http://www.arl.wustl.edu/~lockwood/class/cs306/books/artofasm/Chapter_3/CH03-1.html

