#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ======================= Config DLL ======================= */
static HMODULE g_hDll = NULL;

/* Convenção de chamada (Windows): __stdcall */
#ifndef CALLCONV
#  define CALLCONV WINAPI
#endif

/* ======================= Assinaturas da DLL ======================= */
typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
typedef int (CALLCONV *Corte_t)(int);
typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (CALLCONV *AvancaPapel_t)(int);
typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (CALLCONV *InicializaImpressora_t)(void);

/* ======================= Ponteiros ======================= */
static AbreConexaoImpressora_t        AbreConexaoImpressora        = NULL;
static FechaConexaoImpressora_t       FechaConexaoImpressora       = NULL;
static ImpressaoTexto_t               ImpressaoTexto               = NULL;
static Corte_t                        Corte                        = NULL;
static ImpressaoQRCode_t              ImpressaoQRCode              = NULL;
static ImpressaoCodigoBarras_t        ImpressaoCodigoBarras        = NULL;
static AvancaPapel_t                  AvancaPapel                  = NULL;
static AbreGavetaElgin_t              AbreGavetaElgin              = NULL;
static AbreGaveta_t                   AbreGaveta                   = NULL;
static SinalSonoro_t                  SinalSonoro                  = NULL;
static ImprimeXMLSAT_t                ImprimeXMLSAT                = NULL;
static ImprimeXMLCancelamentoSAT_t    ImprimeXMLCancelamentoSAT    = NULL;
static InicializaImpressora_t         InicializaImpressora         = NULL;

/* ======================= Configuração ======================= */
static int   g_tipo      = 1;
static char  g_modelo[64] = "i9";
static char  g_conexao[128] = "USB";
static int   g_parametro = 0;
static int   g_conectada = 0;

/* ======================= Utilidades ======================= */
#define LOAD_FN(h, name)                                                         \
    do {                                                                         \
        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
        if (!(name)) {                                                           \
            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
                    #name, GetLastError());                                      \
            return 0;                                                            \
        }                                                                        \
    } while (0)

static void flush_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ======================= Funções para manipular a DLL ======================= */
static int carregarFuncoes(void)
{
    g_hDll = LoadLibraryA("E1_Impressora01.dll");
    if (!g_hDll) {
        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
        return 0;
    }

    LOAD_FN(g_hDll, AbreConexaoImpressora);
    LOAD_FN(g_hDll, FechaConexaoImpressora);
    LOAD_FN(g_hDll, ImpressaoTexto);
    LOAD_FN(g_hDll, Corte);
    LOAD_FN(g_hDll, ImpressaoQRCode);
    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
    LOAD_FN(g_hDll, AvancaPapel);
    LOAD_FN(g_hDll, AbreGavetaElgin);
    LOAD_FN(g_hDll, AbreGaveta);
    LOAD_FN(g_hDll, SinalSonoro);
    LOAD_FN(g_hDll, ImprimeXMLSAT);
    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
    LOAD_FN(g_hDll, InicializaImpressora);

    return 1;
}

static void liberarBiblioteca(void)
{
    if (g_hDll) {
        FreeLibrary(g_hDll);
        g_hDll = NULL;
    }
}

/* ======================= Funções a serem implementadas pelos alunos ======================= */

static void exibirMenu(void)
{   
    printf("\n");
    printf("-------------------------------------------\n");
    printf("        SISTEMA DE IMPRESSORA ELGIN        \n");
    printf("-------------------------------------------\n");
    printf("CONFIGURACAO:\n");
    printf("  [1] Configurar Conexao\n");
    printf("  [2] Abrir Conexao\n");
    printf("\n");
    printf("IMPRESSAO:\n");
    printf("  [3] Imprimir Texto\n");
    printf("  [4] Imprimir QR Code\n");
    printf("  [5] Imprimir Codigo de Barras\n");
    printf("  [6] Imprimir XML SAT\n");
    printf("  [7] Imprimir XML Cancelamento SAT\n");
    printf("\n");
    printf("EXTRAS:\n");
    printf("  [8] Abrir Gaveta Elgin\n");
    printf("  [9] Abrir Gaveta\n");
    printf(" [10] Emitir Sinal Sonoro\n");
    printf("\n");
    printf("  [0] Fechar Conexao\n");
    printf("-------------------------------------------\n");
}

static void configurarConexao(void)
{
    int tipo;
    char modelo[64];
    char conexao[128];
    int parametro = 0;
    
    printf("\n=== CONFIGURAR CONEXAO ===\n");
    printf("\n");
    
    //1.Tipo de comunicacao

	printf("\n");
    printf("Digite o tipo de comunicacao\n");
	printf("\n");
    
    printf("1 - USB\n");
    printf("2 - RS232\n");
    printf("3 - TCP/IP\n");
    printf("4 - Bluetooth\n");
    printf("5 - Impressoras acopladas (Android)\n");
	printf("\n");

    scanf("%d", &tipo);
    flush_entrada();
    
    
    //2.Modelo da impressora
    
	printf("\n");
    printf("Digite o modelo da impressora\n");
    printf("\n");
    printf("i7\n");
    printf("i7 Plus\n");
    printf("i8\n");
    printf("i9\n");
    printf("ix\n");
    printf("Fitpos\n");
    printf("BK-T681\n");
    printf("MP-4200 (Para modelos TH e ADV)\n");
    printf("MP-4200 HS\n");
    printf("MK\n");
    printf("MP-2800\n");
    printf("\n");

    scanf(" %s", &modelo);
    flush_entrada();
    
    //3.Solicitar tipo de Conexão

	printf("\n");
    printf("Digite o tipo de parametro\n");
	printf("\n");
    printf("USB\n");
    printf("RS232\n");
    printf("TCP/IP\n");
    printf("Bluetooth\n");
	printf("\n");

    scanf(" %s", &conexao);
    flush_entrada();
    
    //4.Parametro especifico
    
    if (tipo == 3){ //TCP\IP
    	printf("Digite a porta TCP: ");
    	scanf("%d", &parametro);
    	flush_entrada();
    	
	} else if (tipo == 2){
		printf("Digite a taxa de baudrate: ");
		scanf("%d", &parametro);
		flush_entrada();
	}
	
	//Parametro USB e Bluetooth o parametro e O
	
	
	//5. SALVAR NAS VARIÁVEIS GLOBAIS
	g_tipo = tipo;
	strcpy(g_modelo,modelo);
	strcpy(g_conexao, conexao);
	g_parametro = parametro;
	
	// 6. CONFIRMAÇÃO
	printf("\nCONFIGURACAO SALVA: \n");
	printf("Tipo: %d, Modelo: %s, Conexao: %s, Parametro: %d\n", g_tipo, g_modelo, g_conexao, g_parametro);
}

static int abrirConexao(int tipo, char modelo[], char conexao[], int parametro)
{
    int resultado;
	
	printf("\nABRINDO CONEXAO\n");
	printf("Tipo: %d, Modelo: %s, Conexao: %s, Parametro: %d\n", tipo, modelo, conexao, parametro);
	printf("\n");
	
	resultado = AbreConexaoImpressora(tipo, modelo, conexao, parametro);
	
	if (resultado == 0){
		printf("Conexao aberta com sucesso\n");
		g_conectada = 0;
	} else {
		printf("Erro ao abrir conexao\n");
		g_conectada = 1;
	}
	
	return resultado;
}

static void fecharConexao(void)
{
    int retorno = FechaConexaoImpressora();

    if (retorno == 0) {
        printf("Conexão com a impressora encerrada com sucesso.\n");
    } else {
        printf("Erro ao fechar conexão com a impressora. Código de erro: %d\n", retorno);
        // Consultar GER_Erro_Conexao para interpretar o código
    }
}

static void imprimirTexto(void)
{
	char texto[200];
	int posicao;            
    int estilo;            
    int tamanho;
	
	printf("Digite o texto que deseja imprimir:\n");
	fgets(texto, 200, stdin);
	texto[strcspn(texto, "\n")] = '\0';
	flush_entrada();
	
	// Alinhamento
	printf("\n");
	printf("-------------------------------------------\n");	       
	printf("Escolha a posicao do texto:\n");
	printf("[0] Esquerda\n");
	printf("[1] Centro\n");
	printf("[2] Direita\n");
	printf("-------------------------------------------\n");
	printf("\n");
	
	scanf("%d", &posicao);
	
	// Formatacao (negrito, sublinhado, etc)
	printf("\n");
	printf("-------------------------------------------\n");	       
	printf("Escolha um estilo:\n");
	printf("[0] Fonte A\n");
	printf("[1] Fonte B\n");
	printf("[2] Sublinhado\n");
	printf("[4] Modo reverso\n");
	printf("[8] Negrito\n");
	printf("-------------------------------------------\n");
	printf("\n");
	
	scanf("%d", &estilo);	
	flush_entrada();
		
	// Multiplicadores de tamanho (altura e largura)
	printf("\n");
	printf("-------------------------------------------\n");	       
	printf("Escolha um estilo:\n");
	printf("[0] 1 x na altura e largura\n");
	printf("[1] 2 x na altura\n");
	printf("[2] 3 x na altura\n");
	printf("[3] 4 x na altura\n");
	printf("[4] 5 x na altura\n");
	printf("[5] 6 x na altura\n");
	printf("[6] 7 x na altura\n");
	printf("[7] 8 x na altura\n");
	printf("\n");
	printf("[16] 2 x na largura\n");
	printf("[32] 3 x na largura\n");
	printf("[48] 4 x na largura\n");
	printf("[64] 5 x na largura\n");
	printf("[80] 6 x na largura\n");
	printf("[96] 7 x na largura\n");
	printf("[112] 8 x na largura\n");
	printf("-------------------------------------------\n");
	printf("\n");
	
	scanf("%d", &tamanho);	
	flush_entrada();	
		
	int ret = ImpressaoTexto(texto, posicao, estilo, tamanho);
	
	if (ret == 0) {
		printf("Impressao feita com sucesso.\n");
	} else {
		printf("Erro na impressao.\n");
	}
	
    AvancaPapel(5);
    Corte(1);
}

static void imprimirQRCode(void)
{
	char texto[200]; 

    printf("Digite o conteudo do QR Code: \n");
	fgets(texto, 200, stdin);
	flush_entrada();

    // tamanho: 6, nivelCorrecao: 4 (alto)
    int ret = ImpressaoQRCode(texto, 6, 4);


    if (ret == 0) {
        printf("QR Code impresso\n");
    } else {
        printf("Erro ao imprimir QR Code\n");
    };

    AvancaPapel(5);
    Corte(1);
}

static void imprimirCodigoBarras(void)
{
	// tipo: 8 (EAN-13), codigo, altura: 100, largura: 2, HRI: 3
    int ret = ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3);
    
    if (ret == 0) {
    	printf("Codigo de barras impresso\n");
	} else {
		printf("Erro ao imprimir codigo de barras\n");
	}
    
    AvancaPapel(5);
	Corte(1);
}

static void imprimirXMLSAT(void)
{
	const char *caminho = "path=./XMLSAT.xml";
    int g_parametro = 0;

    if (!ImprimeXMLSAT) {
        printf("Função ImprimeXMLSAT nao carregada.\n");
        return;
    }

    int r = ImprimeXMLSAT(caminho, g_parametro);
    
    if (r != 0) {
        printf("Erro ao imprimir XMLSAT. Codigo: %d\n", r);
	} else {
		printf("Impressao XMLSAT enviada com sucesso.\n");
	}    
        
    AvancaPapel(5);
    Corte(1);
}

static void imprimirXMLCancelamentoSAT(void)
{  
    const char *xmlPath = "path=./CANC_SAT.xml";

    // Assinatura do QRCode
    const char *assinaturaQRCode =
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";

    // Parâmetro de layout
	//(exemplo: logo + novo layout)
    int param = 65; // 1 (logo) + 64 (novo layout)

    int ret = ImprimeXMLCancelamentoSAT(xmlPath, assinaturaQRCode, param);

    if (ret == 0) {
        printf("Cancelamento SAT impresso com sucesso!\n");
    } else {
        printf("Erro ao imprimir cancelamento SAT: %d\n", ret);
    }

    AvancaPapel(5);   
    Corte(1);  
}

static void abrirGavetaElginOpc(void)
{
	// Pino 1, pulso curto (5), tempo de espera 10
    int ret = AbreGavetaElgin(1, 50, 50);
    
    if (ret == 0) {
        printf("Gaveta Elgin aberta com sucesso!\n");
    } else {
        printf("Erro ao abrir a gaveta Elgin.\n");
    }
}

static void abrirGavetaOpc(void)
{
	// Pino 1, pulso curto (5), tempo de espera 10
    int ret = AbreGaveta(1, 5, 10);
    
    if (ret == 0) {
        printf("Gaveta aberta com sucesso!\n");
    } else {
        printf("Erro ao abrir a gaveta.\n");
    }
}

static void emitirSinalSonoro(void)
{
	// 4 beeps, 50ms de duracao, intervalo de 5ms
    int ret = SinalSonoro(4, 50, 5);
    
    if (ret == 0) {
       printf("Sinal sonoro emitido!\n");       
    }  else {
       printf("Erro ao emitir o sinal sonoro.\n");     
    }
}

/* ======================= Função principal ======================= */
int main(void)
{
    if (!carregarFuncoes()) {
        return 1;
    }

    int opcao = 0;
    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        flush_entrada();
        
        switch (opcao) {
        	   case 0:
        	   		fecharConexao();
        			break;
        			
               case 1:
                    configurarConexao();
                    break;
                    
               case 2:
                    abrirConexao(g_tipo, g_modelo, g_conexao, g_parametro);
                    break;
               
               case 3:
                    imprimirTexto();
                    break;
                    
               case 4:
                    imprimirQRCode();
                    break;
                    
               case 5:
                    imprimirCodigoBarras();
                    break;
                    
               case 6:
                    imprimirXMLSAT();
                    break;
                    
               case 7:
                    imprimirXMLCancelamentoSAT();
                    break;
                    
               case 8:
                    abrirGavetaElginOpc();
                    break;
                    
               case 9:
                    abrirGavetaOpc();
                    break;
                    
               case 10:
                    emitirSinalSonoro();
                    break;
                    
               default:
                    printf("Opcao invalida, insira uma correta.");
                    break;
        }          
        
    }
    
    return 0;
}
