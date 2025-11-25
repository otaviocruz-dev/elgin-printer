# 🖨️ Sistema de Impressora Elgin

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Windows">
  <img src="https://img.shields.io/badge/Elgin-FF6B6B?style=for-the-badge" alt="Elgin">
</p>

Sistema em C que integra com impressoras fiscais Elgin, permitindo operações completas dentro das funcionalidades de uma impressora Elgin.

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Pré-requisitos](#-pré-requisitos)
- [Instalação](#-instalação)
- [Documentação da API](#-documentação-da-api)


## 🎯 Sobre o Projeto

Este projeto foi desenvolvido como uma aplicação prática de programação usando C, integrando:

- Laços de repetição;
- Estruturas condicionais;
- Funções personalizadas;
- Integração com DLLs Windows;
- Automação de hardware.

O sistema simula um terminal, permitindo ao usuário executar todas as operações necessárias em uma impressora Elgin através de um menu interativo.

## ✨ Funcionalidades

### 🔧 Configuração
- [x] Configurar tipo de conexão (USB, RS232, TCP/IP, Bluetooth);
- [x] Selecionar modelo da impressora;
- [x] Iniciar e encerrar conexão.

### 🖨️ Impressão
- [x] Imprimir texto formatado (tamanho, estilo, alinhamento);
- [x] Gerar e imprimir QR Code;
- [x] Imprimir código de barras;
- [x] Imprimir cupom fiscal XML SAT;
- [x] Imprimir cupom de cancelamento SAT.

### 🎛️ Extras
- [x] Abrir gaveta de dinheiro (modo Elgin e genérico);
- [x] Emitir sinais sonoros (beeps);
- [x] Avançar papel;
- [x] Corte automático.

## 🔧 Pré-requisitos

- **DLL:** `E1_Impressora01.dll` (fornecida pela Elgin);
- **Impressora:** Modelos compatíveis Elgin (i7, i8, i9, ix, etc.).

## 📥 Instalação

### 1. Clone o repositório
```bash
git clone https://github.com/otaviocruz-dev/elgin-printer.git
cd elgin-printer
```

### 2. Obtenha a DLL da Elgin

Baixe a biblioteca `E1_Impressora01.dll` do [Elgin Developer Community](https://elgindevelopercommunity.github.io/) e coloque ela na mesma pasta do exe.

### 3. Compile o projeto

### 4. Prepare os arquivos XML (opcional)

Se for testar impressão SAT, coloque os arquivos na pasta raiz:
- `XMLSAT.xml`
- `CANC_SAT.xml`

### Fluxo básico de operação

1. **Configurar Conexão** (Opção 1)
   - Escolha o tipo de comunicação;
   - Selecione o modelo da impressora;
   - Informe os parâmetros de conexão.

2. **Abrir Conexão** (Opção 2)
   - Estabelece comunicação com a impressora.

3. **Realizar Operações** (Opções 3-10)
   - Execute as funcionalidades desejadas.

4. **Fechar Conexão** (Opção 0)
   - Encerra a conexão ao finalizar.

## 📚 Documentação da API

Este projeto utiliza a **API E1_Impressora** da Elgin. Documentação completa disponível em:

🔗 [Elgin Developer Community - API Impressora](https://elgindevelopercommunity.github.io/group___m1.html)

### Principais funções utilizadas

| Função | Descrição |
|--------|-----------|
| `AbreConexaoImpressora()` | Estabelece conexão com a impressora |
| `FechaConexaoImpressora()` | Encerra a conexão |
| `ImpressaoTexto()` | Imprime texto formatado |
| `ImpressaoQRCode()` | Gera e imprime QR Code |
| `ImpressaoCodigoBarras()` | Imprime código de barras |
| `ImprimeXMLSAT()` | Imprime cupom fiscal SAT |
| `ImprimeXMLCancelamentoSAT()` | Imprime cancelamento SAT |
| `AbreGaveta()` / `AbreGavetaElgin()` | Aciona gaveta |
| `SinalSonoro()` | Emite beeps |
| `AvancaPapel()` | Avança o papel |
| `Corte()` | Corta o papel com a gilhotina |

## 🎓 Conceitos Aplicados

- ✅ Carregamento dinâmico de bibliotecas (DLL);
- ✅ Manipulação de strings;
- ✅ Entrada/saída formatada;
- ✅ Estruturas condicionais (switch-case);
- ✅ Laços de repetição (while);
- ✅ Variáveis globais e estáticas.

## 🧙‍♂️ Autores

- Arthur Lima Santos;
- Fredson Vicente;
- Gustavo Dias de Sousa;
- Igor Medeiros Miguel;
- Lucas Libano Gomes da Silva;
- Otávio Henrique Moraes Cruz.

---

<p align="center">
  Obrigado por ter lido o README! 
  --Otávio :)
</p>
