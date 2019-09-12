#include <iostream>
#include <fstream>
#include <bitset>

#define qtd_bytes 6
#define tam_byte  8

using namespace std;

void exibe_byte(bitset<8> byte){ // Printa vetor de bit

    for(int i = tam_byte-1; i >= 0; i--)
        cout<<byte[i]<<"  ";
}

/*------------------------------ FUNÇÕES QUESTÃO 1 ----------------------------*/

int conta_ate_8bits(bitset<8> dado_8bits){ // Conta bits '1' do vetor

    int qtd_1 = 0; // Contador de '1's do 'dado_8bits'

    for(int i = 0; i < 8; i++)
        if(dado_8bits[i] == 1) // Se o dado_8bits na posição i for 1, faça:
            qtd_1++; // Incrementa o contador

    return qtd_1; // Retorna quantidade de '1' existentes em 'dado_8bits'
}

int conta_ate_6bits(bitset<6> dado_6bits){ // Conta bits '1' do vetor

    int qtd_1 = 0; // Contador de '1's do 'dado_8bits'

    for(int i = 0; i < 6; i++)
        if(dado_6bits[i] == 1) // Se o dado_8bits na posição i for 1, faça:
            qtd_1++; // Incrementa o contador

    return qtd_1; // Retorna quantidade de '1' existentes em 'dado_8bits'
}

bool verifica_paridade(int qtd_1){ // Verifica a paridade do vetor

    bool bit_paridade; // Variável que define o tipo de paridade

    if(qtd_1%2 == 0) // Se o resto da divisão qtd_1/2 for 0, faça:
        return bit_paridade = 0; // Retorna paridade par
    else // Se não, faça:
        return bit_paridade = 1; // Retorna paridade ímpar
}

void paridade_unidimensional(){

    cout<<"Questao 1-> Paridade Unidimensional"<<endl<<endl;

    bitset<8> dado_8bits_transmissor = 0b00000001; // Armazena o dado de 8 bits do trasnmissor
    bitset<8> dado_8bits_receptor    = 0b00000111; // Armazena o dado de 8 bits do receptor

    cout<<" Bits enviados pelo transmissor: ";
    exibe_byte(dado_8bits_transmissor);

    cout<<" Bits enviados pelo receptor:    ";
    exibe_byte(dado_8bits_receptor);

    bool bit_paridade_transmissor, // Armazena o bit de paridade da palavra enviada pelo transmissor
         aux_paridade_receptor; // Auxlia na verificação da pariadade interceptada pelo receptor

    int qtd_1_transmissor, // Armazena a quantidade de '1's (uns) buscada em dado_8bits_transmissor
        qtd_1_receptor; // Armazena a quantidade de '1's (uns) buscada em dado_8bits_receptor

    qtd_1_transmissor = conta_ate_8bits(dado_8bits_transmissor); // Conta os '1's do transmissor
    bit_paridade_transmissor = verifica_paridade(qtd_1_transmissor); // Retorna o tipo de paridade

    qtd_1_receptor = conta_ate_8bits(dado_8bits_receptor); // Conta os '1's do receptor
    aux_paridade_receptor = verifica_paridade(qtd_1_receptor); // Retorna o tipo de paridade

    cout<<endl;

    if(bit_paridade_transmissor == aux_paridade_receptor) // Se os bits de paridade são iguais:
        cout<< "A transmissao, provavelmente foi bem sucedida"<<endl;
    else
        cout<< "A transmissao foi mal sucedida"<<endl;
}

void paridade_bidimensional(){

    cout<<"Questao 1-> Paridade Bidimensional"<<endl<<endl;

    bitset<8> dado_8bits_transmissor[6] = {
        0b10010011,
        0b11101110,
        0b10100100,
        0b01000011,
        0b00000011,
        0b00111010
    };

    bitset<8> dado_8bits_receptor[6] = {
        0b10010011,
        0b11101110,
        0b10100100,
        0b01000011,
        0b00000011,
        0b00111010
    };

    int qtd_1_transmissor_linhas[6], // Armazena a quantidade de '1's (uns) buscada nas linhas dos dado_8bits_transmissor
        qtd_1_receptor_linhas[6], // Armazena a quantidade de '1's (uns) buscada nas linhas em dado_8bits_receptor
        qtd_1_transmissor_colunas[6],// Armazena a quantidade de '1's (uns) buscada nas colunas dos dado_8bits_transmissor
        qtd_1_receptor_colunas[6]; // Armazena a quantidade de '1's (uns) buscada nas colunas em dado_8bits_receptor

    bool bits_paridade_linhas_transmissor[6], //Armazena os bits de paridade das linhas das palavras enviada pelo transmissor
         aux_paridade_receptor_linhas[6], // Auxlia na verificação da pariadade das linhas interceptada pelo receptor
         bits_paridade_colunas_transmissor[8], //Armazena os bits de paridade das colunas das palavras enviada pelo transmissor
         aux_paridade_receptor_colunas[8]; // Auxlia na verificação da pariadade das colunas interceptada pelo receptor

    int index_erro_linha, // Armazena posicao da linha onde aconteceu um erro
        index_erro_coluna;// Armazena posicao da coluna onde aconteceu um erro

    // paridades das linhas do transmissor
    for(int i = 0; i < 6; i++){ // 6 linhas
        qtd_1_transmissor_linhas[i] = conta_ate_8bits(dado_8bits_transmissor[i]);
        bits_paridade_linhas_transmissor[i] = verifica_paridade(qtd_1_transmissor_linhas[i]);
    }

    bitset<6> aux_dado_6bits_coluna[8];

    // paridades das colunas do transmissor
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++)
                aux_dado_6bits_coluna[i][j] = dado_8bits_transmissor[j][i];

        qtd_1_transmissor_colunas[i] = conta_ate_6bits(aux_dado_6bits_coluna[i]);
        bits_paridade_colunas_transmissor[i] = verifica_paridade(qtd_1_transmissor_colunas[i]);
    }
    //-----------------------------------------------------------------------///

    // paridades das linhas do receptor
    for(int i = 0; i < 6; i++){ // 6 linhas
        qtd_1_receptor_linhas[i] = conta_ate_8bits(dado_8bits_receptor[i]);
        aux_paridade_receptor_linhas[i] = verifica_paridade(qtd_1_receptor_linhas[i]);
    }

    // paridades das colunas do receptor
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++)
                aux_dado_6bits_coluna[i][j] = dado_8bits_receptor[j][i];

        qtd_1_receptor_colunas[i] = conta_ate_6bits(aux_dado_6bits_coluna[i]);
        aux_paridade_receptor_colunas[i] = verifica_paridade(qtd_1_receptor_colunas[i]);
    }

    bool correcao = 0;
    for(int i = 0; i < 6; i++){ //6 linhas
        if(bits_paridade_linhas_transmissor[i] != aux_paridade_receptor_linhas[i])
            for(int j = 0; j < 8; j++) // 8 colunas
                if(bits_paridade_colunas_transmissor[j] != aux_paridade_receptor_colunas[j]){
                    cout<<endl<<"Houve um erro na tramsmissao, e ele foi corrigido. ( Linha: "<<i<<" e Coluna: "<<j<<") "<<endl;
                    index_erro_linha = i;
                    index_erro_coluna = j;
                    //dado_8bits_receptor[i][j] = ~dado_8bits_receptor[i][j];
                    correcao = 1;
                    break;
                }
    }


    /* ----------- EXIBIÇÃO DOS VALORES -------------*/

    // Dados  & bits de paridade (das linhas de dados) do Transmissor
    cout<<"Dados do Transmitor :"<<endl<<endl;
    for(int i = 0; i < 6; i++){
        exibe_byte(dado_8bits_transmissor[i]);

        cout<<"| "<<bits_paridade_linhas_transmissor[i]<<endl;
    }
    cout<<"------------------------- "<<endl;

    // Bits de paridade de (das Colunas de dados) do Transmissor
    for(int i = 8-1; i >= 0; i--)
        cout<<bits_paridade_colunas_transmissor[i]<<"  ";

    cout<<endl;
    if(correcao){ // Se foi realizado uma correcao
        cout<<endl<<"Dados do Receptor depois de corrigido:"<<endl<<endl;
    }

    cout<<endl;

    // Dados  & bits de paridade (das linhas de dados) do Receptor
    for(int i = 0; i < 6; i++){
        exibe_byte(dado_8bits_receptor[i]);

        cout<<"| "<<aux_paridade_receptor_linhas[i]<<endl;
    }
    cout<<"------------------------- "<<endl;
    // Bits de paridade de (das Colunas de dados) do Receptor
    for(int i = 8-1; i >= 0; i--)
        cout<<aux_paridade_receptor_colunas[i]<<"  ";
    cout<<endl;
}

/*-----------------------------------------------------------------------------*/


/*------------------------------ FUNÇÕES QUESTÃO 2 ----------------------------*/

bitset<8> fSoma(bitset<8> vet[]) {  //	Função que realiza a soma das palavras

    bitset<8> soma;

    int carry = 0;
    int aux;
    soma = vet[0];

    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            aux = soma[j];
            soma[j] = ((soma[j] ^ vet[i][j]) ^ carry); // À cada iteração realiza um XOR entre a posição do vetor soma e a mesma posição do vetor palavra e depois com o carry
			carry = ((aux & vet[i][j]) | (aux & carry)) | (vet[i][j] & carry); // Verifica se há carry bit para a próxima operação
        }
    }

    if (carry == 1) { //  Caso no final da operação de soma tenha sobrado um carry é necessário somá-lo
        bitset<8> vcarry = 0b00000001;
        carry = 0;
        for (int j = 0; j < 8; j++) {
            aux = soma[j];
            soma[j] = ((soma[j] ^ vcarry[j]) ^ carry); 
            carry = ((aux & vcarry[j]) | (aux & carry)) | (vcarry[j] & carry);
        }
    }

    return soma;
}

void inverteBit(bitset<8> vet[], int posVet, int posBit){ // Função que simula a inversão de um bit durante a transmissão
    vet[posVet][posBit] = ~vet[posVet][posBit];
}

bool fChecksum(bitset<8> complUm, bitset<8> somaReceptor){ // Função que verifica se houve erro na transmissão 
    return (complUm == ~somaReceptor) ?  true : false; // Se o complemento de 1 do transmissor for igual ao do receptor retorna true
}

void questao_2(){ // Main da questão 2

    bitset<8> vet[8] = { // Declaração das palavras a serem enviadas
        0b10010011,
        0b11101110,
        0b10100100,
        0b01000011,
        0b00000011,
        0b00111010,
        0b01010101,
        0b01111001
    };

    bitset<8> somaEmissor;
    bitset<8> somaReceptor;

    somaEmissor = fSoma(vet); // Realiza a soma no emissor
    bitset<8> complUm = ~somaEmissor; // Realiza complemento de 1 na soma do emissor

    inverteBit(vet,4,5); // Força a inversão de um bit na quinta palavra do vetor de palavras no sexto bit 

	somaReceptor = fSoma(vet); // Realiza a soma no receptor

    bool verificador = fChecksum(complUm, somaReceptor); // Verifica se houve erro 

    (verificador) ? cout << "SUCESSO" : cout << "FALHOU";

    cout << endl;
    cout << somaEmissor << endl;
    cout << complUm << endl;
    cout << somaReceptor << endl;

}

/*-----------------------------------------------------------------------------*/


/*------------------------------ FUNÇÕES QUESTÃO 3 ----------------------------*/

bitset<11> fCrc(bitset<11> palavra, bitset<4> divisor){ // Função que realiza o cálculo do CRC para uma palavra de 8 bits e um divisor de grau 3 de 4 bits
    std::bitset<11> CRC = palavra;
    std::bitset<11> dividendo = palavra;
    int cont = 0;
        for (int i = 10; i >= 3; i--) { // Começa a divisão do bit mais significativo
            if (dividendo[i] != 0) { // Caso o bit mais significativo seja 0 não é necessário realizar a divisão e o divisor move para o próximo bit
                for (int j = 3; j >= 0; j--) {
                    dividendo[i - cont] = (dividendo[i - cont] ^ divisor[j]); // À cada iteração é realizado um XOR entre o bit do dividendo e o do divisor
                    cont++;
                }
            }
         cont = 0;
    }

    for (int i = 0; i < 3; i++) { // Após a divisão, o resto é adicionado ao final da palavra que será enviada
        CRC[i] = dividendo[i];
    }

    return CRC;
}

void questao_3(){ // Main da questão 3

    bitset<11> palavra = 0b10010011000;
    bitset<4> divisor = 0b1011;

    bitset<11> CRC = fCrc(palavra, divisor); // Chamada da função CRC

    cout << CRC << endl; // Imprime o CRC (palavra concatenada com o resto da divisão)

    cout << fCrc(CRC, divisor) << std::endl; // Imprime o resultado do CRC no receptor. Caso o resto seja 0 nenhum erro foi detectado
}

/*-----------------------------------------------------------------------------*/

int main(){
	//paridade_unidimensional();
    paridade_bidimensional();
	//questao_2();
	//questao_3();
    cout<<endl;
    return 0;
}
